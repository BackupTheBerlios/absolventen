<?php /* $Id: anzeige.inc,v 1.6 2004/07/19 22:19:21 keinstein Exp $
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

$Log: anzeige.inc,v $
Revision 1.6  2004/07/19 22:19:21  keinstein
globale Variablen nach $GLOBALS
format_kommentar() -> geleert
HTML XML-fähig gemacht
Abbrechen bei fehlerhafter Email
puffer_leeren()

Revision 1.5  2004/07/15 00:09:57  keinstein
select_jgs(): Neues Formular.
              Automatisches Submit, falls JS eingeschaltet
	      in diesem Falle: Knopf verstecken
anzeige_jg(): Neues Formular: strukturiert und mit CSS-Klassen
emailformular(): Neues Formular: strukturiert und mit
                 CSS-Klassen, labels, Fehlermeldungen usw.
mailsenden(): Neue HTML-Ausgabe, Neue Statuszeilen in Email
              UTF-8 und mb_*-Funktionen zur Kodierung verwendet.
	      Fehlermeldungen
anzeige_mailformopt():Session-Var. Umbenannt, HTML-Einrückung

*/ 

function format_kommentar($kommentar) {
}

function select_jgs($db,$jahrgang=""){
  
  
  $jg=new jg($db);
  if (!$jg->erste_nur_jahrgang()) { 
    echo "Nix gefunden."; 
    $jg->puffer_leeren();
    return; 
  } ;
?>
<form method="get" action="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>" enctype="application/x-www-form-urlencoded" 
    class="absolventen anzeige select_jgs"><label for="jganzeige_sel">Jahrgang wählen:
    <input type="hidden" name="aktion" value="jganzeige" 
      class="absolventen anzeige select_jgs" /></label><select 
      size="1" name="jahrgang" class="absolventen anzeige select_jgs" 
      onchange="this.form.submit()" id="jganzeige_sel">
<?php
  if (empty($jahrgang)) print("<option  class=\"absolventen anzeige anzeige_jgliste\""
			      . " value=\"\">Wahl</option>\n");
  $jg->optionprint($jahrgang); 
?></select>
<input type="submit" value="Ok." class="absolventen anzeige select_jgs" id="abs-jganzeige-knopf" />
<script type="text/javascript">
<![CDATA[
    document.getElementById("abs-jganzeige-knopf").style.display = "none";
    ]]>
</script>
</form>
<?php  // bei meinem Mozilla kann man die Vorauswahl nicht wählen :-(
       // Ansonsten verstecken wir den Knopf einfach, wenn JS eingeschaltet ist.
    $jg->puffer_leeren();
}


