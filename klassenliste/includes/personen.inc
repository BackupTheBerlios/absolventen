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

class personen {
  var $db;
  var $sql;
  var $Werte;
  var $Qresult;
  
  function personen ($h_db=0) {
    $this->db=$h_db;
  }

  function puffer_leeren() {
    if ($this->Qresult) {
      $this->db->puffer_leeren($this->Qresult);
      $this->Qresult=0;
    }
  }

  function erste_jahrgang($jahrgang,$klasse,$drin){
    $this->puffer_leeren();
    $sql="select StAg.id as "
      . "id,login,aktueller_name,geburtsname,vorname,kommentar,"
      . "DATE_FORMAT(aktualisierung,'%d.%m.%Y %T') as aktualisierung "
      . "from StAg,StAgJg"
      . " where StAgJg.jahrgang=" . $jahrgang 
      . " and StAgJg.klasse='" . $klasse
      . "' and StAgJg.drin=". $drin
      . " and StAgJg.uid=StAg.id"
      . " order by geburtsname,vorname,aktueller_name";
    if (!$this->Qresult=$this->db->query($sql)) {
      fehler("personen-&gt;erste_jahrgang(" . $jahrgang . ','
	     . $klasse . "," . $drin . ")");
      return false;
    }
    $this->Werte=$this->db->fetch_array($this->Qresult);
    return ($this->Werte != false);
  }

  function diese($id){
    $this->puffer_leeren();
    $sql="select id,login,aktueller_name,geburtsname,vorname,kommentar,"
      . "DATE_FORMAT(aktualisierung,'%d.%m.%Y %T') as aktualisierung "
      . "from StAg"
      . " where id=" . $id;
    if (!$this->Qresult=$this->db->query($sql)) {
      fehler("personen-&gt;diese(" . $id . ")");
      return false;
    }
    $this->Werte=$this->db->fetch_array($this->Qresult);
    return ($this->Werte != false);
  }

  function insert($daten) {
    $this->puffer_leeren();
    if ($daten['id'] && !ereg('^[0-9]*$',$daten['id'])) {
      return -1;
    }
    $sql=sprintf("insert into StAg (%slogin,aktueller_name,geburtsname,"
		 . "vorname,kommentar,pw) values (%s'%s','%s','%s','%s','%s',"
		 . "encrypt('%s'))",$daten['id']?"id,":"",
		 $daten['id']?addslashes($daten['id']) . ',':"",
		 addslashes($daten['login']),
		 addslashes($daten['aktueller_name']),
		 addslashes($daten['geburtsname']),
		 addslashes($daten['vorname']),
		 addslashes(nl2br($daten['kommentar'])),
		 addslashes($daten['pw']));
    if (!$this->Qresult=$this->db->query($sql)) {
      fehler("personen-&gt;insert(" . $daten . ")");
      return -2;
    }
    $id=@$this->puffer_leeren();
    return $id;
  }

  function update($daten) {
    $this->puffer_leeren();
    if (!$daten['id'] ||  !ereg('^[0-9]*$',$daten['id'])) {
      return -1;
    }
    $sql=sprintf("update StAg set login='%s',aktueller_name='%s',"
		 . "geburtsname='%s',vorname='%s',kommentar='%s'%s"
		 . "where id=%d",
		 addslashes($daten['login']),
		 addslashes($daten['aktueller_name']),
		 addslashes($daten['geburtsname']),
		 addslashes($daten['vorname']),
		 addslashes(nl2br($daten['kommentar'])),
		 $daten['pw']?",pw=encrypt('" 
		   . addslashes($daten['pw']) . "')":"",
		 $daten['id']);
    if (!$this->Qresult=$this->db->query($sql)) {
      fehler("personen-&gt;update(" . $daten . ")");
      return -2;
    }
    @$this->puffer_leeren();
    return 0;
  }

  function aktualisiere_akt($id){
    $this->puffer_leeren();
    if (!$id ||  !ereg('^[0-9]*$',$id)) {
      return -1;
    }
    $sql=sprintf("update StAg set aktualisierung=now() "
		 . "where id=%d",
		 $id);
    if (!$this->Qresult=$this->db->query($sql)) {
      fehler("personen-&gt;aktualisiere_akt(" . $id . ")");
      return -2;
    }
    @$this->puffer_leeren();
    return 0;
  }

  function pruefe_login($login,$pw){
    $sql="select aktueller_name,geburtsname,vorname,"
      . "id,pw=encrypt('" . $pw . "',pw) as richtig "
      . "from StAg where login='" . $login . "'";
    if (!$this->Qresult=$this->db->query($sql)) {
      fehler("personen-&gt;pruefe_login(" . $login . ',passwort)');
      return false;
    }
    $this->Werte=$this->db->fetch_array($this->Qresult);
    return $this->Werte['richtig'];
  }

  function login_exists($login){
    $sql="select id "
      . "from StAg where login='" . $login . "'";
    if (!$this->Qresult=$this->db->query($sql)) {
      fehler("personen-&gt;pruefe_login(" . $login . ',passwort)');
      return false;
    }
    $this->Werte=$this->db->fetch_array($this->Qresult);
    return $this->Werte['id'];
  }

