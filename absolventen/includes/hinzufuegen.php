<?php 
//echo "<br> $db <br>";
if (!$db = @mysql_connect($mysql_daten['Rechner'], $mysql_daten['Nutzer'], $mysql_daten['Passwort'])){
  authenticate();
}
unset($Fehler);
if (isset($vorname)){
//|| $geburtsname || $aktname || $kommentar || $neupass1 || $neupass2 || $jahrgang || $klasse
//    || $drin || $anfang || $plz || $ort || $ende || $vorwahl || $telefon || $zvorwahl || $ztelefon || $mail || $hpadresse || $hpname){

   if(!$vorname)     $Fehler = "Der Vorname fehlt.<br>\n";
   if(!$geburtsname) $Fehler .= "Der Geburtsname fehlt.<br>\n";
   if(!$aktname)     $Fehler .= "Der aktuelle Name fehlt.<br>\n";

   if($geburtsdatum && !ereg("^[0-9]{1,2}[\.,][0-9]{1,2}[\.,][0-9]{2,4}$",$geburtsdatum)) $Fehler .= "Das Datum muss numerisch im Format tag.monat.jahr angegeben werden.<br>\n";

   if ($mail && !ereg( "^[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+@[-!#$%&\'*+\\/0-9=?A-Z^_`a-z{|}~]+\.[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+$",$mail))
     $Fehler .= "Die Mailadresse scheint ung&uuml;ltig zu sein.<br>\n";

   if ($hpadresse && (!ereg( "^http://[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+\.[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+/.*$",$hpadresse)))
     $Fehler .= "Die WWW-Adresse scheint fehlerhaft zu sein.<br>\n";


} else $Fehler=0;

