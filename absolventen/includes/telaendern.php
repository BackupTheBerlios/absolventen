<?php



if (!$db = @mysql_connect($mysql_daten['Rechner'], $mysql_daten['Nutzer'], $mysql_daten['Passwort'])){
  authenticate();
}

function nochmal(){
          Fehlermeldung('Die Passw&ouml;rter sind nicht identisch.');  
}


mysql_select_db($mysql_daten['Datenbank'],$db);

if ($id) {
    if ($aktion=="Telefonnummer hinzufügen"){
          if ($vorwahl||$telefon)
            $sql=sprintf("insert Telefon (vorwahl,telefon,uid) values (%s,%s,%s)",
                 $vorwahl?'"'.($vorwahl).'"':"NULL",
                 $telefon?'"'.($telefon).'"':"NULL",
                 $id);
           else $sql="";
          if (ereg("^[0-9]*$",$id) && $sql) mysql_query($sql,$db);
                       
        } else{
          if ($aktion=="Telefonnummer ändern")
              if ($vorwahl||$telefon) {
                $sql=sprintf("update Telefon set vorwahl=%s,telefon=%s where uid=%s and id=%s",
                  $vorwahl?'"'.($vorwahl).'"':"NULL",
                  $telefon?'"'.($telefon).'"':"NULL",
                  $id,$tid); echo $sql;
              } else $aktion="Telefonnummer löschen";
            
          if($aktion=="Telefonnummer löschen")
            $sql="delete from Telefon where id=$tid and uid=$id";         
          if (ereg("^[0-9]*$",$aid)&&ereg("^[0-9]*$",$id)&& $sql)
            mysql_query($sql,$db);
        }
        include('bearbeiten.php');
    } else { include('index.html');die;
}
//include('ende.php'); 
  
?>