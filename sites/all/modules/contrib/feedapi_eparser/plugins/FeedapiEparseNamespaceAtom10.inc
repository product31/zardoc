<?php
// $Id: FeedapiEparseNamespaceAtom10.inc,v 1.2 2009/08/17 21:59:38 neclimdul Exp $
/**
 * @file
 * Parse Atom data from its namespace.
 */

class FeedapiEparseNamespaceAtom10 extends FeedapiEparserNamespacePlugin {

  function parseGlobal($global_context) {
    $content = $this->findContent($global_context);

    $atom = &$this->feed->parsed_source->atom;

    // Find what we can find without our simple converter.
    $atom = $this->convertStrings(array(
      // Optional
      'icon',
      'logo',
      'rights',
      'subtitle',
      // Required
      'title',
      'id',
      'updated',
      ), $content);


    // Find links if they exist.
    if (isset($content->link)) {
      $links = count($content->link) ? $content->link : array($content->link);
      foreach ($links as $link) {
        //
        $attributes = $link->attributes();
        $atom->link[] = $this->convertStrings(array(
          'href',
          'rel',
          'type',
          'hreflang',
          'title',
          'length',
        ), $attributes);
      }
    }

    // Find any authors.
    if (isset($content->author)) {
      $authors = count($content->author) ? $content->author : array($content->author);
      foreach ($authors as $author) {
        $atom->author[] = $this->convertStrings(array(
          'name',
          'uri',
          'email',
        ), $author);
      }
    }

    $this->convert_attributes_string(array(
      'generator' => array(
        'uri',
        'version',
      ),
    ), $content, $atom);
    if (isset($atom->generator)) {
      $atom->generator->name = (string) $content->generator;
    }

      // Multiple items
      // author, category, contributor, link
      // 'author' => array(
      //   'name',
      //   'email',
      // ),
  }

  /**
   * Parse feed item data.
   */
  function parseItem(&$xml_item, &$item) {
    $data = $this->convertStrings(array(
      'title',
      'summary',
      'content',
      'link',
      'id',
      'published',
      'updated',
    ), $xml_item);

    if (!empty($xml_item->content)) {
      $body = '';
      foreach ($xml_item->content->children() as $child)  {
        $body .= $child->asXML();
      }
      $body .= "{$xml_item->content}";
    }
    else if (!empty($xml_item->summary)) {
      $body = '';
      foreach ($xml_item->summary->children() as $child)  {
        $body .= $child->asXML();
      }
      $body .= "{$xml_item->summary}";
    }
    $data->description = $body;

    // Find links if they exist.
    if (isset($xml_item->link)) {
      $links = count($xml_item->link) ? $xml_item->link : array($xml_item->link);
      foreach ($links as $link) {
        $attributes = $link->attributes();
        $data->link[] = $this->convertStrings(array(
          'href',
          'rel',
          'type',
          'hreflang',
          'title',
          'length',
        ), $attributes);
      }
    }
    // Required values.
    $data->timestamp = isset($data->published) ? $this->parseDate($data->published) : time();
    $item->atom = $data;
  }

  function convert_attributes_string($map, &$content, &$base = NULL) {

    if (!isset($base)) {
      $base = new stdClass();
    }

    foreach ($map as $key => $attribute_names) {
      if (isset($content->$key)) {
        $base->$key = $this->convertStrings($attribute_names, $content->$key->attributes());
      }
    }

    return $base;
  }

  /**
   * Figure out where the Atom data is stored.
   *
   * @param $context
   * @return
   * SimpleXML Object pointing to our rss content.
   */
  function findContent($context) {
    // In a very rare few cases, this could be actually stored using an XML namespace.
    $content = $context->children('http://www.w3.org/2005/Atom');
    // Its a very very very rare case so we fall back to the basic context where
    // these items will generally show up if the namespace isn't there.
    if (empty($content)) {
      $content = $context;
    }
    return $content;
  }
}
