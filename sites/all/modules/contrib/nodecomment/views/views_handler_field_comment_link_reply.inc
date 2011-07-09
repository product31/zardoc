<?php

/**
 * Field handler to present a link to delete a node.
 */
class views_handler_field_comment_link_reply extends views_handler_field_comment_link {
  function construct() {
    parent::construct();
    $this->additional_fields['type'] = array('table' => 'node', 'field' => 'type');
  }

  function render($values) {
    //check for permission to reply to comments
    if (!user_access('post comments')) {
      return;
    }
    $text = !empty($this->options['text']) ? $this->options['text'] : t('reply');
    $comment_type = nodecomment_get_comment_type($values->{$this->aliases['type']});
    return l($text, 'node/add/'. $comment_type .'/' . $values->{$this->aliases['nid']} . '/' . $values->{$this->aliases['cid']});
  }
}
