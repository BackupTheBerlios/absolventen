<?php



if (!$db = @mysql_connect($mysql_daten['Rechner'], $mysql_daten['Nutzer'], $mysql_daten['Passwort'])){
  include('anfang.php');
  Fehlermeldung('Die Verbindung zum Datenbank-Server ist nicht möglich.');
}

function nochmal(){
          Fehlermeldung('Die Passw&ouml;rter sind nicht identisch.');  
}


mysql_select_db($mysql_daten['Datenbank'],$db);
if ($id) {
    if ($aktion=="Adresse hinzufügen"){
          if ($anfang||$plz||$ort||$ende)
             $sql=sprintf("insert into Adressen (anfang,plz,ort,ende,vorwahl,telefon,uid) values (%s,\"%s\",\"%s\",%s,%s,%s,%s)",
                 $anfang?'"'.($anfang).'"':"NULL",
                 ($plz),($ort),
                 $ende?'"'.($ende).'"':"NULL",
                 $vorwahl?'"'.($vorwahl).'"':"NULL",
                 $telefon?'"'.($telefon).'"':"NULL",
                 $id);

           else if ($vorwahl||$telefon)
            $sql=sprintf("insert into Telefon (vorwahl,telefon,uid) values (%s,%s,%s)",
                 $vorwahl?'"'.($vorwahl).'"':"NULL",
                 $telefon?'"'.($telefon).'"':"NULL",
                 $id);
           else $sql="";
         if (ereg("^[0-9]*$",$id) && $sql) {mysql_query($sql,$db);} 
                       
        } else{
          if ($aktion=="Adresse ändern")
            if ($anfang||$plz||$ort||$ende)
              $sql=sprintf("update Adressen set anfang=%s, plz=\"%s\",ort=\"%s\",ende=%s,vorwahl=%s,telefon=%s,aktiv=%d where id=%s and uid=%s",
                 $anfang?'"'.($anfang).'"':"NULL",
                 ($plz),($ort),
                 $ende?'"'.($ende).'"':"NULL",
                 $vorwahl?'"'.($vorwahl).'"':"NULL",
                 $telefon?'"'.($telefon).'"':"NULL",
                 $aktiv,
                 $aid,$id);
            else {
              $aktion="Adresse löschen";
              if ($vorwahl||$telefon) {
                $sql=sprintf("insert Telefon (vorwahl,telefon,uid) values (%s,%s,%s)",
                  $vorwahl?'"'.($vorwahl).'"':"NULL",
                  $telefon?'"'.($telefon).'"':"NULL",
                  $id);
                if (ereg("^[0-9]*$",$id) && $sql) mysql_query($sql,$id);
              }
            }
          if($aktion=="Adresse löschen")
            $sql="delete from Adressen where id=$aid and uid=$id";         
          if (ereg("^[0-9]*$",$aid)&&ereg("^[0-9]*$",$id)&& $sql)
            mysql_query($sql,$db);
        }
        include('bearbeiten.php');
    }else { include('index.html');die;
}
//include('ende.php'); 
  
?>