function anzeige_jg ($jahrgang,&$db) {
  
  $mailformopts=array();
  select_jgs(&$db,$jahrgang);
  $jg=new jg(&$db);
  if (!$jg->erste_jahrgang($jahrgang)) { 
    echo "Nix gefunden."; 
    $jg->puffer_leeren();
    return; 
  }
?>
<table border="1" class="absolventen anzeige anzeige_jg">
<thead class="absolventen anzeige anzeige_jg">
<tr class="absolventen anzeige anzeige_jg"><th colspan="5" class="absolventen anzeige anzeige_jahrgang"><font
size="+2" class="absolventen anzeige anzeige_jahrgang">Jahrgang <?=$jahrgang?></font></th></tr>
<?=$GLOBALS['mod_absolventen_glob']['layout']['tabtrenner']?>
<tr align="left" class="absolventen anzeige anzeige_jg">
<th class="absolventen anzeige anzeige_geburtsname">Geburtsname</th>
<th class="absolventen anzeige anzeige_vorname">Vorname</th>
<th colspan="2" class="absolventen anzeige anzeige_adranfang">Adresse erster Teil</th>
<th rowspan="3" class="absolventen anzeige anzeige_telefon">Telefon</th></tr>
<tr align="left" class="absolventen anzeige anzeige_jg">
<th class="absolventen anzeige anzeige_jg"></th>
<th class="absolventen anzeige anzeige_aktname">aktueller Name</th>
<th class="absolventen anzeige anzeige_plz">PLZ</th>
<th class="absolventen anzeige anzeige_ort">Ort</th></tr>
<tr align="left" class="absolventen anzeige anzeige_jg">
<th colspan="2" class="absolventen anzeige anzeige_jg"></th>
<th colspan="2" class="absolventen anzeige anzeige_adrende">Adresse zweiter Teil</th></tr>
<tr align="left" class="absolventen anzeige anzeige_jg">
<th colspan="2" class="absolventen anzeige anzeige_timestamp"><font size="-2" 
class="absolventen anzeige anzeige_timestamp">letzte &Auml;nderung</font></th>
<th colspan="3" class="absolventen anzeige anzeige_email">Email</th></tr>
<tr align="left" class="absolventen anzeige anzeige_jg">
<th colspan="2" class="absolventen anzeige anzeige_jg"></th>
<th colspan="3" class="absolventen anzeige anzeige_hp">Homepage</th></tr>
<tr align="left" class="absolventen anzeige anzeige_jg">
<th colspan="5" class="absolventen anzeige anzeige_bemerkungen">Bemerkungen</th></tr>
</thead>
<tbody class="absolventen anzeige anzeige_jg">
<?php
  do {
     $jg->normprint();
  }while ($jg->naechste());
  $jg->erste_jahrgang($jahrgang);
  do {
     $mailformopts =array_merge($mailformopts,$jg -> mailformopts());
  }while ($jg->naechste());
  echo "</tbody></table>";
  unset($mailformopts["  /0/0"]);
  ksort($mailformopts);
  emailformular(array("adressen" => $mailformopts, "jahrgang" => $jahrgang));
  $jg->puffer_leeren();
}


