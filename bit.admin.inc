<?php

/**
 * Generates the bit type editing form.
 */
function bit_type_form($form, &$form_state, $bit_type, $op = 'edit') {

  if ($op == 'clone') {
    $bit_type->label .= ' (cloned)';
    $bit_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $bit_type->label,
    '#description' => t('The human-readable name of this bit type.'),
    '#required' => TRUE,
    '#size' => 30,
  );

  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($bit_type->type) ? $bit_type->type : '',
    '#maxlength' => 32,
    '#disabled' => $bit_type->isLocked() && $op != 'clone',
    '#machine_name' => array(
      'exists' => 'bit_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this bit type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#default_value' => isset($bit_type->description) ? $bit_type->description : '',
    '#description' => t('Description about the bit type.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save bit type'),
    '#weight' => 40,
  );

  if (!$bit_type->isLocked() && $op != 'add' && $op != 'clone') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete bit type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('bit_type_form_submit_delete')
    );
  }
  return $form;
}

/**
 * Submit handler for creating/editing bit_type.
 */
function bit_type_form_submit(&$form, &$form_state) {
  $bit_type = entity_ui_form_submit_build_entity($form, $form_state);
  // Save and go back.
  bit_type_save($bit_type);

  // Redirect user back to list of bit types.
  $form_state['redirect'] = 'admin/structure/bit-types';
}

function bit_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/bit-types/' . $form_state['bit_type']->type . '/delete';
}

/**
 * Bit type delete form.
 */
function bit_type_form_delete_confirm($form, &$form_state, $bit_type) {
  $form_state['bit_type'] = $bit_type;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['bit_type_id'] = array('#type' => 'value', '#value' => entity_id('bit_type' ,$bit_type));
  return confirm_form($form,
    t('Are you sure you want to delete bit type %title?', array('%title' => entity_label('bit_type', $bit_type))),
    'bit/' . entity_id('bit_type' ,$bit_type),
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Bit type delete form submit handler.
 */
function bit_type_form_delete_confirm_submit($form, &$form_state) {
  $bit_type = $form_state['bit_type'];
  bit_type_delete($bit_type);

  watchdog('bit_type', '@type: deleted %title.', array('@type' => $bit_type->type, '%title' => $bit_type->label));
  drupal_set_message(t('@type %title has been deleted.', array('@type' => $bit_type->type, '%title' => $bit_type->label)));

  $form_state['redirect'] = 'admin/structure/bit-types';
}

/**
 * Page to select bit Type to add new bit.
 */
function bit_admin_add_page() {
  $items = array();
  foreach (bit_types() as $bit_type_key => $bit_type) {
    $items[] = l(entity_label('bit_type', $bit_type), 'bit/add/' . $bit_type_key);
  }
  return array('list' => array('#theme' => 'item_list', '#items' => $items, '#title' => t('Select type of bit to create.')));
}

/**
 * Add new bit page callback.
 */
function bit_add($type) {
  $bit_type = bit_types($type);

  $bit = entity_create('bit', array('type' => $type));
  drupal_set_title(t('Create @name', array('@name' => entity_label('bit_type', $bit_type))));

  $output = drupal_get_form('bit_form', $bit);

  return $output;
}

/**
 * Bit Form.
 */
function bit_form($form, &$form_state, $bit) {
  $form_state['bit'] = $bit;

  $form['title'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Name'),
    '#default_value' => $bit->title,
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => $bit->description,
  );

  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $bit->uid,
  );

  field_attach_form('bit', $bit, $form, $form_state);

  $submit = array();
  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions'] = array(
    '#weight' => 100,
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save bit'),
    '#submit' => $submit + array('bit_form_submit'),
  );

  // Show Delete button if we edit bit.
  $bit_id = entity_id('bit' ,$bit);
  if (!empty($bit_id) && bit_access('edit', $bit)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('bit_form_submit_delete'),
    );
  }

  $form['#validate'][] = 'bit_form_validate';

  return $form;
}

function bit_form_validate($form, &$form_state) {

}

/**
 * Bit submit handler.
 */
function bit_form_submit($form, &$form_state) {
  $bit = $form_state['bit'];

  entity_form_submit_build_entity('bit', $bit, $form, $form_state);

  bit_save($bit);

  $bit_uri = entity_uri('bit', $bit);

  $form_state['redirect'] = $bit_uri['path'];

  drupal_set_message(t('Bit %title saved.', array('%title' => entity_label('bit', $bit))));
}

function bit_form_submit_delete($form, &$form_state) {
  $bit = $form_state['bit'];
  $bit_uri = entity_uri('bit', $bit);
  $form_state['redirect'] = $bit_uri['path'] . '/delete';
}

/**
 * Delete confirmation form.
 */
function bit_delete_form($form, &$form_state, $bit) {
  $form_state['bit'] = $bit;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['bit_type_id'] = array('#type' => 'value', '#value' => entity_id('bit' ,$bit));
  $bit_uri = entity_uri('bit', $bit);
  return confirm_form($form,
    t('Are you sure you want to delete bit %title?', array('%title' => entity_label('bit', $bit))),
    $bit_uri['path'],
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Delete form submit handler.
 */
function bit_delete_form_submit($form, &$form_state) {
  $bit = $form_state['bit'];
  bit_delete($bit);

  drupal_set_message(t('Bit %title deleted.', array('%title' => entity_label('bit', $bit))));

  $form_state['redirect'] = '<front>';
}
