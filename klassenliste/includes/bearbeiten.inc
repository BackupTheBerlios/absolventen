<?php /* $Id: bearbeiten.inc,v 1.7 2004/07/19 22:20:52 keinstein Exp $
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

$Log: bearbeiten.inc,v $
Revision 1.7  2004/07/19 22:20:52  keinstein
puffer_leeren() aufrufen
globale Variablen nach $GLOBALS

Revision 1.6  2004/07/15 11:30:39  keinstein
Allgemein: Klassen für HTML-Ausgabe
	   Fehlermeldungen bei Formularen
	   $_SESSION -> $_SESSION['mod_absolventen']

Neu: bearb_fehlerliste() -- callback für array_walk
     bearb_verweigert()  -- Fehlermeldung für falsche
     	                    Zugriffsrechte
     bearb_sicherheitscheck() -- Überprüfung von Session-
     	                         und empfangenen Daten

bearb_menu(): keine Tabelle mehr, ul für Menü

persdatenaendern(): Sicherheitscheck ausgelagert
                    Neuer Datensatz per extra Variable
		    Sitzungsnamen setzen

untertabdatenform(): Kurzmenü am Anfang
untertabdatenaendern(): Sicherheitscheck ausgelagert
	                Fehlermeldung ul
			Neu mit extra Variable
austragen(): Sicherheitscheck ausgelagert
	     fast komplett neu

*/ 

function bearb_fehlerliste($value,$key) {
  printf("<li>%s</li>\n",$value);
}

function bearb_verweigert($db) {
    logout($db);
    print('<ul class="absolventen bearbeiten fehler"><li>Zugriff verweigert!</li></ul>');
}

function bearb_sicherheitscheck($tabelle,$daten,$neu,$uidcheck=true) {
  // Gravierende Fehler bezüglich Zugriffskontrolle
  // (Angriffe; können nicht vom Nutzer korrigiert werden)
  // fehlerhafte id und uid
  if (!$neu || $uidcheck) {
    if (empty($_SESSION['mod_absolventen']['uid']) || (empty($daten[$uidcheck?'uid':'id'])) ||
	($_SESSION['mod_absolventen']['uid']!=$daten[$uidcheck?'uid':'id'])) {
      bearb_verweigert($tabelle->db);
      $tabelle->puffer_leeren();
      return true;
    }  
  }

  if (!$uidcheck && !empty($daten['uid'])) {
    bearb_verweigert($tabelle->db);
    $tabelle->puffer_leeren();
    return true;
  }  

  if (!$neu) {
    if (empty($daten['id']) || !ereg('^[0-9]+$',$daten['id']) || !$tabelle->diese($daten['id']) ||
	($uidcheck && ($tabelle->uid() != $_SESSION['mod_absolventen']['uid']))){
      bearb_verweigert($tabelle->db);
      $tabelle->puffer_leeren();
      return true;
    }  
  } elseif (!empty($daten['id'])) {
      bearb_verweigert($tabelle->db);
      $tabelle->puffer_leeren();
      return true;
  }

  $tabelle->puffer_leeren();
  return false;
}

function bearb_menu(&$db) {
  
  $jg=new jg(&$db);
  $person =new  personen(&$db);
  $jg->erste_person($_SESSION['mod_absolventen']['uid']);
  $jg->mitjg=1;
  $person->diese($_SESSION['mod_absolventen']['uid']);
?>
  <h2 class="absolventen bearbeiten">Nutzerdaten bearbeiten</h2>
<p class="absolventen bearbeiten menu">
     Wählen Sie bitte die zu bearbeitenden Daten:
  <ul class="absolventen bearbeiten menu">
    <li class="absolventen bearbeiten menu"><a href="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>?aktion=persformaendern">Allgemeine Daten</a></li>
    <li class="absolventen bearbeiten menu"><a href="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>?aktion=jgform">Jahrgang</a></li>
    <li class="absolventen bearbeiten menu"><a href="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>?aktion=adrform">Adressen</a></li>
    <li class="absolventen bearbeiten menu"><a href="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>?aktion=telform">Telefonnummern</a></li>
    <li class="absolventen bearbeiten menu"><a href="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>?aktion=mailform">Adressen elektronischer Post</a></li>
    <li class="absolventen bearbeiten menu"><a href="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>?aktion=hpform">WWW-Seiten</a></li>
    <li class="absolventen bearbeiten menu"><a href="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>?aktion=austragen">Aus 
        der Datenbank austragen</a></li>
    <li class="absolventen bearbeiten menu"><a href="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>?aktion=logout">Abmelden</a></li>
  </ul>
</p>
<p class="absolventen bearbeiten anzeige">
  <table border="1" class="absolventen anzeige berarbeiten_pers">
     <?php $jg->nurjgprint();
     $person->normprint(); ?>
  </table>
</p>
<?php
    $person->puffer_leeren();
     $jg->puffer_leeren();
}

