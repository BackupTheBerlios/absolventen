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

class jg{
  var $db;
  var $sql;
  var $Werte;
  var $Qresult;
  var $personen;
  var $mitjg;
  
  function jg($h_db=0) {
    $this->db=$h_db;
    $this->mitjg=0;
  }

  function dbset($hdb) {
    $this->db=$hdb;
  }

  function puffer_leeren() {
    if ($this->Qresult) {
      $this->db->puffer_leeren($this->Qresult);
      $this->Qresult=0;
    }
  }

  function erste_jahrgang($jahrgang){
    $this->puffer_leeren();
    $sql="select distinct jahrgang,klasse,drin "
      . "from StAgJg"
      . " where jahrgang=" . $jahrgang
      . " order by jahrgang,drin desc,klasse";
    if (!$this->Qresult=$this->db->query($sql)) {
      fehler("jahrgang-&gt;erste_jahrgang(" . $jahrgang . ")");
      return false;
    }
    $this->Werte=$this->db->fetch_array($this->Qresult);
    return ($this->Werte != false);
  }

  function erste_person($uid){
    $this->puffer_leeren();
    $sql="select distinct jahrgang,klasse,drin "
      . "from StAgJg"
      . " where uid=" . $uid
      . " order by jahrgang,drin desc,klasse";
    if (!$this->Qresult=$this->db->query($sql)) {
      fehler("jahrgang-&gt;erste_person(" . $uid . ")");
      return false;
    }
    $this->Werte=$this->db->fetch_array($this->Qresult);
    return ($this->Werte != false);
  }

  function erste_nur_jahrgang(){
    $this->puffer_leeren();
    $sql="select distinct jahrgang "
      . "from StAgJg"
      . " order by jahrgang";
    if (!$this->Qresult=$this->db->query($sql)){
      fehler("jahrgang-&gt;erste_nur_jahrgang(" . $jahrgang . ")");
      return false;
    }
    $this->Werte=$this->db->fetch_array($this->Qresult);
    return ($this->Werte != false);
  }

  function naechste(){
    $this->Werte=$this->db->fetch_array($this->Qresult);
    return ($this->Werte!=false);
  }


  function personen(){
    $pers = new personen($this->db);
    $pers->erste_jahrgang($this->jahrgang(),$this->klasse(),$this->drin());
    return $pers;
  }


  /* die einzelnen Felder der Person */

  function jahrgang() {
    return $this->Werte["jahrgang"];
  }

  function klasse() {
    return $this->Werte["klasse"];
  }

  function drin() {
    return $this->Werte["drin"];
  }

  function normprint($erstspalte=""){
    global $layout;
    $personen=new personen($this->db);

    if ($erstespalte) {
      $spalten=6;
    } else {
      $spalten=5;
    }

    do {
      $jgstring="";
      
      if ($this->mitjg) 
	$jgstring .="Jahrgang " . $this->jahrgang() . " ";
      if ($this->klasse()) 
	$jgstring .= $this->klasse() . "-Zug";
      if (!$this->drin()) 
	$jgstring .= " sonstige zugeh&ouml;rige Personen";

      if ($jgstring) {
	echo $layout['tabtrenner'];
	?>
<tr><th colspan="<?=$spalten?>" align="center"><?=$jgstring?></th></tr>
   <?php }
      $personen->erste_jahrgang($this->jahrgang(),
				$this->klasse(),$this->drin());
      $personen->normprint($erstespalte);
    } while ($this->naechste());
    $personen->puffer_leeren();
  }

  function nurjgprint($erstspalte=""){
    global $layout;

    if ($erstespalte) {
      $spalten=6;
    } else {
      $spalten=5;
    }

    do {
      $jgstring="";
      
      if ($this->mitjg) 
	$jgstring .="Jahrgang " . $this->jahrgang() . " ";
      if ($this->klasse()) 
	$jgstring .= $this->klasse() . "-Zug";
      if (!$this->drin()) 
	$jgstring .= " sonstige zugeh&ouml;rige Personen";

      if ($jgstring) {
	echo $layout['tabtrenner'];
	?>
<tr><th colspan="<?=$spalten?>" align="center"><?=$jgstring?></th></tr>
   <?php }
    } while ($this->naechste());
  }

  function optionprint($jahrgang=""){
    do {
      printf("<option value=\"%s\" %s>%s</option>\n",$this->jahrgang(),
	     $this->jahrgang()==$jahrgang?" selected":"",$this->jahrgang());
    } while ($this->naechste());
  }
}

?>