function emailformular($daten,$fehler=0){
  
  if (!isset($_SESSION['mod_absolventen']['mailtimestamp'])) $_SESSION['mod_absolventen']['mailtimestamp']=microtime();
  if (!empty($daten['adressen'])  ||  isset($daten['empfaenger'])) {
?>
<div class="absolventen  datenformular">
<h3 class="absolventen formular emailformular">Einer der obigen Personen eine Nachricht 
   per elektronischer Post zukommen lassen</h3>
<form method="post" action="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>" class="absolventen formular emailformular">
  <input type="hidden" name="jahrgang" value="<?=isset($daten['jahrgang'])?$daten['jahrgang']:""?>" />
  <table  class="absolventen formular emailformular">
    <tbody class="absolventen formular emailformular">
      <tr  class="absolventen formular emailformular">
        <th class="absolventen formular emailform an"><?php
     if (!empty($daten['adressen'])){ 
?><label 
            for="abs_empfaenger" class="absolventen formular emailform an">Nachricht an:</label></th>
        <td class="absolventen formular emailform an"><select 
            id="abs_empfaenger" name="empfaenger" 
            class="absolventen formular emailform an<?=isset($fehler['empfaenger'])?" fehler":""?>">
<?php array_walk($daten['adressen'],'anzeige_mailformopt'); ?></select></td>
      </tr>
      <?php }
     else 
     { ?><input type="hidden" name="empfaenger" 
            value="<?=isset($daten['empfaenger'])?$daten['empfaenger']:""?>" />Nachricht an:</th>
        <td class="absolventen formular emailform an"><?=isset($daten['an'])?$daten['an']:""?></td>
      </tr>
      <?php
     } ?><tr class="absolventen formular emailformular">
        <th class="absolventen formular emailform von"><label 
            for="abs_absender" class="absolventen formular emailform von">Ihr Name:</label></th>
        <td class="absolventen formular emailform von"><input 
            type="text" id="abs_absender" name="absender" 
            value="<?=isset($daten['absender'])?$daten['absender']:""?>" 
            class="absolventen formular emailform von<?=isset($fehler['absender'])?" fehler":""?>" /></td>
      </tr>
      <tr class="absolventen formular emailformular">
        <th class="absolventen formular emailform abs_adr"><label 
            for="abs_adr" class="absolventen formular emailform abs_adr">Ihre Email-Adresse:</label></th>
        <td class="absolventen formular emailform abs_adr"><input 
            type="text" id="abs_adr" name="absender_adr" 
            value="<?=isset($daten['absender_adr'])?$daten['absender_adr']:""?>" 
            class="absolventen formular emailform abs_adr<?=isset($fehler['absender_adr'])?" fehler":""?>" /></td>
      </tr>
      <tr class="absolventen formular emailformular">
	<th class="absolventen formular emailform betreff"><label 
            for="abs_betreff" class="absolventen formular emailform betreff">Thema:</label></th>
        <td class="absolventen formular emailform betreff"><input type="text" id="abs_betreff" name="betreff" 
            value="<?=isset($daten['betreff'])?$daten['betreff']:""?>"  
            class="absolventen formular emailform betreff<?=isset($fehler['betreff'])?" fehler":""?>"/></td>
      </tr>
      <tr class="absolventen formular emailformular">
        <th colspan="2" class="absolventen formular emailform text"><label 
            for="abs_text" class="absolventen formular emailform text">Text der Nachricht:</label></th>
      </tr>
      <tr class="absolventen formular emailformular">
        <td colspan="2" class="absolventen formular emailform text"><textarea 
            id="abs_text" name="text" cols="30" rows="6"
            class="absolventen formular emailform text<?=isset($fehler['text'])?" fehler":""?>"><?=isset(
						  $daten['text'])?$daten['text']:""?></textarea></td>
      </tr>
      <tr class="absolventen formular emailformular knoepfe">
        <td colspan="2" class="absolventen formular emailform senden knoepfe"><input 
            type="hidden" name="aktion" value="email" /><input 
            type="submit" name="Abschicken" value="Abschicken"  
            class="absolventen formular emailform senden"/></td>
      </tr>
    </tbody>
  </table>
</form>
<?php if (!empty($fehler)) { ?>
<form method="get" action="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>" class="absolventen formular emailformular"><input 
	    type="hidden" name="jahrgang" value="<?=isset($daten['jahrgang'])?$daten['jahrgang']:""?>" /><input 
            type="hidden" name="aktion" value="jganzeige" /><input 
            type="submit" name="Abbrechen" value="Abbrechen"  
            class="absolventen formular emailform senden"/>
</form><?php } ?>
</div>
<?php
  }
}

