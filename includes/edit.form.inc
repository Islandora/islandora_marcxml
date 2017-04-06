<?php

/**
 * @file
 * Form functions for editing a MODS datastream by re-transforming MARCXML.
 */

/**
 * Form to allow editing of an existing MODS datastream.
 *
 * @param array $form
 *   The Drupal form.
 * @param array $form_state
 *   The Drupal form state.
 * @param AbstractObject $object
 *   A object within Fedora.
 *
 * @return array
 *   A Drupal form definition.
 */
function islandora_marcxml_edit_file_form(array $form, array &$form_state, AbstractObject $object) {
  $form = array();
  $form['file'] = array(
    '#type' => 'managed_file',
    '#title' => t('MARCXML File'),
    '#description' => t('A file containing a MARCXML record, to be transformed to MODS.'),
    '#upload_validators' => array(
      'file_validate_extensions' => array('xml'),
    ),
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
  );
  return $form;
}

/**
 * Populate the MODS datastream with the transformed MARCXML.
 *
 * @param array $form
 *   The Drupal form.
 * @param array $form_state
 *   The Drupal form state.
 */
function islandora_marcxml_edit_file_form_submit(array &$form, array &$form_state) {
  module_load_include('inc', 'islandora_marcxml', 'includes/utilities');
  $file = file_load($form_state['values']['file']);
  $object = islandora_object_load($form_state['build_info']['args'][0]->id);
  islandora_marcxml_populate_mods($object, $file);
  file_delete($file);
  drupal_set_message(t('The MODS datastream has been updated from the uploaded MARCXML.'));
  $form_state['redirect'] = "islandora/object/{$object->id}";
}