  function naechste(){
    return $this->Werte=$this->db->fetch_array($this->Qresult);
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
  
  function normprint($erstspalte=""){
    global $layout;
    $adresse=new adresse($this->db);
    $telefon=new telefon($this->db);
    $hp=new homepage($this->db); 
    $email=new email($this->db);
    do {
      echo $layout['tabtrenner'];
?>
<tr><?=$erstespalte?><td><?=$this->geburtsname()?></td><td><?=$this->vorname()?></td><?php
   if ($adresse->erste_person($this->id())){
     $adrzeilen=$adresse->erstprint($telefon);
     ?></tr>
<tr><td></td><td><?=$this->aktueller_name()?></td><?php 
     $adresse->zweitprint();?></tr><?php
     if ($adrzeilen==3) {
       print('<tr><td colspan="2"></td>');
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
<td colspan=2></td><td rowspan=2><?php 
   if ($telefon->erste_person_ohne_adr($this->id())){
     $telefon->nurtelprint();
   }
?></td></tr>
<tr><td></td><td><?=$this->aktueller_name()?></td><td colspan=2></td><td></td></tr>
   <?php } ?>
<tr><td colspan="2" valign="bottom"><font size="-2"><?=$this->aktualisierung()?></font></td><td colspan="3"><?php
   if ($email->erste_person($this->id())) {
     $email->normprint($erstespalte);
   }
   if ($hp->erste_person($this->id())) {
     echo "</td></tr>\n";
     echo '<tr><td colspan="2"></td><td colspan="3">';
     $hp->normprint($erstespalte);
   } ?>
</td></tr>
<?php
      if ($this->kommentar()) {
     ?><tr><td colspan="5"><?=$this->kommentar()?></td></tr>
<?php
      }
    } while ($this->naechste());
    $adresse->puffer_leeren();
    $telefon->puffer_leeren();
    $hp->puffer_leeren(); 
    $email->puffer_leeren();
  } 

  function formular($daten=0) {
?>
<form method="post" action="<?=$PHP_SELF?>">
<input type="hidden" name="aktion" 
   value="<?=$daten['id']?"persdbaendern":"persdbneu"?>" />
<?php if ($daten['id']) { ?>
<input type="hidden" name="id" value="<?=$daten['id']?>" />
			  <?php } ?>
<table border="0">
<tr><td>Geburtsname</td><td><input type="text" name="geburtsname"
   value="<?=$daten['geburtsname']?>" size="40" maxlength="40" /></td></tr>
<tr><td>aktueller Name</td><td><input type="text" name="aktueller_name"
   value="<?=$daten['aktueller_name']?>" size="40" maxlength="40" /></td></tr>
<tr><td>Vorname</td><td><input type="text" name="vorname"
   value="<?=$daten['vorname']?>" size="40" maxlength="40" /></td></tr>
<tr><td>Bemerkungen</td>
<td><textarea name="kommentar" cols="40" rows="5" 
><?=preg_replace("/<br[^>]*>/i","",$daten["kommentar"])?></textarea></td></tr>
<tr><td>Nutzername</td><td><input type="text" name="login"
   value="<?=$daten['login']?>" size="40" maxlength="255" /></td></tr>
<tr><td>Passwort</td><td><input type="password" name="pw1"
   value="<?=$daten['pw1']?>" size="40" maxlength="40" /></td></tr>
<tr><td>Passwort wiederholen</td><td><input type="password" name="pw2"
   value="<?=$daten['pw2']?>" size="40" maxlength="40" /></td></tr>
<tr><td colspan="2" align="center">
   <input type="submit" 
   value="<?=$daten['id']?"&Auml;ndern":"Einf&uuml;gen"?>" />&nbsp;<input
   type="reset" value="Zur&uuml;cksetzen" /></td></tr>
</table>
</form>
<?php
  }

  function datenformular() {
    $this->formular($this->Werte);
  }

  function checkdaten($daten,$pwforce=0) {
    $fehler="";
    if (!$daten['geburtsname']) $fehler.="<br />Der Geburtsname fehlt."; 
    if (!$daten['aktueller_name']) $fehler.="<br />Der aktuelle Name fehlt."; 
    if (!$daten['vorname']) $fehler.="<br />Der Vorname fehlt."; 
    if (!$daten['login']) $fehler.="<br />Der Nutzername fehlt."; 
    if ($lid=$this->login_exists($daten['login'])){
      if($lid!=$daten['id']) {
	$fehler .= "<br />Der Nutzername wird von einem anderen Nutzer verwendet.";
      }
    }
    if (($pwforce && !$daten['pw1']) || ($daten['pw1']!=$daten['pw2']))
      $fehler.="<br/>Es wurden keine zwei identischen " 
	. "Passw&ouml;rter eingegeben.";
    return $fehler;
    if ($daten['pw1']) $daten['pw']=$daten['pw1'];
  }
}
?>