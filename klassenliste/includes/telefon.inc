<?php /*
$Id: telefon.inc,v 1.5 2004/07/19 22:49:02 keinstein Exp $
Copyright © 2000-2004 SchlemmerSoft (Tobias Schlemmer)

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

$Log: telefon.inc,v $
Revision 1.5  2004/07/19 22:49:02  keinstein
globals ->$GLOBALS
id() und uid() raus
sonstige felder: testen vor Rückgabe
Tipfehler korrigiert im Formular
ggf. puffer_leeren() aufrufen

Revision 1.4  2004/07/15 11:55:05  keinstein
SQLs überprüft und geändert
     (z.B. id bei insert auf NULL gesetzt
       und nicht weggelassen).
       aus erste_person_ohne_adr() und erste_adresse()
       nach sql()

Referenz auf Datenbank
Variablen auf Existenz prüfen
Klassen in HTML-Ausgaben
Formular neu formatiert. Fehlerhafte Felder ber CSS markiert
         Neu als variable
	 ggf. Abbrechen-Knopf
checkdaten gibt Fehler-Array zurück

Revision 1.3  2004/05/08 16:12:06  keinstein
Person/Adresse löschen
Labels für radio-buttons


*/ 

class telefon extends dbtabelle{
  function sql($funktion,$args){
    
    switch ($funktion) {
	case "erste_person": 
		return sprintf("select id,uid,aid,vorwahl,telefon,kommentar"
		               . " from %s where uid=%d",
			$GLOBALS['mod_absolventen_glob']['mysql']['TelTab'],$args);
        case "erste_pers_ohne_adr":
                return sprintf("select id,uid,aid,vorwahl,telefon,kommentar"
			       . " from %s where uid=%d and aid is null",
			       $GLOBALS['mod_absolventen_glob']['mysql']['TelTab'],$args);
        case "erste_adresse":
                return sprintf("select id,uid,aid,vorwahl,telefon,kommentar"
			       . " from %s where aid=%d",
			       $GLOBALS['mod_absolventen_glob']['mysql']['TelTab'],$args);
  	case "diese": 
		return sprintf("select id,uid,aid,vorwahl,telefon,kommentar"
			       . " from %s where id=%d",
			$GLOBALS['mod_absolventen_glob']['mysql']['TelTab'],$args);
	case "insert":
		return sprintf("insert into %s (id,uid,aid,vorwahl,telefon,kommentar"
			       . ") values (%s,%d,%s,%s,%s,%s)",
			       $GLOBALS['mod_absolventen_glob']['mysql']['TelTab'],
			       empty($args['id'])?'NULL':sprintf("%d",$args['id']),
			       $args['uid'],
			       empty($args['aid'])?'NULL':sprintf("%d",$args['aid']),
			       empty($args['vorwahl'])?'NULL': "'" . addslashes($args['vorwahl']) . "'",
			       empty($args['telefon'])?'NULL': "'" . addslashes($args['telefon']) . "'",
			       empty($args['kommentar'])?'NULL': "'" . addslashes($args['kommentar']) . "'");
	case "update":
		return sprintf("update %s set uid=%d,aid=%s,vorwahl=%s,telefon=%s,kommentar=%s"
			       . " where id=%d",
			       $GLOBALS['mod_absolventen_glob']['mysql']['TelTab'],
			       $args['uid'],
			       empty($args['aid'])?'NULL':sprintf("%d",$args['aid']),
			       empty($args['vorwahl'])?'NULL': "'" . addslashes($args['vorwahl']) . "'",
			       empty($args['telefon'])?'NULL': "'" . addslashes($args['telefon']) . "'",
			       empty($args['kommentar'])?'NULL': "'" . addslashes($args['kommentar']) . "'",
			       $args['id']);
        case "adr_loeschen":
                return sprintf("update %s set aid=NULL,uid=%d where aid=%d",
			       $GLOBALS['mod_absolventen_glob']['mysql']['TelTab'],$args['uid'],$args['aid']);
	case "loeschen":
	        return sprintf("delete from %s where id=%d",$GLOBALS['mod_absolventen_glob']['mysql']['TelTab'],$args);
	case "persloeschen":
	        return sprintf("delete from %s where uid=%d",$GLOBALS['mod_absolventen_glob']['mysql']['TelTab'],$args);
    }
  }
	
  function telefon (&$h_db) {
    $this->dbtabelle(&$h_db);
  }

  function erste_person_ohne_adr($person){
    $this->Qresult=$this->db->query($this->sql("erste_pers_ohne_adr",$person));
    $this->Werte=$this->db->fetch_array($this->Qresult);
    return ($this->Werte && true);
  }

