<?php if (!$db = @mysql_connect($mysql_daten['Rechner'], $mysql_daten['Nutzer'], $mysql_daten['Passwort'])){
  authenticate();
}
include('anfang.php');
echo "<H2>Einladungen bearbeiten</H2>";
//echo "<br> $db <br>";


mysql_select_db($mysql_daten['Datenbank'],$db);

if ($terminid)
{ 
  anzeige("Einladungen bearbeiten",$terminid);
  include('ende.php');
}
#include('ende.php');
?>
