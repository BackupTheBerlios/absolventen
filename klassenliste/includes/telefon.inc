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

class telefon extends dbtabelle{
  function sql($funktion,$args){
    global $mysql_daten;
    switch ($funktion) {
	case "erste_person": 
		return sprintf("select id,uid,aid,vorwahl,telefon,kommentar"
		               . " from %s where uid=%d",
			$mysql_daten['TelTab'],$args);
  	case "diese": 
		return sprintf("select id,uid,aid,vorwahl,telefon,kommentar"
			       . " from %s where id=%d",
			$mysql_daten['TelTab'],$args);
	case "insert":
		return sprintf("insert into %s (%suid,aid,vorwahl,telefon,kommentar"
			       . ") values (%s%d,%s,'%s','%s','%s')",
			       $mysql_daten['TelTab'],
			       $args['id']?"id,":"",
			       $args['id']?$args['id'] . ',':"",
			       $args['uid'],
			       $args['aid']?sprintf("%d",$args['aid']):"NULL",
			       addslashes($args['vorwahl']),
			       addslashes($args['telefon']),
			       addslashes($args['kommentar']));
	case "update":
		return sprintf("update %s set uid=%d,aid=%s,vorwahl='%s',telefon='%s',kommentar='%s'"
			       . " where id=%d",
			       $mysql_daten['TelTab'],
			       $args['uid'],
			       $args['aid']?sprintf("%d",$args['aid']):"NULL",
			       addslashes($args['vorwahl']),
			       addslashes($args['telefon']),
			       addslashes($args['kommentar']),
			       $args['id']);
	case "loeschen":
	        return sprintf("delete from %s where id=%d",$mysql_daten['TelTab'],$args);
    }
  }
	
  function telefon ($h_db) {
    $this->dbtabelle($h_db);
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

  function insert($daten) {
    $this->puffer_leeren();
    if ($daten['id'] && !ereg('^[0-9]*$',$daten['id'])) {
      return -1;
    }
    return $this->insert_backend($this->sql("insert",$daten),$daten['uid']);
  }

  function update($daten) {
    $this->puffer_leeren();
    if (!$daten['id'] || !ereg('^[0-9]*$',$daten['id'])) {
      return -1;
    }
    return $this->update_backend($this->sql("update",$daten),$daten['uid']);
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
  /* adresse,name */

  function formular($daten=0) {
    if (!$daten) $daten=array('uid' => $_SESSION['uid']);
    $adressen=new adresse($this->db);
    $adressen->erste_person($daten['uid']);
?>
<form method="post" action="<?=$PHP_SELF?>">
<input type="hidden" name="aktion" 
   value="<?=$daten['id']?"teldbaendern":"teldbneu"?>" />
   <?php if ($daten['id']) { ?>
<input type="hidden" name="id" value="<?=$daten['id']?>" />
			  <?php } ?>
<input type="hidden" name="uid" value="<?=$daten['uid']?>" />
<table border="0">
<tr><td>Adresse</td><td>
      <p>
      <input type="radio" name="aid" value="" /> Keine 
   </p>
   <?php do { ?><p>
      <input type="radio" name="aid" value="<?=$adressen->id();?>" 
	      <?=$daten['aid']==$adressen->id()?"checked=\"1\"":""?> /><?=$adressen->anfang()?><br>
	      <?=$adressen->plz()?>&nbsp;<?=$adressen->ort()?><br>
	      <?=$adressen->ende()?>
	      </p>
<?php } while ($adressen->naechste()); ?>
</td></tr>
<tr><td>Vorwahl</td><td>
<input type="text" size=30 name="vorwahl" value="<?=$daten['vorwahl']?>" /></td></tr>
<tr><td>Telefon</td><td>
<input type="text" size=30 name="telefon" value="<?=$daten['telefon']?>" /></td></tr>
<tr><td>Bemerkung</td><td>
<input type="text" size=30 name="kommentar" value="<?=$daten['kommentar']?>" /></td></tr>
<tr><td colspan="2" align="center">
   <input type="submit" 
   value="<?=$daten['id']?"&Auml;ndern":"Einf&uuml;gen"?>" />&nbsp;<input
   type="reset" value="Zur&uuml;cksetzen" /></td></tr>
</table>
</form>
<?php if ($daten['id']) { ?>
<form method="post" action="<?=$PHP_SELF?>">
<input type="hidden" name="aktion" value="teldbloeschen" />
<input type="hidden" name="id" value="<?=$daten['id']?>" />
   <input type="submit"  value="L&ouml;schen" />
</form>
<?php
      $adressen->puffer_leeren();
    }
  }

  function checkdaten($daten) {
    //    global $klasse;
    $fehler="";
    if (!ereg("^[0-9]*$",$daten['id'])) 
      $fehler.="<br />Fehlerhafte id";
    if (!ereg("^[0-9]*$",$daten['uid']))
      $fehler.="<br />Fehlerhafte uid";
    if (!($daten['uid']==$_SESSION['uid']))
      $fehler.="<br />Ung&uuml;ltige Nutzeridentifikation";
    if ($daten['aid']) {
      if (!ereg('^[0-9]*$',$daten['aid']))
	$fehler.="<br />Ung&uuml;ltige Adresse";
      $adressen=new adresse($this->db);
      $adressen->diese($daten['aid']);
      if ($adressen->uid()!=$daten['uid']) 
	$fehler.="<br />Ung&uuml;ltige Adresse";
    }
    return $fehler;
  }
}
?>