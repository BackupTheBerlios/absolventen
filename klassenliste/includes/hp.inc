<?php /* $Id: hp.inc,v 1.5 2004/07/19 22:28:17 keinstein Exp $
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

$Log: hp.inc,v $
Revision 1.5  2004/07/19 22:28:17  keinstein
globale Variablen nach $GLOBALS
formular: array nicht mehr komplett löschen
XHTML-fähig gemacht

Revision 1.4  2004/07/15 11:40:33  keinstein

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

*/ 

class homepage   extends dbtabelle{
  function sql($funktion,$args){
    
    switch ($funktion) {
	case "erste_person": 
		return sprintf("select id, uid, adresse, name"
		               . " from %s where uid=%d",
			$GLOBALS['mod_absolventen_glob']['mysql']['HPTab'],$args);
  	case "diese": 
		return sprintf("select id,uid, adresse, name"
			       . " from %s where id=%d",
			$GLOBALS['mod_absolventen_glob']['mysql']['HPTab'],$args);
	case "insert":
		return sprintf("insert into %s (id,uid,adresse,name"
			       . ") values (%s,%d,%s,%s)",
			       $GLOBALS['mod_absolventen_glob']['mysql']['HPTab'],
			       empty($args['id'])?'NULL':sprintf('%d',$args['id']),
			       $args['uid'],
			       empty($args['adresse'])?'NULL': "'" . addslashes($args['adresse']) . "'",
			       empty($args['name'])?'NULL':"'" . addslashes($args['name']) . "'");
	case "update":
		return sprintf("update %s set uid=%d,adresse=%s,name=%s"
			       . " where id=%d",
			       $GLOBALS['mod_absolventen_glob']['mysql']['HPTab'],
			       $args['uid'],
			       empty($args['adresse'])?'NULL': "'" . addslashes($args['adresse']) . "'",
			       empty($args['name'])?'NULL':"'" . addslashes($args['name']) . "'",
			       $args['id']);
	case "loeschen":
	        return sprintf("delete from %s where id=%d",$GLOBALS['mod_absolventen_glob']['mysql']['HPTab'],$args);
	case "persloeschen":
	  return sprintf("delete from %s where uid=%d",$GLOBALS['mod_absolventen_glob']['mysql']['HPTab'],$args);
    }
  }
	
