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
	        return sprintf("insert into %s (%slogin,aktueller_name,geburtsname,"
			       . "vorname,kommentar,pw) values (%s'%s','%s','%s','%s','%s',"
			       . "encrypt('%s'))",$args['id']?"id,":"",
			       $mysql_daten['PersTab'],
			       $args['id']?addslashes($args['id']) . ',':"",
			       addslashes($args['login']),
			       addslashes($args['aktueller_name']),
			       addslashes($args['geburtsname']),
			       addslashes($args['vorname']),
			       addslashes(nl2br($args['kommentar'])),
			       addslashes($args['pw']));

	case "update":
                return sprintf("update %s set login='%s',aktueller_name='%s',"
			       . "geburtsname='%s',vorname='%s',kommentar='%s'%s"
			       . "where id=%d",
			       $mysql_daten['PersTab'],
			       addslashes($daten['login']),
			       addslashes($daten['aktueller_name']),
			       addslashes($daten['geburtsname']),
			       addslashes($daten['vorname']),
			       addslashes(nl2br($daten['kommentar'])),
			       $daten['pw']?",pw=encrypt('" 
			       . addslashes($daten['pw']) . "')":"",
			       $daten['id']);

        case "loeschen":
	        return sprintf("delete from %s where id=%d",$mysql_daten['PersTab'],$args);

        case "erste_jahrgang":
	        return sprintf("select %s.id as "
			       . "id,login,aktueller_name,geburtsname,vorname,kommentar,"
			       . "DATE_FORMAT(aktualisierung,'%%d.%%m.%%Y %%T') as aktualisierung "
			       . "from %s,%s"
			       . " where %s.jahrgang=%d"
			       . " and %s.klasse='%s' and %s.drin=%d". $drin
			       . " and %s.uid=%s.id"
			       . " order by geburtsname,vorname,aktueller_name",
			       $mysql_daten['PersTab'],
			       $mysql_daten['PersTab'],
			       $mysql_daten['JgTab'],
			       $mysql_daten['JgTab'],
			       $args['jahrgang'],
			       $mysql_daten['JgTab'],
			       addslashes($args['klasse']),
			       $mysql_daten['JgTab'],
			       $args['drin'],
			       $mysql_daten['JgTab'],
			       $mysql_daten['PersTab']);
        case "aktualisiere_akt":
                return sprintf("update %s set aktualisierung=now() "
			       . "where id=%d",
			       $mysql_daten['PersTab'],
			       $args);
        case "pruefe_login":
        	return sprintf("select aktueller_name,geburtsname,vorname,"
			       . "id,pw=encrypt('%s',pw) as richtig "
			       . "from %s where login='%s'",
			       addslashes($args['pw']),
			       $mysql_daten['PersTab'],
			       $args['login']);
        case "login_exists":
	  return sprintf("select id from %s where login='%s'",
			 $mysql_daten['PersTab'],addslashes($args));

    }
  }
	
  function personen ($h_db=0) {
    $this->dbtabelle($h_db);
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
    if ($daten['id'] && !ereg('^[0-9]*$',$daten['id'])) {
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
		 $this->sql('pruefe_login',array('pw' => $pw, 'login' => $login)))) {
      fehler("personen-&gt;pruefe_login(" . $login . ',passwort)');
      return false;
    }
    $this->Werte=$this->db->fetch_array($this->Qresult);
    return $this->Werte['richtig'];
  }

  function login_exists($login){
    if (!$this->Qresult=$this->db->query($this->sql('login_exists',$login))) {
      fehler("personen-&gt;login_exists(" . $login . ')');
      return false;
    }
    $this->Werte=$this->db->fetch_array($this->Qresult);
    return $this->Werte['id'];
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