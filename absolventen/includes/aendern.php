<?php

if (!$db = @mysql_connect($mysql_daten['Rechner'], $mysql_daten['Nutzer'], $mysql_daten['Passwort'])){ 
   authenticate();
}

function nochmal($Fehler,$id,$geburtsname,$vorname,$aktname,$kommentar,$von,$bis,$studiengang,$geburtsdatum,$geschlecht,$grad,$PHP_SELF){
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
<tr><td>Akademischer Grad </td><td><input type="text" name="grad" value="<?php echo $grad?>" maxlength=20 size=20></td></tr>
<tr><td>Geburtsname<sup>*</sup></td><td><input type="text" name="geburtsname" 
  value="<?php echo $geburtsname;?>" maxlength=40 size=30></td></tr>
<tr><td>Vorname<sup>*</sup></td><td><input type="text" name="vorname" 
  value="<?php echo $vorname;?>" maxlength=40 size=30></td></tr>
<tr><td>aktueller Name<sup>*</sup></td><td><input type="text" name="aktname" 
  value="<?php echo $aktname;?>" maxlength=40 size=30></td></tr>
<tr><td>Bemerkungen</td><td><textarea cols=30 rows=5 name="kommentar"><?php echo str_replace("<br>","",nl2br(str_replace("&amp;","&",htmlspecialchars($kommentar))));?></textarea>
<tr><td>Zeit</td><td><input type="text" size=4 maxlength=4 name="von" value="<?php echo $von ?>">-<input type="text" size=4 maxlength=4 name="bis" value="<?php echo $bis ?>"></td></tr>
<tr><td>Studiengang</td><td><input type="text" name="studiengang" maxlength=40 size=30 name="studiengang" value="<?php echo $studiengang;?>"></td></tr>
<tr><td>Geburtsdatum</td><td><input type="text" name="geburtsdatum" maxlength=12 size=12 name="geburtsdatum" value="<?php echo $geburtsdatum;?>"></td></tr>
<tr><td>Geschlecht</td><td><input type="radio" name="geschlecht" <?php if ($geschlecht==1) echo "checked" ?> value="1">männlich 
<input type="radio" name="geschlecht" value="2"<?php if ($geschlecht==2) echo "checked" ?>>weiblich</td></tr>
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


mysql_select_db($mysql_daten['Datenbank'],$db);

if ($id) {
#      printf("%d %s, %d %s, %d %s",strlen($vorname),$vorname,);
      if(strlen($vorname)==0 || strlen($geburtsname)==0 || strlen($aktname)==0) 
        nochmal("Vorname,aktueller Name und Geburtsname m&uuml;ssen angegeben werden.",$id,$geburtsname,$vorname,$aktname,$kommentar,$von,$bis,
                 $studiengang,$geburtsdatum,$geschlecht,$grad,$PHP_SELF);

#      $vorname=str_replace("&amp;","&",htmlspecialchars($vorname));
      
#      $geburtsname=str_replace("&amp;","&",htmlspecialchars($geburtsname));
#      $aktname=str_replace("&amp;","&",htmlspecialchars($aktname));
#      $kommentar=nl2br(str_replace("&amp;","&",htmlspecialchars($kommentar)));
      if ($geburtsdatum){
  ereg("^([0-9]{1,2})[\.,]([0-9]{1,2})[\.,]([0-9]{2,4})$",$geburtsdatum,$datum);
      $sql=sprintf("update Personen set vorname=\"%s\", geburtsname=\"%s\""
           .", aktueller_name=\"%s\", kommentar=\"%s\", von=%d, bis=%d, studiengang=\"%s\", geburtsdatum='%d-%d-%d',grad=\"%s\",geschlecht=%d",
           ($vorname),($geburtsname),($aktname),($kommentar),($von),($bis),
	   ($studiengang),$datum[3],$datum[2],$datum[1],($grad),$geschlecht);
      } else
      $sql=sprintf("update Personen set vorname=\"%s\", geburtsname=\"%s\""
           .", aktueller_name=\"%s\", kommentar=\"%s\", von=%d, bis=%d, studiengang=\"%s\",geburtsdatum=null,grad=\"%s\",geschlecht=%d",
           ($vorname),($geburtsname),($aktname),($kommentar),($von),($bis),
	   ($studiengang),($grad),$geschlecht);
 
      $sql .= " where id=$id";
      mysql_query($sql,$db);
      include('bearbeiten.php');
    } else { include('index.html');die;
}
//include('ende.php'); 
  
?>
