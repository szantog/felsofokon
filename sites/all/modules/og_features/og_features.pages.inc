<?php

/**
 * Group feature selection form
 */
function og_features_feature_form(&$form_state, $group) {
  $form = array();
  // Fetch the og features registry
  $registry = og_features_get_registry();
  
  // Iterate all the available features to provide a toggle switch
  foreach ($registry as $key => $feature) {
    $form["feature-$key"]["name-$key"] = array(
      '#type' => 'item',
      '#value' => $feature->name,
    );
    $form["feature-$key"]["description-$key"] = array(
      '#type' => 'item',
      '#value' => $feature->description,
    );
    $form["feature-$key"]["toggle-$key"] = array(
      '#type' => 'checkbox',
      '#default_value' => isset($group->features_disabled[$key]) ? 0 : 1,
    );
  }
  
  // Store the group
  $form['group'] = array(
    '#type' => 'value',
    '#value' => $group,
  );
  
  // Submit button
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  
  return $form;
}

/**
 * Submit the group features form
 */
function og_features_feature_form_submit(&$form, &$form_state) {
  // Extract the group
  $group = $form_state['values']['group'];
  
  // Collect the disabled features
  $disabled = array();
  foreach ($form_state['values'] as $key => $value) {
    if (substr($key, 0, 7) == 'toggle-' && !$value) {
      $feature = substr($key, 7);
      $disabled[$feature] = $feature;
    }
  }
  
  // Remove any old settings for this group
  db_query("DELETE FROM {og_features} WHERE nid = %d", $group->nid);
  
  // Save the new settings, if there are any features disabled
  if (!empty($disabled)) {
    $record = new stdClass;
    $record->nid = $group->nid;
    $record->disabled = $disabled;
    if (!drupal_write_record('og_features', $record)) {
      drupal_set_message(t('An error occurred while trying to save your settings.'), 'error');
      watchdog('og_features', t('An error occurred while trying to save feature settings for group !nid', array('!nid' => $group->nid)), array(), WATCHDOG_ERROR);
      return;
    }
  }
  
  // Alert other modules about the change
  module_invoke_all('og_features_toggle', $group, $disabled);
  
  // Set a message
  drupal_set_message(t('Your settings have been saved succesfully'));
}
