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

class email  extends dbtabelle{
  function sql($funktion,$args){
    global $mysql_daten;
    switch ($funktion) {
	case "erste_person": 
		return sprintf("select id, uid, adresse, name, link, encode, mailformular"
		               . " from %s where uid=%d",
			$mysql_daten['EmailTab'],$args);
  	case "diese": 
		return sprintf("select id,uid, adresse, name, link, encode, mailformular"
			       . " from %s where id=%d",
			$mysql_daten['EmailTab'],$args);
	case "insert":
		return sprintf("insert into %s (%suid,adresse,name,link,encode,mailformular"
			       . ") values (%s%d,'%s','%s',%d,%d,%d)",
			       $mysql_daten['EmailTab'],
			       $args['id']?"id,":"",
			       $args['id']?$args['id'] . ',':"",
			       $args['uid'],
			       addslashes($args['adresse']),
			       addslashes($args['name']),
			       $args['link'],
			       $args['encode'],
			       $args['mailformular']);
	case "update":
		return sprintf("update %s set uid=%d,adresse='%s',name='%s',"
			       . "link=%d,encode=%d,mailformular=%d"
			       . " where id=%d",
			       $mysql_daten['EmailTab'],
			       $args['uid'],
			       addslashes($args['adresse']),
			       addslashes($args['name']),
			       $args['link'],
			       $args['encode'],
			       $args['mailformular'],			       
			       $args['id']);
	case "loeschen":
	        return sprintf("delete from %s where id=%d",$mysql_daten['EmailTab'],$args);
	case "persloeschen":
	        return sprintf("delete from %s where id=%d",$mysql_daten['EmailTab'],$args);
        case "mailformopts": 
	  return sprintf("select %s.id as id, %s.uid as uid, %s.adresse as adresse, "
			 . "%s.name as name, %s.aktueller_name as aktueller_name, "
			 . "%s.vorname as vorname"
			 . " from %s,%s where %s.uid=%d and %s.id=%d and %s.mailformular=1",
			 $mysql_daten['EmailTab'],$mysql_daten['EmailTab'],
			 $mysql_daten['EmailTab'],$mysql_daten['EmailTab'],
			 $mysql_daten['PersTab'],$mysql_daten['PersTab'],
			 $mysql_daten['EmailTab'],$mysql_daten['PersTab'],
			 $mysql_daten['EmailTab'],$args,
			 $mysql_daten['PersTab'],$args,
			 $mysql_daten['EmailTab']);
      
    }
  }
	
  function email ($h_db=0) {
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

  function mailformular() {
    return $this->Werte["mailformular"];
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

  /* adresse,name,link,encode,mailformular */

  function erste_nurformular($uid) {
    return $this->select_backend($this->sql('mailformopts',$uid));
  }

  function mailformopts() {
    $rueckgabe=array();
    $status=1;
    while ($status) {
      $rueckgabe[sprintf('%s %s %s/%d/%d',
			 urlencode($this->Werte['aktueller_name']),
			 urlencode($this->Werte['vorname']),			 
			 urlencode($this->name()),
			 $this->uid(),$this->id())]
	=sprintf("%s %s %s",$this->Werte['vorname'], 
		 $this->Werte['aktueller_name'],
		 $this->name()?"(" . $this->name() . ")":"");
      $status=$this->naechste();
    } 
    return $rueckgabe;
  }

  function formular($daten=0) {
    if (!$daten) $daten=array('uid' => $_SESSION['uid']);
?>
<form method="post" action="<?=$PHP_SELF?>">
<input type="hidden" name="aktion" 
   value="<?=$daten['id']?"maildbaendern":"maildbneu"?>" />
   <?php if ($daten['id']) { ?>
<input type="hidden" name="id" value="<?=$daten['id']?>" />
			  <?php } ?>
<input type="hidden" name="uid" value="<?=$daten['uid']?>" />
<table border="0">
<tr><td>Name der Adresse</td><td>
<input type="text" size=30 name="name" value="<?=$daten['name']?>" /></td></tr>
<tr><td>Adresse</td><td>
<input type="text" size=30 name="adresse" value="<?=$daten['adresse']?>" /></td></tr>
<tr><td colspan=2>
<input type="checkbox" name="link" value="1" <?=$daten['link']?"checked=\"1\" ":""?> />
Diese Adresse soll mit einer Verknüpfung versehen werden.
</td></tr>
<tr><td colspan=2>
<input type="checkbox" name="encode" value="1" <?=$daten['encode']?"checked=\"1\" ":""?> />
Diese Adresse soll kodiert angezeigt werden.
</td></tr>
<tr><td colspan=2>
<input type="checkbox" name="mailformular" value="1" <?=$daten['mailformular']?"checked=\"1\" ":""?> />
Auf diese Adresse sollen Emails vom Formular aus gesendet werden.
</td></tr>
<tr><td colspan="2" align="center">
   <input type="submit" 
   value="<?=$daten['id']?"&Auml;ndern":"Einf&uuml;gen"?>" />&nbsp;<input
   type="reset" value="Zur&uuml;cksetzen" /></td></tr>
</table>
</form>
<?php if ($daten['id']) { ?>
<form method="post" action="<?=$PHP_SELF?>">
<input type="hidden" name="aktion" value="maildbloeschen" />
<input type="hidden" name="id" value="<?=$daten['id']?>" />
   <input type="submit"  value="L&ouml;schen" />
</form>
<?php
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
    if (!ereg("^[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+"
	      . "@[-!#$%&\'*+\\/0-9=?A-Z^_`a-z{|}~]+"
	      . "\.[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+$",$daten['adresse'])) 
      $fehler.="<br />Ung&uuml;ltige Email-Adresse";
    return $fehler;
  }
}
?>