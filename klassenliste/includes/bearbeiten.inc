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
<table border=0>
     <tr>
     <th><a href="<?=$PHP_SELF?>?aktion=persformaendern">Allgemeine Daten</a></th>
     </tr>
     <tr>
     <th>Jahrgang</th>
     </tr>
     <tr>
     <th>Adresse</th>
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
<table border=1>
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
      seitenanfang();
      print('<strong>Zugriff verweigert!</strong>');
      select_jgs($db);
      seitenende();
      return;
    }  
  }
  $fehler=$person->checkdaten($daten,!$daten['id']);
  if ($fehler) {
    seitenanfang();
    printf("<strong>%s</strong>",$fehler);
    $person->formular($daten);
    seitenende();
    return;
  }
}

?>