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
 * Acts on gallery_entity being loaded from the database.
 *
 * This hook is invoked during $gallery_entity loading, which is handled by
 * entity_load(), via the EntityCRUDController.
 *
 * @param array $entities
 *   An array of $gallery_entity entities being loaded, keyed by id.
 *
 * @see hook_entity_load()
 */
function hook_gallery_entity_load(array $entities) {
  $result = db_query('SELECT pid, foo FROM {mytable} WHERE pid IN(:ids)', array(':ids' => array_keys($entities)));
  foreach ($result as $record) {
    $entities[$record->pid]->foo = $record->foo;
  }
}

/**
 * Responds when a $gallery_entity is inserted.
 *
 * This hook is invoked after the $gallery_entity is inserted into the database.
 *
 * @param GalleryEntity $gallery_entity
 *   The $gallery_entity that is being inserted.
 *
 * @see hook_entity_insert()
 */
function hook_gallery_entity_insert(GalleryEntity $gallery_entity) {
  db_insert('mytable')
    ->fields(array(
      'id' => entity_id('gallery_entity', $gallery_entity),
      'extra' => print_r($gallery_entity, TRUE),
    ))
    ->execute();
}

/**
 * Acts on a $gallery_entity being inserted or updated.
 *
 * This hook is invoked before the $gallery_entity is saved to the database.
 *
 * @param GalleryEntity $gallery_entity
 *   The $gallery_entity that is being inserted or updated.
 *
 * @see hook_entity_presave()
 */
function hook_gallery_entity_presave(GalleryEntity $gallery_entity) {
  $gallery_entity->name = 'foo';
}

/**
 * Responds to a $gallery_entity being updated.
 *
 * This hook is invoked after the $gallery_entity has been updated in the database.
 *
 * @param GalleryEntity $gallery_entity
 *   The $gallery_entity that is being updated.
 *
 * @see hook_entity_update()
 */
function hook_gallery_entity_update(GalleryEntity $gallery_entity) {
  db_update('mytable')
    ->fields(array('extra' => print_r($gallery_entity, TRUE)))
    ->condition('id', entity_id('gallery_entity', $gallery_entity))
    ->execute();
}

/**
 * Responds to $gallery_entity deletion.
 *
 * This hook is invoked after the $gallery_entity has been removed from the database.
 *
 * @param GalleryEntity $gallery_entity
 *   The $gallery_entity that is being deleted.
 *
 * @see hook_entity_delete()
 */
function hook_gallery_entity_delete(GalleryEntity $gallery_entity) {
  db_delete('mytable')
    ->condition('pid', entity_id('gallery_entity', $gallery_entity))
    ->execute();
}

/**
 * Act on a gallery_entity that is being assembled before rendering.
 *
 * @param $gallery_entity
 *   The gallery_entity entity.
 * @param $view_mode
 *   The view mode the gallery_entity is rendered in.
 * @param $langcode
 *   The language code used for rendering.
 *
 * The module may add elements to $gallery_entity->content prior to rendering. The
 * structure of $gallery_entity->content is a renderable array as expected by
 * drupal_render().
 *
 * @see hook_entity_prepare_view()
 * @see hook_entity_view()
 */
function hook_gallery_entity_view($gallery_entity, $view_mode, $langcode) {
  $gallery_entity->content['my_additional_field'] = array(
    '#markup' => $additional_field,
    '#weight' => 10,
    '#theme' => 'mymodule_my_additional_field',
  );
}

/**
 * Alter the results of entity_view() for gallery_entitys.
 *
 * @param $build
 *   A renderable array representing the gallery_entity content.
 *
 * This hook is called after the content has been assembled in a structured
 * array and may be used for doing processing which requires that the complete
 * gallery_entity content structure has been built.
 *
 * If the module wishes to act on the rendered HTML of the gallery_entity rather than
 * the structured content array, it may use this hook to add a #post_render
 * callback. Alternatively, it could also implement hook_preprocess_gallery_entity().
 * See drupal_render() and theme() documentation respectively for details.
 *
 * @see hook_entity_view_alter()
 */
