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

function format_kommentar($kommentar) {
  global $kommentar_tags_suche;
  global $kommentar_tag_ersetze;
}

function select_jgs($db){
  global $layout;
  $jg=new jg($db);
  if (!$jg->erste_nur_jahrgang()) { 
    echo "Nix gefunden."; 
    $jg->puffer_leeren();
    return; 
  } ;
?>
<form method="get" action="<?=$PHP_SELF?>" enctype="application/x-www-form-urlencoded">
<input type="hidden" name="aktion" value="jganzeige" />
<select size="1" name="jahrgang">
   <?php $jg->optionprint(); ?>
</select>
<input type="submit" value="Ok." />
</form>
<?php
    $jg->puffer_leeren();
}


function anzeige_jg ($jahrgang,$db) {
  global $layout;
  $mailformopts=array();
  $jg=new jg($db);
  if (!$jg->erste_jahrgang($jahrgang)) { 
    echo "Nix gefunden."; 
    $jg->puffer_leeren();
    return; 
  }
?>
<table border="1">
<tr><th colspan="5"><font size="+2">Jahrgang <?=$jahrgang?></font></th></tr>
<tr align="left"><th>Geburtsname</th><th>Vorname</th><th colspan="2">Adresse erster Teil</th><th rowspan="3">Telefon</th></tr>
<tr align="left"><th></th><th>aktueller Name</th><th>PLZ</th><th>Ort</th></tr>
<tr align="left"><th colspan="2"></th><th colspan="2">Adresse zweiter Teil</th></tr>
<tr align="left"><th colspan="2"><font size="-2">letzte &Auml;nderung</font></th><th colspan="3">Email</th></tr>
<tr align="left"><th colspan="2"></th><th colspan="3">Homepage</th></tr>
<tr align="left"><th colspan="5">Bemerkungen</th></tr>
<?php
  do {
     $jg->normprint();
  }while ($jg->naechste());
  $jg->erste_jahrgang($jahrgang);
  do {
     $mailformopts =array_merge($mailformopts,$jg -> mailformopts());
  }while ($jg->naechste());
  echo "</table>";
  unset($mailformopts["  /0/0"]);
  ksort($mailformopts);
  emailformular(array("adressen" => $mailformopts));
  $jg->puffer_leeren();
}


function emailformular($daten){
  if (!$_SESSION['mailtimestamp']) $_SESSION['mailtimestamp']=microtime();
?>
<p>
<form method="post" action="<?=$PHP_SELF?>">
<?php
   if ($daten['adressen']){ 
?><label for="empfaenger">An:
<select id="empfaenger" name="empfaenger"><?php 
array_walk($daten['adressen'],'anzeige_mailformopt'); ?></select></label><br /><?php
   }
   else 
   { ?>
<input type="hidden" name="empfaenger" value="<?=$daten['empfaenger']?>">
   <?php 
   if ($daten['an']) printf("An: %s<br />\n",$daten['an']); } ?>
<label for="absender">Von:<input type="text" id="absender" name="absender" value="<?=$daten['absender']?>" /></label><br />
<label for="betreff">Betrifft: <input type="text" id="betreff" name="betreff" value="<?=$daten['betreff']?>" /></label><br />
		      <label for="text">Text:<br />
<textarea id="text" name="text"><?=$daten['text']?></textarea></label><br />
<input type="hidden" name="aktion" value="email" />
<input type="submit" name="Abschicken" value="Abschicken" />
</form>
</p>
<?php
}


function mailsenden ($db,$daten) {
  global $HTTP_SERVER_VARS;
  $person=new personen($db);
  $email=new email($db);
  ereg("/([0-9]*)/([0-9]*)$",$daten['empfaenger'],$ids);
  $person->diese($ids[1]);
  $email->diese($ids[2]);
  if (!($email->uid()==$person->id() && 
      sprintf("%s%s %s %s/%d/%d",
	      $_SESSION['mailtimestamp'],
	      urlencode($person->aktueller_name()),
	      urlencode($person->vorname()),
	      urlencode($email->name()),
	      $person->id(),$email->id())==$daten['empfaenger']))
  { 
    echo "Fehler. Dies kann bei normaler Nutzung nicht passieren."; 
    return;
  }
  if (!ereg("^[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+"
	      . "@[-!#$%&\'*+\\/0-9=?A-Z^_`a-z{|}~]+"
	    . "\.[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+$",$daten['absender']))
  { 
    echo "Absender-Adresse ist Ungültig.";
    $daten['an']=sprintf("%s %s %s",$person->vorname(),$person->aktueller_name(),
      $email->name()?$email->name():"");
    emailformular($daten);
  } else {
    $header="From: " . $daten['absender'] . "
User-Agent: Kontaktformular der Klassenliste von St. Augustin" ;
$daten['text'] .= "

- . - . - . - . -
Statistik:
von: " . $HTTP_SERVER_VARS["REMOTE_ADDR"] . ":" . $HTTP_SERVER_VARS["REMOTE_PORT"] . "\n(" . $HTTP_SERVER_VARS["HTTP_USER_AGENT"] . ")
Methode: " . $HTTP_SERVER_VARS["REQUEST_METHOD"] . "
Query string: " . $HTTP_SERVER_VARS["QUERY_STRING"]; 
mail($email->adresse() ,
   "[WWW-Formular] " . stripslashes($daten['betreff']),stripslashes($daten['text']),
   stripslashes($header));
?>
<p>
Das Formular wurde erfolgreich abgeschickt.
</p>
<p>
<table border=2>
<tr><td><tt>An: <?=htmlspecialchars(sprintf("%s %s",$person->vorname(),$person->aktueller_name()))?><br>
Betreff: [WWW-Formular] <?=$daten['betreff']?></tt></td></tr>
<tr><td><tt><?=nl2br(htmlspecialchars(stripslashes($header)))?></tt></td></tr>
<tr><td><tt><?=nl2br(htmlspecialchars(stripslashes($daten['text'])))?></tt></td></tr>
</table>
</p>
<?php
   unset($_SESSION['mailtimestamp']);
  }
    
}



function anzeige_mailformopt($wert,$schluessel) {
  printf('<option value="%s%s">%s</option>'. "\n",
	 $_SESSION['mailtimestamp'],
	 $schluessel,$wert);
}
?>
