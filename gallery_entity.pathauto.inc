<?php

/**
 * @file
 * Pathauto integration for MOH Premises
 */

/**
 * Implements hook_path_alias_types().
 *
 * Used primarily by the bulk delete form.
 */
function gallery_entity_path_alias_types() {
  return array('gallery/' => t('Fashion Show'));
}

/**
 * Implements hook_pathauto().
 */
function gallery_entity_pathauto($op) {
  switch ($op) {
    case 'settings':
      $settings = array();
      $settings['module'] = 'gallery_entity';
      $settings['token_type'] = 'gallery_entity';
      $settings['groupheader'] = t('Gallery Entity paths');
      $settings['patterndescr'] = t('Default path pattern');
      $settings['patterndefault'] = 'gallery/[gallery_entity:name]';
      $settings['batch_update_callback'] = 'gallery_entity_pathauto_bulk_update_batch_process';
      $settings['batch_file'] = drupal_get_path('module', 'gallery_entity') . '/gallery_entity.pathauto.inc';

      $languages = array();
      if (module_exists('locale')) {
        $languages = array(LANGUAGE_NONE => t('language neutral')) + locale_language_list('name');
      }
      return (object) $settings;
    default:
      break;
  }
}

/**
 * Batch processing callback; Generate aliases for nodes.
 */
function gallery_entity_pathauto_bulk_update_batch_process(&$context) {
  if (!isset($context['sandbox']['current'])) {
    $context['sandbox']['count'] = 0;
    $context['sandbox']['current'] = 0;
  }

  $query = db_select('gallery_entity', 'ge');
  $query->leftJoin('url_alias', 'ua', "CONCAT('gallery_entity/', ge.gid) = ua.source");
  $query->addField('ge', 'gid');
  $query->isNull('ua.source');
  $query->condition('ge.gid', $context['sandbox']['current'], '>');
  $query->orderBy('ge.gid');
  $query->addTag('pathauto_bulk_update');
  $query->addMetaData('entity', 'gallery_entity');

  // Get the total amount of items to process.
  if (!isset($context['sandbox']['total'])) {
    $context['sandbox']['total'] = $query->countQuery()->execute()->fetchField();

    // If there are no nodes to update, the stop immediately.
    if (!$context['sandbox']['total']) {
      $context['finished'] = 1;
      return;
    }
  }

  $query->range(0, 25);
  $pids = $query->execute()->fetchCol();

  gallery_entity_update_alias_multiple($pids, 'bulkupdate');
  $context['sandbox']['count'] += count($pids);
  $context['sandbox']['current'] = max($pids);
  $context['message'] = t('Updated alias for premise @pid.', array('@pid' => end($pids)));

  if ($context['sandbox']['count'] != $context['sandbox']['total']) {
    $context['finished'] = $context['sandbox']['count'] / $context['sandbox']['total'];
  }
}

/**
 * Update the URL aliases for an individual my_entity.
 *
 * @param $my_entity
 *   A gallery_entity object.
 * @param $op
 *   Operation being performed on the gallery_entity ('insert', 'update' or 'bulkupdate').
 * @param $options
 *   An optional array of additional options.
 */
function gallery_entity_update_alias($gallery_entity, $op, array $options = array()) {
  // Skip processing if the user has disabled pathauto for the gallery_entity.
  if (isset($gallery_entity->path['pathauto']) && empty($gallery_entity->path['pathauto'])) {
    return;
  }

  $options += array(
    'language' => isset($gallery_entity->language) ? $gallery_entity->language : LANGUAGE_NONE,
  );

  // Skip processing if the gallery_entity has no pattern.
  if (!pathauto_pattern_load_by_entity('gallery_entity', $gallery_entity->type, $options['language'])) {
    return;
  }

  module_load_include('inc', 'pathauto');
  $uri = entity_uri('gallery_entity', $gallery_entity);
  pathauto_create_alias('gallery_entity', $op, $uri['path'], array('gallery_entity' => $gallery_entity), $gallery_entity->type, $options['language']);
}

/**
 * Update the URL aliases for multiple premises.
 *
 * @param $pids
 *   An array of premise IDs.
 * @param $op
 *   Operation being performed on the nodes ('insert', 'update' or
 *   'bulkupdate').
 * @param $options
 *   An optional array of additional options.
 */
function gallery_entity_update_alias_multiple(array $pids, $op, array $options = array()) {
  $options += array('message' => FALSE);

  $galleries = gallery_entity_load_multiple($pids);
  foreach ($galleries as $gallery_entity) {
    gallery_entity_update_alias($gallery_entity, $op, $options);
  }

  if (!empty($options['message'])) {
    drupal_set_message(format_plural(count($pids), 'Updated URL alias for 1 gallery.', 'Updated URL aliases for @count galleries.'));
  }
}
