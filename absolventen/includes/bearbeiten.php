<?php if (!$db = @mysql_connect($mysql_daten['Rechner'], $mysql_daten['Nutzer'], $mysql_daten['Passwort'])){
  authenticate();
}
anfang();
echo "<H2>Datensatz Bearbeiten/L&ouml;schen</H2>";
//echo "<br> $db <br>";

mysql_select_db($mysql_daten['Datenbank'],$db);

if ($id) {
  $sql="select aktueller_name,vorname,geburtsname,aktualisierung,kommentar,von,bis,studiengang,DATE_FORMAT(geburtsdatum,'%d.%m.%Y')as geburtsdatum"
	.",geschlecht,grad from Personen where id=$id";
  $result=mysql_query($sql,$db);
  if ($Person=@mysql_fetch_array($result)){
?>
<H3>Pers&ouml;nliche Daten</H3>
<table border=2>
<tr align=center><td>
<form method="post" action="<?php echo $PHP_SELF ?>">
<input type="hidden" name="id" value="<?php echo $id?>">
<?php if (isset($penne)) {?>
<input type="hidden" name="penne" value="ja">
<?php } ?>
<table border="0">
<tr><td>Akademischer Grad </td><td><input type="text" name="grad" value="<?php echo $Person["grad"]?>" maxlength=20 size=20></td></tr>
<tr><td>Geburtsname<sup>*</sup></td><td><input type="text" name="geburtsname" 
  value="<?php echo $Person["geburtsname"]?>" maxlength=40 size=30></td></tr>
<tr><td>Vorname<sup>*</sup></td><td><input type="text" name="vorname" 
  value="<?php echo $Person["vorname"]?>" maxlength=40 size=30 name="vorname"></td></tr>
<tr><td>aktueller Name<sup>*</sup></td><td><input type="text" name="aktname" 
  value="<?php echo $Person["aktueller_name"]?>" maxlength=40 size=30></td></tr>
<tr><td>Bemerkungen</td><td><textarea cols=30 rows=5 name="kommentar"><?php echo str_replace("<br>","",$Person["kommentar"])?></textarea>
<tr><td>Zeitspanne</td>
<td><input type="text" name="von" value="<?php echo $Person["von"]?>" maxlength=4 size=4>-<input type="text" name="bis" value="<?php echo $Person["bis"]?>" maxlength=4 size=4>
<tr><td>Studiengang</td><td><input type="text" name="studiengang" maxlength=40 size=30 name="studiengang" value="<?php echo $Person["studiengang"];?>"></td></tr>
<tr><td>Geburtsdatum</td><td><input type="text" name="geburtsdatum" maxlength=12 size=12 name="geburtsdatum" value="<?php echo $Person["geburtsdatum"];?>"></td></tr>
<tr><td>Geschlecht</td><td><input type="radio" name="geschlecht" <?php if ($Person["geschlecht"]==1) echo "checked" ?> value="1">männlich 
<input type="radio" name="geschlecht" value="2" <?php if ($Person["geschlecht"]==2) echo "checked" ?>>weiblich</td></tr>
<tr align=center><td colspan=2>
<input type="submit" name="aktion" value="&Auml;ndern"> <input type="reset" value="Zur&uuml;cksetzen">
</td></tr>
</table>
</form>
</table>

<?php
    $sql="select id as aid,anfang,plz,ort,ende,vorwahl,telefon,aktiv from Adressen "
        ."where uid=$id order by aktiv desc"; 
    $Adressen=mysql_query($sql,$db);
  ?><br><<?php echo $dividier ?> width="95%"><br>
<H3>Adressen</H3>
<table border="2">
<?php
  while ($Adresse=@mysql_fetch_array($Adressen)){    
?>
<tr align=center><td>
<form method="post" action="<?php echo $PHP_SELF ?>">
<?php if (isset($penne)) {?>
<input type="hidden" name="penne" value="ja">
<?php }?>
<input type="hidden" name="id" value="<?php echo $id?>">
<input type="hidden" name="aid" value="<?php echo $Adresse["aid"]?>">
<table border=0>
<tr><td>Priorit&auml;t<sup>**</sup></td><td><input type=text name=aktiv value="<?=$Adresse["aktiv"]?>" size=4 maxlength=8></td>
<tr><td>Adresse erster Teil</td><td><textarea cols=30 rows=2 name="anfang"><?php echo $Adresse["anfang"]?></textarea></td></tr>
<tr><td>PLZ Ort</td><td><input type="text" size=5 maxlength=25 name="plz" value="<?php echo $Adresse["plz"];?>"> 
  <input type="text" size=20 maxlength=40 name="ort" value="<?php echo $Adresse["ort"];?>"></td></tr>
<tr><td>Adresse zweiter Teil</td><td><textarea cols=30 rows=2 name="ende"><?php echo $Adresse["ende"]?></textarea></td></tr>
<tr><td>Vorwahl</td><td><input type="text" size=20 maxlength=30 name="vorwahl" value="<?php echo $Adresse["vorwahl"]?>"></td></tr>
<tr><td>Telefon</td><td><input type="text" size=20 maxlength=30 name="telefon" value="<?php echo $Adresse["telefon"]?>"></td></tr>
<tr align=center><td colspan=2><input type="submit" name="aktion" value="Adresse &auml;ndern">
<input type="submit" name="aktion" value="Adresse l&ouml;schen">
<input type="reset" value="Zur&uuml;cksetzen"></td></tr>
</table>
</form>
<?php
}
?>
<tr align=center><td>
<form method="post" action="<?php echo $PHP_SELF ?>">
<?php if (isset($penne)) {?>
<input type="hidden" name="penne" value="ja">
<?php }?>
<input type="hidden" name="id" value="<?php echo $id?>">
<table border=0>
<tr><td>Priorit&auml;t<sup>**</sup></td><td><input type=text name=aktiv size=4 maxlength=8></td>
<tr><td>Adresse erster Teil</td><td><textarea cols=30 rows=2 name="anfang"></textarea></td></tr>
<tr><td>PLZ Ort</td><td><input type="text" size=5 maxlength=25 name="plz"> 
  <input type="text" size=20 maxlength=40 name="ort"></td></tr>
<tr><td>Adresse zweiter Teil</td><td><textarea cols=30 rows=2 name="ende"></textarea></td></tr>
<tr><td>Vorwahl</td><td><input type="text" size=20 maxlength=30 name="vorwahl"></td></tr>
<tr><td>Telefon</td><td><input type="text" size=20 maxlength=30 name="telefon"></td></tr>
<tr align=center><td colspan=2><input type="submit" name="aktion" value="Adresse hinzuf&uuml;gen"> <input type="reset" value="Zur&uuml;cksetzen"></td></tr>
</table></td></tr></form>
</table>


<?php
    $sql="select id,vorwahl,telefon from Telefon "
        ."where uid=$id"; 
    $Adressen=mysql_query($sql,$db);
  ?><br><<?php echo $dividier ?> width="95%"><br>
<H3>Sonstige Telefonnummern</H3>
<table border="2">
<?php
  while ($Adresse=@mysql_fetch_array($Adressen)){    
?>
<tr align=center><td>
<form method="post" action="<?php echo $PHP_SELF ?>">
<?php if (isset($penne)) {?>
<input type="hidden" name="penne" value="ja">
<?php }?>
<input type="hidden" name="id" value="<?php echo $id?>">
<input type="hidden" name="tid" value="<?php echo $Adresse["id"]?>">
<table border=0>
<tr><td>Vorwahl</td><td><input type="text" size=20 maxlength=30 name="vorwahl" value="<?php echo $Adresse["vorwahl"]?>"></td></tr>
<tr><td>Telefon</td><td><input type="text" size=20 maxlength=30 name="telefon" value="<?php echo $Adresse["telefon"]?>"></td></tr>
<tr align=center><td colspan=2><input type="submit" name="aktion" value="Telefonnummer &auml;ndern">
<input type="submit" name="aktion" value="Telefonnummer l&ouml;schen">
<input type="reset" value="Zur&uuml;cksetzen"></td></tr>
</table>
</form>
<?php
}
?>
<tr align=center><td>
<form method="post" action="<?php echo $PHP_SELF ?>">
<?php if (isset($penne)) {?>
<input type="hidden" name="penne" value="ja">
<?php }?>
<input type="hidden" name="id" value="<?php echo $id?>">
<table border=0>
<tr><td>Vorwahl</td><td><input type="text" size=20 maxlength=30 name="vorwahl"></td></tr>
<tr><td>Telefon</td><td><input type="text" size=20 maxlength=30 name="telefon"></td></tr>
<tr align=center><td colspan=2><input type="submit" name="aktion" value="Telefonnummer hinzuf&uuml;gen"> <input type="reset" value="Zur&uuml;cksetzen"></td></tr>
</table></td></tr></form>
</table>

<?php
    $sql="select id,adresse from EMail "
        ."where uid=$id"; 
    $Adressen=mysql_query($sql,$db);
  ?><br><<?php echo $dividier ?> width="95%"><br>
<H3>E-Mail-Adressen</H3>
<table border="2">
<?php
  while ($Adresse=@mysql_fetch_array($Adressen)){    
?>
<tr align=center><td>
<form method="post" action="<?php echo $PHP_SELF ?>">
<?php if (isset($penne)) {?>
<input type="hidden" name="penne" value="ja">
<?php }?>
<input type="hidden" name="id" value="<?php echo $id?>">
<input type="hidden" name="mid" value="<?php echo $Adresse["id"]?>">
<table border=0>
<tr><td>Email</td><td><input type="text" size=40 maxlength=255 name="adresse" value="<?php echo $Adresse["adresse"]?>"></td></tr>
<tr align=center><td colspan=2><input type="submit" name="aktion" value="Email &auml;ndern">
<input type="submit" name="aktion" value="Email l&ouml;schen">
<input type="reset" value="Zur&uuml;cksetzen"></td></tr>
</table>
</form>
<?php
}
?>
<tr align=center><td>
<form method="post" action="<?php echo $PHP_SELF ?>">
<?php if (isset($penne)) {?>
<input type="hidden" name="penne" value="ja">
<?php }?>
<input type="hidden" name="id" value="<?php echo $id?>">
<table border=0>
<tr><td>Email</td><td><input type="text" size=40 maxlength=255 name="adresse"></td></tr>
<tr align=center><td colspan=2><input type="submit" name="aktion" value="Email hinzuf&uuml;gen"> <input type="reset" value="Zur&uuml;cksetzen"></td></tr>
</table></td></tr></form>
</table>

<?php
    $sql="select id,adresse,name from HP "
        ."where uid=$id"; 
    $Adressen=mysql_query($sql,$db);
  ?><br><<?php echo $dividier ?> width="95%"><br>
<H3>WWW-Adressen</H3>
<table border="2">
<?php
  while ($Adresse=@mysql_fetch_array($Adressen)){    
?>
<tr align=center><td>
<form method="post" action="<?php echo $PHP_SELF ?>">
<?php if (isset($penne)) {?>
<input type="hidden" name="penne" value="ja">
<?php }?>
<input type="hidden" name="id" value="<?php echo $id?>">
<input type="hidden" name="hpid" value="<?php echo $Adresse["id"]?>">
<table border=0>
<tr><td>Adresse</td><td><input type="text" size=40 maxlength=255 name="adresse" value="<?php echo $Adresse["adresse"]?>"></td></tr>
<tr><td>Name</td><td><input type="text" size=40 maxlength=255 name="name" value="<?php echo $Adresse["name"]?>"></td></tr>
<tr align=center><td colspan=2><input type="submit" name="aktion" value="WWW-Adresse &auml;ndern">
<input type="submit" name="aktion" value="WWW-Adresse l&ouml;schen">
<input type="reset" value="Zur&uuml;cksetzen"></td></tr>
</table>
</form>
<?php
}
?>
<tr align=center><td>
<form method="post" action="<?php echo $PHP_SELF ?>">
<?php if (isset($penne)) {?>
<input type="hidden" name="penne" value="ja">
<?php }?>
<input type="hidden" name="id" value="<?php echo $id?>">
<table border=0>
<tr><td>Adresse</td><td><input type="text" size=40 maxlength=255 name="adresse"></td></tr>
<tr><td>Name</td><td><input type="text" size=40 maxlength=255 name="name"></td></tr>
<tr align=center><td colspan=2><input type="submit" name="aktion" value="WWW-Adresse hinzuf&uuml;gen">
<input type="reset" value="Zur&uuml;cksetzen"></td></tr>
</table></td></tr></form>
</table>
<br><<?php echo $dividier ?> width=50%><br>
<sup>*</sup>Bei den mit diesen Angaben gekennzeichneten Feldern muss immer mindestens eines f&uuml;r jede Person ausgef&uuml;llt sein.
D.h. z.B. es muss mindestens ein Jahrgang für die Person angegeben werden.<br>
<sup>**</sup>Bei der Erstellung von Serienbriefen wird automatisch die Adresse
mit der größten Priorität verwendet.
<?php
   Personentermine_anzeigen($id);
}
else{
?>
Der Datensatz wurde leider nicht gefunden.<br>
Beginnen Sie <a href="<?php echo $PHP_SELF?>?aktion=bearbeiten$penne">hier</a> noch einmal!
<?php 
  }
}else
{
  anzeige("bearbeiten");
}
ende();
?>
