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

class personen {
  var $db;
  var $sql;
  var $Werte;
  var $Qresult;
  
  function personen ($h_db=0) {
    $db=$h_db;
  }

  function erste_jahrgang($jahrgang,$klasse,$drin){
    $sql="select StAg.id as "
      . "id,aktueller_name,geburtsname,vorname,kommentar,"
      . "DATE_FORMAT(aktualisierung,'%d.%m.%Y %T') as aktualisierung "
      . "from StAg,StAgJg"
      . " where StAgJg.jahrgang=" . $jahrgang 
      . " and StAgJg.klasse='" . $klasse
      . "' and StAgJg.drin=". $drin
      . " and StAgJg.uid=StAg.id"
      . " order by geburtsname,vorname,aktueller_name";
    $Qresult=$db->query($sql);
    $Werte=$db->fetch_array($Qresult);
    return ($Werte!=false);
  }

  function naechste(){
    $Werte=$db->fetch_array($Qresult);
  }

  /* die einzelnen Felder der Person */

  function id() {
    return Werte["id"];
  }

  function aktueller_name() {
    return Werte["aktueller_name"];
  }

  function geburtsname() {
    return Werte["geburtsname"];
  }

  function vorname() {
    return Werte["vorname"];
  }

  function kommentar() {
    return Werte["kommentar"];
  }

  function aktualisierung() {
    return Werte["aktualisierung"];
  }
  
  function normprint($erstspalte=""){
?>
<tr><?=$erstespalte?><td><?=geburtsname()?></td><td><?=vorname()?></td><td colspan=2></td><td></td><td></td></tr>    
<tr><td></td><td><?=aktueller_name()?></td><td></td><td colspan=2></td></tr>
<tr><td colspan="2" valign="bottom"><font size="-2"><?=aktualisierung()?></font></td><td colspan="4">%s</td></tr>
<?php
   if (kommentar()) {
     ?><tr><td colspan=6><?=kommentar()?></td></tr>
<?php
   }
  }
}
?>