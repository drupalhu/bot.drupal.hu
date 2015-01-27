FROM debian:wheezy

COPY config/php /etc/apt/preferences.d/
COPY config/sources.list /etc/apt/

RUN apt-get update
RUN apt-get install -y libapache2-mod-php5 php-apc php-pear php5 php5-cli php5-common php5-curl php5-gd php5-mcrypt php5-mysql git curl locales
RUN apt-get clean
RUN apt-get autoremove -y
RUN echo 'en_US.UTF-8 UTF-8' >> /etc/locale.gen && locale-gen

RUN echo "suhosin.simulation = On" | tee /etc/php5/conf.d/suhosin.ini
RUN pear install Net_SmartIRC

COPY config/default /etc/apache2/sites-available/
COPY config/drush_install /root/

RUN cd /var/www && git clone https://github.com/drupalhu/bot.drupal.hu.git
RUN /bin/sh /root/drush_install
RUN drush --version

COPY config/run.sh /root/
COPY config/settings.php /var/www/bot.drupal.hu/docroot/sites/default/

EXPOSE 80

CMD /root/run.sh
