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

class adresse extends dbtabelle{
  function sql($funktion,$args){
    global $mysql_daten;
    switch ($funktion) {
	case "erste_person": 
		return sprintf("select id, uid, anfang, plz, ort, ende from %s where uid=%d",
			$mysql_daten['AdrTab'],$args);
  	case "diese": 
		return sprintf("select id,uid,anfang,plz,ort,ende from %s where id=%d",
			$mysql_daten['AdrTab'],$args);
	case "insert":
		return sprintf("insert into %s (%suid,anfang,plz,ort,ende"
		 	. ") values (%s%d,'%s','%s','%s','%s')",
			 $mysql_daten['AdrTab'],
			 $args['id']?"id,":"",
			 $args['id']?$args['id'] . ',':"",
			 $args['uid'],
			 addslashes($args['anfang']),
			 addslashes($args['plz']),
			 addslashes($args['ort']),
			 addslashes($args['ende']));
	case "update":
		return sprintf("update %s set uid=%d,anfang='%s',plz='%s',"
		 . "ort='%s',ende='%s'"
		 . " where id=%d",
		 $mysql_daten['AdrTab'],
		 $args['uid'],
		 addslashes($args['anfang']),
		 addslashes($args['plz']),
		 addslashes($args['ort']),
		 addslashes($args['ende']),
		 $args['id']);
	case "loeschen":
	        return sprintf("delete from %s where id=%d",$mysql_daten['AdrTab'],$args);
    }
  }
	
  function adresse ($h_db=0) {
    $this->dbtabelle($h_db);
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

  function loeschen($id,$uid){
	return parent::loeschen($id,$uid);
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

  function formular($daten=0) {
    if (!$daten) $daten=array('uid' => $_SESSION['uid']);
?>
<form method="post" action="<?=$PHP_SELF?>">
<input type="hidden" name="aktion" 
   value="<?=$daten['id']?"adrdbaendern":"adrdbneu"?>" />
   <?php if ($daten['id']) { ?>
<input type="hidden" name="id" value="<?=$daten['id']?>" />
			  <?php } ?>
<input type="hidden" name="uid" value="<?=$daten['uid']?>" />
<table border="0">
<tr><td>Anfang der Adresse</td><td>
<textarea cols=30 rows=2 name="anfang"><?=preg_replace("/<br[^>]*>/i","",$daten['anfang'])?></textarea></td></tr>
<tr><td>PLZ&nbsp;Ort</td><td>
<input type="text" size=5 name="plz" value="<?=$daten['plz']?>" 
/>&nbsp;<input type="text" size=20 name="ort" value="<?=$daten['ort']?>" />
</td></tr>
<tr><td>Weiteres zu dieser Adresse (z.B. Land)</td><td>
<textarea cols=30 rows=2 
name="ende"><?=preg_replace("/<br[^>]*>/i","",$daten['ende'])?></textarea>
</td></tr>
<tr><td colspan="2" align="center">
   <input type="submit" 
   value="<?=$daten['id']?"&Auml;ndern":"Einf&uuml;gen"?>" />&nbsp;<input
   type="reset" value="Zur&uuml;cksetzen" /></td></tr>
</table>
</form>
<?php if ($daten['id']) { ?>
<form method="post" action="<?=$PHP_SELF?>">
<input type="hidden" name="aktion" value="adrdbloeschen" />
<input type="hidden" name="id" value="<?=$daten['id']?>" />
   <input type="submit"  value="L&ouml;schen" />
</form>
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
    if (!($daten['uid']==$_SESSION['uid']))
      $fehler.="<br />Ung&uuml;ltige Nutzeridentifikation";
    return $fehler;
  }

}
?>