function persdatenform($db){
  
  $person=new personen($db);
  if (!$person->diese($_SESSION['mod_absolventen']['uid'])) bearb_verweigert($db);
?>
<p class="absolventen bearbeiten menu">Auswahl:
  <ul class="absolventen bearbeiten menu">
     <li class="absolventen bearbeiten menu"><a 
        href="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>?aktion=bearbmenu">Übersicht&nbsp;eigene&nbsp;Daten</a></li>
     <li class="absolventen bearbeiten menu"><a 
        href="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>?aktion=logout">Abmelden</a></li>
  </ul>
</p>
<?php 
  $person->datenformular();
  $person->puffer_leeren();
}

function persdatenaendern($db,$daten,$neu){
  // Personen brauchen wir
  $person=new personen($db);
  // Sicherheitscheck
  if (bearb_sicherheitscheck($person,$daten,$neu,false)) return;
  // Plausibilitätsprüfung (Nutzer kann korrigieren)
  $fehler=$person->checkdaten($daten,$neu);
  if (!empty($fehler)) {
    print('<ul class="absolventen bearbeiten fehler">');
    array_walk($fehler,'bearb_fehlerliste');
    print('</ul>');
    print('<div class="absolventen bearbeiten datenformular">');
    
    $person->formular($neu,$daten,$fehler);
    print('</div>');
    $person->puffer_leeren();
    return;
  }
  if (!empty($daten['pw1'])) $daten['pw']=$daten['pw1'];
  if (!$neu) {
    $person->update($daten);
    setzesitzungsname($daten['vorname'],$daten['aktueller_name'],$daten['geburtsname']);
    $person->puffer_leeren();
    persdatenform($db);
  } else {
    if($_SESSION['mod_absolventen']['uid']=$person->insert($daten)) {
      setzesitzungsname($daten['vorname'],$daten['aktueller_name'],$daten['geburtsname']);
      bearb_menu($db);
    } else {
      print('<ul class="absolventen bearbeiten fehler">');
      print('<li>Daten konnten nicht gespeichert werden</li>');
      print('</ul>');
      print('<div class="absolventen bearbeiten datenformular">');
      
      $person->formular($neu,$daten);
      print('</div>');
    }
  }
  $person->puffer_leeren();
}

function untertabdatenform($tabelle){
  
?>
<p class="absolventen bearbeiten menu">Auswahl:
  <ul class="absolventen bearbeiten menu">
    <li class="absolventen bearbeiten menu"><a 
        href="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>?aktion=bearbmenu">Übersicht&nbsp;eigene&nbsp;Daten</a></li>
    <li class="absolventen bearbeiten menu"><a href="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>?aktion=logout">Abmelden</a></li>
  </ul>
</p>
<?php 
  if ($tabelle->erste_person($_SESSION['mod_absolventen']['uid'])) {
    do {
      print('<div class="absolventen bearbeiten datenformular">' . "\n");
      $tabelle->datenformular();
      print('</div>' . "\n");
    } while ($tabelle->naechste());
  }
  print('<div class="absolventen bearbeiten datenformular">' . "\n");
  $tabelle->formular(true);
  print('</div>' . "\n");
  $tabelle->puffer_leeren();
}

function untertabdatenaendern($tabelle,$daten,$neu){
  // id/uid/Sitzung testen
  if (bearb_sicherheitscheck($tabelle,$daten,$neu)) return;
  // Normale Fehler müssen von der Klasse gefunden werden
  $fehler=$tabelle->checkdaten($daten,$neu);
  if (!empty($fehler)) {
    print('<ul class="absolventen bearbeiten fehler">');
    array_walk($fehler,'bearb_fehlerliste');
    print('</ul>');
    print('<div class="absolventen bearbeiten datenformular">');
    $tabelle->formular($neu,$daten,$fehler);
    print('</div>');
    $tabelle->puffer_leeren();
    return;
  }
  if (!$neu) {
    $tabelle->update($daten);
  } else {
    $tabelle->insert($daten);
  }
  $person=new personen($tabelle->db);
  $person->aktualisiere_akt($daten['uid']);
  untertabdatenform($tabelle);
  $tabelle->puffer_leeren();
}

