<?php /* $Id: personen.inc,v 1.6 2004/07/15 11:52:57 keinstein Exp $
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

$Log: personen.inc,v $
Revision 1.6  2004/07/15 11:52:57  keinstein


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

crypt jetzt lokal ausgeführt (PW nicht unverschlüsselt über Link)

loeschen(): ohne Statusmeldungen


*/ 

class personen extends dbtabelle {
  function sql($funktion,$args){
    global $mysql_daten;
    switch ($funktion) {
	case "erste_person": 
  	case "diese": 
		return sprintf("select id,login,aktueller_name,geburtsname,vorname,kommentar,"
			       . "DATE_FORMAT(aktualisierung,'%%d.%%m.%%Y %%T') as aktualisierung "
			       . "from %s where id=%d",
			       $mysql_daten['PersTab'],$args);

	case "insert":
	        return sprintf("insert into %s (id,login,aktueller_name,geburtsname,"
			       . "vorname,kommentar,pw) values (%s,'%s','%s','%s','%s',%s,"
			       . "%s)",
			       $mysql_daten['PersTab'],
			       empty($args['id'])?"NULL":sprintf("%d",$args['id']),
			       addslashes($args['login']),
			       addslashes($args['aktueller_name']),
			       addslashes($args['geburtsname']),
			       addslashes($args['vorname']),
			       empty($args['kommentar'])?"NULL":"'" . addslashes(nl2br($args['kommentar'])) . "'",
			       empty($args['pw'])?"NULL":"'" . addslashes(crypt($args['pw'])) . "'");

	case "update":
                return sprintf("update %s set login='%s',aktueller_name='%s',"
			       . "geburtsname='%s',vorname='%s',kommentar=%s%s"
			       . " where id=%d",
			       $mysql_daten['PersTab'],
			       addslashes($args['login']),
			       addslashes($args['aktueller_name']),
			       addslashes($args['geburtsname']),
			       addslashes($args['vorname']),
			       empty($args['kommentar'])?"NULL":"'" . addslashes(nl2br($args['kommentar'])) . "'",
			       empty($args['pw'])?"":",pw='" . addslashes(crypt($args['pw'])) . "'",
			       $args['id']);

        case "loeschen":
	        return sprintf("delete from %s where id=%d",$mysql_daten['PersTab'],$args);

        case "erste_jahrgang":
	        return sprintf("select %s.id as "
			       . "id,login,aktueller_name,geburtsname,vorname,kommentar,"
			       . "DATE_FORMAT(aktualisierung,'%%d.%%m.%%Y %%T') as aktualisierung "
			       . "from %s,%s"
			       . " where %s.jahrgang=%d"
			       . " and %s.klasse=%s and %s.drin=%d"
			       . " and %s.uid=%s.id"
			       . " order by geburtsname,vorname,aktueller_name",
			       $mysql_daten['PersTab'],
			       $mysql_daten['PersTab'],
			       $mysql_daten['JgTab'],
			       $mysql_daten['JgTab'],
			       $args['jahrgang'],
			       $mysql_daten['JgTab'],
			       isset($args['klasse'])?"'" . addslashes($args['klasse']) . "'":"NULL",
			       $mysql_daten['JgTab'],
			       $args['drin'],
			       $mysql_daten['JgTab'],
			       $mysql_daten['PersTab']);
        case "aktualisiere_akt":
                return sprintf("update %s set aktualisierung=NULL "
			       . "where id=%d",
			       $mysql_daten['PersTab'],
			       $args);
        case "get_pw":
        	return sprintf("select aktueller_name,geburtsname,vorname,"
			       . "id,pw "
			       . "from %s where login='%s'",
			       $mysql_daten['PersTab'],
			       empty($args)?"":addslashes($args));
        case "login_exists":
	  return sprintf("select id from %s where login='%s'",
			 $mysql_daten['PersTab'],empty($args)?"":addslashes($args));

    }
  }
	
  function personen (&$h_db) {
    $this->dbtabelle(&$h_db);
  }

  function erste_jahrgang($jahrgang,$klasse,$drin){
    $this->puffer_leeren();
    if (!$this->Qresult=$this->db->query(
	       $this->sql('erste_jahrgang',
			array('jahrgang' => $jahrgang,
			      'klasse'   => $klasse,
			      'drin'     => $drin)))) 
    {
      fehler("personen-&gt;erste_jahrgang(" . $jahrgang . ','
	     . $klasse . "," . $drin . ")");
      return false;
    }
    $this->Werte=$this->db->fetch_array($this->Qresult);
    return ($this->Werte != false);
  }

  function insert($daten) {
    $this->puffer_leeren();
    if (!empty($daten['id']) && !ereg('^[0-9]*$',$daten['id'])) {
      return -1;
    }
    return $this->insert_backend($this->sql("insert",$daten));
  }

