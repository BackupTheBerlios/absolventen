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

  function diese($id){
    return $this->dieser($id);
  }

  function dieser($id){
    $this->puffer_leeren();
    $sql="select distinct id,uid,jahrgang,klasse,drin "
      . "from StAgJg"
      . " where id=" . $id
      . " order by jahrgang,drin desc,klasse";
    if (!$this->Qresult=$this->db->query($sql)) {
      fehler("jahrgang-&gt;dieser(" . $jahrgang . ")");
      return false;
    }
    $this->Werte=$this->db->fetch_array($this->Qresult);
    return ($this->Werte != false);
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
    $sql="select distinct id,uid,jahrgang,klasse,drin "
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

  function insert($daten) {
    $this->puffer_leeren();
    if ($daten['id'] && !ereg('^[0-9]*$',$daten['id'])) {
      return -1;
    }
    $sql=sprintf("insert into StAgJg (%suid,jahrgang,klasse,drin"
		 . ") values (%s%d,%d,'%s',%d)",
		 $daten['id']?"id,":"",
		 $daten['id']?$daten['id'] . ',':"",
		 $daten['uid'],
		 $daten['jahrgang'],
		 addslashes($daten['klasse']),
		 $daten['drin']);
    if (!$this->Qresult=$this->db->query($sql)) {
      fehler("jg-&gt;insert(" . $daten . ")");
      return -2;
    }
    $person=new personen($this->db);
    $person->aktualisiere_akt($daten['id']);
    $id=@$this->puffer_leeren();
    return $id;
  }

  function update($daten) {
    $this->puffer_leeren();
    if (!$daten['id'] || !ereg('^[0-9]*$',$daten['id'])) {
      return -1;
    }
    $sql=sprintf("update StAgJg set uid=%d,jahrgang=%d,"
		 . "klasse='%s',drin=%d"
		 . " where id=%d",
		 $daten['uid'],
		 $daten['jahrgang'],
		 addslashes($daten['klasse']),
		 $daten['drin'],
		 $daten['id']);
    if (!$this->Qresult=$this->db->query($sql)) {
      fehler("jg-&gt;update(" . $daten . ")");
      return -2;
    }
    $person=new personen($this->db);
    $person->aktualisiere_akt($daten['id']);
    @$this->puffer_leeren();
    return 0;
  }

  function loeschen($id,$uid){
    $this->puffer_leeren();
    $sql=sprintf("delete from StAgJg where id=%d",$id);
    if (!$this->Qresult=$this->db->query($sql)) {
      fehler("jg-&gt;loeschen(" . $id . ")");
      return -2;
    }
    $person=new personen($this->db);
    $person->aktualisiere_akt($uid);
    @$this->puffer_leeren();
    return 0;
  }

  function personen(){
    $pers = new personen($this->db);
    $pers->erste_jahrgang($this->jahrgang(),$this->klasse(),$this->drin());
    return $pers;
  }


  /* die einzelnen Felder der Person */
  function id() {
    return $this->Werte["id"];
  }
  
  function uid() {
    return $this->Werte["uid"];
  }

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
	$jgstring .= $this->klasse();
      if (!$this->drin()) 
	$jgstring .= " sonstige nahestehende Personen";

      if ($jgstring) {
	echo $layout['tabtrenner'];
?><tr><th colspan="<?=$spalten?>" align="center"><?=$jgstring?></th></tr>
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
	$jgstring .= " sonstige nahestehende Personen";

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




function formular($daten=0) {
  global $klasse;
  reset($klasse);
  if (!$daten) $daten=array('uid' => $_SESSION['uid']);
?>
<form method="post" action="<?=$PHP_SELF?>">
<input type="hidden" name="aktion" 
   value="<?=$daten['id']?"jgdbaendern":"jgdbneu"?>" />
<?php if ($daten['id']) { ?>
<input type="hidden" name="id" value="<?=$daten['id']?>" />
			  <?php } ?>
<input type="hidden" name="uid" value="<?=$daten['uid']?>" />
<table border="0">
<tr><td>Jahrgang</td><td><input type="text" name="jahrgang"
   value="<?=$daten['jahrgang']?>" size="4" maxlength="4" /></td></tr>
<tr><td>Klasse</td><td><select name="klasse">
<?php
while (list ($key, $val) = each ($klasse)) {
  printf('<option value="%s"%s>%s</option>',
	 $val,
	 $daten['klasse']==$val?' selected="1"':'',
	 $key);
}
  reset($klasse);
?></select></td></tr>
<tr><td>Verhältnis</td><td><input type="radio" name="drin" value="1" <?=$daten['drin']?'checked="checked" ':''?>/> Zugeh&ouml;rig<br />
<input type="radio" name="drin" value="0" <?=(!$daten['drin'])?'checked="checked" ':''?>/>sonstige nahestehende Person</td></tr>
<tr><td colspan="2" align="center">
   <input type="submit" 
   value="<?=$daten['id']?"&Auml;ndern":"Einf&uuml;gen"?>" />&nbsp;<input
   type="reset" value="Zur&uuml;cksetzen" /></td></tr>
</table>
</form>
<?php if ($daten['id']) { ?>
<form method="post" action="<?=$PHP_SELF?>">
<input type="hidden" name="aktion" value="jgdbloeschen" />
<input type="hidden" name="id" value="<?=$daten['id']?>" />
   <input type="submit"  value="L&ouml;schen" />
</form>
<?php
    }
  }

  function datenformular() {
    $this->formular($this->Werte);
  }

  function checkdaten($daten) {
    global $klasse;
    $fehler="";
    if (!ereg("^[0-9]*$",$daten['id'])) 
      $fehler.="<br />Fehlerhafte id";
    if (!ereg("^[0-9]*$",$daten['uid']))
      $fehler.="<br />Fehlerhafte uid";
    if (!ereg("^[0-9]*$",$daten['jahrgang']))
      $fehler.="<br />Der Jahrgang sollte eine sinnvolle Jahreszahl sein.";
    if (!in_array($daten['klasse'],$klasse)) 
      $fehler.="<br />Ung&uuml;ltige Klasse";
    if (!ereg("^[0-9]*$",$daten['drin']))
      $fehler.="<br />Wie denn nun? Drin oder nicht drin?";
    if (!($daten['uid']==$_SESSION['uid']))
      $fehler.="<br />Ung&uuml;ltige Nutzeridentifikation";
    return $fehler;
  }
}
?>