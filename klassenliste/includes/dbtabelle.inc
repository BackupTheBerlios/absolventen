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

class dbtabelle {
  var $db;
  var $Werte;
  var $Qresult;
  
  function dbtabelle ($h_db=0) {
    $this->db=$h_db;
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

  function erste_person($person){
    return $this->select_backend($this->sql('erste_person',$person));
  }

  function diese($id){
    return $this->select_backend($this->sql('diese', $id));
   }

  function select_backend($sql) {
    $this->puffer_leeren();
    if (!$this->Qresult=$this->db->query($sql)){
      fehler('dbtabelle-&gt;select_backend(' . $sql . ')');
      return false;
    }
    $this->Werte=$this->db->fetch_array($this->Qresult);
    return ($this->Werte && true);
  }

  function naechste(){
    return $this->Werte=$this->db->fetch_array($this->Qresult);
  }

  function insert_backend($sql,$uid=0) {
    $this->puffer_leeren();
    if (!$this->Qresult=$this->db->query($sql)) {
      fehler("dbtabelle-&gt;insert_backend(" . $sql . "," . $aktpers . ")");
      return -2;
    } 
    $id=$this->db->insert_id();
    if ($uid) {
      $person=new personen($this->db);
      $person->aktualisiere_akt($uid);
    }
    @$this->puffer_leeren();
    return $id;
  }

  function update_backend($sql,$uid=0) {
    $this->puffer_leeren();
    if (!$this->Qresult=$this->db->query($sql)) {
      fehler("adresse-&gt;update(" . $daten . ")");
      return -2;
    }
    if ($uid) {
      $person=new personen($this->db);
      $person->aktualisiere_akt($uid);
    }
    @$this->puffer_leeren();
    return 0;
  }

  function loeschen($id,$uid=0){
    $this->puffer_leeren();
    if ($id) {
      $query=$this->sql('loeschen',$id);
    } else {
      if ($uid) {
	$query=$this->sql('persloeschen',$uid);
      } else return -3;
    }
    echo $query . "<br>";
    if (!$this->Qresult=$this->db->query($query)) {
      fehler("dbtabelle-&gt;loeschen(" . $id . ")");
      return -2;
    }
    if ($uid) {
      $person=new personen($this->db);
      $person->aktualisiere_akt($uid);
    }
    @$this->puffer_leeren();
    return 0;
  }

  /* die einzelnen Felder der Person */

  function id() {
    return $this->Werte["id"];
  }

  function uid() {
    return $this->Werte["uid"];
  }

  function datenformular() {
    $this->formular($this->Werte);
  }

}
?>