  function update($daten) {
    $this->puffer_leeren();
    if (!$daten['id'] || !ereg('^[0-9]*$',$daten['id'])) {
      return -1;
    }
    return $this->update_backend($this->sql("update",$daten));
  }

  function aktualisiere_akt($id){
    $this->puffer_leeren();
    if (!$id ||  !ereg('^[0-9]*$',$id)) {
      return -1;
    }
    if (!$this->Qresult=$this->db->query($this->sql('aktualisiere_akt',$id))) {
      fehler("personen-&gt;aktualisiere_akt(" . $id . ")");
      return -2;
    }
    @$this->puffer_leeren();
    return 0;
  }

  function pruefe_login($login,$pw){
    if (!$this->Qresult=$this->db->query(
		 $this->sql('get_pw', $login))) {
      fehler("personen-&gt;pruefe_login(" . $login . ',passwort)');
      return false;
    }
    $this->Werte=$this->db->fetch_array($this->Qresult);
    return ($this->Werte['pw']==crypt($pw,$this->Werte['pw']));
  }

  function login_exists($login){
    if (!$this->Qresult=$this->db->query($this->sql('login_exists',$login))) {
      fehler("personen-&gt;login_exists(" . $login . ')');
      return false;
    }
    $this->Werte=$this->db->fetch_array($this->Qresult);
    return $this->Werte['id'];
  }

  function loeschen($id,$tr_aktiv=0){
    echo "Transaktion: ";
    if (!$tr_aktiv){
      $status=!($this->db->transaction_start());
    }
    if (!$status) {
      echo "OK<br />Adressen: ";
      $tabelle= new adresse($this->db);
      $status=$tabelle->loeschen(0,$id,1);
      if (!$status) {
	echo "OK<br />Emails: ";
	$tabelle= new email($this->db);
	$status= $tabelle->loeschen(0,$id);
      }
      if (!$status) {
	echo "OK<br />Emails: ";
	$tabelle= new homepage($this->db);
	$status= $tabelle->loeschen(0,$id);
      }
      if (!$status) {
	echo "OK<br />Emails: ";
	$tabelle= new jg($this->db);
	$status= $tabelle->loeschen(0,$id);
      }
      if (!$status) {
	echo "OK<br />Emails: ";
	$tabelle= new telefon($this->db);
	$status= $tabelle->loeschen(0,$id);
      }
      if (!$status) {
	echo "OK<br />Emails: ";
	$status=parent::loeschen($id);
      } else echo "Fehler<br />";
    } else echo "Fehler<br />";
    if (!$tr_aktiv){
      if ($status) $this->db->rollback();
      else $this->db->commit();
    }
    return $status;
  }

  /* die einzelnen Felder der Person */

  function id() {
    return $this->Werte["id"];
  }

  function aktueller_name() {
    return $this->Werte["aktueller_name"];
  }

  function geburtsname() {
    return $this->Werte["geburtsname"];
  }

  function vorname() {
    return $this->Werte["vorname"];
  }

  function kommentar() {
    return $this->Werte["kommentar"];
  }

  function aktualisierung() {
    return $this->Werte["aktualisierung"];
  }
  
  function login() {
    return $this->Werte["login"];
  }
  
