<?php

/**
 * Administration form for setting up connection to twilio account.
 *
 * @param $form
 * @param $form_state
 * @return mixed(sets all inputted field values to matching system variable)
 */
function my_twilio_admin_form($form, &$form_state) {
  $form['my_twilio_account'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Twilio Account SID'),
    '#default_value' => variable_get('my_twilio_account'),
    '#description' => t('Enter your Twilio account id'),
  );
  $form['my_twilio_token'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Twilio Auth Token'),
    '#default_value' => variable_get('my_twilio_token'),
    '#description' => t('Enter your Twilio token id'),
  );
  $form['my_twilio_number'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Twilio Phone Number'),
    '#default_value' => variable_get('my_twilio_number'),
    '#description' => t('Enter your Twilio phone number'),
  );

  $form['my_twilio_country_codes_container'] = array(
    '#type' => 'fieldset',
    '#title' => t('Country codes'),
    '#description' => t('Select the country codes you would like available, If none are selected all will be available.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['my_twilio_country_codes_container']['twilio_country_codes'] = array(
    '#type' => 'checkboxes',
    '#options' => my_twilio_country_codes(TRUE),
    '#default_value' => variable_get('my_twilio_country_codes', array()),
  );

  return system_settings_form($form);
}

/**
 * My Twilio admin form for sending/testing twilio SMS service.
 *
 * @param $form
 * @param $form_state
 * @return mixed
 */
function my_twilio_admin_test_form($form, &$form_state) {
  $form['country'] = array(
    '#type' => 'select',
    '#title' => t('Country code'),
    '#options' => my_twilio_country_codes(),
  );
  $form['number'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Phone Number'),
    '#description' => t('The number to send your message to. Include all numbers except the country code'),
  );
  $form['message'] = array(
    '#type' => 'textarea',
    '#required' => TRUE,
    '#title' => t('Message'),
    '#description' => t("The body of your SMS message.")
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Send SMS'),
  );
  return $form;
}

function my_twilio_admin_test_form_validate($form, &$form_state) {
  $value = $form_state['values']['number'];
  if (!is_numeric($value)) {
    form_set_error('number', t('You must enter a phone number'));
  }
}

/**
 * My Twilio admin test form submit function.
 *
 * @param $form
 * @param $form_state
 */
function my_twilio_admin_test_form_submit($form, &$form_state) {
  $sent = my_twilio_send(
    $form_state['values']['number'],
    $form_state['values']['message'],
    $form_state['values']['country'],
    !empty($form_state['values']['media']) ? $form_state['values']['media'] : NULL
  );

  if ($sent) {
    drupal_set_message(t('Your message has been sent'));
  }
  else {
    drupal_set_message(t('Unable to send your message.'), 'error');
  }
}
