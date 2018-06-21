<?php

/**
 * @file
 * Define the query to use for fetching the entities.
 *
 * Either pass a string or array for use with db_query() or return a
 * \SelectQuery object.
 *
 * The array for db_query() should be in the form of:
 * array (
 *   $query = '',
 *   $args = array(),
 *   $options = array(),
 * )
 */

namespace Drupal\_drush_script;

/**
 * Get the query.
 *
 * @return string|array|\SelectQuery
 *   The query.
 */
function get_query() {
  $query = db_select('node', 'n');
  $query->addField('n', 'nid', 'entity_id');

  return $query;
}