function untertabdatenloeschen($tabelle,$daten){
  // id/uid/Sitzung testen
  if (bearb_sicherheitscheck($tabelle,$daten,false)) return;
  $tabelle->loeschen($daten['id'],$_SESSION['mod_absolventen']['uid']);
  untertabdatenform($tabelle);
  $tabelle->puffer_leeren();
}

function austragen($db,$daten) {
  
  $person =new  personen($db);
  $jg=new jg($db);
  if (isset($daten['wirklich']) || isset($daten['austrageid'])) {
    if (bearb_sicherheitscheck($person,$daten,false,false)) return;
    if (!isset($daten['wirklich']) || $daten['wirklich']!='ja' || !isset($_SESSION['mod_absolventen']['uid']) ||
	!isset($daten['austrageid']) || !isset($_SESSION['mod_absolventen']['austrageid'])
	|| ($_SESSION['mod_absolventen']['austrageid']!=$daten['austrageid']) ||
	!ereg("^" . $_SESSION['mod_absolventen']['uid'] . '+',$daten['austrageid']) ||
	!isset($daten['id']) || $_SESSION['mod_absolventen']['uid']!=$daten['id']){
  ?>
 <ul class="absolventen bearbeiten fehler"><li>Sie wurden <em>nicht</em> 
    aus der Datenbank ausgetragen.</li></ul>
       <?php    
          unset($_SESSION['mod_absolventen']['austrageid']);
          bearb_menu($db);
	  $person->puffer_leeren();
          return;
    }
    if ($_SESSION['mod_absolventen']['austrageid']==$daten['austrageid'] &&
	$_SESSION['mod_absolventen']['uid']==$daten['id']) {
      if (! $person->loeschen($daten['id'])) {
  ?><p class="absolventen bearbeiten austragen status">
<strong class="absolventen bearbeiten austragen status">
Sie wurden aus der Datenbank ausgetragen.</strong>
</p>
       <?php    
        logout($db);
        select_jgs($db);
      } else {
  ?><p class="absolventen bearbeiten austragen status">
<strong class="absolventen bearbeiten fehler">Beim Austragen ist ein Fehler aufgetreten.<br />
Sie wurden <em>nicht</em> aus der Datenbank ausgetragen.</strong>
</p>
       <?php    
	bearb_menu($db);
      }
    }
  } else {
    $_SESSION['mod_absolventen']['austrageid']=uniqid($_SESSION['mod_absolventen']['uid'] . "+");
    $jg->erste_person($_SESSION['mod_absolventen']['uid']);
    $jg->mitjg=1;
    $person->diese($_SESSION['mod_absolventen']['uid']);
?><h2 class="absolventen bearbeiten austragen">Austragen</h2>
<p class="absolventen bearbeiten austragen"><strong 
     class="absolventen bearbeiten austragen">Ihre kompletten Daten werden gelöscht.</strong>
     <br />Sind Sie sich wirklich sicher?
</p>
<form method="post" action="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>" class="absolventen bearbeiten austragen">
  <input type="hidden" name="austrageid" value="<?=$_SESSION['mod_absolventen']['austrageid']?>" />
  <input type="hidden" name="id" value="<?=$_SESSION['mod_absolventen']['uid']?>" />
  <input type="hidden" name="aktion" value="austragen" />
  <div class="absolventen bearbeiten austragen formular abs-ja-nein"> 
     <div class="absolventen bearbeiten formular austragen radio abs-ja"><input 
         type="radio" name="wirklich" value="ja" id="abs-ja"  
         class="absolventen bearbeiten formular austragen"/><label 
         class="absolventen bearbeiten formular austragen radio abs-ja" for="abs-ja">Ja</label></div>
     <div class="absolventen bearbeiten formular austragen radio abs-ja"><input 
         type="radio" name="wirklich" value="nein" id="abs-nein" 
         checked="checked" class="absolventen bearbeiten formular austragen" /><label 
         for="abs-nein" class="absolventen bearbeiten formular austragen radio abs-nein">Nein</label></div>
     <div class="absolventen bearbeiten austragen knoepfe"><input type="submit" 
         value="Weiter" class="absolventen bearbeiten austragen knoepfe"/></div>
  </div>
</form>
<p class="absolventen bearbeiten anzeige">
  <table border="1" class="absolventen bearbeiten anzeige anzeige_jg">
     <?php $jg->nurjgprint();
     $person->normprint(); ?>
  </table>
</p>
<?php
    $person->puffer_leeren();
    $jg->puffer_leeren();
  }
}
?>
