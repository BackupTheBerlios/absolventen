<?php 
function anfang($stil="Haupstil.css",$target=""){
global $startzeit;
global $dividier;
global $aktion;
global $PHP_SELF;
$startzeit=ereg_replace("^0(.)([0-9]*) ([0-9]*)$","\\3\\1\\2",microtime());?>
<html>
<head>
   <title>Alt-ESG-ler von Freiberg</title>
<link rel=stylesheet type="text/css" href="<?=$stil?>"> 
<?php $dividier='hr'; ?>
<?php if ($target) echo "   <base target=\"$target\">\n";?>
</head>
<body background="../bilder/back.gif" bgcolor=#FFFFFF text=#000000 link=#0000EE alink=#FF0000 vlink=#551A8B>
<center>
<?php if (!($aktion=="menue")) echo "<H1>Alt-ESGler der ESG Freiberg</H1>";
  echo "<p><$dividier";
 if (!($aktion=="menue")) echo '  width="50%"'; else echo ' width="95%"';
          echo "><p>\n";
  echo "<a href=\"$PHP_SELF?aktion=anzeige\">Abfrage</a>\n";
  if ($aktion=="menue") echo "<br>\n";
  echo "<a href=\"$PHP_SELF?aktion=bearbeiten\">Bearbeiten</a>\n";
  if ($aktion=="menue") echo "<br>\n";
  echo "<a href=\"$PHP_SELF?aktion=hinzufuegen\">Hinzuf&uuml;gen</a>\n";
  if ($aktion=="menue") echo "<br>\n";
  echo "<a href=\"$PHP_SELF?aktion=termine\">Termine</a>\n";
  echo "<p><$dividier";
  if (!($aktion=="menue")) echo' width="50%"'; else echo ' width="95%"';
      echo"><p>\n";
}?>
