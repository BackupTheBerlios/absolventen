<?php /* $Id: jahrgang.inc,v 1.8 2004/07/19 22:32:13 keinstein Exp $
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

$Log: jahrgang.inc,v $
Revision 1.8  2004/07/19 22:32:13  keinstein
globale Variablen -> $globals
Werte testen vor Rückgabe

Revision 1.7  2004/07/15 11:46:05  keinstein


SQLs überprüft und geändert
     (z.B. id bei insert auf NULL gesetzt
       und nicht weggelassen).

Referenz auf Datenbank
Variablen auf Existenz prüfen
Klassen in HTML-Ausgaben
Formular neu formatiert. Fehlerhafte Felder ber CSS markiert
         Neu als variable
	 ggf. Abbrechen-Knopf
checkdaten gibt Fehler-Array zurück
           Bereichs-Check für Jahrgang

id() und uid() raus (gibts schon in dbtabelle.inc)
Tippfehler in normprint(), nurjgprint()

*/ 

class jg extends dbtabelle{
  var $personen;
  var $mitjg;

  function jg(&$h_db) {
    $this->dbtabelle(&$h_db);
    $this->mitjg=0;
    $this->mailformopts="";
  }

  function sql($funktion,$args=0){
    
    switch ($funktion) {
	case "erste_person": 
		return sprintf("select distinct id,uid,jahrgang,klasse,drin "
			       . "from %s"
			       . " where uid=%d"
			       . " order by jahrgang,drin desc,klasse",
			       $GLOBALS['mod_absolventen_glob']['mysql']['JgTab'],$args);
  	case "diese": 
		return sprintf("select distinct id,uid,jahrgang,klasse,drin "
			       . "from %s"
			       . " where id=%d"
			       . " order by jahrgang,drin desc,klasse",
			       $GLOBALS['mod_absolventen_glob']['mysql']['JgTab'],$args);
        case "erste_jahrgang": 
	        return sprintf("select distinct jahrgang,klasse,drin "
			       . "from %s"
			       . " where jahrgang=%d"
			       . " order by jahrgang,drin desc,klasse",
   			       $GLOBALS['mod_absolventen_glob']['mysql']['JgTab'],$args);
        case "erste_nur_jahrgang": 
	        return sprintf("select distinct jahrgang "
			       . "from %s"
			       . " order by jahrgang",
   			       $GLOBALS['mod_absolventen_glob']['mysql']['JgTab']);
	case "insert":
		return sprintf("insert into %s (id,uid,jahrgang,klasse,drin"
			       . ") values (%s,%d,%d,%s,%d)",
			       $GLOBALS['mod_absolventen_glob']['mysql']['JgTab'],
			       empty($args['id'])?"NULL":sprintf("%d",$args['id']),
			       $args['uid'],
			       $args['jahrgang'],
			       isset($args['klasse'])?"'" . addslashes($args['klasse']) . "'":"NULL",
			       $args['drin']);
	case "update":
	        return sprintf("update %s set uid=%d,jahrgang=%d,"
			       . "klasse=%s,drin=%d"
			       . " where id=%d",
			       $GLOBALS['mod_absolventen_glob']['mysql']['JgTab'],
			       $args['uid'],
			       $args['jahrgang'],
			       isset($args['klasse'])?"'" . addslashes($args['klasse']) . "'":"NULL",
			       $args['drin'],
			       $args['id']);
       case "loeschen":
	 return sprintf("delete from %s where id=%d",$GLOBALS['mod_absolventen_glob']['mysql']['JgTab'],$args);
       case "persloeschen":
	 return sprintf("delete from %s where uid=%d",$GLOBALS['mod_absolventen_glob']['mysql']['JgTab'],$args);
    }
  }
	
