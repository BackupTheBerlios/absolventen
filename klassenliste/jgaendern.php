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
  function  authenticate($id)  {
    Header( sprintf("WWW-authenticate: Basic realm=\"Klassenliste Authentifikation. Als Nutzer-ID bitte %d eingeben.\"",$id));
    Header( "HTTP/1.0  401  Unauthorized");
    include('anfang.php');
    echo  "<font size=7 color=red><blink>Zugriff verweigert.</blink></font>\n";
    include('ende.php');
    exit;
  }



if (!$db = @mysql_connect($mysql_daten['Rechner'], $mysql_daten['Nutzer'], $mysql_daten['Passwort'])){
  include('anfang.php');
  Fehlermeldung('Die Verbindung zum Datenbank-Server ist nicht möglich.');
}

function nochmal(){
          Fehlermeldung('Die Passw&ouml;rter sind nicht identisch.');  
}


mysql_select_db($mysql_daten['DB'],$db);

if ($id) {
  $sql="select encrypt('$PHP_AUTH_PW',pw)=pw as richtig,"
      ."to_days(now())-to_days(aktualisierung)=0 and time_to_sec(now())-time_to_sec(aktualisierung)<600 as zeit" 
      ." from StAg where id=$id";
  $result=mysql_query($sql,$db);
  if ($Ergebnis=@mysql_fetch_array($result)){ 
    if ($Ergebnis["richtig"]==1&&$PHP_AUTH_USER==$id){
      if (!(ereg("^[a-zA-Z0-9]{0,2}$",$klasse) && ereg("^[0-9]{0,4}$",$jahrgang) && ereg("^(ja|nein)$",$drin))&& 
            (!(aktion=="Jahrgang löschen"))) {
        include('anfang.php');
?>
<emph>Sie m&uuml;ssen einen Jahrgang zum Datensatz angeben und ob sie in diesem Jahrgang Ihr Abitur gemacht haben!<br>
Die Klasse darf nur aus maximal 2 alphanumerischen Zeichen bestehen, w&auml;hrend der Jahrgang eine Zahl sein muss.</emph>
<table border="2">
<tr align=center><td>
<form method="post" action="<?php echo $PHP_SELF ?>">
<?php if (isset($penne)) {?>
<input type="hidden" name="penne" value="ja">
<?php }?>
<input type="hidden" name="id" value="<?php echo $id;?>">
<input type="hidden" name="jid" value="<?php echo $jid;?>">
<table border=0>
<tr><td>Jahrgang</td><td><input type="text" size=4  maxlength=4 name="jahrgang" value="<?php echo $jahrgang; ?>"></td></tr>
<tr><td>Klasse</td><td><input type="text" size=2 maxlength=2 name="klasse" value="<?php echo $klasse; ?>"></td></tr>
<tr><td>Haben Sie Ihr Abitur im gleichen Jahr gemacht?</td>
<td><input type="radio" name="drin" value="ja" <?php if ($drin=="ja") echo "checked";?>>Ja
<input type="radio" name="drin" value="nein" <?php if ($drin=="nein") echo "checked";?>>Nein</td></tr>
<tr align=center><td colspan=2><input type="submit" name="aktion" value="<?php echo $aktion;?>"> <input type="reset" value="Zur&uuml;cksetzen"></td></tr>
</table>
</form>
</td></tr></table>
<?php   include('ende.php');
      } else {
        if ($aktion=="Jahrgang hinzufügen")
          $sql=sprintf("insert StAgJg (jahrgang,klasse,drin,uid) values (%s,\"%s\",%d,%s)",$jahrgang,$klasse,($drin=="ja"?1:0),$id);
        else{ 
          $sql="select uid from StAgJg where id=$jid";
          $result=mysql_query($sql,$db);
          if ($Ergebnis=@mysql_fetch_array($result))
            if ($Ergebnis["uid"]==$id){
              if($aktion=="Jahrgang löschen")
                $sql="delete from StAgJg where id=$jid";
               else  
                $sql=sprintf("update StAgJg set jahrgang=%s, klasse=\"%s\", drin=%d where id=%s and uid=%s",$jahrgang,$klasse,($drin=="ja"?1:0),$jid,$id);
           }
        }
        if (ereg("^[0-9]*$",$jid)&&ereg("^[0-9]*$",$id)&& $sql)
          mysql_query($sql,$db);
        include('bearbeiten.php');
        
      }
    } else authenticate($id);
  } else { include('index.html');die;}
} else { include('index.html');die;
}
//include('ende.php'); 
  
?>