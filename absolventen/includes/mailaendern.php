<?php
if (!$db = @mysql_connect($mysql_daten['Rechner'], $mysql_daten['Nutzer'], $mysql_daten['Passwort'])){
  authenticate();
}

function nochmal(){
          Fehlermeldung('Die Passw&ouml;rter sind nicht identisch.');  
}


mysql_select_db($mysql_daten['Datenbank'],$db);

if ($id) {
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
            $sql=sprintf("insert EMail (adresse,uid) values (\"%s\",%s)",
                 $adresse,
                 $id);
           else $sql="";
          if (ereg("^[0-9]*$",$id) && $sql) mysql_query($sql,$db);
                       
        } else{
          if ($aktion=="Email ändern")
              if ($adresse) {
                $sql=sprintf("update EMail set adresse=\"%s\" where uid=%s and id=%s",
                  ($adresse),$id,$mid); 
              } else $aktion="Email löschen";
            
          if($aktion=="Email löschen")
            $sql="delete from EMail where id=$mid and uid=$id";         
          if (ereg("^[0-9]*$",$mid)&&ereg("^[0-9]*$",$id)&& $sql)
            mysql_query($sql,$db);
        }
        include('bearbeiten.php');
      }
    }else { include('index.html');die;
}
//include('ende.php'); 
  
?>