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

class telefon {
  var $db;
  var $sql;
  var $Werte;
  var $Qresult;
  
  function telefon ($h_db) {
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
    $sql="select id,uid,aid,vorwahl,telefon,kommentar"
      . "from StAgTel where uid=" . $person;
    $this->Qresult=$this->db->query($sql);
    $this->Werte=$this->db->fetch_array($this->Qresult);
    return ($this->Werte && true);
  }

  function erste_person_ohne_adr($person){
    $sql="select id,uid,aid,vorwahl,telefon,kommentar"
      . " from StAgTel where uid=" . $person
      . " and aid is null";
    $this->Qresult=$this->db->query($sql);
    $this->Werte=$this->db->fetch_array($this->Qresult);
    return ($this->Werte && true);
  }

  function erste_adresse($aid){
    $sql="select id,uid,aid,vorwahl,telefon,kommentar"
      . " from StAgTel where aid=" . $aid;
    $this->Qresult=$this->db->query($sql);
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

  function aid() {
    return $this->Werte["aid"];
  }

  function vorwahl() {
    return $this->Werte["vorwahl"];
  }

  function telefon_nr() {
    return $this->Werte["telefon"];
  }
  
  function kommentar() {
    return isset($this->Werte["kommentar"])?$this->Werte["kommentar"]:"";
  }

  function nurtelprint() {
    printf('(%s) %s %s',$this->vorwahl(),$this->telefon_nr(),$this->kommentar());
    while ($this->naechste())
      printf('<br />(%s) %s %s',
	     $this->vorwahl(),$this->telefon_nr(),$this->kommentar());
  }

  function normprint($erstspalte=""){
    do {
      printf('<tr><td colspan="4"></td><td>(%s) %s %s</td></tr>',
	     $this->vorwahl(),$this->telefon_nr(),$this->kommentar());
    }while ($this->naechste());
  }
}
?>