#!/bin/bash
service apache2 start
dd if=/dev/urandom of=/tmp/key bs=1 count=64
cd /var/www/bot.drupal.hu/docroot
drush bot-status-reset -y
drush bot-start  >/dev/null 2>&1
