<?php
function db_verbinden(){
  global $db;
  global $mysql_daten;
  if (! $db=@mysql_connect($mysql_daten['Rechner'],
    $mysql_daten['Nutzer'],$mysql_daten['Passwort']))
    authenticate();
  mysql_select_db($mysql_daten['Datenbank'],$db);
}

function db_anfrage($sql,$datb=0){
  global $db;
  if (!$datb) $datb=$db;
  return @mysql_query($sql,$datb);
}

function db_array_holen($anfrage){
  global $db;
  return @mysql_fetch_array($anfrage);
}


?>
