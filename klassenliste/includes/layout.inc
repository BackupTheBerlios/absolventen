<?php /*
Copyright (c) 2000 SchlemmerSoft (Tobias Schlemmer)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

his program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License 
along with this program; if not, write to the Free Software 
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

Der Autor kann unter der Email: Tobias.Schlemmer@web.de erreicht werden.

*/ 

/* Trennlinie in der Tabelle (komplette Tabellenzeile) */
$layout['tabtrenner']='<tr><td colspan="5" align="center"><img src="../eksg/bilder/regenbogen.gif" height="5" width="700" align="center" /></td></tr>';

/* Trennlinie im freien Text */
$layout['linie']='<hr width="95%" />';



function seitenanfang($title="ehemalige Sch&uuml;ler von St.&nbsp;Augustin",
		      $style="Hauptstil.css",
		      $body='<body background="back.png" bgcolor="#440055" text="#FFFF88" link="#D3EEFF" alink="#FFFFFF" vlink="#DDDD00">',
		      $target="") 
{
  Header("Content-Type: text/html; charset=" . $_SESSION['zeichensatz']);
?>
<?="<?"?>xml version="1.0" encoding="UTF-8"<?="?>"?>
<?="<?"?>xml-stylesheet type="text/css" href="<?=$style?>"<?="?>"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
     "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
  <title><?=$title?></title>
   <link rel="stylesheet" type="text/css" 
   href="<?=$style?>" />
   <?php if ($target) echo "   <base target=\"$target\" />\n";?>
</head>
<?=$body?>
<center>
<?php if ($_SESSION['name']) 
  printf('<p><font size="-1">%s</font></p>',$_SESSION['name']);
 if ($title) printf("<h1>%s</h1>\n",$title);
}

function seitenende($br=" | ",$copy=1){
  global $layout;
  global $version;
  global $startzeit;
?>
  <p><?=$layout['linie']?>
  <a href="<?=$PHP_SELF?>?aktion=jgauswahl">Abfrage</a><?=$br?>
  <a href="<?=$PHP_SELF?>?aktion=hinzufuegen">Neu</a><?=$br?>
<?php if (isset($_SESSION['uid'])) { ?>
  <a href="<?=$PHP_SELF?>?aktion=bearbmenu">eigene&nbsp;Daten</a><?=$br?>
  <a href="<?=$PHP_SELF?>?aktion=logout">Abmelden</a>
 <?php } else { ?>
  <a href="<?=$PHP_SELF?>?aktion=login">Einloggen</a>
 <?php } ?>
  </p>
<?php if ($layout['homelink']) {?>
  <p><?=$layout['linie']?>
  <?=$layout['homelink']?>
  </p>
<?php }
  if ($copy) 
  { 
?>
  <p><?=$layout['linie']?><font size="-1">
  <a href="http://absolventen.berlios.de">Klassenliste Version <?=$version?></a></font></p>
  <address><font size="-2">
   &copy; 2000-2003
    <a href="mailto:Tobias.Schlemmer@web.de">SchlemmerSoft 
     (Tobias Schlemmer)</a><br />
    Dieses Programm steht unter der 
      <a href="http://www.gnu.org/copyleft/gpl.html">GPL</a></font>
  </address>
 <font size="-3">Rechenzeit: <?php printf("%.3f",ereg_replace("^0.([0-9]*) ([0-9]*)$","\\2.\\1",microtime())*1000.-$startzeit)?> ms</font>
<?php } ?>
</center>
</body>
</html>
<?php
}

function fehler($fehler){
?><h2>Fehler</h2>
<p>
<?=$fehler?>
</p>
<?php
}

?>