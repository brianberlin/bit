<?php

/**
 * Bit view callback.
 */
function bit_view($bit) {
  drupal_set_title(entity_label('bit', $bit));
  return entity_view('bit', array(entity_id('bit', $bit) => $bit), 'full');
}