  function erste_adresse($aid){
    $this->Qresult=$this->db->query($this->sql("erste_adresse",$aid));
    $this->Werte=$this->db->fetch_array($this->Qresult);
    return ($this->Werte && true);
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

  function adr_loeschen($aid,$uid){
    $this->puffer_leeren();
    if (!$aid || !ereg('^[0-9]*$',$aid) || !$uid || !ereg('^[0-9]*$',$uid) ) {
      return -1;
    }
    return $this->update_backend($this->sql("adr_loeschen",array('aid'=> $aid, 'uid'=>$uid)),$uid);
  }
  /* die einzelnen Felder der Person */

  function aid() {
    return isset($this->Werte["aid"])?$this->Werte["aid"]:false;
  }

  function vorwahl() {
    return isset($this->Werte["vorwahl"])?$this->Werte["vorwahl"]:false;
  }

  function telefon_nr() {
    return isset($this->Werte["telefon"])?$this->Werte["telefon"]:false;
  }
  
  function kommentar() {
    return isset($this->Werte["kommentar"])?$this->Werte["kommentar"]:false;
  }

  function nurtelprint() {
    printf('(%s) %s %s',$this->vorwahl(),$this->telefon_nr(),$this->kommentar());
    while ($this->naechste())
      printf('<br />(%s) %s %s',
	     $this->vorwahl(),$this->telefon_nr(),$this->kommentar());
  }

  function normprint($erstspalte=""){
    do {
      printf('<tr class="absolventen anzeige anzeige_jg">'
	     .'<td colspan="4" class="absolventen anzeige anzeige_leer"></td>'
	     .'<td class="absolventen anzeige adresse telefon">(%s) %s %s</td></tr>',
	     $this->vorwahl(),$this->telefon_nr(),$this->kommentar());
    }while ($this->naechste());
  }
  /* adresse,name */

  function formular($neu,$daten=array(),$fehler=array()) {
    if ($neu) {
      $daten['uid'] = $_SESSION['mod_absolventen']['uid'];
      if (isset($daten['id'])) unset($daten['id']);
    }
    $adressen=new adresse($this->db);
    $adressen->erste_person($daten['uid']);
?>      
<form method="post" action="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>" class="absolventen telefon formular">
  <input type="hidden" name="aktion" 
     value="<?=$neu?"teldbneu":"teldbaendern"?>" />
     <?php if (isset($daten['id'])) { ?>
  <input type="hidden" name="id" value="<?=$daten['id']?>" />
  			  <?php } ?>
  <input type="hidden" name="uid" value="<?=$daten['uid']?>" />
  <table border="0" class="absolventen telefon formular">
    <tr class="absolventen telefon formular tel_adr">
      <th class="absolventen telefon formular tel_adr"><label 
       class="absolventen telefon formular tel_adr"
       for="abs_aidinputp<?=isset($daten['id'])?$daten['id']:""?>">Adresse</label></th>
      <td class="absolventen telefon formular tel_adr"><div 
	class="absolventen telefon formular tel_adr<?=isset($fehler['aid'])?" fehler":""?>" 
        id="abs_aidinputp<?=isset($daten['id'])?$daten['id']:""?>"><div
        class="absolventen telefon formular adresse tel_adr<?=isset($fehler['aid'])?" fehler":""?>"><input 
								type="radio" 
        id="aidinputnull<?=isset($daten['id'])?$daten['id']:""?>" name="aid" 
        class="absolventen telefon formular adresse tel_adr"
        value="" <?=(isset($daten['aid'])&& $daten['aid'])?"":"checked=\"checked\" "?> /><label 
        class="absolventen telefon formular adresse tel_adr<?=isset($fehler['aid'])?" fehler":""?>"
        for="aidinputnull<?=isset($daten['id'])?$daten['id']:""?>">Keine</label></div><?php 
        do { 
?><div
        class="absolventen telefon formular adresse tel_adr<?=isset($fehler['aid'])?" fehler":""?>"><input 
        type="radio" name="aid"<?=(isset($daten['aid'])&&$daten['aid']==$adressen->id())?" checked=\"checked\"":""?> 
        id="aid<?=$adressen->id()?>input<?=isset($daten['id'])?$daten['id']:""?>" 
        value="<?=$adressen->id();?>" class="absolventen telefon formular adresse tel_adr" /><label 
        class="absolventen telefon formular adresse tel_adr<?=isset($fehler['aid'])?" fehler":""?>"
        for="aid<?=$adressen->id()?>input<?=isset($daten['id'])?$daten['id']:""?>"><?=$adressen->anfang()?><br />
    	      <?=$adressen->plz()?>&nbsp;<?=$adressen->ort()?><br />
    	      <?=$adressen->ende()?></label></div><?php 
        } while ($adressen->naechste()); ?></div></td>
    </tr>
    <tr class="absolventen telefon formular tel_vorwahl">
      <th class="absolventen telefon formular tel_vorwahl"><label 
        class="absolventen telefon formular tel_vorwahl"
        for="abs-vorwahl<?=isset($daten['id'])?$daten['id']:""?>">Vorwahl</label></th>
      <td class="absolventen telefon formular tel_vorwahl"><input type="text" size="30" name="vorwahl" 
        class="absolventen telefon formular tel_vorwahl<?=isset($fehler['vorwahl'])?" fehler":""?>"
        id="abs-vorwahl<?=isset($daten['id'])?$daten['id']:""?>"
        value="<?=isset($daten['vorwahl'])?$daten['vorwahl']:""?>" /></td>
    </tr>
    <tr class="absolventen telefon formular tel_telefon">
      <th class="absolventen telefon formular tel_telefon"><label 
        class="absolventen telefon formular tel_telefon"
        for="abs-telefon<?=isset($daten['id'])?$daten['id']:""?>">Telefon</label></th>
      <td class="absolventen telefon formular tel_telefon"><input type="text" size="30" name="telefon" 
        class="absolventen telefon formular tel_telefon<?=isset($fehler['telefon'])?" fehler":""?>"
        id="abs-telefon<?=isset($daten['id'])?$daten['id']:""?>"
        value="<?=isset($daten['telefon'])?$daten['telefon']:""?>" /></td>
    </tr>
    <tr class="absolventen telefon formular tel_bem">
      <th class="absolventen telefon formular tel_bem"><label 
        class="absolventen telefon formular tel_bem"
        for="abs-bemerkung<?=isset($daten['id'])?$daten['id']:""?>">Bemerkung</label></th>
      <td class="absolventen telefon formular tel_bem"><input type="text" size="30" name="kommentar" 
        class="absolventen telefon formular tel_bem<?=isset($fehler['kommentar'])?" fehler":""?>"
        id="abs-bemerkung<?=isset($daten['id'])?$daten['id']:""?>"
        value="<?=isset($daten['kommentar'])?$daten['kommentar']:""?>" /></td>
    </tr>
    <tr class="absolventen telefon formular knoepfe">
      <td colspan="2" align="center" class="absolventen telefon formular knoepfe">
       <input type="submit"  class="absolventen telefon formular knoepfe"
       value="<?=$neu?"Einf&uuml;gen":"&Auml;ndern"?>" />&nbsp;<input
       type="reset" class="absolventen telefon formular knoepfe" value="Zur&uuml;cksetzen" /></td>
    </tr>
  </table>
</form>
<?php if (!$neu) { ?>
<form method="post" action="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>">
  <input type="hidden" name="aktion" value="teldbloeschen" />
  <input type="hidden" name="id" value="<?=$daten['id']?>" />
  <input type="hidden" name="uid" value="<?=$daten['uid']?>" />
  <input type="submit"  value="L&ouml;schen"  class="absolventen telefon formular knoepfe tel_loeschen" />
</form>
<?php  }
if (!empty($fehler)) { ?>
<form method="post" action="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>">
  <input type="hidden" name="aktion" value="telform" />
  <input type="submit"  value="Abbrechen" class="absolventen telefon formular knoepfe tel_abbrechen" />
</form>
<?php
    }
    $adressen->puffer_leeren();
  }

  function checkdaten($daten,$neu) {
    //    
    $fehler=array();
    if (!empty($daten['id']) && !ereg("^[0-9]*$",$daten['id'])) 
      $fehler['id']="Fehlerhafte id";
    if (!ereg("^[0-9]*$",$daten['uid']))
      $fehler['uid']="Fehlerhafte uid";
    if (!($daten['uid']==$_SESSION['mod_absolventen']['uid']))
      $fehler[]="Ung&uuml;ltige Nutzeridentifikation.";
    if ($daten['aid']) {
      if (!ereg('^[0-9]*$',$daten['aid']))
	$fehler['aid']="Ung&uuml;ltige Adresse.";
      else {
	$adressen=new adresse($this->db);
	$adressen->diese($daten['aid']);
	if ($adressen->uid()!=$daten['uid']) 
	  $fehler['aid']="Die Adresse existiert nicht oder gehört nicht zu Ihnen.";
	$adressen->puffer_leeren();
      }
    }
    if (empty($daten['vorwahl']) && empty($daten['telefon']) && empty($daten['kommentar'])){
      $fehler[] = "Die Telefonnummer ist ein wenig dürftig:";
      $fehler['vorwahl'] = "Es gibt keine Vorwahl.";
      $fehler['telefon'] = "Es gibt keine Telefonnummer.";
      $fehler['kommentar'] = "Noch nicht einmal eine Bemerkung haben Sie eingegeben.";
    }
    return $fehler;
  }
}
?>