function hook_gallery_entity_view_alter($build) {
  if ($build['#view_mode'] == 'full' && isset($build['an_additional_field'])) {
    // Change its weight.
    $build['an_additional_field']['#weight'] = -10;

    // Add a #post_render callback to act on the rendered HTML of the entity.
    $build['#post_render'][] = 'my_module_post_render';
  }
}

/**
 * Acts on gallery_entity_type being loaded from the database.
 *
 * This hook is invoked during gallery_entity_type loading, which is handled by
 * entity_load(), via the EntityCRUDController.
 *
 * @param array $entities
 *   An array of gallery_entity_type entities being loaded, keyed by id.
 *
 * @see hook_entity_load()
 */
function hook_gallery_entity_type_load(array $entities) {
  $result = db_query('SELECT pid, foo FROM {mytable} WHERE pid IN(:ids)', array(':ids' => array_keys($entities)));
  foreach ($result as $record) {
    $entities[$record->pid]->foo = $record->foo;
  }
}

/**
 * Responds when a gallery_entity_type is inserted.
 *
 * This hook is invoked after the gallery_entity_type is inserted into the database.
 *
 * @param GalleryEntityType $gallery_entity_type
 *   The gallery_entity_type that is being inserted.
 *
 * @see hook_entity_insert()
 */
function hook_gallery_entity_type_insert(GalleryEntityType $gallery_entity_type) {
  db_insert('mytable')
    ->fields(array(
      'id' => entity_id('gallery_entity_type', $gallery_entity_type),
      'extra' => print_r($gallery_entity_type, TRUE),
    ))
    ->execute();
}

/**
 * Acts on a gallery_entity_type being inserted or updated.
 *
 * This hook is invoked before the gallery_entity_type is saved to the database.
 *
 * @param GalleryEntityType $gallery_entity_type
 *   The gallery_entity_type that is being inserted or updated.
 *
 * @see hook_entity_presave()
 */
function hook_gallery_entity_type_presave(GalleryEntityType $gallery_entity_type) {
  $gallery_entity_type->name = 'foo';
}

/**
 * Responds to a gallery_entity_type being updated.
 *
 * This hook is invoked after the gallery_entity_type has been updated in the database.
 *
 * @param GalleryEntityType $gallery_entity_type
 *   The gallery_entity_type that is being updated.
 *
 * @see hook_entity_update()
 */
function hook_gallery_entity_type_update(GalleryEntityType $gallery_entity_type) {
  db_update('mytable')
    ->fields(array('extra' => print_r($gallery_entity_type, TRUE)))
    ->condition('id', entity_id('gallery_entity_type', $gallery_entity_type))
    ->execute();
}

/**
 * Responds to gallery_entity_type deletion.
 *
 * This hook is invoked after the gallery_entity_type has been removed from the database.
 *
 * @param GalleryEntityType $gallery_entity_type
 *   The gallery_entity_type that is being deleted.
 *
 * @see hook_entity_delete()
 */
function hook_gallery_entity_type_delete(GalleryEntityType $gallery_entity_type) {
  db_delete('mytable')
    ->condition('pid', entity_id('gallery_entity_type', $gallery_entity_type))
    ->execute();
}

/**
 * Define default gallery_entity_type configurations.
 *
 * @return
 *   An array of default gallery_entity_type, keyed by machine names.
 *
 * @see hook_default_gallery_entity_type_alter()
 */
function hook_default_gallery_entity_type() {
  $defaults['main'] = entity_create('gallery_entity_type', array(
    // …
  ));
  return $defaults;
}

/**
 * Alter default gallery_entity_type configurations.
 *
 * @param array $defaults
 *   An array of default gallery_entity_type, keyed by machine names.
 *
 * @see hook_default_gallery_entity_type()
 */
function hook_default_gallery_entity_type_alter(array &$defaults) {
  $defaults['main']->name = 'custom name';
}
