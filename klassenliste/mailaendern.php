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


      if ((!ereg( "^[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+@[-!#$%&\'*+\\/0-9=?A-Z^_`a-z{|}~]+\.[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+$",$adresse))&&
            !($aktion=="Email löschen")) {
        include('anfang.php');
?>
<emph>Bei der Adresse scheint es sich nicht um eine g&uuml;ltige Mailadresse zu handeln.<br>
Bitte nochmal prüfen!</emph>
<table border="2">
<tr align=center><td>
<form method="post" action="<?php echo $PHP_SELF ?>">
<?php if (isset($penne)) {?>
<input type="hidden" name="penne" value="ja">
<?php }?>
<input type="hidden" name="id" value="<?php echo $id;?>">
<input type="hidden" name="mid" value="<?php echo $mid;?>">
<table border=0>
<tr><td>Email</td><td><input type="text" size=40 maxlength=255 name="adresse" value="<?php echo $adresse;?>"></td></tr>
<tr align=center><td colspan=2><input type="submit" name="aktion" value="<?php echo $aktion;?>">
<input type="reset" value="Zur&uuml;cksetzen"></td></tr>
</table>
</form>
</td></tr></table>
<?php   include('ende.php');
      } else {
      
        $adresse=str_replace("&amp;","&",htmlspecialchars($adresse));

        if ($aktion=="Email hinzufügen"){
          if ($adresse)
            $sql=sprintf("insert StAgMail (adresse,uid) values (\"%s\",%s)",
                 $adresse,
                 $id);
           else $sql="";
          if (ereg("^[0-9]*$",$id) && $sql) mysql_query($sql,$db);
                       
        } else{
          if ($aktion=="Email ändern")
              if ($adresse) {
                $sql=sprintf("update StAgMail set adresse=\"%s\" where uid=%s and id=%s",
                  AddSlashes($adresse),$id,$mid); 
              } else $aktion="Email löschen";
            
          if($aktion=="Email löschen")
            $sql="delete from StAgMail where id=$mid and uid=$id";         
          if (ereg("^[0-9]*$",$mid)&&ereg("^[0-9]*$",$id)&& $sql)
            mysql_query($sql,$db);
        }
        include('bearbeiten.php');
      }
    } else authenticate($id);
  } else { include('index.html');die;}
} else { include('index.html');die;
}
//include('ende.php'); 
  
?>