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

class homepage {
  var $db;
  var $sql;
  var $Werte;
  var $Qresult;
  
  function homepage ($h_db=0) {
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
    $sql="select adresse,name from StAgHP where uid=" . $person;
    if(!$this->Qresult=$this->db->query($sql)){
      fehler('homepage-&gt;erste_person(' . $person .')');
      return false;
    }
    $this->Werte=$this->db->fetch_array($this->Qresult);
    return ($this->Werte && true);
  }

  function naechste(){
    return $this->Werte=$this->db->fetch_array($this->Qresult);
  }

  /* die einzelnen Felder der Person */

  function adresse() {
    return $this->Werte["adresse"];
  }

  function name() {
    return $this->Werte["name"];
  }

  
  function normprint($erstspalte=""){
    printf('<a href="%s">%s</a>',$this->adresse(),$this->name());
    while ($this->naechste()) {
      printf("<br />\n" . '<a href="%s">%s</a>',$this->adresse(),$this->name());
    }
  }
}
?>