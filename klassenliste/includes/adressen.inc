<?php /* $Id: adressen.inc,v 1.6 2004/07/15 00:02:42 keinstein Exp $
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

$Log: adressen.inc,v $
Revision 1.6  2004/07/15 00:02:42  keinstein
ids beim insert notfalls mit NULL belegen, aber immer
    mit aufführen
addslashes bei den SQL-Anweisungen überprüft
leere Felder möglichst mit NULL belegen
loeschen: Statusmeldungen raus
          Löschen der Tel-Nrn überprüft

id und uid: raus (sind in dbtabelle)

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
		return sprintf("insert into %s (id,uid,anfang,plz,ort,ende"
			       . ") values (%s,%d,%s,%s,%s,%s)",
			       $mysql_daten['AdrTab'],
			       empty($args['id'])?'NULL':sprintf('%d',$args['id']),
			       $args['uid'],
			       empty($args['anfang'])?'NULL':"'" . addslashes(nl2br($args['anfang'])) . "'",
			       empty($args['plz'])?"NULL":"'" . addslashes($args['plz']) . "'",
			       empty($args['ort'])?"NULL":"'" . addslashes($args['ort']) . "'",
			       empty($args['ende'])?"NULL":"'" . addslashes(nl2br($args['ende'])) . "'");
	case "update":
		return sprintf("update %s set uid=%d,anfang=%s,plz=%s,"
			       . "ort=%s,ende=%s"
			       . " where id=%d",
			       $mysql_daten['AdrTab'],
			       $args['uid'],
			       empty($args['anfang'])?'NULL':"'" . addslashes(nl2br($args['anfang'])) . "'",
			       empty($args['plz'])?"NULL":"'" . addslashes($args['plz']) . "'",
			       empty($args['ort'])?"NULL":"'" . addslashes($args['ort']) . "'",
			       empty($args['ende'])?"NULL":"'" . addslashes(nl2br($args['ende'])) . "'",
			       $args['id']);
	case "loeschen":
	        return sprintf("delete from %s where id=%d",$mysql_daten['AdrTab'],$args);
	case "persloeschen":
	        return sprintf("delete from %s where uid=%d",$mysql_daten['AdrTab'],$args);
    }
  }
	
  function adresse (&$h_db) {
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

  function loeschen($id,$uid,$tr_aktiv=0){
    $status=0;
    if (!$tr_aktiv){
      $status=!($this->db->transaction_start());
    }
    if (!$status) {
      $tel= new telefon($this->db);
      if ($id) {
	$status=$tel->adr_loeschen($id,$uid);
      }
      else {
	if ($this->erste_person($uid))
	  do {
	    $status=$tel->adr_loeschen($this->id(),$uid);
	  } while ($this->naechste() && !$status);
      }
      $tel->puffer_leeren();
      unset($tel);
      if (!$status) {
	$status=parent::loeschen($id,$uid);
      } 
    }
    if (!$tr_aktiv){
      if ($status) $this->db->rollback();
      else $this->db->commit();
    }
    return $status;
  }

  /* die einzelnen Felder der Adresse */
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
    printf('<td class="absolventen anzeige adresse adr_anfang" colspan="2">'
	   .'%s</td><td class="absolventen anzeige adresse telefon" rowspan="%d">',$this->anfang(),$zeilen);
    if ($telefon->erste_adresse($this->id())) {
            $telefon->nurtelprint();
    }
    print('</td>');
    return $zeilen;
  }

  function zweitprint(){
    printf('<td class="absolventen anzeige adresse adr_plz">%s</td>'
	   .'<td class="absolventen anzeige adresse adr_ort">%s</td>',$this->plz(),$this->ort());
  }
  
  function drittprint(){
    printf('<td class="absolventen anzeige adresse adr_ende" colspan="2">%s</td>',$this->ende());
  }
  
  function normprint($telefon,$erstespalte=false){
    do {
  ?><tr class="absolventen anzeige anzeige_jg"><?=$erstespalte?>
       <td class="absolventen anzeige anzeige_leer" colspan="2"></td><?php
       $zeilen=$this->erstprint($telefon);
    ?>
       </tr>
       <tr class="absolventen anzeige anzeige_jg"><?=$erstespalte?>
       <td class="absolventen anzeige anzeige_leer" colspan="2"></td><?=$this->zweitprint()?></tr>
       <?php if ($zeilen==3) {
?><tr class="absolventen anzeige anzeige_jg"><?=$erstespalte?><td colspan="2"></td><?=$this->drittprint()?></tr>
       <?php 
       }
    }  while ($this->naechste());
  }

  function formular($neu,$daten=0,$fehler=0) {
    global $PHP_SELF;
    if ($neu) $daten=array('uid' => $_SESSION['mod_absolventen']['uid']);
?>
<form class="absolventen adressen formular" method="post" action="<?=$PHP_SELF?>">
  <input class="absolventen adressen formular" type="hidden" name="aktion" 
    value="<?=$neu?"adrdbneu":"adrdbaendern"?>" />
  <?php if (isset($daten['id'])) 
{ ?><input class="absolventen adressen formular" type="hidden" name="id" value="<?=$daten['id']?>" />
  <?php } 
?><input class="absolventen adressen formular" type="hidden" name="uid" value="<?=$daten['uid']?>" />
  <table class="absolventen adressen formular" border="0">
    <tr class="absolventen adressen formular adranfang">
      <th class="absolventen adressen formular adranfang"><label 
          class="absolventen adressen formular adranfang"
          for="adranfang<?=isset($daten['id'])?$daten['id']:""?>"
          class="absolventen adressen formular">Anfang der Adresse</label></th>
      <td class="absolventen adressen formular adranfang"><textarea cols=30 rows=2 name="anfang" 
          class="absolventen adressen formular<?=isset($fehler['anfang'])?" fehler":""?>" 
          id="adranfang<?=isset($daten['id'])?$daten['id']:""?>"><?=isset($daten['anfang'])?
                preg_replace("/<br[^>]*>/i","",$daten['anfang']):""?></textarea></td>
    </tr>
    <tr class="absolventen adressen formular adrplz">
      <th class="absolventen adressen formular adrplz"><label
          class="absolventen adressen formular adrplz" 
          for="adrplz<?=isset($daten['id'])?$daten['id']:""?>">Postleitzahl</label></th>
      <td class="absolventen adressen formular adrplzort"><input type="text" size=5 name="plz" 
	  value="<?=isset($daten['plz'])?$daten['plz']:""?>" 
          class="absolventen adressen formular adrplzort<?=isset($fehler['plz'])?" fehler":""?>"
          id="adrplz<?=isset($daten['id'])?$daten['id']:""?>"/></td>
    </tr>
    <tr class="absolventen adressen formular adrort">
      <th class="absolventen adressen formular adrort"><label 
          class="absolventen adressen formular adrort" 
          for="adrort<?=isset($daten['id'])?$daten['id']:""?>">Ort</label></th>
      <td class="absolventen adressen formular adrplzort"><input type="text" size=20 name="ort" 
          value="<?=isset($daten['ort'])?$daten['ort']:""?>" 
          class="absolventen adressen formular adrplzort<?=isset($fehler['ort'])?" fehler":""?>"
          id="adrort<?=isset($daten['id'])?$daten['id']:""?>" /></td>
    </tr>
    <tr class="absolventen adressen formular adrende">
      <th class="absolventen adressen formular adrende"><label
	  class="absolventen adressen formular adrende"
          for="adrende<?=isset($daten['id'])?$daten['id']:""?>">Weiteres zu 
        dieser<br />Adresse (z.&thinsp;B. Land)</label></th>
      <td class="absolventen adressen formular adrende"><textarea cols=30 rows=2 
          id="adrende<?=isset($daten['id'])?$daten['id']:""?>"
          class="absolventen adressen formular<?=isset($fehler['ende'])?" fehler":""?>" 
          name="ende"><?=isset($daten['ende'])?preg_replace(
                         "/<br[^>]*>/i","",$daten['ende']):""?></textarea></td>
    </tr>
    <tr class="absolventen adressen formular">
      <td class="absolventen adressen formular knoepfe" colspan="2" align="center"><input 
          type="submit"  class="absolventen adressen formular"
          value="<?=$neu?"Einf&uuml;gen":"&Auml;ndern"?>" />&nbsp;<input
          type="reset" value="Zur&uuml;cksetzen"  class="absolventen adressen formular"/></td>
    </tr>
  </table>
</form>
<?php if (!$neu) { ?>
<form method="post" action="<?=$PHP_SELF?>" class="absolventen adressen formular adrloeschen">
  <input type="hidden" name="aktion" value="adrdbloeschen"  class="absolventen adressen formular"/>
  <input type="hidden" name="id" value="<?=$daten['id']?>"  class="absolventen adressen formular"/>
  <input type="hidden" name="uid" value="<?=$daten['uid']?>"  class="absolventen adressen formular"/>
  <input type="submit"  value="L&ouml;schen" class="absolventen adressen formular adrloeschen" />
</form>
<?php
    }
    if (!empty($fehler)) { ?>
<form method="post" action="<?=$PHP_SELF?>" class="absolventen adressen formular adrabbrechen">
  <input type="hidden" name="aktion" value="adrform" class="absolventen adressen formular"/>
  <input type="submit"  value="Abbrechen" class="absolventen adressen formular adrabbrechen" />
</form>
<?php
    }
  }

  function checkdaten($daten,$neu) {
    global $klasse;
    $fehler=array();
    if (!empty($daten['id']) && !ereg("^[0-9]*$",$daten['id'])) 
      $fehler['id'] ="Fehlerhafte id";
    if (!empty($daten['uid']) && !ereg("^[0-9]*$",$daten['uid']))
      $fehler['uid'] ="Fehlerhafte uid";
    if (!empty($daten['id']) && (empty($_SESSION['mod_absolventen']['uid']) || !($daten['uid']==$_SESSION['mod_absolventen']['uid'])))
      $fehler[] ="Ung&uuml;ltige Nutzeridentifikation";
    if (empty($daten['anfang']) && empty($daten['plz']) && empty($daten['ort']) && empty($daten['ende'])) {
      $fehler[] = "Es sollte wenigstens ein Teil der Adresse eingetragen sein, aber:";
      $fehler['anfang'] = "Es gibt keine Straße oder sonstigen Anfang der Adresse.";
      $fehler['plz'] = "Es gibt keine Postleitzahl.";
      $fehler['ort'] = "Es gibt keinen Ort.";
      $fehler['ende'] = "Es gibt kein Land oder sonstiges Ende der Adresse.";
    }
    return $fehler;
  }

}
?>
