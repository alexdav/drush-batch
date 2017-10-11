<?php

/**
 * @file
 * Define the $entities array to be passed to the batch operation.
 *
 * The format should be the key is the entity ID and the value is an array of
 * arguments passed to the batch callback.
 */

namespace Drupal\_drush_script;

function get_entities() {
  return array(
    1 => array(
      'entity_type' => 'node',
      'entity_id' => 1,
      'vars' => array(),
    ),
  );
}
