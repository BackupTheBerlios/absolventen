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

class adresse {
  var $db;
  var $sql;
  var $Werte;
  var $Qresult;
  
  function adresse ($h_db=0) {
    $this->db=$h_db;
  }

  function puffer_leeren() {
    if ($this->Qresult) {
      $this->db->puffer_leeren($this->Qresult);
      $this->Qresult=0;
    }
  }

  function erste_person($person){
    $this->puffer_leeren();
    $sql="select id,uid,anfang,plz,ort,ende from StAgAdr where uid=" . $person;
    if (!$this->Qresult=$this->db->query($sql)){
      fehler('adresse-&gt;erste_person(' . $person . ')');
      return false;
    }
    $this->Werte=$this->db->fetch_array($this->Qresult);
    return ($this->Werte && true);
  }

  function naechste(){
    return $this->Werte=$this->db->fetch_array($this->Qresult);
  }

  /* die einzelnen Felder der Person */

  function id() {
    return $this->Werte["id"];
  }

  function uid() {
    return $this->Werte["uid"];
  }

  function anfang() {
    return $this->Werte["anfang"];
  }

  function plz() {
    return $this->Werte["plz"];
  }

  function ort() {
    return $this->Werte["ort"];
  }

  function ende() {
    return $this->Werte["ende"];
  }

  function formular() {
    return $this->Werte["formular"];
  }

  function erstprint($telefon){
    if ($this->ende()) $zeilen=3; else $zeilen=2;
    printf('<td colspan="2">%s</td><td rowspan="%d">',$this->anfang(),$zeilen);
    if ($telefon->erste_adresse($this->id())) {
            $telefon->nurtelprint();
    }
    print('</td>');
    return $zeilen;
  }

  function zweitprint(){
    printf('<td>%s</td><td>%s</td>',$this->plz(),$this->ort());
  }
  
  function drittprint(){
    printf('<td colspan="2">%s</td>',$this->ende());
  }
  
  function normprint($telefon,$erstspalte=""){
    do {
  ?><tr><?=$erstespalte?><td colspan="2"></td><?php
       $zeilen=$this->erstprint($telefon);
    ?></tr>
<tr><?=$erstespalte?><td colspan="2"></td><?=$this->zweitprint()?></tr>
       <?php if ($zeilen==3) {
?><tr><?=$erstespalte?><td colspan="2"></td><?=$this->dittprint()?></tr>
       <?php 
       }
    }  while ($this->naechste());
  }
}
?>