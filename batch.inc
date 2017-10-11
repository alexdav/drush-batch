<?php

/**
 * @file
 * Batch callback script.
 */

namespace Drupal\_drush_script;

// Limit the memory of the batch process. Drush will automatically fork the
// process once it reaches at least 50% of this limit.
ini_set('memory_limit', '256M');

/**
 * Batch callback.
 */
function batch_callback($entity_type, $id, array $vars = array()) {
  $current_set = &_batch_current_set();
  $high_water_var = $current_set['script_settings']['high_water_var'];
  $dry_run = !empty($current_set['script_settings']['dry_run']);

  $wrapper = entity_metadata_wrapper($entity_type, $id);
  if (!$wrapper->getBundle()) {
    drush_log(dt('Could not load entity @type with ID @id', array(
      '@type' => $entity_type,
      '@id' => $id,
    )), 'error');
    return;
  }

  try {
    do_work($wrapper);

    if (!$dry_run) {
      $wrapper->save();
      variable_set($high_water_var, $id);

      // Load it back into the entity cache.
      entity_load_single($entity_type, $id);
    }

    $seconds = microtime(TRUE) - $current_set['start'];
    $total = $current_set['total'];
    $number_processed = $total - $current_set['count'] + 1;
    $approximate_total_time = $seconds / ($number_processed / $total);
    $remaining = $approximate_total_time - $seconds;
    drush_log(dt('Updated id @id. Remaining time: @remaining. Memory usage: @memory.', array(
      '@id' => $id,
      '@remaining' => format_interval($remaining, 3),
      '@memory' => drush_format_size(memory_get_usage()),
    )), 'completed');
  }
  catch (\Exception $e) {
    drush_log(t('Error on id @id: @message', array(
      '@id' => $id,
      '@message' => $e->getMessage(),
    )), 'error');
  }
}
