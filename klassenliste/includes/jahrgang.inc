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

class jg extends dbtabelle{
  var $personen;
  var $mitjg;

  function jg($h_db=0) {
    $this->dbtabelle($h_db);
    $this->mitjg=0;
    $this->mailformopts="";
  }

  function sql($funktion,$args=0){
    global $mysql_daten;
    switch ($funktion) {
	case "erste_person": 
		return sprintf("select distinct id,uid,jahrgang,klasse,drin "
			       . "from %s"
			       . " where uid=%d"
			       . " order by jahrgang,drin desc,klasse",
			       $mysql_daten['JgTab'],$args);
  	case "diese": 
		return sprintf("select distinct id,uid,jahrgang,klasse,drin "
			       . "from %s"
			       . " where id=%d"
			       . " order by jahrgang,drin desc,klasse",
			       $mysql_daten['JgTab'],$args);
        case "erste_jahrgang": 
	        return sprintf("select distinct jahrgang,klasse,drin "
			       . "from %s"
			       . " where jahrgang=%d"
			       . " order by jahrgang,drin desc,klasse",
   			       $mysql_daten['JgTab'],$args);
        case "erste_nur_jahrgang": 
	        return sprintf("select distinct jahrgang "
			       . "from %s"
			       . " order by jahrgang",
   			       $mysql_daten['JgTab']);
	case "insert":
		return sprintf("insert into %s (%suid,jahrgang,klasse,drin"
			       . ") values (%s%d,%d,'%s',%d)",
			       $mysql_daten['JgTab'],
			       $args['id']?"id,":"",
			       $args['id']?$args['id'] . ',':"",
			       $args['uid'],
			       $args['jahrgang'],
			       addslashes($args['klasse']),
			       $args['drin']);
	case "update":
	       return sprintf("update %s set uid=%d,jahrgang=%d,"
			      . "klasse='%s',drin=%d"
			      . " where id=%d",
			      $mysql_daten['JgTab'],
			      $args['uid'],
			      $args['jahrgang'],
			      addslashes($args['klasse']),
			      $args['drin'],
			      $args['id']);
       case "loeschen":
	 return sprintf("delete from %s where id=%d",$mysql_daten['JgTab'],$args);
       case "persloeschen":
	 return sprintf("delete from %s where uid=%d",$mysql_daten['JgTab'],$args);
    }
  }
	
  function insert($daten) {
    if ($daten['id'] && !ereg('^[0-9]*$',$daten['id'])) {
      return -1;
    }
    return $this->insert_backend($this->sql("insert",$daten),$daten['uid']);
  }

  function update($daten) {
    if (!$daten['id'] || !ereg('^[0-9]*$',$daten['id'])) {
      return -1;
    }
    return $this->update_backend($this->sql("update",$daten),$daten['uid']);
  }

  function dieser($id){
    return $this->diese($id);
  }

  function erste_jahrgang($jahrgang){
    return $this->select_backend($this->sql("erste_jahrgang",$jahrgang));
  }

  function erste_nur_jahrgang(){
    return $this->select_backend($this->sql("erste_nur_jahrgang"));
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

  function mailformopts(){
    $mailformopts=array();
    $personen=new personen($this->db);

    do {
      $personen->erste_jahrgang($this->jahrgang(),
				$this->klasse(),$this->drin());
      $mailformopts=array_merge($mailformopts,$personen->mailformopts());
    } while ($this->naechste());
    $personen->puffer_leeren();
    return $mailformopts;
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
	$jgstring .= $this->klasse();
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
      print_r ($this);
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
<p>Hinweis: Es werden nur Jahrgänge ab 1901 akzeptiert.</p>
<?php
    }
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