<?php

unset($mysql_daten);
require_once('config.inc');
require_once('mysqldb.inc');
require_once('jahrgang.inc');
require_once('personen.inc');
require_once('adressen.inc');
require_once('telefon.inc');
require_once('hp.inc');
require_once('email.inc');

require_once('anzeige.inc');
require_once('login.inc');
require_once('bearbeiten.inc');

echo $layoutid;
unset($layout);
if (file_exists("layout" . $_SESSION['layoutid'] . ".inc")) 
     include("layout" . $_SESSION['layoutid'] . ".inc");
else {
  echo "default";
  $layoutid="";
  include("layout.inc");
}
?>