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
      if ((!ereg( "^http://[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+\.[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+$",$adresse))&&
            (!(aktion=="WWW-Adresse löschen"))) {
        include('anfang.php');
?>
<emph>Bei der Adresse scheint es sich nicht um eine g&uuml;ltige URL zu handeln.<br>
Bitte nochmal prüfen!</emph>
<table border="2">
<tr align=center><td>
<form method="post" action="<?php echo $PHP_SELF ?>">
<?php if (isset($penne)) {?>
<input type="hidden" name="penne" value="ja">
<?php }?>
<input type="hidden" name="id" value="<?php echo $id;?>">
<input type="hidden" name="hpid" value="<?php echo $hpid;?>">
<table border=0>
<tr><td>Adresse</td><td><input type="text" size=40 maxlength=255 name="adresse" value="<?php echo $adresse;?>"></td></tr>
<tr><td>Name</td><td><input type="text" size=40 maxlength=255 name="name" value="<?php echo $adresse;?>"></td></tr>
<tr align=center><td colspan=2>
<input type="submit" name="aktion" value="<?php echo $aktion;?>">
<input type="reset" value="Zur&uuml;cksetzen"></td></tr>
</table>
</form>
</td></tr></table>
<?php   include('ende.php');
      } else {
        
             
        $name=str_replace("&amp;","&",htmlspecialchars($name));
        $adresse=str_replace("&amp;","&",htmlspecialchars($adresse));
        if (!$name) $name=$adresse;

        if ($aktion=="WWW-Adresse hinzufügen"){
          if ($adresse)
            $sql=sprintf("insert StAgHP (adresse,name,uid) values (%s,%s,%s)",
                 $adresse?'"'.AddSlashes($adresse).'"':"NULL",
                 $name?'"'.AddSlashes($name).'"':"NULL",
                 $id);
           else $sql="";
          if (ereg("^[0-9]*$",$id) && $sql) mysql_query($sql,$db);
                       
        } else{
          if ($aktion=="WWW-Adresse ändern")
              if ($adresse) {
                $sql=sprintf("update StAgHP set adresse=%s,name=%s where uid=%s and id=%s",
                  $adresse?'"'.AddSlashes($adresse).'"':"NULL",
                  $name?'"'.AddSlashes($name).'"':"NULL",
                  $id,$hpid); 
              } else $aktion="Adresse löschen";
            
          if($aktion=="WWW-Adresse löschen")
            $sql="delete from StAgHP where id=$hpid and uid=$id";         
          if (ereg("^[0-9]*$",$hpid)&&ereg("^[0-9]*$",$id)&& $sql)
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