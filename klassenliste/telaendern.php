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
      
        $vorwahl=str_replace("&amp;","&",htmlspecialchars($vorwahl));
        $telefon=str_replace("&amp;","&",htmlspecialchars($telefon));

        if ($aktion=="Telefonnummer hinzufügen"){
          if ($vorwahl||$telefon)
            $sql=sprintf("insert StAgTel (vorwahl,telefon,uid) values (%s,%s,%s)",
                 $vorwahl?'"'.AddSlashes($vorwahl).'"':"NULL",
                 $telefon?'"'.AddSlashes($telefon).'"':"NULL",
                 $id);
           else $sql="";
          if (ereg("^[0-9]*$",$id) && $sql) mysql_query($sql,$db);
                       
        } else{
          if ($aktion=="Telefonnummer ändern")
              if ($vorwahl||$telefon) {
                $sql=sprintf("update StAgTel set vorwahl=%s,telefon=%s where uid=%s and id=%s",
                  $vorwahl?'"'.AddSlashes($vorwahl).'"':"NULL",
                  $telefon?'"'.AddSlashes($telefon).'"':"NULL",
                  $id,$tid); echo $sql;
              } else $aktion="Telefonnummer löschen";
            
          if($aktion=="Telefonnummer löschen")
            $sql="delete from StAgTel where id=$tid and uid=$id";         
          if (ereg("^[0-9]*$",$aid)&&ereg("^[0-9]*$",$id)&& $sql)
            mysql_query($sql,$db);
        }
        include('bearbeiten.php');
    } else authenticate($id);
  } else { include('index.html');die;}
} else { include('index.html');die;
}
//include('ende.php'); 
  
?>