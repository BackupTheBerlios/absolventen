<?php /* $Id: layoutstagv4.inc,v 1.3 2004/07/25 17:34:50 keinstein Exp $
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

$Log: layoutstagv4.inc,v $
Revision 1.3  2004/07/25 17:34:50  keinstein
Tippfehler in Fußzeile: Hilfe

Revision 1.2  2004/07/19 22:35:29  keinstein
globale Variablen nach $GLOBALS

Revision 1.1  2004/07/15 11:56:15  keinstein
Layoutbeispiel für Verwendung als Modul

*/ 

/* Trennlinie in der Tabelle (komplette Tabellenzeile) */

$GLOBALS['mod_absolventen_glob']['layout']['tabtrenner']='<tr class="absolventen trenner"><td colspan="5" align="center" class="absolventen trenner">&nbsp;</td></tr>';

/* Trennlinie im freien Text */
$GLOBALS['mod_absolventen_glob']['layout']['linie']='<hr class="absolventen linie" width="95%" />';



function seitenanfang($title="",
		      $style="Hauptstil.css",
		      $body='<body background="back.png" bgcolor="#440055" text="#FFFF88" link="#D3EEFF" alink="#FFFFFF" vlink="#DDDD00">',
		      $target="") 
{
  
  Header("Content-Type: text/html; charset=" . $_SESSION['mod_absolventen']['zeichensatz']);
?><div class="absolventen">
   <?php if (isset($_SESSION['mod_absolventen']['name'])) 
     printf('<div class="absolventen loginstatus">%s</div>',$_SESSION['mod_absolventen']['name']);
 if ($title) printf("<h1>%s</h1>\n",$title);
}

function seitenende($br=" | ",$copy=1){
?>
  <p class="absolventen fussmenu"><?=$GLOBALS['mod_absolventen_glob']['layout']['linie']?>
  <a class="absolventen fussmenu" href="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>?aktion=jgauswahl">Abfrage</a><?=$br?>
  <a  class="absolventen fussmenu"href="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>?aktion=hinzufuegen">Neu</a><?=$br?>
<?php if (isset($_SESSION['mod_absolventen']['uid'])) { ?>
  <a class="absolventen fussmenu" href="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>?aktion=bearbmenu">eigene&nbsp;Daten</a><?=$br?>
  <a class="absolventen fussmenu" href="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>?aktion=logout">Abmelden</a>
 <?php } else { ?>
  <a class="absolventen fussmenu" href="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>?aktion=login">Einloggen</a>
 <?php } ?><?=$br?>
  <a class="absolventen fussmenu" href="http://absolventen.berlios.de/hilfe/" target="_empty">Hilfe</a>
  </p><?=$GLOBALS['mod_absolventen_glob']['layout']['linie']?><?php
      if (isset($_SESSION['mod_absolventen']['name']))
  printf('<p><font size="-1">Sie sind %s.<br /> Nein? '
         . 'Dann <a href="%s?aktion=logout">melden Sie sich bitte ab!</a></font></p>%s',
	 $_SESSION['mod_absolventen']['name'],
	 $GLOBALS['mod_absolventen_glob']['php_self'],$GLOBALS['mod_absolventen_glob']['layout']['linie']);?>
       <font size="-3" class="absolventen rechenzeit">Rechenzeit: <?php 
	  printf("%.3f",ereg_replace("^0.([0-9]*) ([0-9]*)$","\\2.\\1",microtime())*1000.-$GLOBALS['mod_absolventen_glob']['startzeit'])?> ms</font>
  </div>
<?php
}

function fehler($fehler){
?><h2 class="absolventen fehler">Fehler</h2>
<p class="absolventen fehler">
<?=$fehler?>
</p>
<?php
}

?>
