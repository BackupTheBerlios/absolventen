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

function bearb_menu($db) {
  $jg=new jg($db);
  $person =new  personen($db);
  $jg->erste_person($_SESSION['uid']);
  $jg->mitjg=1;
  $person->diese($_SESSION['uid']);
?>
  <h2>Nutzerdaten bearbeiten</h2>
<p>
<table border="0">
     <tr>
     <td><a href="<?=$PHP_SELF?>?aktion=persformaendern">Allgemeine Daten</a></td>
     </tr>
     <tr>
     <td><a href="<?=$PHP_SELF?>?aktion=jgform">Jahrgang</a></td>
     </tr>
     <tr>
     <td><a href="<?=$PHP_SELF?>?aktion=adrform">Adressen</a></td>
     </tr>
     <tr>
     <td><a href="<?=$PHP_SELF?>?aktion=telform">Telefonnummer</a></td>
     </tr>
     <tr>
     <td><a href="<?=$PHP_SELF?>?aktion=mailform">Adressen elektronischer Post</a></td>
     </tr>
     <tr>
     <td><a href="<?=$PHP_SELF?>?aktion=hpform">WWW-Seiten</a></td>
     </tr>
     <tr>
     <td><a href="<?=$PHP_SELF?>?aktion=austragen">Aus der Datenbank austragen</a></td>
     </tr>
     <tr>
     <td><a href="<?=$PHP_SELF?>?aktion=logout">Abmelden</a></td>
     </tr>

</table>
</p>
<p>
<table border="1">
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
  $person->diese($_SESSION['uid']);
  $person->datenformular();
  $person->puffer_leeren();
}

function persdatenaendern($db,$daten){
  $person=new personen($db);
  if ($daten['id']) {
    $person->diese($_SESSION['uid']);
    if ($daten['id'] != $_SESSION['uid']){
      print('<strong>Zugriff verweigert!</strong>');
      select_jgs($db);
      return;
    }  
  }
  $fehler=$person->checkdaten($daten,!$daten['id']);
  if ($fehler) {
    printf("<strong>%s</strong>",$fehler);
    $person->formular($daten);
    return;
  }
  if ($daten['pw1']) $daten['pw']=$daten['pw1'];
  if ($daten['id']) {
    $person->update($daten);
    $person->puffer_leeren();
    persdatenform($db);
  } else {
    $_SESSION['uid']=$person->insert($daten);
    $_SESSION['name']=$daten['vorname'] . " " . $daten['aktueller_name']
      . ($daten['geburtsname']!=$daten['aktueller_name']?" geb. " .
	 $daten['geburtsname']:"");
    bearb_menu($db);
  }
}

function untertabdatenform($tabelle){
  $tabelle->erste_person($_SESSION['uid']);
  echo '<table border="1">';
  do {
    echo '<tr><td align="center">';
    $tabelle->datenformular();
    echo '</td></tr>';
  } while ($tabelle->naechste());
  echo '<tr><td align="center">';
  $tabelle->formular();
  ?></td></tr></table>
<p>
<b><a href="<?=$PHP_SELF?>?aktion=bearbmenu">eigene&nbsp;Daten</a><br>
   <a href="<?=$PHP_SELF?>?aktion=logout">Abmelden</a>
</b>
</p>
<?php 
  $tabelle->puffer_leeren();
}

function untertabdatenaendern($tabelle,$daten){
  if ($daten['id']) {
    $tabelle->diese($daten['id']);
    if ($daten['uid'] != $_SESSION['uid']){
      print('<strong>Zugriff verweigert!</strong>');
      select_jgs($this->db);
      return;
    }  
  }
  $fehler=$tabelle->checkdaten($daten);
  if ($fehler) {
    printf("<strong>%s</strong>",$fehler);
    $tabelle->formular($daten);
    return;
  }
  if ($daten['id']) {
    $tabelle->update($daten);
    $tabelle->puffer_leeren();
  } else {
    $tabelle->insert($daten);
  }
  $person=new personen($tabelle->db);
  $person->aktualisiere_akt($daten['uid']);
  untertabdatenform($tabelle);
}

function untertabdatenloeschen($tabelle,$daten){
  $tabelle->diese($daten['id']);
  if ($tabelle->uid() != $_SESSION['uid']){
    print('<strong>Zugriff verweigert!</strong>');
    select_jgs($tabelle->db);
    return;
  }  
  $tabelle->loeschen($daten['id'],$_SESSION['uid']);
  untertabdatenform($tabelle);
}

function austragen($db,$daten) {
  $person =new  personen($db);
  $jg=new jg($db);
  if ($daten['wirklich']=='nein'||
      ($daten['austrageid'] && ($_SESSION['austrageid']!=$daten['austrageid'] ||
      !ereg("^" . $_SESSION['uid'] . '+',$daten['austrageid']))) ||
      ($daten['uid'] && $_SESSION['uid']!=$daten['uid'])){
?> Sie wurden <em>nicht</em> aus der Datenbank ausgetragen.
<?php    
     unset($_SESSION['austrageid']);
    bearb_menu($db);
    return;
  }
  if ($_SESSION['austrageid'] && $_SESSION['austrageid']==$daten['austrageid'] &&
      $_SESSION['uid']==$daten['uid']) {
    if (! $person->loeschen($daten['uid'])) {
      logout($db);
      select_jgs($db);
    }else {
      bearb_menu($db);
    }
  } else {
    $_SESSION['austrageid']=uniqid($_SESSION['uid'] . "+");
  $jg->erste_person($_SESSION['uid']);
  $jg->mitjg=1;
  $person->diese($_SESSION['uid']);
?><h2>Austragen</h2>
  <p><strong>Ihre kompletten Daten werden gelöscht.</strong></p>
  <form method="post" action="<?=$PHP_SELF?>">
  <input type="hidden" name="austrageid" value="<?=$_SESSION['austrageid']?>" />
  <input type="hidden" name="uid" value="<?=$_SESSION['uid']?>">
  Sind Sie sich wirklich sicher?
  </p>
  <p><input type="radio" name="wirklich" value="ja" id="ja" /> <label for="ja">Ja</label><br>
     <input type="radio" name="wirklich" value="nein" id="nein" checked="1" /> 
     <label for="nein">Nein</label>
  </p>
  <p><input type="submit" value="Weiter"/></p>
  </form>
<p>
<table border="1">
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