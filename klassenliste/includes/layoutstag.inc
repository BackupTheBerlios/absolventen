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
$layout['tabtrenner']='<tr><td colspan=5 align=center><IMG SRC="../eksg/bilder/regenbogen.gif" HEIGHT=5 WIDTH=700 ALIGN=CENTER></td></tr>';

/* Trennlinie im freien Text */
$layout['linie']='<hr width="95%" />';



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
  global $layout;
  global $version;
  global $startzeit;
?>
  <p><?=$layout['linie']?>
  <a href="<?=$PHP_SELF?>?aktion=jgauswahl">Abfrage</a><?=$br?>
  <a href="<?=$PHP_SELF?>?aktion=hinzufuegen">Hinzuf&uuml;gen</a><?=$br?>
  <a href="<?=$PHP_SELF?>?aktion=login">Einloggen</a>
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
  <a href="http://absolventen.berlios.de">Klassenliste Version <?=$version?></a></font><br />
  <address><font size="-2">
   &copy; 2000
    <a href="mailto:Tobias.Schlemmer@web.de">SchlemmerSoft 
     (Tobias schlemmer)</a><br />
    Dieses Programm steht unter der 
      <a href="http://www.gnu.org/copyleft/gpl.html">GPL</a></font>
  </address>
 <font size=-3>Rechenzeit: <?php printf("%.3f",ereg_replace("^0.([0-9]*) ([0-9]*)$","\\2.\\1",microtime())*1000.-$startzeit)?> ms</font>
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