  function normprint($erstespalte=false){
    global $layout;
    $adresse=new adresse($this->db);
    $telefon=new telefon($this->db);
    $hp=new homepage($this->db); 
    $email=new email($this->db);
    do {
      echo $layout['tabtrenner']. "\n";
?>
<tr class="absolventen anzeige anzeige_jg"><?=$erstespalte?>
<td class="absolventen anzeige anzeige_geburtsname"><?=$this->geburtsname()?></td>
<td class="absolventen anzeige anzeige_vorname"><?=$this->vorname()?></td><?php
   if ($adresse->erste_person($this->id())){
     $adrzeilen=$adresse->erstprint($telefon);
     ?></tr>
<tr class="absolventen anzeige anzeige_jg"><td class="absolventen anzeige anzeige_leer"></td>
<td class="absolventen anzeige anzeige_akuteller_name"><?=$this->aktueller_name()?></td><?php 
     $adresse->zweitprint();?></tr><?php
     if ($adrzeilen==3) {
       print('<tr class="absolventen anzeige anzeige_jg"><td colspan="2 class="absolventen anzeige anzeige_leer""></td>');
       $adresse->drittprint();
       print('</tr>');
     }
     if ($adresse->naechste()){
       $adresse->normprint($telefon);
     }
     if ($telefon->erste_person_ohne_adr($this->id())){
       $telefon->normprint();
     }
   } else {
?>
<td colspan="2" class="absolventen anzeige adresse adr_anfang"></td><td rowspan="2" class="absolventen anzeige adresse telefon"><?php 
     if ($telefon->erste_person_ohne_adr($this->id())){
       $telefon->nurtelprint();
     }
?></td></tr>
<tr class="absolventen anzeige anzeige_jg">
<td class="absolventen anzeige anzeige_leer"></td>
<td class="absolventen anzeige anzeige_akuteller_name"><?=$this->aktueller_name()?></td>
<td class="absolventen anzeige adresse adr_plz"></td><td class="absolventen anzeige adresse adr_ort"></td></tr>
   <?php } ?>
<tr class="absolventen anzeige anzeige_jg">
<td colspan="2" valign="bottom" class="absolventen anzeige anzeige_timestamp"><font 
size="-2" class="absolventen anzeige anzeige_timestamp"><?=$this->aktualisierung()?></font></td><td colspan="3" <?php
   if ($istemail=$email->erste_person($this->id())) {
     print('class="absolventen anzeige anzeige_email">');
     $email->normprint($erstespalte);
   }
   if ($hp->erste_person($this->id())) {
     if ($istemail) {
       echo "</td></tr>\n";
       echo '<tr><td colspan="2"></td><td colspan="3"';
     }
     print ('class="absolventen anzeige anzeige_hp">');
     $hp->normprint($erstespalte);
   } else if (!$istemail) print ('class="absolventen anzeige anzeige_leer">');
?>
</td></tr>
<?php
      if ($this->kommentar()) {
     ?><tr class="absolventen anzeige anzeige_jg">
	  <td colspan="5" class="absolventen anzeige anzeige_bemerkungen"><?=$this->kommentar()?></td></tr>
<?php
      }
    } while ($this->naechste());
    $adresse->puffer_leeren();
    $telefon->puffer_leeren();
    $hp->puffer_leeren(); 
    $email->puffer_leeren();
  } 

  function mailformopts(){
    $email=new email($this->db);
    $mailformopts=array();
    do {
      $email->erste_nurformular($this->id());
      $neuformopts=$email->mailformopts();
      $mailformopts=array_merge($mailformopts,$neuformopts);
    } while ($this->naechste());
    $email->puffer_leeren();
    return $mailformopts;
  } 