if (isset($Fehler)){
if ($Fehler) include('anfang.php'); 
?>
<H2>Neuen Datensatz hinzuf&uuml;gen</H2>
<?php if ($Fehler) {
     echo "<font color=\"#FF0000\"><br><blink>Ung&uuml;ltige Eingabe</blink>\n<br>";
     echo $Fehler;
     echo "</font>";
}?>
<form method="post" action="<?php echo $PHP_SELF ?>">
<?php if (isset($penne)) echo "  <input type=\"hidden\" name=\"penne\" value=\"ja\">";?>
 <H3>Pers&ouml;nliche Daten</H3>
<table border=2>
<tr align=center><td>
<table border="0">
<tr><td>Akademischer Grad </td><td><input type="text" name="grad" value="<?php echo $grad ?>" maxlength=20 size=20></td></tr>
<tr><td>Geburtsname<sup>*</sup></td><td><input type="text" name="geburtsname" value="<?php echo $geburtsname;?>" maxlength=40 size=30></td></tr>
<tr><td>Vorname<sup>*</sup></td><td><input type="text" name="vorname" maxlength=40 size=30 name="vorname" value="<?php echo $vorname;?>"></td></tr>
<tr><td>aktueller Name<sup>*</sup></td><td><input type="text" name="aktname" 
  value="<?php echo $aktname;?>" maxlength=40 size=30></td></tr>
<tr><td>Bemerkungen</td><td><textarea cols=30 rows=5 name="kommentar"><?php echo str_replace("<br>","",$kommentar);?></textarea>
<tr><td>Zeit</td><td><input type="text" size=4 maxlength=4 name="von" value="<?php echo $von?>">-<input type="text" size=4 maxlength=4 name="bis" value="<?php echo $bis?>"></td></tr>
<tr><td>Studiengang</td><td><input type="text" name="studiengang" maxlength=40 size=30 name="studiengang" value="<?php echo $studiengang;?>"></td></tr>
<tr><td>Geburtsdatum</td><td><input type="text" name="geburtsdatum" maxlength=12 size=12 name="geburtsdatum" value="<?php echo $geburtsdatum;?>"></td></tr>
<tr><td>Geschlecht</td><td><input type="radio" name="geschlecht" <?php if ($geschlecht==1) echo "checked" ?> value="1">männlich 
<input type="radio" name="geschlecht" value="2"<?php if ($geschlecht==2) echo "checked" ?>>weiblich</td></tr>
</table>
</table>

<H3>Adressen</H3>
<table border="2">
<tr align=center><td>
<tr><td>Adresse erster Teil</td><td><textarea cols=30 rows=2 name="anfang"><?php echo str_replace("<br>","",$anfang);?></textarea></td></tr>
<tr><td>PLZ Ort</td><td><input type="text" size=5 maxlength=25 name="plz" value="<?php echo $plz?>"> 
  <input type="text" size=20 maxlength=40 name="ort" value="<?php echo $ort;?>"></td></tr>
<tr><td>Adresse zweiter Teil</td><td><textarea cols=30 rows=2 name="ende"><?php echo str_replace("<br>","",$ende);?></textarea></td></tr>
<tr><td>Vorwahl</td><td><input type="text" size=20 maxlength=30 name="vorwahl" value="<?php echo $vorwahl?>"></td></tr>
<tr><td>Telefon</td><td><input type="text" size=20 maxlength=30 name="telefon" value="<?php echo $telefon?>"></td></tr>
</table></td></tr>
</table>


<H3>Sonstige Telefonnummern</H3>
<table border="2">
<tr align=center><td>
<table border=0>
<tr><td>Vorwahl</td><td><input type="text" size=20 maxlength=30 name="zvorwahl" value="<?php echo $zvorwahl?>"></td></tr>
<tr><td>Telefon</td><td><input type="text" size=20 maxlength=30 name="ztelefon" value="<?php echo $ztelefon?>"></td></tr>
</table></td></tr>
</table>

<H3>E-Mail-Adressen</H3>
<table border="2">
<tr align=center><td>
<table border=0>
<tr><td>Email</td><td><input type="text" size=40 maxlength=255 name="mail" value="<?php echo $mail?>"></td></tr>
</table></td></tr>
</table>

<H3>WWW-Adressen</H3>
<table border="2">
<tr align=center><td>
<table border=0>
<tr><td>Adresse</td><td><input type="text" size=40 maxlength=255 name="hpadresse" value="<?php echo $hpadresse;?>"></td></tr>
<tr><td>Name</td><td><input type="text" size=40 maxlength=255 name="hpname" value="<?php echo $hpname;?>"></td></tr>
</table></td></tr>
</table>
<br>
<input type="submit" name="aktion" value="Hinzuf&uuml;gen"> <input type="reset" value="Zur&uuml;cksetzen">
<br>
</form>
<p><<?php echo $dividier ?> width=50%><p>
<sup>*</sup>Bei den mit diesen Angaben gekennzeichneten Feldern muss immer mindestens eines f&uuml;r jede Person ausgef&uuml;llt sein.
D.h. z.B. es muss mindestens ein Jahrgang für die Person angegeben werden.
<?php include('ende.php');
} else { // Eingaben OK, Aktualisiere Tabelle


  mysql_select_db($mysql_daten['Datenbank'],$db);

  if ($geburtsdatum){
  ereg("^([0-9]{1,2})[\.,]([0-9]{1,2})[\.,]([0-9]{2,4})$",$geburtsdatum,$datum);

      
  $sql=sprintf("insert into Personen (vorname,geburtsname,aktueller_name,kommentar,von,bis,studiengang,geburtsdatum) values (\"%s\",\"%s\""
           .",\"%s\",\"%s\",%d,%d,\"%s\",'%d-%d-%d')",
           ($vorname),($geburtsname),($aktname),($kommentar),$von,$bis,($studiengang),
           $datum[3],$datum[2],$datum[1]);
  }else 
  $sql=sprintf("insert into Personen (vorname,geburtsname,aktueller_name,kommentar,von,bis,studiengang,grad,geschlecht) values (\"%s\",\"%s\""
           .",\"%s\",\"%s\",%d,%d,\"%s\",\"%s\",%d)",
           ($vorname),($geburtsname),($aktname),($kommentar),$von,$bis,($studiengang),
           ($grad),$geschlecht);
  mysql_query($sql,$db);
  $id=mysql_insert_id($db);


  if ($anfang||$plz||$ort||$ende)
    $sql=sprintf("insert Adressen (anfang,plz,ort,ende,vorwahl,telefon,uid) values (%s,\"%s\",\"%s\",%s,%s,%s,%s)",
                 $anfang?'"'.($anfang).'"':"NULL",
                 ($plz),($ort),
                 $ende?'"'.($ende).'"':"NULL",
                 $vorwahl?'"'.($vorwahl).'"':"NULL",
                 $telefon?'"'.($telefon).'"':"NULL",
                 $id);
   else if ($vorwahl||$telefon)
    $sql=sprintf("insert Telefon (vorwahl,telefon,uid) values (%s,%s,%s)",
                 $vorwahl?'"'.($vorwahl).'"':"NULL",
                 $telefon?'"'.($telefon).'"':"NULL",
                 $id);
   else $sql="";
  if ($sql) mysql_query($sql,$db);
  if ($zvorwahl||$ztelefon){
    $sql=sprintf("insert Telefon (vorwahl,telefon,uid) values (%s,%s,%s)",
                 $vorwahl?'"'.($zvorwahl).'"':"NULL",
                 $telefon?'"'.($ztelefon).'"':"NULL",
                 $id);
    mysql_query($sql,$db);
  }

  if ($mail){
    $sql=sprintf("insert EMail (adresse,uid) values (\"%s\",%s)",
                 $mail,$id);
    mysql_query($sql,$db);
  } 

  if ($hpadresse){
    if (!$hpname) $hpname=$hpadresse;
  
    $sql=sprintf("insert HP (adresse,name,uid) values (%s,%s,%s)",
                 $adresse?'"'.($hpadresse).'"':"NULL",
                 $name?'"'.($hpname).'"':"NULL",
                 $id);
    mysql_query($sql,$db);
  } 

  include("bearbeiten.php");
}
?>
