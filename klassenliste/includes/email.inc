<?php /* $Id: email.inc,v 1.4 2004/07/15 11:38:38 keinstein Exp $
Copyright (c) 2000-2004 SchlemmerSoft (Tobias Schlemmer)

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

$Log: email.inc,v $
Revision 1.4  2004/07/15 11:38:38  keinstein

SQLs überprüft und geändert
     (z.B. id bei insert auf NULL gesetzt
       und nicht weggelassen).

Referenz auf Datenbank
Variablen auf Existenz prüfen
Klassen in HTML-Ausgaben
Formular neu formatiert. Fehlerhafte Felder ber CSS markiert
         Neu als variable
checkdaten gibt Fehler-Array zurück

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
		return sprintf("insert into %s (id,uid,adresse,name,link,encode,mailformular"
			       . ") values (%s,%d,%s,%s,%d,%d,%d)",
			       $mysql_daten['EmailTab'],
			       empty($args['id'])?"NULL":sprintf('%d',$args['id']),
			       $args['uid'],
			       empty($args['adresse'])?"NULL": "'" . addslashes($args['adresse']) . "'",
			       empty($args['name'])?"NULL":"'" . addslashes($args['name']) . "'",
			       empty($args['link'])?0:$args['link'],
			       empty($args['encode'])?0:$args['encode'],
			       empty($args['mailformular'])?0:$$args['mailformular']);
	case "update":
		return sprintf("update %s set uid=%d,adresse=%s,name=%s,"
			       . "link=%d,encode=%d,mailformular=%d"
			       . " where id=%d",
			       $mysql_daten['EmailTab'],
			       $args['uid'],
			       empty($args['adresse'])?"NULL": "'" . addslashes($args['adresse']) . "'",
			       empty($args['name'])?"NULL":"'" . addslashes($args['name']) . "'",
			       empty($args['link'])?0:$args['link'],
			       empty($args['encode'])?0:$args['encode'],
			       empty($args['mailformular'])?0:$args['mailformular'],			       
			       $args['id']);
	case "loeschen":
	        return sprintf("delete from %s where id=%d",$mysql_daten['EmailTab'],$args);
	case "persloeschen":
	        return sprintf("delete from %s where uid=%d",$mysql_daten['EmailTab'],$args);
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
	
  function email (&$h_db) {
    $this->dbtabelle(&$h_db);
  }

  function insert($daten) {
    $this->puffer_leeren();
    if (!empty($daten['id']) && !ereg('^[0-9]*$',$daten['id'])) {
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
      printf('<a class="absolventen anzeige anzeige_email" href="mailto:%s">%s</a>',$adr,$adr);
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
	printf('<a class="absolventen anzeige anzeige_email" href="mailto:%s">%s</a>',$adr,$adr);
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

  function formular($neu,$daten=0,$fehler=0) {
    global $PHP_SELF;
    if ($neu) $daten=array('uid' => $_SESSION['mod_absolventen']['uid']);
?>
<form method="post" action="<?=$PHP_SELF?>" class="absolventen email formular">
  <input type="hidden" name="aktion" value="<?=$neu?"maildbneu":"maildbaendern"?>" />
  <?php if (isset($daten['id'])) { 
?><input type="hidden" name="id" value="<?=isset($daten['id'])?$daten['id']:""?>" />
  <?php } 
?><input type="hidden" name="uid" value="<?=isset($daten['uid'])?$daten['uid']:""?>" />
  <table class="absolventen email formular" border="0">
    <tr class="absolventen email formular emailname">
      <th class="absolventen email formular emailname"><label 
          class="absolventen email formular"
          for="adrname<?=isset($daten['id'])?$daten['id']:""?>">Name der Adresse</label></th>
      <td class="absolventen email formular emailname"><input 
          type="text" size="30" name="name" id="adrname<?=isset($daten['id'])?$daten['id']:""?>"
          class="absolventen email formular emailname<?=isset($fehler['name'])?" fehler":""?>"
          value="<?=isset($daten['name'])?$daten['name']:""?>" /></td>
    </tr>
    <tr class="absolventen email formular">
      <th class="absolventen email formular emailadr"><label 
          class="absolventen email formular"
          for="adrtext<?=isset($daten['id'])?$daten['id']:""?>">Adresse</th>
      <td class="absolventen email formular emailadr"><input type="text" 
          size="30" name="adresse" id="adrtext<?=isset($daten['id'])?$daten['id']:""?>"
          class="absolventen email formular emailadr<?=isset($fehler['adresse'])?" fehler":""?>"
          value="<?=isset($daten['adresse'])?$daten['adresse']:""?>" /></td>
    </tr>
    <tr class="absolventen email formular">
      <td colspan="2" class="absolventen email formular emaillink">
        <div class="absolventen email formular emaillink checkbox"><input 
            type="checkbox" name="link" value="1" 
            class="absolventen email formular emaillink" id="adrlink<?=isset($daten['id'])?$daten['id']:""?>" 
            <?=empty($daten['link'])?"":'checked="1" '?> /><label 
            class="absolventen email formular checkbox<?=isset($fehler['link'])?" fehler":""?>"
            for="adrlink<?=isset($daten['id'])?$daten['id']:""?>">Diese Adresse soll mit einer 
	    Verknüpfung versehen werden.</label></div>
      </td>
    </tr>
    <tr class="absolventen email formular">
      <td colspan="2" class="absolventen email formular adrencode">
        <div class="absolventen email formular adrencode checkbox"><input 
            type="checkbox" name="encode" value="1" id="adrencode<?=isset($daten['id'])?$daten['id']:""?>" 
            class="absolventen email formular adrencode"
            <?=empty($daten['encode'])?"":'checked="1" '?> /><label 
            class="absolventen email formular email_form checkbox<?=isset($fehler['encode'])?" fehler":""?>" 
            for="adrencode<?=isset($daten['id'])?$daten['id']:""?>">Diese Adresse soll 
            kodiert angezeigt werden.</label></div>
      </td>
    </tr>
    <tr class="absolventen email formular">
      <td colspan=2 class="absolventen email formular email_form">
        <div class="absolventen email formular email_form checkbox"><input 
            type="checkbox" name="mailformular" value="1" 
            class="absolventen email formular email_form"
            id="adrform<?=isset($daten['id'])?$daten['id']:""?>"
            <?=(empty($daten['mailformular']))?"":'checked="1" '?> /><label 
            class="absolventen email formular email_form checkbox<?=isset($fehler['mailformular'])?" fehler":""?>" 
            for="adrform<?=isset($daten['id'])?$daten['id']:""?>">Auf diese Adresse sollen 
            Emails vom Formular aus gesendet werden können.</label></div>
      </td>
    </tr>
    <tr class="absolventen email formular knoepfe">
      <td colspan="2" align="center"  class="absolventen email formular knoepfe">
	<input type="submit" class="absolventen email formular knoepfe"
          value="<?=$neu?"Einf&uuml;gen":"&Auml;ndern"?>" />&nbsp;<input
          type="reset" value="Zur&uuml;cksetzen"  class="absolventen email formular knoepfe" />
      </td>
    </tr>
  </table>
</form>
<?php if (!$neu) { 
?><form method="post" action="<?=$PHP_SELF?>" class="absolventen email formular">
  <input type="hidden" name="aktion" value="maildbloeschen" />
  <input type="hidden" name="id" value="<?=$daten['id']?>" />
  <input type="hidden" name="uid" value="<?=$daten['uid']?>" />
  <input type="submit" value="L&ouml;schen" class="absolventen email formular knoepfe email_loeschen" />
</form>
<?php } if (!empty($fehler)) { 
?><form method="post" action="<?=$PHP_SELF?>" class="absolventen email formular">
  <input type="hidden" name="aktion" value="mailform" />
  <input type="submit" value="Abbrechen" class="absolventen email formular knoepfe email_abbrechen" />
</form>
<?php
    }
  }

  function checkdaten($daten,$neu) {
    //    global $klasse;
    $fehler=array();
    if (!empty($daten['id']) && !ereg("^[0-9]*$",$daten['id'])) 
      $fehler['id'] ="Fehlerhafte id";
    if (!isset($daten['uid']) || !ereg("^[0-9]*$",$daten['uid']))
      $fehler['uid'] ="Fehlerhafte uid";
    if (!isset($daten['uid']) || !isset($_SESSION['mod_absolventen']['uid']) || !($daten['uid']==$_SESSION['mod_absolventen']['uid']))
      $fehler[] ="Ung&uuml;ltige Nutzeridentifikation";
    if (!ereg("^[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+"
	      . "@[-!#$%&\'*+\\/0-9=?A-Z^_`a-z{|}~]+"
	      . "\.[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+$",$daten['adresse'])) 
      $fehler['adresse'] ="Ung&uuml;ltige Email-Adresse";
    return $fehler;
  }
}
?>
