<?php

/**
 * Implementation of hook_views_data().
 */
function m2api_views_data() {
  $data = array(
    'm2api_nodes' => array(
      'table' => array(
        'group' => 'M2',
        'join' => array(
          'node' => array(
            'left_field' => 'nid',
            'field' => 'nid',
          ),
        ),
      ),
      'm2id' => array(
        'title' => t('Document ID'),
        'help' => t('ID which identifies the M2 Document. Could be an album or track'),
        'field' => array(
          'handler' => 'views_handler_field_numeric',
          'click sortable' => TRUE,
        ),
        // Information for accepting a nid as an argument
        'argument' => array(
          'handler' => 'views_handler_argument_numeric',
          'numeric' => TRUE,
        ),
        // Information for accepting a nid as a filter
        'filter' => array(
          'handler' => 'views_handler_filter_numeric',
        ),
        // Information for sorting on a nid.
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),
    ),
//    'm2api_nodes_products' => array(
//      'table' => array(
//        'group' => 'M2',
//        'join' => array(
//          'node' => array(
//            'left_field' => 'nid',
//            'field' => 'nid',
//          ),
//        ),
//      ),
//      'm2id' => array(
//        'title' => t('Product Document ID'),
//        'help' => t('ID which identifies the M2 Document. Most likely instances of an album.'),
//        'field' => array(
//          'handler' => 'm2api_handler_field_products',
//          'click sortable' => TRUE,
//        ),
//        // Information for accepting a nid as an argument
//        'argument' => array(
//          'handler' => 'views_handler_argument_numeric',
//          'numeric' => TRUE,
//        ),
//        // Information for accepting a nid as a filter
//        'filter' => array(
//          'handler' => 'views_handler_filter_numeric',
//        ),
//        // Information for sorting on a nid.
//        'sort' => array(
//          'handler' => 'views_handler_sort',
//        ),
//      ),
//    ),
  );
  return $data;
}
