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

*/  include('anfang.php');
echo "<img src=\"../scanbild/schulefarb1.jpg\" vspace=20><br>\n";
echo "<H2>Datensatz Bearbeiten/L&ouml;schen</H2>";
//echo "<br> $db <br>";
if (!$db = @mysql_connect($mysql_daten['Rechner'], $mysql_daten['Nutzer'], $mysql_daten['Passwort'])){
  Fehlermeldung('Die Verbindung zum Datenbank-Server ist nicht möglich.');
}

mysql_select_db($mysql_daten['DB'],$db);

if ($id){
  $sql="select aktueller_name,vorname,geburtsname,aktualisierung,kommentar from StAg where id=$id";
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
<tr><td>Geburtsname<sup>*</sup></td><td><input type="text" name="geburtsname" 
  value="<?php echo $Person["geburtsname"]?>" maxlength=40 size=30></td></tr>
<tr><td>Vorname<sup>*</sup></td><td><input type="text" name="vorname" 
  value="<?php echo $Person["vorname"]?>" maxlength=40 size=30 name="vorname"></td></tr>
<tr><td>aktueller Name<sup>*</sup></td><td><input type="text" name="aktname" 
  value="<?php echo $Person["aktueller_name"]?>" maxlength=40 size=30></td></tr>
<tr><td>Bemerkungen</td><td><textarea cols=30 rows=5 name="kommentar"><?php echo str_replace("<br>","",$Person["kommentar"])?></textarea>
<tr><td>neues Passwort</td><td><input type="password" size=8 maxlength=8 name="neupass1"></td></tr>
<tr><td>neues Passwort wiederholen</td><td><input type="password" size=8 maxlength=8 name="neupass2"></td></tr>
<tr align=center><td colspan=2>
<input type="submit" name="aktion" value="&Auml;ndern"> <input type="reset" value="Zur&uuml;cksetzen">
</td></tr>
</table>
</form>
</table>

<?php
    $sql="select id,jahrgang,klasse,drin from StAgJg "
        ."where StAgJg.uid=$id"; 
    $Adressen=mysql_query($sql,$db);
  ?><br><<?php echo $dividier ?> width="95%"><br>
<H3>Jahrg&auml;nge</H3>
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
<input type="hidden" name="jid" value="<?php echo $Adresse["id"]?>">
<table border=0>
<tr><td>Jahrgang<sup>*</sup></td><td><input type="text" size=4  maxlength=4 name="jahrgang" value="<?php echo $Adresse["jahrgang"]?>"></td></tr>
<tr><td>Klasse</td><td><input type="text" size=2 maxlength=2 name="klasse" value="<?php echo $Adresse["klasse"];?>"></td></tr>
<tr><td>Haben Sie Ihr Abitur im gleichen Jahr gemacht?<sup>*</sup></td>
<td><input type="radio" name="drin" value="ja" <?php if ($Adresse["drin"]) echo "checked";?>>Ja
<input type="radio" name="drin" value="nein" <?php if (!$Adresse["drin"]) echo "checked";?>>Nein</td></tr>
<tr align=center><td colspan=2><input type="submit" name="aktion" value="Jahrgang &auml;ndern"> 
<input type="submit" name="aktion" value="Jahrgang l&ouml;schen"> 
<input type="reset" value="Zur&uuml;cksetzen"></td></tr>
</table>
</form>
</td></tr>
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
<tr><td>Jahrgang<sup>*</sup></td><td><input type="text" size=4  maxlength=4 name="jahrgang"></td></tr>
<tr><td>Klasse</td><td><input type="text" size=2 maxlength=2 name="klasse"></td></tr>
<tr><td>Haben Sie Ihr Abitur im gleichen Jahr gemacht?<sup>*</sup></td>
<td><input type="radio" name="drin" value="ja">Ja
<input type="radio" name="drin" value="nein">Nein</td></tr>
<tr align=center><td colspan=2><input type="submit" name="aktion" value="Jahrgang hinzuf&uuml;gen"> <input type="reset" value="Zur&uuml;cksetzen"></td></tr>
</table>
</form></td></tr>
</table>

<?php
    $sql="select StAgAdr.id as aid,anfang,plz,ort,ende,vorwahl,telefon from StAgAdr "
        ."where StAgAdr.uid=$id"; 
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
    $sql="select id,vorwahl,telefon from StAgTel "
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
    $sql="select id,adresse from StAgMail "
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
    $sql="select id,adresse,name from StAgHP "
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
D.h. z.B. es muss mindestens ein Jahrgang für die Person angegeben werden.

<?php
}
else{
?>
Der Datensatz wurde leider nicht gefunden.<br>
Beginnen Sie <a href="<?php echo $PHP_SELF?>?aktion=bearbeiten$penne">hier</a> noch einmal!
<?php
  }
}else
if ($jahrgang){
  echo "Bitte den zu bearbeitenden Datensatz auswählen!\n";
  printf("<form method=\"get\" action=\"%s\">",$PHP_SELF);
  if (isset($penne)) {?>
<input type="hidden" name="penne" value="ja">
<?php }
  $sql="select StAg.id as id,aktueller_name,geburtsname,vorname,kommentar,DATE_FORMAT(aktualisierung,'%d.%m.%Y %T') as aktualisierung,klasse from StAg,StAgJg"
   . " where StAgJg.jahrgang=$jahrgang and StAgJg.uid=StAg.id"
   . " order by jahrgang,klasse, drin desc,geburtsname,vorname,aktueller_name";
  $Personen=mysql_query($sql,$db);
  if ($Person=@mysql_fetch_array($Personen)){
    $persid=$Person["id"];
    echo "<table border=1>\n";
    echo "<tr><th colspan=7><font size=+2>Jahrgang $jahrgang</th></tr>\n";
    echo "<tr align=left><th></th><th>Geburtsname</th><th>Vorname</th><th colspan=2>Adresse erster Teil</th><th>Vorwahl</th><th>Telefon</th></tr>\n";
    echo "<tr align=left><th></th><th></th><th>aktueller Name</th><th>PLZ</th><th>Ort</th><th colspan=2></th></tr>\n";
    echo "<tr align=left><th></th><th colspan=2></th><th colspan=2>Adresse zweiter Teil</th><th colspan=2></th></tr>\n";
    echo "<tr align=left><th></th><th colspan=2><font size=-2>letzte &Auml;nderung</font></th><th colspan=4>Email</th></tr>\n";
    echo "<tr align=left><th></th><th colspan=2></th><th colspan=4>Homepage</th></tr>\n";
    echo "<tr align=left><th></th><th colspan=6>Bemerkungen</th><tr>\n";
    echo "<tr><td colspan=7 align=center><IMG SRC=\"../sonstbild/fahne.gif\" HEIGHT=5 WIDTH=700 ALIGN=CENTER></td></tr>\n";
    $sql="select anfang,plz,ort,ende,vorwahl,telefon from StAgAdr "
        ."where StAgAdr.uid=$persid"; 
    $Adressen=mysql_query($sql,$db);
  if ($Adresse=@mysql_fetch_array($Adressen)){    
       printf("<tr valign=top><td rowspan=2><input type=\"radio\" name=\"id\" value=\"%s\"></td><td>%s</td><td>%s</td><td colspan=2>%s</td><td>%s</td><td>%s</td></tr>\n",
         $persid,$Person["geburtsname"],$Person["vorname"],$Adresse["anfang"],$Adresse["vorwahl"],$Adresse["telefon"]);
       printf("<tr valign=top><td></td><td>%s</td><td>%s</td><td>%s</td><td colspan=2></td></tr>\n",
         $Person["aktueller_name"],$Adresse["plz"],$Adresse["ort"]);
       if ($Person["ende"]) 
         printf("<tr><td></td><td colspan=2></td><td colspan=2>%s</td><td colspan=2></td></tr>",
               $Adresse["ende"]);
       while ($Adresse=@mysql_fetch_array($Adressen)){    
         printf("<tr valign=top><td></td><td></td><td></td><td colspan=2>%s</td><td>%s</td><td>%s</td></tr>\n",
           $Adresse["anfang"],$Adresse["vorwahl"],$Adresse["telefon"]);
         printf("<tr valign=top><td></td><td></td><td></td><td>%s</td><td>%s</td><td colspan=2></td></tr>\n",
           $Adresse["plz"],$Adresse["ort"]);
         if ($Person["ende"]) 
           printf("<tr><td></td><td colspan=2></td><td colspan=2>%s</td><td colspan=2></td></tr>\n",
               $Adresse["ende"]);
      }
    }else{
      printf("<tr><td rowspan=2><input type=\"radio\" name=\"id\" value=\"%s\"></td><td>%s</td><td>%s</td><td colspan=2></td><td></td><td></td></tr>\n",
         $persid,$Person["geburtsname"],$Person["vorname"]);
      printf("<tr><td></td><td>%s</td><td></td><td colspan=2></td></tr>\n",
         $Person["aktueller_name"]);
    }
    $sql="select vorwahl,telefon from StAgTel where uid=$persid";
    $Adressen=mysql_query($sql,$db);    
    while ($Adresse=@mysql_fetch_array($Adressen)) 
      printf("<tr><td></td><td colspan=4></td><td>%s</td><td>%s</td>\n",$Adresse["vorwahl"],$Adresse["telefon"]);

    // Emails  
    $sql="select adresse from StAgMail where uid=$persid";
    $emails=mysql_query($sql,$db);
    if ($email=@mysql_fetch_array($emails)) 
           $mailstring='<a href="mailto:'.$email["adresse"].'">'.$email["adresse"]."</a>"; else $mailstring="";
    while ($email=@mysql_fetch_array($emails)) 
         $mailstring .= '<br><a href="mailto:'.$email["adresse"].'">'.$email["adresse"]."</a>";
    printf("<tr><td></td><td colspan=\"2\" valign=\"bottom\"><font size=-2>%s</font></td><td colspan=4>%s</td></tr>\n",
       $Person["aktualisierung"],$mailstring);

    // Homepages
    $sql="select adresse,name from StAgHP where uid=$persid";
    $emails=mysql_query($sql,$db);
    if ($email=@mysql_fetch_array($emails)) {
         $mailstring='<a href="'.$email["adresse"].'">'.$email["name"]."</a>";
    while ($email=@mysql_fetch_array($emails)) 
         $mailstring .= '<br><a href="'.$email["adresse"].'">'.$email["name"]."</a>";
    printf("<tr><td></td><td colspan=2></td><td colspan=4>%s</td></tr>\n",$mailstring);
    }
    if ($Person["kommentar"])
      printf("<tr><td></td><td colspan=6>%s</td></tr>\n",
       $Person["kommentar"]);
    while($Person=mysql_fetch_array($Personen)){
      $persid=$Person["id"];
      echo "<tr><td colspan=7 align=center><IMG SRC=\"../sonstbild/fahne.gif\" HEIGHT=5 WIDTH=700 ALIGN=CENTER></td></tr>\n";
      $sql="select anfang,plz,ort,ende,vorwahl,telefon from StAgAdr "
          ."where StAgAdr.uid=$persid"; 
      $Adressen=mysql_query($sql,$db);
      if ($Adresse=@mysql_fetch_array($Adressen)){    
         printf("<tr valign=top><td rowspan=2><input type=\"radio\" name=\"id\" value=\"%s\"></td><td>%s</td><td>%s</td><td colspan=2>%s</td><td>%s</td><td>%s</td></tr>\n",
           $persid,$Person["geburtsname"],$Person["vorname"],$Adresse["anfang"],$Adresse["vorwahl"],$Adresse["telefon"]);
         printf("<tr valign=top><td></td><td>%s</td><td>%s</td><td>%s</td><td colspan=2></td></tr>\n",
           $Person["aktueller_name"],$Adresse["plz"],$Adresse["ort"]);
         if ($Person["ende"]) 
           printf("<tr><td></td><td colspan=2></td><td colspan=2>%s</td><td colspan=2></td></tr>",
                 $Adresse["ende"]);
         while ($Adresse=@mysql_fetch_array($Adressen)){    
           printf("<tr valign=top><td></td><td></td><td></td><td colspan=2>%s</td><td>%s</td><td>%s</td></tr>\n",
             $Adresse["anfang"],$Adresse["vorwahl"],$Adresse["telefon"]);
           printf("<tr valign=top><td></td><td></td><td></td><td>%s</td><td>%s</td><td colspan=2></td></tr>\n",
             $Adresse["plz"],$Adresse["ort"]);
           if ($Person["ende"]) 
             printf("<tr><td></td><td colspan=2></td><td colspan=2>%s</td><td colspan=2></td></tr>",
                 $Adresse["ende"]);
         }
      }else{
        printf("<tr><td rowspan=2><input type=\"radio\" name=\"id\" value=\"%s\"></td><td>%s</td><td>%s</td><td colspan=2></td><td></td><td></td></tr>\n",
           $persid,$Person["geburtsname"],$Person["vorname"]);
        printf("<tr><td></td><td>%s</td><td></td><td colspan=2></td></tr>\n",
           $Person["aktueller_name"]);
      }
      $sql="select vorwahl,telefon from StAgTel where uid=$persid";
      $Adressen=mysql_query($sql,$db);    
      while ($Adresse=@mysql_fetch_array($Adressen)) 
        printf("<tr><td></td><td colspan=4></td><td>%s</td><td>%s</td>\n",$Adresse["vorwahl"],$Adresse["telefon"]);

      // Emails  
      $sql="select adresse from StAgMail where uid=$persid";
      $emails=mysql_query($sql,$db);
      if ($email=@mysql_fetch_array($emails)) 
           $mailstring='<a href="mailto:'.$email["adresse"].'">'.$email["adresse"]."</a>"; else $mailstring="";
      while ($email=@mysql_fetch_array($emails)) 
           $mailstring .= '<br><a href="mailto:'.$email["adresse"].'">'.$email["adresse"]."</a>";
      printf("<tr><td></td><td colspan=2><font size=-2>%s</font></td><td colspan=4>%s</td></tr>\n",
         $Person["aktualisierung"],$mailstring);

      // Homepages
      $sql="select adresse,name from StAgHP where uid=$persid";
      $emails=mysql_query($sql,$db);
      if ($email=@mysql_fetch_array($emails)) {
           $mailstring='<a href="'.$email["adresse"].'">'.$email["name"]."</a>"; 
        while ($email=@mysql_fetch_array($emails)) 
           $mailstring .= '<br><a href="'.$email["adresse"].'">'.$email["name"]."</a>";
        printf("<tr><td></td><td colspan=2></td><td colspan=4>%s</td></tr>\n",$mailstring);
      }
      if ($Person["kommentar"])
        printf("<tr><td></td><td colspan=6>%s</td></tr>\n",$Person["kommentar"]);
    }
    echo "</table><table border=0><tr><td align=center>\n";
    echo "<input type=\"submit\" name=\"aktion\" value=\"Bearbeiten\"> ";
    echo "<input type=\"submit\" name=\"aktion\" value=\"L&ouml;schen\"> ";
    echo "<input type=\"reset\" value=\"Zur&uuml;cksetzen\">\n";
    echo "</td></tr></table></form>\n";
  } else {?>
  <p>Leider nichts gefunden.</p>
  <p><a href="<?php echo $PHP_SELF?>?aktion=bearbeiten$penne">Hier gehts zur&uuml;ck zum Anfang</a></p>
  <?php }
} else {

  $sql="select jahrgang from StAgJg group by jahrgang order by jahrgang";
  $result=mysql_query($sql,$db);
  if ($result){
?>
<table border=0>
<tr><td align=center>
<form method="get" action="<?php echo $PHP_SELF?>" style="background-color=#000000;">
<?php if (isset($penne)) {?>
<input type="hidden" name="penne" value="ja">
<?php }?>
  <input type="hidden" name="aktion" value="bearbeiten">
  <select name="jahrgang" style="background-color=#000000;">
<?php
      while($myrow=mysql_fetch_array($result)){
        printf("<option>%s\n",$myrow["jahrgang"]);
   
    }?>
</select><br>
<input type="submit" value="Ok" style="background-color=#000000;">
</form> </td></tr></table><?php
  }

}
include('ende.php');?>