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

class homepage   extends dbtabelle{
  function sql($funktion,$args){
    global $mysql_daten;
    switch ($funktion) {
	case "erste_person": 
		return sprintf("select id, uid, adresse, name"
		               . " from %s where uid=%d",
			$mysql_daten['HPTab'],$args);
  	case "diese": 
		return sprintf("select id,uid, adresse, name"
			       . " from %s where id=%d",
			$mysql_daten['HPTab'],$args);
	case "insert":
		return sprintf("insert into %s (%suid,adresse,name"
			       . ") values (%s%d,'%s','%s')",
			       $mysql_daten['HPTab'],
			       $args['id']?"id,":"",
			       $args['id']?$args['id'] . ',':"",
			       $args['uid'],
			       addslashes($args['adresse']),
			       addslashes($args['name']));
	case "update":
		return sprintf("update %s set uid=%d,adresse='%s',name='%s'"
			       . " where id=%d",
			       $mysql_daten['HPTab'],
			       $args['uid'],
			       addslashes($args['adresse']),
			       addslashes($args['name']),
			       $args['id']);
	case "loeschen":
	        return sprintf("delete from %s where id=%d",$mysql_daten['HPTab'],$args);
    }
  }
	
  function homepage ($h_db=0) {
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

  function adresse() {
    return $this->Werte["adresse"];
  }

  function name() {
    return $this->Werte["name"];
  }

  
  function normprint($erstspalte=""){
    printf('<a href="%s">%s</a>',$this->adresse(),$this->name());
    while ($this->naechste()) {
      printf("<br />\n" . '<a href="%s">%s</a>',$this->adresse(),$this->name());
    }
  }
  /* adresse,name */

  function formular($daten=0) {
    if (!$daten) $daten=array('uid' => $_SESSION['uid']);
?>
<form method="post" action="<?=$PHP_SELF?>">
<input type="hidden" name="aktion" 
   value="<?=$daten['id']?"hpdbaendern":"hpdbneu"?>" />
   <?php if ($daten['id']) { ?>
<input type="hidden" name="id" value="<?=$daten['id']?>" />
			  <?php } ?>
<input type="hidden" name="uid" value="<?=$daten['uid']?>" />
<table border="0">
<tr><td>Name der Adresse</td><td>
<input type="text" size=30 name="name" value="<?=$daten['name']?>" /></td></tr>
<tr><td>Adresse</td><td>
<input type="text" size=30 name="adresse" value="<?=$daten['adresse']?>" /></td></tr>
<tr><td colspan="2" align="center">
   <input type="submit" 
   value="<?=$daten['id']?"&Auml;ndern":"Einf&uuml;gen"?>" />&nbsp;<input
   type="reset" value="Zur&uuml;cksetzen" /></td></tr>
</table>
</form>
<?php if ($daten['id']) { ?>
<form method="post" action="<?=$PHP_SELF?>">
<input type="hidden" name="aktion" value="hpdbloeschen" />
<input type="hidden" name="id" value="<?=$daten['id']?>" />
   <input type="submit"  value="L&ouml;schen" />
</form>
<font size="-1">
<b>Hinweis:</b> Um Probleme mit unterschiedlichen Browsern und WWW-Server-Konfigurationen zu vermeiden, 
			  bitten wir darum, die Adresse Standard-konform in entsprechend
<tt>http://[nutzername[:passwort]@]rechner.example.com[:port]/[pfad/zur/datei/[datei.ext]]</tt>
anzugeben. Die eckigen Klammern bezeichnen hierbei Teile, die weggelassen werden können. Insbesondere Schrägstriche am Ende der Adresse sind <em><b>kein</b></em> Luxus.
</font>
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
    //"^http://[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+\.[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+$"
    if (!ereg("^http://([^:@ ]+(:[^@]*)?@)?"
	      . "[^@ /.:]+\.[^@ /:]+"
	      . "(:[0-9]+)?/[^@ :]*$",$daten['adresse'])) 
      $fehler.="<br />Ung&uuml;ltige WWW-Adresse";
    return $fehler;
  }
}
?>