  function insert($daten) {
    if (isset($daten['id']) && !ereg('^[0-9]+$',$daten['id'])) {
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
  function jahrgang() {
    return isset($this->Werte["jahrgang"])?$this->Werte["jahrgang"]:false;
  }

  function klasse() {
    return isset($this->Werte["klasse"])?$this->Werte["klasse"]:false;
  }

  function drin() {
    return isset($this->Werte["drin"])?$this->Werte["drin"]:false;
  }

  function normprint($erstespalte=""){
    
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
	echo $GLOBALS['mod_absolventen_glob']['layout']['tabtrenner'];
?><tr class="absolventen anzeige anzeige_jg">
<th colspan="<?=$spalten?>" align="center" 
class="absolventen anzeige anzeige_jahrgang"><?=$jgstring?></th></tr>
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

  function nurjgprint($erstespalte=""){
    

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
	echo $GLOBALS['mod_absolventen_glob']['layout']['tabtrenner'];
	?>
<tr class="absolventen anzeige anzeige_jg">
<th colspan="<?=$spalten?>" align="center" 
class="absolventen anzeige anzeige_jahrgang"><?=$jgstring?></th></tr>
   <?php }
    } while ($this->naechste());
  }

  function optionprint($jahrgang=""){
    do {
      printf("<option  class=\"absolventen anzeige anzeige_jgliste\""
	     . " value=\"%s\" %s>%s</option>\n",$this->jahrgang(),
	     $this->jahrgang()==$jahrgang?" selected=\"1\"":"",$this->jahrgang());
    } while ($this->naechste());
  }
  
  function formular($neu,$daten=array(),$fehler=array()) {
    reset($GLOBALS['mod_absolventen_glob']['klasse']);
    if ($neu) {
      $daten['uid'] = $_SESSION['mod_absolventen']['uid'];
      if (isset($daten['id'])) unset($daten['id']);
    }
?>
<form method="post" action="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>" class="absolventen jahrgang formular">
  <input type="hidden" name="aktion" 
     value="<?=$neu?"jgdbneu":"jgdbaendern"?>" />
<?php if (!empty($daten['id'])) 
    { ?>  <input type="hidden" name="id" value="<?=$daten['id']?>" /><?php 
    } ?>  <input type="hidden" name="uid" value="<?=$daten['uid']?>" />
  <table border="0" class="absolventen jahrgang formular">
    <tr class="absolventen jahrgang formular jg_jg">
      <th class="absolventen jahrgang formular jg_jg"><label 
          for="abs_jg<?=isset($daten['id'])?$daten['id']:""?>" 
          class="absolventen jahrgang formular jg_jg">Abitur-Jahrgang</label></th>
      <td class="absolventen jahrgang formular jg_jg"><input type="text" name="jahrgang" 
          class="absolventen jahrgang formular jg_jg<?=isset($fehler['jahrgang'])?" fehler":""?>"
          id="abs_jg<?=isset($daten['id'])?$daten['id']:""?>"
          value="<?=isset($daten['jahrgang'])?$daten['jahrgang']:""?>" size="4" maxlength="4" /></td>
    </tr>
    <tr class="absolventen jahrgang formular jg_klasse">
      <th class="absolventen jahrgang formular jg_klasse"><label 
          for="abs_kl<?=isset($daten['id'])?$daten['id']:""?>" 
          class="absolventen jahrgang formular jg_klasse">Klasse</label></th>
      <td class="absolventen jahrgang formular jg_klasse"><select name="klasse" 
          class="absolventen jahrgang formular jg_klasse<?=isset($fehler['klasse'])?" fehler":""?>"
          id="abs_kl<?=isset($daten['id'])?$daten['id']:""?>">
<?php
    while (list ($key, $val) = each ($GLOBALS['mod_absolventen_glob']['klasse'])) {
      printf('          <option value="%s"%s>%s</option>' . "\n",
	     $val,isset($daten['klasse'])&&
	     ($daten['klasse']==$val)?' selected="1"':'',
	     $key);
    }
    reset($GLOBALS['mod_absolventen_glob']['klasse']);
?>        </select></td>
    </tr>
    <tr class="absolventen jahrgang formular jg_drin">
      <th class="absolventen jahrgang formular jg_drin"><label 
          for="abs-ver<?=isset($daten['id'])?$daten['id']:""?>" 
          class="absolventen jahrgang formular jg_drin">Verhältnis<br />zum Jahrgang</label></th>
      <td id="abs_ver<?=isset($daten['id'])?$daten['id']:""?>" 
          class="absolventen jahrgang formular jg_drin">
        <div class="absolventen jahrgang formular jg_drin radio<?=isset($fehler['drin'])?
                    " fehler":""?>"><input type="radio" name="drin" value="1" id=
	           "abs_drin<?=isset($daten['id'])?$daten['id']:""?>" <?=empty(
	    $daten['drin'])?"":'checked="checked" '?>class="absolventen jahrgang formular jg_drin" /><label 
            class="absolventen jahrgang formular jg_drin radio<?=isset($fehler['drin'])?" fehler":""?>"
            for="abs-drin<?=isset($daten['id'])?$daten['id']:""?>">Zugeh&ouml;rig</label></div>
        <div class="absolventen jahrgang formular jg_drin radio<?=isset($fehler['drin'])?
                    " fehler":""?>"><input type="radio" class=
           "absolventen jahrgang formular jg_drin" name="drin" value="0" id="abs-drauszen<?=isset(
                        $daten['id'])?$daten['id']:""?>" <?=(isset($daten['drin']) && 
							     empty($daten['drin']))?'checked="checked" ':''?>/><label 
            for="abs-drauszen<?=isset($daten['id'])?$daten['id']:""?>"
            class="absolventen jahrgang formular jg_drin radio<?=isset($fehler['drin'])?
                          " fehler":""?>">sonstige nahestehende Person</label></div>
      </td>
    </tr>
    <tr class="absolventen jahrgang formular knoepfe">
      <td colspan="2" align="center" class="absolventen jahrgang formular knoepfe"><input type="submit" 
          class="absolventen jahrgang formular knoepfe"
          value="<?=$neu?"Einf&uuml;gen":"&Auml;ndern"?>" />&nbsp;<input
          class="absolventen jahrgang formular knoepfe"
          type="reset" value="Zur&uuml;cksetzen" /></td>
    </tr>
  </table>
</form>
<?php if (!$neu) { ?>
<form method="post" action="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>" class="absolventen jahrgang formular">
  <input type="hidden" name="aktion" value="jgdbloeschen" />
  <input type="hidden" name="id" value="<?=$daten['id']?>" />
  <input type="hidden" name="uid" value="<?=$daten['uid']?>" />
  <input type="submit"  value="L&ouml;schen" 
	class="absolventen jahrgang formular knoepfe jg_loeschen" />
</form><?php } ?>
<?php if (!empty($fehler)) { ?>
<form method="post" action="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>" class="absolventen jahrgang formular">
  <input type="hidden" name="aktion" value="jgform" />
  <input type="submit"  value="Abbrechen" 
	class="absolventen jahrgang formular knoepfe jg_abbrechen" />
</form><?php } ?>
<p class="absolventen jahrgang formular hinweis">Hinweis: Es werden nur sinnvolle Jahrgänge
 akzeptiert.</p>
<?php
   }


  function checkdaten(&$daten,$neu) {
    
    $fehler=array();
    if (!empty($daten['id']) && !ereg("^[0-9]*$",$daten['id'])) 
      $fehler['id'] ="Fehlerhafte id";
    if (empty($daten['uid']) || !ereg("^[0-9]*$",$daten['uid']))
      $fehler['uid'] ="Fehlerhafte uid";
    if (empty($daten['jahrgang'])){
      $fehler['jahrgang'] = "Diese Angaben machen nur Sinn, wenn Sie eine gültige Jahreszahl eingeben.";
    } else {
      if (isset($daten['jahrgang']) && ereg("^[1-9][0-9]*$",$daten['jahrgang'])
	  && $daten['jahrgang']>=0 && $daten['jahrgang']<100)
	{ if (($daten['jahrgang']+= date("Y")-(date("Y") % 100)) > date("Y")) $daten['jahrgang']-=100;
	} else
	  if (isset($daten['jahrgang']) && (!ereg("^[0-9]*$",$daten['jahrgang']) || 
					    $daten['jahrgang']<$GLOBALS['mod_absolventen_glob']['jahrgang']['von']
					    || $daten['jahrgang']>$GLOBALS['mod_absolventen_glob']['jahrgang']['bis']))
	    $fehler['jahrgang'] ="Der Jahrgang sollte eine sinnvolle Jahreszahl sein.";
    }
    if (!isset($daten['klasse']) || !in_array($daten['klasse'],$GLOBALS['mod_absolventen_glob']['klasse'])) 
      $fehler['klasse']="Ung&uuml;ltige Klasse";
    if (!isset($daten['drin']) || !ereg("^[0-9]+$",$daten['drin']))
      $fehler['drin']="Wie denn nun? Drin oder nicht drin? "
	. "Klären Sie bitte Ihr Verhältnis zum Jahrgang.";
    if (empty($daten['uid']) || empty($_SESSION['mod_absolventen']['uid']) || 
      ($daten['uid']!=$_SESSION['mod_absolventen']['uid']))
      $fehler[]="Ung&uuml;ltige Nutzeridentifikation";
    return $fehler;
  }
}
?>
