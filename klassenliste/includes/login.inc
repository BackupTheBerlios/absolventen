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

function anzeige_login($daten=0){
?>
<form method="post" action="<?$PHP_SELF?>">
<input type="hidden" name="aktion" value="dologin" />
<table border=1>
   <tr><td>Nutername:</td>
   <td><input type="text" name="nutzername" 
   value="<?=$daten['nutzername']?>" size="10" /></td></tr>
   <tr><td>Passwort:</td>
<td><input type="password" name="passwort" value="" size="10"/></td></tr>
<tr><td colspan="2" align="center">
<input type="submit" value="Einloggen" />
<input type="reset" value="Zur&uuml;cksetzen" /></td></tr>
</table>
</form>

<?php
}

function tue_login($daten,$db){
  $person=new personen($db);
  if ($person->pruefe_login($daten['nutzername'],$daten['passwort'])){
    $_SESSION['uid']=$person->id();
    $_SESSION['name']=$person->vorname() . " " . $person->aktueller_name()
      . ($person->geburtsname()!=$person->aktueller_name()?" geb. " .
      $person->geburtsname():""); 
    bearb_menu($db);
  } else anzeige_login($daten);
  $person->puffer_leeren();
}


?>