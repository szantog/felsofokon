<?php

/**
 * Implementation of hook_input_formats().
 */
function input_format_editor_input_formats() {
  $input_formats = array();

  $input_format = new stdClass;
  $input_format->api_version = 1;
  $input_format->name = 'editor';
  $input_format->roles = array(
    2 => 'authenticated user',
  );
  $input_format->cache = TRUE;
  $input_format->settings = array(
  );
  $input_format->filters = array(
    'filter' => array(
      // Delta => Weight for: URL filter
      '2' => '0',
      // Delta => Weight for: Line break converter
      '1' => '2',
      // Delta => Weight for: HTML corrector
      '3' => '10',
    ),
    'wysiwyg_filter' => array(
      // Delta => Weight for: WYSIWYG Filter
      '0' => '10',
    ),
  );
  $input_format->machine = 'editor';
  $input_formats['editor'] = $input_format;

  return $input_formats;

}
