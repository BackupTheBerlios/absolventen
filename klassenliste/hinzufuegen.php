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
//echo "<br> $db <br>";
unset($Fehler);
if (isset($vorname)){
//|| $geburtsname || $aktname || $kommentar || $neupass1 || $neupass2 || $jahrgang || $klasse
//    || $drin || $anfang || $plz || $ort || $ende || $vorwahl || $telefon || $zvorwahl || $ztelefon || $mail || $hpadresse || $hpname){

   if(!$vorname)     $Fehler = "Der Vorname fehlt.<br>\n";
   if(!$geburtsname) $Fehler .= "Der Geburtsname fehlt.<br>\n";
   if(!$aktname)     $Fehler .= "Der aktuelle Name fehlt.<br>\n";
   if(!ereg("^[0-9]{0,4}$",$jahrgang))    $Fehler .= "Der Abiturjahrgang fehlt oder ist ung&uuml;ltig.<br>\n";

   if(!ereg("^(ja|nein)$",$drin))	     $Fehler .= "Es fehlt die Angabe, ob Sie im gleichen Jahr ihr Abitur an dieser Schule gemacht haben.<br>\n";

   if((!$neupass1)||$neupass1!=$neupass2) $Fehler .= "Es wurden keine zwei identischen Passw&ouml;rter angegeben.<br>\n";
   if ($klasse && !(ereg("^[a-zA-Z0-9]{0,2}$",$klasse))) $Fehler .= "Die Klasse ist ung&uuml;ltig<br>\n";

   if ($mail && !ereg( "^[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+@[-!#$%&\'*+\\/0-9=?A-Z^_`a-z{|}~]+\.[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+$",$mail))
     $Fehler .= "Die Mailadresse scheint ung&uuml;ltig zu sein.<br>\n";

   if ($hpadresse && (!ereg( "^http://[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+\.[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+/.*$",$hpadresse)))
     $Fehler .= "Die WWW-Adresse scheint fehlerhaft zu sein.<br>\n";


} else $Fehler=0;

if (isset($Fehler)){
include('anfang.php'); 
echo "<img src=\"../scanbild/schulefarb1.jpg\" vspace=20>\n";
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
<tr><td>Geburtsname<sup>*</sup></td><td><input type="text" name="geburtsname" value="<?php echo $geburtsname;?>" maxlength=40 size=30></td></tr>
<tr><td>Vorname<sup>*</sup></td><td><input type="text" name="vorname" maxlength=40 size=30 name="vorname" value="<?php echo $vorname;?>"></td></tr>
<tr><td>aktueller Name<sup>*</sup></td><td><input type="text" name="aktname" 
  value="<?php echo $aktname;?>" maxlength=40 size=30></td></tr>
<tr><td>Bemerkungen</td><td><textarea cols=30 rows=5 name="kommentar"><?php echo str_replace("<br>","",$kommentar);?></textarea>
<tr><td>Passwort</td><td><input type="password" size=8 maxlength=8 name="neupass1"></td></tr>
<tr><td>Passwort wiederholen</td><td><input type="password" size=8 maxlength=8 name="neupass2"></td></tr>
</table>
</table>

<H3>Jahrg&auml;nge</H3>
<table border="2">
<tr align=center><td>
<table border=0>
<tr><td>Jahrgang<sup>*</sup></td><td><input type="text" size=4  maxlength=4 name="jahrgang" value="<?php echo $jahrgang;?>"></td></tr>
<tr><td>Klasse</td><td><input type="text" size=2 maxlength=2 name="klasse" value="<?php echo $klasse?>"></td></tr>
<tr><td>Haben Sie Ihr Abitur im gleichen Jahr gemacht?<sup>*</sup></td>
<td><input type="radio" name="drin" value="ja" <?php if ($drin=="ja") echo "checked";?>>Ja
<input type="radio" name="drin" value="nein" <?php if ($drin=="nein") echo "checked";?>>Nein</td></tr>
</table>
</td></tr>
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
y
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
D.h. z.B. es muss mindestens ein Jahrgang f� die Person angegeben werden.
<?php include('ende.php');
} else { // Eingaben OK, Aktualisiere Tabelle

  if (!$db = @mysql_connect($mysql_daten['Rechner'], $mysql_daten['Nutzer'], $mysql_daten['Passwort'])){
    Fehlermeldung('Die Verbindung zum Datenbank-Server ist nicht m�lich.');
  }

  mysql_select_db($mysql_daten['DB'],$db);


  $vorname=str_replace("&amp;","&",htmlspecialchars($vorname));
  $geburtsname=str_replace("&amp;","&",htmlspecialchars($geburtsname));
  $aktname=str_replace("&amp;","&",htmlspecialchars($aktname));
  $kommentar=nl2br(str_replace("&amp;","&",htmlspecialchars($kommentar)));

  $anfang=nl2br(str_replace("&amp;","&",htmlspecialchars($anfang)));
  $plz=str_replace("&amp;","&",htmlspecialchars($plz));
  $ort=str_replace("&amp;","&",htmlspecialchars($ort));
  $ende=nl2br(str_replace("&amp;","&",htmlspecialchars($ende)));
  $vorwahl=str_replace("&amp;","&",htmlspecialchars($vorwahl));
  $telefon=str_replace("&amp;","&",htmlspecialchars($telefon));

  $zvorwahl=str_replace("&amp;","&",htmlspecialchars($zvorwahl));
  $ztelefon=str_replace("&amp;","&",htmlspecialchars($ztelefon));
  
  $mail=str_replace("&amp;","&",htmlspecialchars($mail));

  $hpname=str_replace("&amp;","&",htmlspecialchars($hpname));
  $hpadresse=str_replace("&amp;","&",htmlspecialchars($hpadresse));
    
  $sql=sprintf("insert into StAg (vorname,geburtsname,aktueller_name,kommentar,pw) values (\"%s\",\"%s\""
           .",\"%s\",\"%s\",encrypt(\"%s\"))",
           AddSlashes($vorname),AddSlashes($geburtsname),AddSlashes($aktname),AddSlashes($kommentar),AddSlashes($neupass1));
  mysql_query($sql,$db);
  $id=mysql_insert_id($db);

  $sql=sprintf("insert StAgJg (jahrgang,klasse,drin,uid) values (%s,\"%s\",%d,%s)",$jahrgang,$klasse,($drin=="ja"?1:0),$id);
  mysql_query($sql,$db);

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
  if ($sql) mysql_query($sql,$db);
  if ($zvorwahl||$ztelefon){
    $sql=sprintf("insert StAgTel (vorwahl,telefon,uid) values (%s,%s,%s)",
                 $vorwahl?'"'.AddSlashes($zvorwahl).'"':"NULL",
                 $telefon?'"'.AddSlashes($ztelefon).'"':"NULL",
                 $id);
    mysql_query($sql,$db);
  }

  if ($mail){
    $sql=sprintf("insert StAgMail (adresse,uid) values (\"%s\",%s)",
                 $mail,$id);
    mysql_query($sql,$db);
  } 

  if ($hpadresse){
    if (!$hpname) $hpname=$hpadresse;
  
    $sql=sprintf("insert StAgHP (adresse,name,uid) values (%s,%s,%s)",
                 $adresse?'"'.AddSlashes($hpadresse).'"':"NULL",
                 $name?'"'.AddSlashes($hpname).'"':"NULL",
                 $id);
    mysql_query($sql,$db);
  } 

  include("bearbeiten.php");
}
?>