<?php /* $Id: login.inc,v 1.5 2004/07/19 22:36:31 keinstein Exp $
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

$Log: login.inc,v $
Revision 1.5  2004/07/19 22:36:31  keinstein
globale Variablen -> $GLOBALS
Formular formatiert und xhtml-fähig gemacht

Revision 1.4  2004/07/15 11:48:50  keinstein
Formular mit klassen
$_SESSION umbenannt
setzesitzungsname(): neu
tue_login(): nutze setzesitzungsname();

*/ 

function anzeige_login($daten=0){
  
?>
<form method="post" action="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>" class="absolventen login formular">
<input type="hidden" name="aktion" value="dologin" />
<table border="0" class="absolventen login formular" >
  <tr class="absolventen login formular login_name">
     <th class="absolventen login formular login_name"><label 
         for="abs_login" class="absolventen login formular login_name">Nutzername</label></th>
     <td class="absolventen login formular login_name"><input type="text" name="nutzername" 
         class="absolventen login formular login_name" id="abs_login"
          value="<?=$daten['nutzername']?>" size="10" /></td>
  </tr>
  <tr class="absolventen login formular login_pw">
    <th class="absolventen login formular login_pw"><label 
        for="abs_pw" class="absolventen login formular login_name">Passwort</label></th>
    <td class="absolventen login formular login_pw"><input type="password" name="passwort" 
        class="absolventen login formular login_pw" value="" size="10" id="abs_pw" /></td>
  </tr>
   <tr class="absolventen login formular knoepfe">
     <td class="absolventen login formular knoepfe" colspan="2" align="center"><input 
         type="submit" value="Einloggen" class="absolventen login formular senden knoepfe" />&nbsp;<input 
         type="reset" value="Zur&uuml;cksetzen" class="absolventen login formular knoepfe" /></td>
  </tr>
</table>
</form>
<?php
}

function setzesitzungsname($vorname,$aktueller_name,$geburtsname) {
    $_SESSION['mod_absolventen']['name']=sprintf("%s %s%s",
			      $vorname,
			      $aktueller_name,
			      ($geburtsname!=$aktueller_name?
			       " geb. " . $geburtsname:"")); 
}

function tue_login($daten,&$db){
  $person=new personen(&$db);
  if ($person->pruefe_login($daten['nutzername'],$daten['passwort'])){
    $_SESSION['mod_absolventen']['uid']=$person->id();
    setzesitzungsname($person->vorname(),$person->aktueller_name(),$person->geburtsname());
  } else {
    unset($_SESSION['mod_absolventen']['uid']);
    $_SESSION['mod_absolventen']['name']='<strong class="absolventen login fehler">fehlgeschlagene Anmeldung</strong>';
  }
  $person->puffer_leeren();
}

function logout($db) {
  unset($_SESSION['mod_absolventen']['uid']);
  unset($_SESSION['mod_absolventen']['name']);
}

?>
