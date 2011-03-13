<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function fr_og_blog_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_node_info().
 */
function fr_og_blog_node_info() {
  $items = array(
    'blog' => array(
      'name' => t('Blog'),
      'module' => 'features',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Blog elnevezése'),
      'has_body' => '1',
      'body_label' => t('Blog leírása'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
