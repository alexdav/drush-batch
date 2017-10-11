<?php

/**
 * @file
 * Drush batch script.
 */

require 'vendor/autoload.php';
use Symfony\Component\Filesystem\Filesystem;

// Define our high water variable for use with this script.
$high_water_var = '_drush_script_high_water_' . md5(__FILE__);
$high_water = variable_get($high_water_var, 0);

// Get whether the user wants this to be a dry run.
$dry_run = drush_get_option('dry-run');

// Define our batch. We need the batch include file to be relative to Drupal
// because that's how Drupal core has it defined.
$batch = array(
  'file' => (new Filesystem())->makePathRelative(__DIR__, DRUPAL_ROOT) . 'batch.inc',
  'script_settings' => array(
    'high_water_var' => $high_water_var,
    'dry_run' => $dry_run,
  ),
);

// Get the entities we're updating.
require "entities.inc";
$entities = \Drupal\_drush_script\get_entities();

// Sort the entities so we can have a high water mark.
asort($entities);

// Filter out those below the high water.
$entities = array_filter($entities, function ($key) use ($high_water) {
  return $key > $high_water;
}, ARRAY_FILTER_USE_KEY);

foreach ($entities as $vars) {
  $batch['operations'][] = array(
    'Drupal\_drush_script\batch_callback',
    $vars,
  );
}

// Check that we have some operations. If we don't have any, there's no batch to
// process.
if (!empty($batch['operations'])) {
  batch_set($batch);
  drush_backend_batch_process();
}

// Delete the high water variable since we're done.
variable_del($high_water_var);

drush_log('Completed processing.', 'success');
