<?php


if (!$db = @mysql_connect($mysql_daten['Rechner'], $mysql_daten['Nutzer'], $mysql_daten['Passwort'])){
  authenticate();
}

function nochmal(){
          Fehlermeldung('Die Passw&ouml;rter sind nicht identisch.');  
}


mysql_select_db($mysql_daten['Datenbank'],$db);

if ($id) {
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
        
             
        if (!$name) $name=$adresse;

        if ($aktion=="WWW-Adresse hinzufügen"){
          if ($adresse)
            $sql=sprintf("insert HP (adresse,name,uid) values (%s,%s,%s)",
                 $adresse?'"'.($adresse).'"':"NULL",
                 $name?'"'.($name).'"':"NULL",
                 $id);
           else $sql="";
          if (ereg("^[0-9]*$",$id) && $sql) mysql_query($sql,$db);
                       
        } else{
          if ($aktion=="WWW-Adresse ändern")
              if ($adresse) {
                $sql=sprintf("update HP set adresse=%s,name=%s where uid=%s and id=%s",
                  $adresse?'"'.($adresse).'"':"NULL",
                  $name?'"'.($name).'"':"NULL",
                  $id,$hpid); 
              } else $aktion="Adresse löschen";
            
          if($aktion=="WWW-Adresse löschen")
            $sql="delete from HP where id=$hpid and uid=$id";         
          if (ereg("^[0-9]*$",$hpid)&&ereg("^[0-9]*$",$id)&& $sql)
            mysql_query($sql,$db);
        }
        include('bearbeiten.php');
       }
    } else { include('index.html');die;
}
//include('ende.php'); 
  
?>