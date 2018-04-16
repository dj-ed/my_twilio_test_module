README.txt
==========
The 'My Twilio' module provides integration with the Twilio cloud communication
platform providing your users two-factor authentication via SMS.

All HTTP requests sent from this module are sent over curl and no additional
libraries are required for its functioning.


Configuration
------------
You will need to input active Twilio account credentials(account SID/token/twilio phone number)
on 'My Twilio' administration configuration page:
> ***admin/config/system/my-twilio***.

In case Your system or network configuration does not allow Drupal to access web pages You will
also need to add the following line to Your *settings.php* file:
> **$conf['drupal_http_request_fails'] = FALSE;**