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
  require_once "query.inc";
  $query = \Drupal\_drush_script\get_query();

  if (is_string($query)) {
    $results = db_query($query);
  }
  elseif (is_array($query)) {
    list($query, $args, $options) = $query;
    $results = db_query($query, $args, $options);
  }
  elseif ($query instanceof \SelectQuery) {
    $results = $query->execute();
  }

  $records = array();
  foreach ($results as $result) {
    $id = $result->entity_id;
    $entity_type = $result->entity_type ?? 'node';

    $records[$id] = array(
      'entity_type' => $entity_type,
      'entity_id' => $id,
      'vars' => array(),
    );
  }
}
