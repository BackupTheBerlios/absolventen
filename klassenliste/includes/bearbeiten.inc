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
     <th><a href="<?=$PHP_SELF?>?aktion=persformaendern">Allgemeine Daten</a></th>
     </tr>
     <tr>
     <th><a href="<?=$PHP_SELF?>?aktion=jgform">Jahrgang</a></th>
     </tr>
     <tr>
     <th><a href="<?=$PHP_SELF?>?aktion=adrform">Adressen</a></th>
     </tr>
     <tr>
     <th>Telefonnummer</th>
     </tr>
     <tr>
     <th>Adresse elektronischer Post</th>
     </tr>
     <tr>
     <th>WWW-Seiten</th>
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
  echo '</td></tr></table>';
  $tabelle->puffer_leeren();
}

function jgdatenaendern($db,$daten){
  $jahrgang=new jg($db);
  if ($daten['id']) {
    $jahrgang->dieser($daten['id']);
    if ($daten['uid'] != $_SESSION['uid']){
      print('<strong>Zugriff verweigert!</strong>');
      select_jgs($db);
      return;
    }  
  }
  $fehler=$jahrgang->checkdaten($daten);
  if ($fehler) {
    printf("<strong>%s</strong>",$fehler);
    $jahrgang->formular($daten);
    return;
  }
  if ($daten['id']) {
    $jahrgang->update($daten);
    $jahrgang->puffer_leeren();
  } else {
    $jahrgang->insert($daten);
  }
  $person=new personen($db);
  $person->aktualisiere_akt($daten['uid']);
  jgdatenform($db);
}
function adrdatenaendern($db,$daten){
  $adresse=new adresse($db);
  if ($daten['id']) {
    $adresse->diese($daten['id']);
    if ($daten['uid'] != $_SESSION['uid']){
      print('<strong>Zugriff verweigert!</strong>');
      select_jgs($db);
      return;
    }  
  }
  $fehler=$adresse->checkdaten($daten);
  if ($fehler) {
    printf("<strong>%s</strong>",$fehler);
    $adresse->formular($daten);
    return;
  }
  if ($daten['id']) {
    $adresse->update($daten);
    $adresse->puffer_leeren();
  } else {
    $adresse->insert($daten);
  }
  $person=new personen($db);
  $person->aktualisiere_akt($daten['uid']);
  adrdatenform($db);
}

function untertabdatenloeschen($tabelle,$daten){
  $tabelle->diese($daten['id']);
  if ($tabelle->uid() != $_SESSION['uid']){
    print('<strong>Zugriff verweigert!</strong>');
    select_jgs($tabelle->db());
    return;
  }  
  $tabelle->loeschen($daten['id'],$daten['uid']);
  adrdatenform($db);
}

?>