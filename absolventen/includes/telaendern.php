<?php



if (!$db = @mysql_connect($mysql_daten['Rechner'], $mysql_daten['Nutzer'], $mysql_daten['Passwort'])){
  authenticate();
}

function nochmal(){
          Fehlermeldung('Die Passw&ouml;rter sind nicht identisch.');  
}


mysql_select_db($mysql_daten['Datenbank'],$db);

if ($id) {
    if ($aktion=="Telefonnummer hinzuf�gen"){
          if ($vorwahl||$telefon)
            $sql=sprintf("insert Telefon (vorwahl,telefon,uid) values (%s,%s,%s)",
                 $vorwahl?'"'.($vorwahl).'"':"NULL",
                 $telefon?'"'.($telefon).'"':"NULL",
                 $id);
           else $sql="";
          if (ereg("^[0-9]*$",$id) && $sql) mysql_query($sql,$db);
                       
        } else{
          if ($aktion=="Telefonnummer �ndern")
              if ($vorwahl||$telefon) {
                $sql=sprintf("update Telefon set vorwahl=%s,telefon=%s where uid=%s and id=%s",
                  $vorwahl?'"'.($vorwahl).'"':"NULL",
                  $telefon?'"'.($telefon).'"':"NULL",
                  $id,$tid); echo $sql;
              } else $aktion="Telefonnummer l�schen";
            
          if($aktion=="Telefonnummer l�schen")
            $sql="delete from Telefon where id=$tid and uid=$id";         
          if (ereg("^[0-9]*$",$aid)&&ereg("^[0-9]*$",$id)&& $sql)
            mysql_query($sql,$db);
        }
        include('bearbeiten.php');
    } else { include('index.html');die;
}
//include('ende.php'); 
  
?>