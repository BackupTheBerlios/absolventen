<?php 
function hinzufuegen($Fehler=0,$daten=0){
  global $PHP_SELF;
  global $penne;
  global $dividier;
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
<tr><td>Akademischer Grad</td>
<td><input type="text" name="grad" value="<?=$daten["grad"]?>" maxlength=20 
size=20></td></tr>
<tr><td>Geburtsname<sup>*</sup></td><td><input type="text" name="geburtsname" 
value="<?=$daten["geburtsname"];?>" maxlength=40 size=30></td></tr>
<tr><td>Vorname<sup>*</sup></td><td><input type="text" name="vorname" 
maxlength=40 size=30 name="vorname" value="<?=$daten["vorname"];?>"></td></tr>
<tr><td>aktueller Name<sup>*</sup></td><td><input type="text" name="aktname" 
  value="<?$daten["aktname"];?>" maxlength=40 size=30></td></tr>
<tr><td>Bemerkungen</td><td><textarea cols=30 rows=5 
name="kommentar"><?=str_replace("<br>","",htmlspecialchars($kommentar));?></textarea>
<tr><td>Zeit</td><td><input type="text" size=4 maxlength=4 name="von" 
value="<?=$daten["von"]?>">-<input type="text" size=4 maxlength=4 name="bis" 
value="<?=$daten["bis"]?>"></td></tr>
<tr><td>Studiengang</td><td><input type="text" name="studiengang" maxlength=40
size=30 name="studiengang" value="<?=$daten["studiengang"];?>"></td></tr>
<tr><td>Geburtsdatum</td><td><input type="text" name="geburtsdatum" maxlength=12
size=12 name="geburtsdatum" value="<?=$daten["geburtsdatum"];?>"></td></tr>
<tr><td>Geschlecht</td><td><input type="radio" name="geschlecht" 
<?=($daten["geschlecht"]==1?"checked":"")?> value="1">männlich 
<input type="radio" name="geschlecht" value="2"
<?=($daten["geschlecht"]==2?"checked":"")?>>weiblich</td></tr>
</table>
</table>

<H3>Adressen</H3>
<table border="2">
<tr align=center><td>
<tr><td>Adresse erster Teil</td><td><textarea cols=30 rows=2 
name="anfang"><?=str_replace("<br>","",htmlspecialchars($daten["anfang"]));?></textarea></td></tr>
<tr><td>PLZ Ort</td><td><input type="text" size=5 maxlength=25 name="plz" 
value="<?=$daten["plz"]?>"> 
<input type="text" size=20 maxlength=40 name="ort" value="<?=$daten[ort];?>"></td></tr>
<tr><td>Adresse zweiter Teil</td><td><textarea cols=30 rows=2 
name="ende"><?=str_replace("<br>","",$daten["ende"]);?></textarea></td></tr>
<tr><td>Vorwahl</td><td><input type="text" size=20 maxlength=30 name="vorwahl" 
value="<?=$daten["vorwahl"]?>"></td></tr>
<tr><td>Telefon</td><td><input type="text" size=20 maxlength=30 name="telefon" 
value="<?=$daten[telefon]?>"></td></tr>
</table></td></tr>
</table>


<H3>Sonstige Telefonnummern</H3>
<table border="2">
<tr align=center><td>
<table border=0>
<tr><td>Vorwahl</td><td><input type="text" size=20 maxlength=30 name="zvorwahl" 
value="<?=$daten["zvorwahl"]?>"></td></tr>
<tr><td>Telefon</td><td><input type="text" size=20 maxlength=30 name="ztelefon" 
value="<?=$daten["ztelefon"]?>"></td></tr>
</table></td></tr>
</table>

<H3>E-Mail-Adressen</H3>
<table border="2">
<tr align=center><td>
<table border=0>
<tr><td>Email</td><td><input type="text" size=40 maxlength=255 name="mail" 
value="<?=$daten["mail"]?>"></td></tr>
</table></td></tr>
</table>

<H3>WWW-Adressen</H3>
<table border="2">
<tr align=center><td>
<table border=0>
<tr><td>Adresse</td><td><input type="text" size=40 maxlength=255 
name="hpadresse" value="<?=$daten["hpadresse"];?>"></td></tr>
<tr><td>Name</td><td><input type="text" size=40 maxlength=255 name="hpname" 
value="<?=$daten["hpname"];?>"></td></tr>
</table></td></tr>
</table>
<br>
<input type="submit" name="aktion" value="Hinzuf&uuml;gen"> 
<input type="reset" value="Zur&uuml;cksetzen">
<br>
</form>
<p><<?=$dividier ?> width=50%><p>
<sup>*</sup>Bei den mit diesen Angaben gekennzeichneten Feldern muss immer 
mindestens eines f&uuml;r jede Person ausgef&uuml;llt sein.
D.h. z.B. es muss mindestens ein Jahrgang für die Person angegeben werden.
<?php
}
?>