  function homepage (&$h_db) {
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

  function adresse() {
    return isset($this->Werte["adresse"])?$this->Werte["adresse"]:false;
  }

  function name() {
    return isset($this->Werte["name"])?$this->Werte["name"]:false;
  }

  
  function normprint($erstspalte=""){
    printf('<a class="absolventen anzeige anzeige_hp" target="_blank" href="%s">%s</a>',
	   $this->adresse(),$this->name());
    while ($this->naechste()) {
      printf("<br />\n" . '<a class="absolventen anzeige anzeige_hp" target="_blank" href="%s">%s</a>',
	     $this->adresse(),$this->name());
    }
  }
  /* adresse,name */

  function formular($neu,$daten=array(),$fehler=array()) {
    if ($neu) {
      $daten['uid'] = $_SESSION['mod_absolventen']['uid'];
      if (isset($daten['id'])) unset($daten['id']);
    }
?>
<form method="post" action="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>" class="absolventen homepage formular">
  <input type="hidden" name="aktion" value="<?=$neu?"hpdbneu":"hpdbaendern"?>" />
  <?php if (!empty($daten['id'])) 
    { ?><input type="hidden" name="id" value="<?=$daten['id']?>" />
<?php 
    } ?><input type="hidden" name="uid" value="<?=$daten['uid']?>" />
  <table border="0" class="absolventen homepage formular">
    <tr class="absolventen homepage formular hp-name">
      <th class="absolventen homepage formular hp-name"><label 
          class="absolventen homepage formular hp-name" 
          for="hp-name<?=isset($daten['id'])?$daten['id']:""?>">Name der Adresse</label></th>
      <td class="absolventen homepage formular hp_name"><input type="text" size="30" name="name" 
          class="absolventen homepage formular hp_name<?=isset($fehler['name'])?" fehler":""?>"
          id="hp-name<?=isset($daten['id'])?$daten['id']:""?>"
          value="<?=isset($daten['name'])?$daten['name']:""?>" /></td>
    </tr>
    <tr class="absolventen homepage formular hp-adr">
      <th class="absolventen homepage formular hp-adr"><label 
          class="absolventen homepage formular hp-adr" 
          for="hp-adr<?=isset($daten['id'])?$daten['id']:""?>">Adresse</label></th>
      <td class="absolventen homepage formular hp-adr"><input type="text" size="30" name="adresse" 
          class="absolventen homepage formular hp-adr<?=isset($fehler['adresse'])?" fehler":""?>" 
          id="hp-adr<?=isset($daten['id'])?$daten['id']:""?>"
          value="<?=isset($daten['adresse'])?$daten['adresse']:""?>" /></td>
    </tr>
    <tr class="absolventen homepage formular knoepfe">
      <td colspan="2" class="absolventen homepage formular knoepfe" align="center"><input 
          type="submit"  class="absolventen homepage formular knoepfe"
          value="<?=$neu?"Einf&uuml;gen":"&Auml;ndern"?>" />&nbsp;<input
          type="reset" value="Zur&uuml;cksetzen" 
          class="absolventen homepage formular knoepfe" /></td>
    </tr>
  </table>
</form>
<?php if (!$neu) { ?>
<form method="post" action="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>" class="absolventen homepage formular">
  <input type="hidden" name="aktion" value="hpdbloeschen" />
  <input type="hidden" name="id" value="<?=$daten['id']?>" />
  <input type="submit"  value="L&ouml;schen"  class="absolventen homepage formular knoepfe hp_loeschen"/>
</form>
<?php  
    }
    if (!empty($fehler)) { ?>
<form method="post" action="<?=$GLOBALS['mod_absolventen_glob']['php_self']?>" class="absolventen homepage formular">
  <input type="hidden" name="aktion" value="hpform" />
  <input type="submit"  value="Abbrechen"  class="absolventen homepage formular knoepfe hp_abbrechen"/>
</form>
<?php  
   } ?>
<font size="-1" class="absolventen homepage formular wwwserver"><b 
   class="absolventen homepage formular wwwserver">Hinweis:</b> 
  Es werden nur gültige WWW-Adressen angenommen.
  Um Probleme mit unterschiedlichen 
  Browsern und WWW-Server-Konfigurationen zu vermeiden, 
  bitten wir darum, die Adresse standardkonform entsprechend dem Muster
  <tt class="absolventen homepage formular wwwserver" 
      >http://[nutzer[:passwort]@]rechner.bsp.de[:port]/[pfad/zur/[datei.ext]]</tt>
  anzugeben. Die eckigen Klammern bezeichnen hierbei Teile, die weggelassen werden können. 
  Insbesondere Schrägstriche am Ende der Adresse sind 
  <em class="absolventen homepage formular wwwserver"><b 
      class="absolventen homepage formular wwwserver">kein</b></em> Luxus.
</font>
<?php  }

  function checkdaten(&$daten,$neu) {
    //    
    $fehler=array();
    if (!empty($daten['id']) && !ereg("^[0-9]*$",$daten['id'])) 
      $fehler['id'] ="Fehlerhafte id";
    if (!empty($daten['uid']) && !ereg("^[0-9]*$",$daten['uid']))
      $fehler['uid'] ="Fehlerhafte uid";
    if (!empty($daten['id']) && !empty($daten['uid']) && !($daten['uid']==$_SESSION['mod_absolventen']['uid']))
      $fehler[] ="Ung&uuml;ltige Nutzeridentifikation";
    /* "^http://[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+\.[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+$" */
    if (empty($daten['adresse']) || !ereg("^http://([^:@ ]+(:[^@]*)?@)?"
	      . "[^@ /.:]+\.[^@ /:]+"
	      . "(:[0-9]+)?/[^@ :]*$",$daten['adresse'])) 
      $fehler['adresse'] ="Ung&uuml;ltige WWW-Adresse";
    else {
      $urlfopenstate=ini_get("allow_url_fopen");
      ini_set("allow_url_fopen","1");
      if (!($fp = @fopen ($daten['adresse'],'r'))) {
	$fehler['adresse'] = "Die WWW-Adresse konnte nicht &uuml;berpr&uuml;ft werden.";
      } else fclose($fp);
      ini_set("allow_url_fopen",$urlfopenstate);
    }
    if (empty($daten['name'])) $daten['name']=$daten['adresse'];
    return $fehler;
  }
}
?>
