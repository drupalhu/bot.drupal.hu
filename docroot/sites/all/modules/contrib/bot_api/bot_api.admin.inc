<?php
/**
 * @file
 * Bot API admin interface.
 */

function bot_api_settings() {
  $branches = array(
    5 => t('Drupal 5'),
    6 => t('Drupal 6'),
    7 => t('Drupal 7'),
  );

  $form = array();
  $form['bot_api_status'] = array(
    '#type' => 'fieldset',
    '#title' => t('Status'),
  );
  $items = array();
  foreach ($branches as $branch => $title) {
    $items[$branch] = t('Branch @title: @count', array('@title' => $title, '@count' => db_select('bot_api', 'ba')
      ->fields('ba', array('count'))
      ->condition('branch', $branch)
      ->countQuery()->execute()->fetchField()));
  }
  $form['bot_api_status']['branches'] = array(
    '#markup' => theme('item_list', array('items' => $items)),
  );
  $last = variable_get('bot_api_last_run', array(5 => 0, 6 => 0, 7 => 0));
  $form['bot_api_status']['last_processed'] = array(
    '#markup' => t('Last updated: @date.', array('@date' => format_date($last[7]))),
  );

  $form['bot_api_update_period'] = array(
    '#title' => t('Update period'),
    '#description' => t('The time between two updates of the API functions. Since the download is a relatively large file it is recommended that this is set to at least a day.'),
    '#default_value' => variable_get('bot_api_update_period', WEEK),
    '#type' => 'select',
    '#options' => drupal_map_assoc(array(DAY, 2*DAY, 3*DAY, WEEK, 2*WEEK, 4*WEEK), 'format_interval'),
  );
  $form['bot_api_api_site'] = array(
    '#title' => t('API site'),
    '#description' => t('URL of the site where API module has been installed. Do not append the /api path.'),
    '#type' => 'textfield',
    '#default_value' => variable_get('bot_api_api_site', 'http://api.drupal.org'),
  );
  $form['bot_api_default_branch'] = array();
  foreach ($branches as $branch => $title) {
    $form['bot_api_branch_' . $branch . '_url'] = array(
      '#default_value' => bot_api_branch_url($branch),
      '#description'   => t('Define the URL displayed in responses to this branch\'s function lookups.'),
      '#title'         => t('Function URLs for branch %name', array('%name' => $branch)),
      '#type'          => 'textfield',
    );
  }

  return system_settings_form($form);
}