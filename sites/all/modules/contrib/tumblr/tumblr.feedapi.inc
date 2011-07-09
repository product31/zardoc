<?php
// $Id: tumblr.feedapi.inc,v 1.1 2009/04/23 15:02:57 rz Exp $

/**
 * @file
 * FeedAPI helper functions
 */

/**
 * Parser function for feed api
 */
function _tumblr_feedapi_parse($tumblr) {
  // Basic info.
  $parsed_source = new stdClass();
  $parsed_source->title = $tumblr->blog->title;
  $parsed_source->description = $tumblr->blog->description;
  $parsed_source->options = new stdClass();

  // Tumblr doesn't give us a base url, so we build it ourselves.
  $parsed_source->options->link = ($tumblr->blog->cname) ? "http://{$tumblr->blog->cname}" : "http://{$tumblr->blog->name}.tumblr.com";

  // Start building the items array.
  $parsed_source->items = array();
  foreach ($tumblr->posts as $post) {
    $item = new stdClass();
    $item->options = new stdClass();

    // Do the type-specific parsing
    $item->type = $post->type;
    $function = '_tumblr_feedapi_parse_post_'. $item->type;
    if (function_exists($function)) {
      $content = $function($post);
      if ($content['title']) {
        $item->title = html_entity_decode($content['title'], ENT_COMPAT, 'UTF-8');
      }
      if ($content['body']) {
        $item->description = $content['body'];
      }
      // Expose the type-specific fields to feed_mapper by adding to the options object
      if (is_array($content['fields']) && count($content['fields'])) {
        foreach ($content['fields'] as $key => $value) {
          $item->options->$key = $value;
        }
      }
    }

    $item->options->tags = $post->tags;

    $item->options->original_author = $tumblr->blog->name;
    $item->options->timestamp = $post->timestamp;
    $item->options->original_url = $post->url;
    $item->options->guid = $post->id;
    $parsed_source->items[] = $item;
  }
  return $parsed_source;
}

/**
 * Implementation of _tumblr_feedapi_parse_post_TYPE().
 */
function _tumblr_feedapi_parse_post_regular($post) {
  $content = array();
  $content['title'] = $post->title;
  $content['body'] = $post->body;
  return $content;
}

/**
 * Implementation of _tumblr_feedapi_parse_post_TYPE().
 */
function _tumblr_feedapi_parse_post_conversation($post) {
  $content = array();
  $content['title'] = $post->title;
  $body = '';
  $i = 0;
  foreach ($post->conversation->lines as $line) {
    if ($line->name) {
      $key = array_search($line->name, $post->conversation->names);
      $text = "<span class=\"user-$key\">{$line->label}</span> {$line->text}";
    }
    else {
      $text = "<em>{$line->text}</em>";
    }

    $zebra = (($i++ % 2) == 0) ? 'odd' : 'even';
    $body .= "<li class=\"$zebra\">$text</li>\n";
  }
  $content['body'] = "<ul class=\"tumblr-conversation\">\n$body</ul>\n";

  return $content;
}

/**
 * Implementation of _tumblr_feedapi_parse_post_TYPE().
 *
 * Tumblr Link fields:
 * - link-text:        Text for the link (optional)
 * - link-url:         URL field (required)
 * - link-description: HTML description field (optional)
 */
function _tumblr_feedapi_parse_post_link($post) {
  $content = array();

  $content['title'] = $post->link->text ? $post->link->text : $post->link->url;

  $content['body'] = l($content['title'], $post->link->url, array('attributes' => array('class' => 'tumblr-link')));
  if ($post->link->description) {
    $content['body'] .= "\n<div class=\"tumblr-link-description\">{$post->link->description}</div>";
  }

  return $content;
}

/**
 * Implementation of _tumblr_feedapi_parse_post_TYPE().
 *
 * Tumblr Quote fields:
 * - quote-text:    Plain-text quote field (required)
 * - quote-source:  HTML quote source field (optional)
 */
function _tumblr_feedapi_parse_post_quote($post) {
  $content = array();
  $content['body'] = "<blockquote class=\"tumblr-quote\">\n<p>{$post->quote->text}</p>\n";
  $content['body'] .= "<p class=\"tumblr-quote-source\">&ndash; {$post->quote->source}</p>\n</blockquote>";
  return $content;
}

/**
 * Implementation of _tumblr_feedapi_parse_post_TYPE().
 *
 * Tumblr Photo fields:
 * - photo-caption:    HTML caption field (optional)
 * - photo-link-url:   Click-through URL field (optional)
 * - photo-url:        URL for the photo.  There are multiple photo-url fields,
 *                     each with a max-width attribute.
 */
function _tumblr_feedapi_parse_post_photo($post) {
  $content = array();

  $content['title'] = $post->photo->caption ? truncate_utf8(strip_tags($post->photo->caption), 255, TRUE, TRUE) : '';

  $img = '<img src="'. $post->photo->url['500'] .'" class="tumblr-photo" />';
  if ($post->photo->link) {
    $img = l($img, $post->photo->link, array('html' => TRUE));
  }
  $content['body'] = $img;
  if ($post->photo->caption) {
    $content['body'] .= "\n<div class=\"tumblr-photo-caption\">{$post->photo->caption}</div>";
  }

  $content['fields'] = array(
    'photo_caption' => $post->photo->caption,
    'photo_link_url' => $post->photo->link,
    'photo_url' => $post->photo->url['500'],
  );

  return $content;
}

/**
 * Implementation of _tumblr_feedapi_parse_post_TYPE().
 *
 * Tumblr Audio fields:
 * - audio-caption:    HTML caption field (optional)
 * - audio-player:     HTML embed code
 */
function _tumblr_feedapi_parse_post_audio($post) {
  $content = array();

  $content['title'] = $post->audio->caption ? truncate_utf8(strip_tags($post->audio->caption), 255, TRUE, TRUE) : '';

  $content['body'] = "<div class=\"tumblr-audio\">{$post->audio->player}</div>";
  if ($post->audio->caption) {
    $content['body'] .= "\n<div class=\"tumblr-audio-caption\">{$post->audio->caption}</div>";
  }

  return $content;
}

/**
 * Implementation of _tumblr_feedapi_parse_post_TYPE().
 *
 * Tumblr Video fields:
 * - video-caption:    HTML caption field (optional)
 * - video-player:     HTML embed code
 */
function _tumblr_feedapi_parse_post_video($post) {
  $content = array();

  $content['title'] = $post->video->caption ? truncate_utf8(strip_tags($post->video->caption), 255, TRUE, TRUE) : '';

  $content['body'] = "<div class=\"tumblr-video\">{$post->video->player}</div>";
  if ($post->video->caption) {
    $content['body'] .= "\n<div class=\"tumblr-video-caption\">{$post->video->caption}</div>";
  }

  $content['fields'] = array(
    'video_caption' => $post->video->caption,
    'video_player' => $post->video->player,
    'video_source' => $post->video->source,
  );

  return $content;
}