  function formular($neu,$daten=0,$fehler=0) {
    global $PHP_SELF;
?>
<form method="post" action="<?=$PHP_SELF?>" class="absolventen person formular">
<input type="hidden" name="aktion" 
   value="<?=$neu?"persdbneu":"persdbaendern"?>" />
<?php if (!empty($daten['id'])) { ?>
<input type="hidden" name="id" value="<?=$daten['id']?>" />
			  <?php } ?>
<table border="0" class="absolventen person formular">
  <tr class="absolventen person formular pers_vorname">
    <th class="absolventen person formular pers_vorname"><label 
        class="absolventen person formular pers_vorname" 
        for="abs_vorname">Vorname</label></th>
    <td class="absolventen person formular pers_vorname"><input type="text" name="vorname" 
        id="abs_vorname"
        class="absolventen person formular pers_vorname<?=isset($fehler['vorname'])?" fehler":""?>"
        value="<?=isset($daten['vorname'])?$daten['vorname']:""?>" size="40" maxlength="40" /></td>
  </tr>
  <tr class="absolventen person formular pers_aktueller_name">
    <th class="absolventen person formular pers_aktueller_name"><label 
        class="absolventen person formular pers_aktueller_name"
        for="abs_aktname">aktueller Name</label></th>
    <td class="absolventen person formular pers_aktueller_name"><input type="text" name="aktueller_name" 
	id="abs_aktname"
        class="absolventen person formular pers_aktueller_name<?=isset($fehler['aktueller_name'])?" fehler":""?>"
        value="<?=isset($daten['aktueller_name'])?$daten['aktueller_name']:""?>" size="40" maxlength="40" /></td>
  </tr>
  <tr class="absolventen person formular pers_geburtsname">
    <th class="absolventen person formular pers_geburtsname"><label 
        class="absolventen person formular pers_geburtsname" 
        for="abs_gebname">Geburtsname</label></th>
    <td class="absolventen person formular pers_geburtsname"><input type="text" name="geburtsname" 
        id="abs_gebname"
        class="absolventen person formular pers_geburtsname<?=isset($fehler['geburtsname'])?" fehler":""?>"
        value="<?=isset($daten['geburtsname'])?$daten['geburtsname']:""?>" size="40" maxlength="40" /></td>
  </tr>
  <tr class="absolventen person formular pers_bemerkungen">
    <th class="absolventen person formular pers_bemerkungen"><label 
        class="absolventen person formular pers_bemerkungen" 
        for="abs_bemerkungen">Bemerkungen</label></th>
    <td class="absolventen person formular pers_bemerkungen"><textarea name="kommentar" cols="40" rows="5"  
	id="abs_bemerkungen"
        class="absolventen person formular pers_bemerkungen<?=isset($fehler['kommentar'])?" fehler":""
          ?>"><?=isset($daten['kommentar'])?preg_replace("/<br[^>]*>/i","",
		    $daten["kommentar"]):""?></textarea></td>
  </tr>
  <tr class="absolventen person formular pers_login">
    <th class="absolventen person formular pers_login"><label 
        class="absolventen person formular pers_login" 
        for="abs_login">Nutzername</label></th>
    <td class="absolventen person formular pers_login"><input type="text" name="login" 
	id="abs_login"
        class="absolventen person formular pers_login<?=isset($fehler['login'])?" fehler":""?>"
        value="<?=isset($daten['login'])?$daten['login']:""?>" size="40" maxlength="255" /></td>
  </tr>
  <tr class="absolventen person formular pers_pw pers_pw1">
    <th class="absolventen person formular pers_pw pers_pw1"><label 
        class="absolventen person formular pers_pw pers_pw1" 
        for="abs_pw1">Passwort</label></th>
    <td class="absolventen person formular pers_pw pers_pw1"><input type="password" name="pw1" 
        id="abs_pw1"
        class="absolventen person formular pers_pw pers_pw1<?=(isset($fehler['pw'])||
               isset($fehler['pw1']))?" fehler":""?>"
        value="" size="40" maxlength="40" /></td>
  </tr>
  <tr class="absolventen person formular pers_pw pers_pw2">
    <th class="absolventen person formular pers_pw pers_pw2"><label 
        class="absolventen person formular pers_pw pers_pw2" 
        for="abs_pw2">Passwort wiederholen</label></th>
    <td class="absolventen person formular pers_pw pers_pw2"><input type="password" name="pw2"
	id="abs_pw2"
        class="absolventen person formular pers_pw pers_pw2<?=(isset($fehler['pw'])||
               isset($fehler['pw2']))?" fehler":""?>"
        value="" size="40" maxlength="40" /></td>
  </tr>
  <tr class="absolventen person formular knoepfe">
    <td colspan="2" align="center" class="absolventen person formular knoepfe">
      <input type="submit"  class="absolventen person formular knoepfe"
        value="<?=$neu?"Einf&uuml;gen":"&Auml;ndern"?>" />&nbsp;<input
        class="absolventen person formular knoepfe" type="reset" value="Zur&uuml;cksetzen" /></td>
  </tr>
</table>
</form>
<?php if (!empty($fehler)) { ?>
<form method="post" action="<?=$PHP_SELF?>" class="absolventen jahrgang formular">
  <input type="hidden" name="aktion" value="<?=$neu?"hinzufuegen":"persformaendern"?>" />
  <input type="submit"  value="Abbrechen" 
	class="absolventen jahrgang formular knoepfe jg_loeschen" />
</form><?php } ?>
<?php
  }

  function checkdaten(&$daten,$neu) {
    $fehler=array();
    if (empty($daten['vorname'])) $fehler['vorname']="Der Vorname fehlt."; 
    if (empty($daten['aktueller_name'])) $fehler['aktueller_name']="Der aktuelle Name fehlt."; 
    if (empty($daten['geburtsname'])) $fehler['geburtsname']="Der &bdquo;Geburtsname&rdquo; fehlt."; 
    if (empty($daten['login'])) $fehler['login']="Der Nutzername fehlt."; 
    if (($neu && (empty($daten['pw1']) ||empty($daten['pw1']))) || 
	((!empty($daten['pw1']) || !empty($daten['pw1'])) && 
	 (empty($daten['pw1']) ||empty($daten['pw1']) || $daten['pw1']!=$daten['pw2'])))
      $fehler['pw']="Es wurden keine zwei identischen Passw&ouml;rter eingegeben.";
    if (!empty($daten['login']) && $lid=$this->login_exists($daten['login'])){
      if(empty($daten['id']) || $lid!=$daten['id']) {
	  $fehler[empty($fehler['login'])?'login':'login2'] = "Der Nutzername wird von schon von einem Nutzer verwendet." .
	    $empty($daten['id'])?" Melden Sie sich bitte gegebenenfalls unter Ihrem Nutzernamen an, bevor Sie Daten ändern.":"";
      }
    }
    if (!empty($daten['id']) && (empty($_SESSION['mod_absolventen']['uid']) || $daten['id']!=$_SESSION['mod_absolventen']['uid'])) {
      $fehler[] = "Zugriff verweigert!";
    }
    return $fehler;
    //    if ($daten['pw1']) $daten['pw']=$daten['pw1'];
  }
}
?>
