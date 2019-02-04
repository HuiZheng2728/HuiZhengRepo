<?php
/**
* The base configurations of the WordPress.
*
* This file has the following configurations: MySQL settings, Table
Prefix,
* Secret Keys, WordPress Language, and ABSPATH. You can find more
information
* by visiting {@link http://codex.wordpress.org/Editing_wp-config.php
Editing
* wp-config.php} Codex page. You can get the MySQL settings from your web
host.
*
* This file is used by the wp-config.php creation script during the
* installation. You don't have to use the web site, you can just copy this
file
* to "wp-config.php" and fill in the values.
*
* @package WordPress
*/
// ** MySQL settings - You can get this info from your web host ** //
/** The name of the database for WordPress */
define('DB_NAME', '{{ db_name }}');
/** MySQL database username */
define('DB_USER', '{{ username }}');
/** MySQL database password */
define('DB_PASSWORD', '{{ password }}');
/** MySQL hostname */
define('DB_HOST', '{{ dbhost }}');