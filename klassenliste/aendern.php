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

function nochmal($Fehler,$id,$geburtsname,$vorname,$aktname,$kommentar,$neupass1,$neupass2,$PHP_SELF){
    include('anfang.php');
    echo $Fehler;
?>
<table border=2>
<tr align=center><td>
<form method="post" action="<?php echo $PHP_SELF; ?>">
<input type="hidden" name="id" value="<?php echo $id;?>">
<?php if (isset($penne)) {?>
<input type="hidden" name="penne" value="ja">
<?php }?>
<table border="0">
<tr><td>Geburtsname<sup>*</sup></td><td><input type="text" name="geburtsname" 
  value="<?php echo $geburtsname;?>" maxlength=40 size=30></td></tr>
<tr><td>Vorname<sup>*</sup></td><td><input type="text" name="vorname" 
  value="<?php echo $vorname;?>" maxlength=40 size=30></td></tr>
<tr><td>aktueller Name<sup>*</sup></td><td><input type="text" name="aktname" 
  value="<?php echo $aktname;?>" maxlength=40 size=30></td></tr>
<tr><td>Bemerkungen</td><td><textarea cols=30 rows=5 name="kommentar"><?php echo str_replace("<br>","",nl2br(str_replace("&amp;","&",htmlspecialchars($kommentar))));?></textarea>
<tr><td>neues Passwort</td><td><input type="password" size=8 maxlength=8 name="neupass1"></td></tr>
<tr><td>neues Passwort wiederholen</td><td><input type="password" size=8 maxlength=8 name="neupass2"></td></tr>
<tr align=center><td colspan=2>
<input type="submit" name="aktion" value="&Auml;ndern"> <input type="reset" value="Zur&uuml;cksetzen">
</td></tr>
</table>
</form>
</table>

<?php
    include('ende.php');
    die;
}


mysql_select_db($mysql_daten['DB'],$db);

if ($id){
  $sql="select encrypt('$PHP_AUTH_PW',pw)=pw as richtig"
//      ."to_days(now())-to_days(aktualisierung)=0 and time_to_sec(now())-time_to_sec(aktualisierung)<600 as zeit" 
      ." from StAg where id=$id";
  $result=mysql_query($sql,$db);
  if ($Ergebnis=@mysql_fetch_array($result)){ 
    if ($Ergebnis["richtig"]==1&&$PHP_AUTH_USER==$id){
#      printf("%d %s, %d %s, %d %s",strlen($vorname),$vorname,);
      if(strlen($vorname)==0 || strlen($geburtsname)==0 || strlen($aktname)==0) 
        nochmal("Vorname,aktueller Name und Geburtsname m&uuml;ssen angegeben werden.",$id,$geburtsname,$vorname,$aktname,$kommentar,$neupass1,$neupass2,$PHP_SELF);

      $vorname=str_replace("&amp;","&",htmlspecialchars($vorname));
      
      $geburtsname=str_replace("&amp;","&",htmlspecialchars($geburtsname));
      $aktname=str_replace("&amp;","&",htmlspecialchars($aktname));
      $kommentar=nl2br(str_replace("&amp;","&",htmlspecialchars($kommentar)));
      $sql=sprintf("update StAg set vorname=\"%s\", geburtsname=\"%s\""
           .", aktueller_name=\"%s\", kommentar=\"%s\"",
           AddSlashes($vorname),AddSlashes($geburtsname),AddSlashes($aktname),AddSlashes($kommentar));
      if ($neupass1||$neupass2) {
        if ($neupass1==$neupass2) 
          $sql .= sprintf(", pw=encrypt(\"%s\")",AddSlashes($neupass1));
        else { 
          nochmal('Die beiden Passw&ouml;rter m&uuml;ssen identisch sein.',$id,$geburtsname,$vorname,$aktname,$kommentar,$neupass1,$neupass2,$PHP_SELF);
        }
      }
      $sql .= " where id=$id";
      mysql_query($sql,$db);
      include('bearbeiten.php');
    } else authenticate($id);
  } else { include('index.html');die;}
} else { include('index.html');die;
}
//include('ende.php'); 
  
?>