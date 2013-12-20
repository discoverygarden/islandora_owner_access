<?php

/**
 * @file
 * Admin settings for islandora access.
 */

/**
 * Menu callback: administer permissions.
 *
 * @ingroup forms
 * @see user_admin_permissions_submit()
 * @see theme_user_admin_permissions()
 */
function islandora_owner_access_user_admin($form, &$form_state) {
  $form = array(
    '#tree' => TRUE,
  );

  $form['islandora_access'] = array(
    '#type' => 'fieldset',
    '#title' => t('Islandora Access Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['islandora_access']['islandora_access_role'] = array(
    '#type' => 'textfield',
    '#title' => t('Islandora Access Role'),
    '#default_value' => variable_get('islandora_access_role', ''),
    '#description' => t('Enter the Islandora Access Role'),
    '#required' => TRUE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

/**
 * Form validation function.
 */
function islandora_owner_access_user_admin_validate($form, &$form_state) {
  $role_name = $form_state['values']['islandora_access']['islandora_access_role'];

  if (user_role_load_by_name($role_name)) {
    form_set_error('islandora_access', t('"%role" role already exists. Enter a different role.', array(
      '%role' => $form_state['values']['islandora_access']['islandora_access_role'],
    )));
  }

}

/**
 * Submit handler form islandora_access_user_admin form.
 */
function islandora_owner_access_user_admin_submit($form, &$form_state) {
  $role_name = $form_state['values']['islandora_access']['islandora_access_role'];
  variable_set('islandora_access_role', $role_name);
  $role = new stdClass();
  $role->name = $role_name;
  user_role_save($role);

  drupal_set_message(filter_xss(t('Created New Role !role_name. Go to !link', array(
          '!link' => l(t('Permissions'), 'admin/people/permissions'),
          '!role_name' => $role_name,
      ))), 'status');
}