function mailsenden ($db,$daten) {
  
  $person=new personen($db);
  $email=new email($db);
  if (empty($daten['empfaenger']) ||
      !ereg("/([0-9]*)/([0-9]*)$",$daten['empfaenger'],$ids)) {
    printf('<ul class="absolventen emailform fehler"><li class="absolventen emailform fehler">%s</li></ul>%s',
    "Interner Fehler 1. Dies kann bei normaler Nutzung nicht passieren.","\n");
    return;
  }
  $person->diese($ids[1]);
  $email->diese($ids[2]);
  if (!($email->uid()==$person->id() && 
      sprintf("%s%s %s %s/%d/%d",
	      isset($_SESSION['mod_absolventen']['mailtimestamp'])?$_SESSION['mod_absolventen']['mailtimestamp']:"",
	      urlencode($person->aktueller_name()),
	      urlencode($person->vorname()),
	      urlencode($email->name()),
	      $person->id(),$email->id())==$daten['empfaenger']))
  { 
    printf('<ul class="absolventen emailform fehler"><li class="absolventen emailform fehler">%s</li></ul>%s',
    "Interner Fehler 2. Dies kann bei normaler Nutzung nicht passieren.","\n");
    $person->puffer_leeren();
    $email->puffer_leeren();
    return;
  }
  if (empty($daten['absender_adr'])) 
    $fehler['absender_adr'] = "Um von diesem Formular aus eine Email zu verschicken,"
      . " müssen Sie schon ihre Email-Adresse angeben";
  elseif (!ereg("^[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+"
	      . "@[-!#$%&\'*+\\/0-9=?A-Z^_`a-z{|}~]+"
	    . "\.[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+$",$daten['absender_adr']))
    $fehler['absender_adr'] = "Absender-Adresse ist Ungültig.";
  if (empty($daten['absender']) || !ereg("[^ \t]+[ \t]+[^ \t]",$daten['absender']))
    $fehler['absender'] = "Geben Sie bitte Ihren Vor- und Zunamen als Absender an!";
  if (empty($daten['betreff']))
    $fehler['betreff'] = "Bitte geben Sie das Thema der Email an.";
  if (empty($daten['text']))
    $fehler['text'] = "Ohne Inhalt schicke ich die Mail nicht weg.";
  $daten['an']=sprintf("%s %s%s",
		       $person->vorname(),
		       $person->aktueller_name(),
		       $email->name()?" (" . $email->name() . ")":"");
  if (empty($fehler)){
    $header=sprintf("From: \"%s\" <%s>  
User-Agent: Kontaktformular der Absolventenliste Ver. %s
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Sender: \"%s\" <%s>  
Return-Path: %s",
		    mb_encode_mimeheader($daten['absender'],'UTF-8','Q'),
		    $daten['absender_adr'],
		    $GLOBALS['mod_absolventen_glob']['version'],
		    mb_encode_mimeheader($daten['absender'],'UTF-8','Q'),
		    $daten['absender_adr'],
		    $daten['absender_adr']) ;
    $daten['text'] .= sprintf("\n\n- . - . - . - . -\nStatistik:\nvon: %s:%s\n    (%s)\nServer %s(%s):%s\n"
			      . "Anforderung: %s %s?%s %s\nvon Seite: %s" , 
			      $_SERVER["REMOTE_ADDR"], 
			      $_SERVER["REMOTE_PORT"], 
			      $_SERVER["HTTP_USER_AGENT"] ,
			      $_SERVER['SERVER_NAME'],
			      $_SERVER['SERVER_ADDR'],
			      $_SERVER['SERVER_PORT'],
			      $_SERVER["REQUEST_METHOD"],
			      $_SERVER['REQUEST_URI'],
			      $_SERVER["QUERY_STRING"],
			      $_SERVER["SERVER_PROTOCOL"],
			      $_SERVER["HTTP_REFERER"]); 
    if(mail(sprintf('"%s" <%s>',
		 mb_encode_mimeheader($daten['an'],'UTF-8','Q'),
		 $email->adresse()) ,
	 "[WWW-Formular] " . mb_encode_mimeheader($daten['betreff'],'UTF-8','Q'),
	 $daten['text'],
	    $header,sprintf("'-f%s'",addslashes($daten['absender_adr'])))){
?>
<p class="absolventen emailformular status">Die Nachricht wurde erfolgreich abgeschickt.</p>
<ul class="absolventen emailformular status">
  <li class="absolventen emailformular gesendet header ges_an">An: <?=htmlspecialchars($daten['an'])?></li>
  <li class="absolventen emailformular gesendet header ges_betr">Betreff: [WWW-Formular] 
     <?=htmlspecialchars($daten['betreff'])?></li>
  <li class="absolventen emailformular gesendet header additional"><?=nl2br(htmlspecialchars($header))?></li>
  <li class="absolventen emailformular gesendet body"><?=nl2br(htmlspecialchars($daten['text']))?></li>
</ul>
<?php
      unset($_SESSION['mod_absolventen']['mailtimestamp']);
    }
    else {
      $fehler[]="Die Email konnte nicht abgeschickt werden";
    }
  } // if emtpy($fehler)
 
  if (!empty($fehler)) {
    print('<ul class="absolventen emailform fehler">');
    array_walk($fehler,'bearb_fehlerliste');
    print('</ul>');
    
    emailformular($daten,$fehler);
  }

  $person->puffer_leeren();
  $email->puffer_leeren();
}



function anzeige_mailformopt($wert,$schluessel) {
  printf('         <option value="%s%s" class="absolventen anzeige emailform an">%s</option>'. "\n",
	 $_SESSION['mod_absolventen']['mailtimestamp'],
	 $schluessel,$wert);
}
?>
