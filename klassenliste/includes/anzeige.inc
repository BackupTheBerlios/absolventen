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
  }
?>
<form method="get" action="<?$PHP_SELF?>" enctype="application/x-www-form-urlencoded">
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
  $jg=new jg($db);
  if (!$jg->erste_jahrgang($jahrgang)) { 
    echo "Nix gefunden."; 
    $jg->puffer_leeren();
    return; 
  }
?>
<table border="1">
<tr><th colspan="5"><font size="+2">Jahrgang <?=$jahrgang?></font></th></tr>
<tr align="left"><th>Geburtsname</th><th>Vorname</th><th colspan="2">Adresse erster Teil</th><th>Telefon</th></tr>
<tr align="left"><th></th><th>aktueller Name</th><th>PLZ</th><th>Ort</th><th></th></tr>
<tr align="left"><th colspan="2"></th><th colspan="2">Adresse zweiter Teil</th><th ></th></tr>
<tr align="left"><th colspan="2"><font size="-2">letzte &Auml;nderung</font></th><th colspan="3">Email</th></tr>
<tr align="left"><th colspan="2"></th><th colspan="3">Homepage</th></tr>
<tr align="left"><th colspan="5">Bemerkungen</th></tr>
<?php
  do {
    $jg->normprint();
  }while ($jg->naechste());
  echo "</table>";
  $jg->puffer_leeren();
}
?>