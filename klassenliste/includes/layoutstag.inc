<?php /* $Id: layoutstag.inc,v 1.4 2004/07/19 22:34:48 keinstein Exp $
Copyright (c) 2000-2004 SchlemmerSoft (Tobias Schlemmer)

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

$Log: layoutstag.inc,v $
Revision 1.4  2004/07/19 22:34:48  keinstein
globale variablen nach $GLOBALS

Revision 1.3  2004/07/15 11:47:15  keinstein
copyright korrigiert

*/ 

/* Trennlinie in der Tabelle (komplette Tabellenzeile) */
$GLOBALS['mod_absolventen_glob']['layout']['tabtrenner']='<tr><td colspan=5 align=center><IMG SRC="../eksg/bilder/regenbogen.gif" HEIGHT=5 WIDTH=700 ALIGN=CENTER></td></tr>';

/* Trennlinie im freien Text */
$GLOBALS['mod_absolventen_glob']['layout']['linie']='<hr width="95%" />';



function seitenanfang($title="ehemalige Sch&uuml;ler von St.&nbsp;Augustin",
		      $style="Hauptstil.css",
		      $body='<body background="back.png" bgcolor=#440055 text=#FFFF88 link=#D3EEFF alink=#FFFFFF vlink=#DDDD00>',
		      $target="") 
{
?>
<html>
<head>
  <title><?=$title?></title>
   <link rel=stylesheet type="text/css" 
   href="<?=$style?>" />
   <?php if ($target) echo "   <base target=\"$target\" />\n";?>
</head>
<?=$body?>
<center>
<h2>StAg</h2>
<?php if ($title) printf("<H1>%s</H1>\n",$title);
}

function seitenende($br=" | ",$copy=1){
  
  
  
?>
  <p><?=$GLOBALS['mod_absolventen_glob']['layout']['linie']?>
  <a href="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>?aktion=jgauswahl">Abfrage</a><?=$br?>
  <a href="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>?aktion=hinzufuegen">Hinzuf&uuml;gen</a><?=$br?>
  <a href="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>?aktion=login">Einloggen</a>
  </p><?=$br?>
  <a href="http://absolventen.berlios.de/hilfe" target="_empty">Hilfe</a>
<?php if ($GLOBALS['mod_absolventen_glob']['layout']['homelink']) {?>
  <p><?=$GLOBALS['mod_absolventen_glob']['layout']['linie']?>
  <?=$GLOBALS['mod_absolventen_glob']['layout']['homelink']?>
  </p>
<?php }
  if ($copy) 
  { 
?>
  <p><?=$GLOBALS['mod_absolventen_glob']['layout']['linie']?><font size="-1">
  <a href="http://absolventen.berlios.de">Klassenliste Version <?=$GLOBALS['mod_absolventen_glob']['version']?></a></font><br />
  <address><font size="-2">
   &copy; 2000-2004
    <a href="mailto:Tobias.Schlemmer@web.de">SchlemmerSoft 
     (Tobias schlemmer)</a><br />
    Dieses Programm steht unter der 
      <a href="http://www.gnu.org/copyleft/gpl.html">GPL</a></font>
  </address>
 <font size=-3>Rechenzeit: <?php printf("%.3f",ereg_replace("^0.([0-9]*) ([0-9]*)$","\\2.\\1",microtime())*1000.-$GLOBALS['mod_absolventen_glob']['startzeit'])?> ms</font>
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
