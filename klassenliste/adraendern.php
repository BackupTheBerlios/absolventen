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
      
        $anfang=nl2br(str_replace("&amp;","&",htmlspecialchars($anfang)));
        $plz=str_replace("&amp;","&",htmlspecialchars($plz));
        $ort=str_replace("&amp;","&",htmlspecialchars($ort));
        $ende=nl2br(str_replace("&amp;","&",htmlspecialchars($ende)));
        $vorwahl=str_replace("&amp;","&",htmlspecialchars($vorwahl));
        $telefon=str_replace("&amp;","&",htmlspecialchars($telefon));

        if ($aktion=="Adresse hinzufügen"){
          if ($anfang||$plz||$ort||$ende)
             $sql=sprintf("insert StAgAdr (anfang,plz,ort,ende,vorwahl,telefon,uid) values (%s,\"%s\",\"%s\",%s,%s,%s,%s)",
                 $anfang?'"'.AddSlashes($anfang).'"':"NULL",
                 AddSlashes($plz),AddSlashes($ort),
                 $ende?'"'.AddSlashes($ende).'"':"NULL",
                 $vorwahl?'"'.AddSlashes($vorwahl).'"':"NULL",
                 $telefon?'"'.AddSlashes($telefon).'"':"NULL",
                 $id);

           else if ($vorwahl||$telefon)
            $sql=sprintf("insert StAgTel (vorwahl,telefon,uid) values (%s,%s,%s)",
                 $vorwahl?'"'.AddSlashes($vorwahl).'"':"NULL",
                 $telefon?'"'.AddSlashes($telefon).'"':"NULL",
                 $id);
           else $sql="";
          if (ereg("^[0-9]*$",$id) && $sql) mysql_query($sql,$db);
                       
        } else{
          if ($aktion=="Adresse ändern")
            if ($anfang||$plz||$ort||$ende)
              $sql=sprintf("update StAgAdr set anfang=%s, plz=\"%s\",ort=\"%s\",ende=%s,vorwahl=%s,telefon=%s where id=%s and uid=%s",
                 $anfang?'"'.AddSlashes($anfang).'"':"NULL",
                 AddSlashes($plz),AddSlashes($ort),
                 $ende?'"'.AddSlashes($ende).'"':"NULL",
                 $vorwahl?'"'.AddSlashes($vorwahl).'"':"NULL",
                 $telefon?'"'.AddSlashes($telefon).'"':"NULL",
                 $aid,$id);
            else {
              $aktion="Adresse löschen";
              if ($vorwahl||$telefon) {
                $sql=sprintf("insert StAgTel (vorwahl,telefon,uid) values (%s,%s,%s)",
                  $vorwahl?'"'.AddSlashes($vorwahl).'"':"NULL",
                  $telefon?'"'.AddSlashes($telefon).'"':"NULL",
                  $id);
                if (ereg("^[0-9]*$",$id) && $sql) mysql_query($sql,$id);
              }
            }
          if($aktion=="Adresse löschen")
            $sql="delete from StAgAdr where id=$aid and uid=$id";         
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