<?php
/**
 * @file
 * Hooks provided by this module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Acts on bit being loaded from the database.
 *
 * This hook is invoked during $bit loading, which is handled by
 * entity_load(), via the EntityCRUDController.
 *
 * @param array $entities
 *   An array of $bit entities being loaded, keyed by id.
 *
 * @see hook_entity_load()
 */
function hook_bit_load(array $entities) {
  $result = db_query('SELECT pid, foo FROM {mytable} WHERE pid IN(:ids)', array(':ids' => array_keys($entities)));
  foreach ($result as $record) {
    $entities[$record->pid]->foo = $record->foo;
  }
}

/**
 * Responds when a $bit is inserted.
 *
 * This hook is invoked after the $bit is inserted into the database.
 *
 * @param Bit $bit
 *   The $bit that is being inserted.
 *
 * @see hook_entity_insert()
 */
function hook_bit_insert(Bit $bit) {
  db_insert('mytable')
    ->fields(array(
      'id' => entity_id('bit', $bit),
      'extra' => print_r($bit, TRUE),
    ))
    ->execute();
}

/**
 * Acts on a $bit being inserted or updated.
 *
 * This hook is invoked before the $bit is saved to the database.
 *
 * @param Bit $bit
 *   The $bit that is being inserted or updated.
 *
 * @see hook_entity_presave()
 */
function hook_bit_presave(Bit $bit) {
  $bit->name = 'foo';
}

/**
 * Responds to a $bit being updated.
 *
 * This hook is invoked after the $bit has been updated in the database.
 *
 * @param Bit $bit
 *   The $bit that is being updated.
 *
 * @see hook_entity_update()
 */
function hook_bit_update(Bit $bit) {
  db_update('mytable')
    ->fields(array('extra' => print_r($bit, TRUE)))
    ->condition('id', entity_id('bit', $bit))
    ->execute();
}

/**
 * Responds to $bit deletion.
 *
 * This hook is invoked after the $bit has been removed from the database.
 *
 * @param Bit $bit
 *   The $bit that is being deleted.
 *
 * @see hook_entity_delete()
 */
function hook_bit_delete(Bit $bit) {
  db_delete('mytable')
    ->condition('pid', entity_id('bit', $bit))
    ->execute();
}

/**
 * Act on a bit that is being assembled before rendering.
 *
 * @param $bit
 *   The bit entity.
 * @param $view_mode
 *   The view mode the bit is rendered in.
 * @param $langcode
 *   The language code used for rendering.
 *
 * The module may add elements to $bit->content prior to rendering. The
 * structure of $bit->content is a renderable array as expected by
 * drupal_render().
 *
 * @see hook_entity_prepare_view()
 * @see hook_entity_view()
 */
function hook_bit_view($bit, $view_mode, $langcode) {
  $bit->content['my_additional_field'] = array(
    '#markup' => $additional_field,
    '#weight' => 10,
    '#theme' => 'mymodule_my_additional_field',
  );
}

/**
 * Alter the results of entity_view() for bits.
 *
 * @param $build
 *   A renderable array representing the bit content.
 *
 * This hook is called after the content has been assembled in a structured
 * array and may be used for doing processing which requires that the complete
 * bit content structure has been built.
 *
 * If the module wishes to act on the rendered HTML of the bit rather than
 * the structured content array, it may use this hook to add a #post_render
 * callback. Alternatively, it could also implement hook_preprocess_bit().
 * See drupal_render() and theme() documentation respectively for details.
 *
 * @see hook_entity_view_alter()
 */
function hook_bit_view_alter($build) {
  if ($build['#view_mode'] == 'full' && isset($build['an_additional_field'])) {
    // Change its weight.
    $build['an_additional_field']['#weight'] = -10;

    // Add a #post_render callback to act on the rendered HTML of the entity.
    $build['#post_render'][] = 'my_module_post_render';
  }
}

/**
 * Acts on bit_type being loaded from the database.
 *
 * This hook is invoked during bit_type loading, which is handled by
 * entity_load(), via the EntityCRUDController.
 *
 * @param array $entities
 *   An array of bit_type entities being loaded, keyed by id.
 *
 * @see hook_entity_load()
 */
function hook_bit_type_load(array $entities) {
  $result = db_query('SELECT pid, foo FROM {mytable} WHERE pid IN(:ids)', array(':ids' => array_keys($entities)));
  foreach ($result as $record) {
    $entities[$record->pid]->foo = $record->foo;
  }
}

/**
 * Responds when a bit_type is inserted.
 *
 * This hook is invoked after the bit_type is inserted into the database.
 *
 * @param BitType $bit_type
 *   The bit_type that is being inserted.
 *
 * @see hook_entity_insert()
 */
function hook_bit_type_insert(BitType $bit_type) {
  db_insert('mytable')
    ->fields(array(
      'id' => entity_id('bit_type', $bit_type),
      'extra' => print_r($bit_type, TRUE),
    ))
    ->execute();
}

/**
 * Acts on a bit_type being inserted or updated.
 *
 * This hook is invoked before the bit_type is saved to the database.
 *
 * @param BitType $bit_type
 *   The bit_type that is being inserted or updated.
 *
 * @see hook_entity_presave()
 */
function hook_bit_type_presave(BitType $bit_type) {
  $bit_type->name = 'foo';
}

/**
 * Responds to a bit_type being updated.
 *
 * This hook is invoked after the bit_type has been updated in the database.
 *
 * @param BitType $bit_type
 *   The bit_type that is being updated.
 *
 * @see hook_entity_update()
 */
function hook_bit_type_update(BitType $bit_type) {
  db_update('mytable')
    ->fields(array('extra' => print_r($bit_type, TRUE)))
    ->condition('id', entity_id('bit_type', $bit_type))
    ->execute();
}

/**
 * Responds to bit_type deletion.
 *
 * This hook is invoked after the bit_type has been removed from the database.
 *
 * @param BitType $bit_type
 *   The bit_type that is being deleted.
 *
 * @see hook_entity_delete()
 */
function hook_bit_type_delete(BitType $bit_type) {
  db_delete('mytable')
    ->condition('pid', entity_id('bit_type', $bit_type))
    ->execute();
}

/**
 * Define default bit_type configurations.
 *
 * @return
 *   An array of default bit_type, keyed by machine names.
 *
 * @see hook_default_bit_type_alter()
 */
function hook_default_bit_type() {
  $defaults['main'] = entity_create('bit_type', array(
    // …
  ));
  return $defaults;
}

/**
 * Alter default bit_type configurations.
 *
 * @param array $defaults
 *   An array of default bit_type, keyed by machine names.
 *
 * @see hook_default_bit_type()
 */
function hook_default_bit_type_alter(array &$defaults) {
  $defaults['main']->name = 'custom name';
}
