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

class email {
  var $db;
  var $sql;
  var $Werte;
  var $Qresult;
  
  function email ($h_db=0) {
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
    $sql="select id,uid,adresse,name,link,encode,formular "
      . "from StAgMail where uid=" . $person;
    if (!$this->Qresult=$this->db->query($sql)){
      fehler('email-&gt;erste_person(' . $person . ')');
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

  function adresse() {
    return $this->Werte["adresse"];
  }

  function name() {
    return $this->Werte["name"];
  }

  function link() {
    return $this->Werte["link"];
  }

  function encode() {
    return $this->Werte["encode"];
  }

  function formular() {
    return $this->Werte["formular"];
  }

  
  function normprint($erstspalte=""){
    if ($this->encode()) 
      $adr=str_replace(array("@","."),
		       array(" AUF "," PUNKT "),
		       $this->adresse());
    else $adr=$this->adresse();
    if ($this->name()) 
      print($this->name() . ": ");
    if ($this->link())
      printf('<a href="mailto:%s">%s</a>',$adr,$adr);
    else 
      print($adr);
    while ($this->naechste()) {
      print ("<br />\n");
      if ($this->encode()) 
	$adr=str_replace(array("@","."),
			 array(" AUF "," PUNKT "),
			 $this->adresse());
      else $adr=$this->adresse();
      if ($this->name()) 
	print($this->name() . ": ");
      if ($this->link())
	printf('<a href="mailto:%s">%s</a>',$adr,$adr);
      else 
	print($adr);
    }
  }
}
?>