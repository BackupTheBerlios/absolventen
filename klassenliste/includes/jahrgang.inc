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

class jahrgang {
  var $db;
  var $sql;
  var $Werte;
  var $Qresult;
  var $personen;
  var $mitjg;
  
  function jahrgang ($h_db=0) {
    $db=$h_db;
    $mitjg=0;
  }

  function erste_jahrgang($jahrgang){
    $sql="select jahrgang,klasse,drin "
      . "from StAgJg"
      . " where jahrgang=" . $jahrgang
      . " order by jahrgang,drin,klasse desc";
    $Qresult=$db->query($sql);
    $Werte=$db->fetch_array($Qresult);
    return ($Werte!=false);
  }

  function naechste(){
    $Werte=$db->fetch_array($Qresult);
  }


  function personen(){
    var $pers;

    $pers = new personen($db);
    $pers->erste_jahrgang(jahrgang(),klasse(),drin());
    return $pers;
  }


  /* die einzelnen Felder der Person */

  function jahrgang() {
    return Werte["jahrgang"];
  }

  function klasse() {
    return Werte["klasse"];
  }

  function drin() {
    return Werte["drin"];
  }

  function normprint($erstspalte=""){
    var $jgstring="";
    var $spalten;
    var $personen;

    if ($erstespalte) {
      $spalten=7;
    } else {
      $spalten=6;
    }
    if ($mitjg) {
      $jgstring .="Jahrgang " . jahrgang() . " ";
    }
    if (klasse()) {
      $jgstring .= klasse() . "-Zug";
    }
    if (!drin()) $jgstring .= " sonstige zugeh&ouml;rige Personen";
      ?>
<tr><th colspan="<?=$spalten?>" align="center"><?=$jgstring?></th></tr>
   <?php
   $personen=personen();
    while ($personen->Werte) {
      $personen->normprint($erstespalte);
      $personen->naechste();
    }
   }
  }
}
?>