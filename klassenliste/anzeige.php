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
if (!($aktion=="menue")) echo "<img src=\"../scanbild/schulefarb1.jpg\" vspace=20>\n<H2>- Anzeigen -</H2>\n"; 
else 
 echo "<p><img src=\"../scanbild/schulesw1.jpg\" vspace=20>\n<p>\n";

//echo "<br> $db <br>";
if (!$db = @mysql_connect($mysql_daten['Rechner'], $mysql_daten['Nutzer'], $mysql_daten['Passwort'])){
  Fehlermeldung('Die Verbindung zum Datenbank-Server ist nicht möglich.');
}

mysql_select_db($mysql_daten['DB'],$db);

if ($jahrgang){
  $sql="select StAg.id as id,aktueller_name,geburtsname,vorname,kommentar,DATE_FORMAT(aktualisierung,'%d.%m.%Y %T') as aktualisierung,klasse from StAg,StAgJg"
   . " where StAgJg.jahrgang=$jahrgang and StAgJg.uid=StAg.id"
   . " order by jahrgang,klasse, drin desc,geburtsname,vorname,aktueller_name";
  $Personen=mysql_query($sql,$db);
  if ($Person=@mysql_fetch_array($Personen)){
    $persid=$Person["id"];
    echo "<table border=1>\n";
    echo "<tr><th colspan=6><font size=+2>Jahrgang $jahrgang</th></tr>\n";
    echo "<tr align=left><th>Geburtsname</th><th>Vorname</th><th colspan=2>Adresse erster Teil</th><th>Vorwahl</th><th>Telefon</th></tr>\n";
    echo "<tr align=left><th></th><th>aktueller Name</th><th>PLZ</th><th>Ort</th><th colspan=2></th></tr>\n";
    echo "<tr align=left><th colspan=2></th><th colspan=2>Adresse zweiter Teil</th><th colspan=2></th></tr>\n";
    echo "<tr align=left><th colspan=2><font size=-2>letzte &Auml;nderung</font></th><th colspan=4>Email</th></tr>\n";
    echo "<tr align=left><th colspan=2></th><th colspan=4>Homepage</th></tr>\n";
    echo "<tr align=left><th colspan=6>Bemerkungen</th><tr>\n";
    echo "<tr><td colspan=6 align=center><IMG SRC=\"../sonstbild/fahne.gif\" HEIGHT=5 WIDTH=700 ALIGN=CENTER></td></tr>\n";
    $sql="select anfang,plz,ort,ende,vorwahl,telefon from StAgAdr "
        ."where StAgAdr.uid=$persid"; 
    $Adressen=mysql_query($sql,$db);
  if ($Adresse=@mysql_fetch_array($Adressen)){    
       printf("<tr valign=top><td>%s</td><td>%s</td><td colspan=2>%s</td><td>%s</td><td>%s</td></tr>\n",
         $Person["geburtsname"],$Person["vorname"],$Adresse["anfang"],$Adresse["vorwahl"],$Adresse["telefon"]);
       printf("<tr valign=top><td></td><td>%s</td><td>%s</td><td>%s</td><td colspan=2></td></tr>\n",
         $Person["aktueller_name"],$Adresse["plz"],$Adresse["ort"]);
       if ($Person["ende"]) 
         printf("<tr><td colspan=2></td><td colspan=2>%s</td><td colspan=2></td></tr>",
               $Adresse["ende"]);
       while ($Adresse=@mysql_fetch_array($Adressen)){    
         printf("<tr valign=top><td></td><td></td><td colspan=2>%s</td><td>%s</td><td>%s</td></tr>\n",
           $Adresse["anfang"],$Adresse["vorwahl"],$Adresse["telefon"]);
         printf("<tr valign=top><td></td><td></td><td>%s</td><td>%s</td><td colspan=2></td></tr>\n",
           $Adresse["plz"],$Adresse["ort"]);
         if ($Person["ende"]) 
           printf("<tr><td colspan=2></td><td colspan=2>%s</td><td colspan=2></td></tr>\n",
               $Adresse["ende"]);
      }
    }else{
      printf("<tr><td>%s</td><td>%s</td><td colspan=2></td><td></td><td></td></tr>\n",
         $Person["geburtsname"],$Person["vorname"]);
      printf("<tr><td></td><td>%s</td><td></td><td colspan=2></td></tr>\n",
         $Person["aktueller_name"]);
    }
    $sql="select vorwahl,telefon from StAgTel where uid=$persid";
    $Adressen=mysql_query($sql,$db);    
    while ($Adresse=@mysql_fetch_array($Adressen)) 
      printf("<tr><td colspan=4></td><td>%s</td><td>%s</td>\n",$Adresse["vorwahl"],$Adresse["telefon"]);

    // Emails  
    $sql="select adresse from StAgMail where uid=$persid";
    $emails=mysql_query($sql,$db);
    if ($email=@mysql_fetch_array($emails)) 
           $mailstring='<a href="mailto:'.$email["adresse"].'">'.$email["adresse"]."</a>"; else $mailstring="";
    while ($email=@mysql_fetch_array($emails)) 
         $mailstring .= '<br><a href="mailto:'.$email["adresse"].'">'.$email["adresse"]."</a>";
    printf("<tr><td colspan=\"2\" valign=\"bottom\"><font size=-2>%s</font></td><td colspan=4>%s</td></tr>\n",
       $Person["aktualisierung"],$mailstring);

    // Homepages
    $sql="select adresse,name from StAgHP where uid=$persid";
    $emails=mysql_query($sql,$db);
    if ($email=@mysql_fetch_array($emails)) {
         $mailstring='<a href="'.$email["adresse"].'">'.$email["name"]."</a>";
       while ($email=@mysql_fetch_array($emails)) 
         $mailstring .= '<br><a href="'.$email["adresse"].'">'.$email["name"]."</a>";
      printf("<tr><td colspan=2></td><td colspan=4>%s</td></tr>\n",$mailstring);
    }
    if ($Person["kommentar"])
      printf("<tr><td colspan=6>%s</td></tr>\n",
       $Person["kommentar"]);
  
    while($Person=mysql_fetch_array($Personen)){
      $persid=$Person["id"];
      echo "<tr><td colspan=6 align=center><IMG SRC=\"../sonstbild/fahne.gif\" HEIGHT=5 WIDTH=700 ALIGN=CENTER></td></tr>\n";
      $sql="select anfang,plz,ort,ende,vorwahl,telefon from StAgAdr "
          ."where StAgAdr.uid=$persid"; 
      $Adressen=mysql_query($sql,$db);
      if ($Adresse=@mysql_fetch_array($Adressen)){    
         printf("<tr valign=top><td>%s</td><td>%s</td><td colspan=2>%s</td><td>%s</td><td>%s</td></tr>\n",
           $Person["geburtsname"],$Person["vorname"],$Adresse["anfang"],$Adresse["vorwahl"],$Adresse["telefon"]);
         printf("<tr valign=top><td></td><td>%s</td><td>%s</td><td>%s</td><td colspan=2></td></tr>\n",
           $Person["aktueller_name"],$Adresse["plz"],$Adresse["ort"]);
         if ($Person["ende"]) 
           printf("<tr><td colspan=2></td><td colspan=2>%s</td><td colspan=2></td></tr>",
                 $Adresse["ende"]);
         while ($Adresse=@mysql_fetch_array($Adressen)){    
           printf("<tr valign=top><td></td><td></td><td colspan=2>%s</td><td>%s</td><td>%s</td></tr>\n",
             $Adresse["anfang"],$Adresse["vorwahl"],$Adresse["telefon"]);
           printf("<tr valign=top><td></td><td></td><td>%s</td><td>%s</td><td colspan=2></td></tr>\n",
             $Adresse["plz"],$Adresse["ort"]);
           if ($Person["ende"]) 
             printf("<tr><td colspan=2></td><td colspan=2>%s</td><td colspan=2></td></tr>",
                 $Adresse["ende"]);
         }
      }else{
        printf("<tr><td>%s</td><td>%s</td><td colspan=2></td><td></td><td></td></tr>\n",
           $Person["geburtsname"],$Person["vorname"]);
        printf("<tr><td></td><td>%s</td><td></td><td colspan=2></td></tr>\n",
           $Person["aktueller_name"]);
      }
      $sql="select vorwahl,telefon from StAgTel where uid=$persid";
      $Adressen=mysql_query($sql,$db);    
      while ($Adresse=@mysql_fetch_array($Adressen)) 
        printf("<tr><td colspan=4></td><td>%s</td><td>%s</td>\n",$Adresse["vorwahl"],$Adresse["telefon"]);

      // Emails  
      $sql="select adresse from StAgMail where uid=$persid";
      $emails=mysql_query($sql,$db);
      if ($email=@mysql_fetch_array($emails)) 
           $mailstring='<a href="mailto:'.$email["adresse"].'">'.$email["adresse"]."</a>"; else $mailstring="";
      while ($email=@mysql_fetch_array($emails)) 
           $mailstring .= '<br><a href="mailto:'.$email["adresse"].'">'.$email["adresse"]."</a>";
      printf("<tr><td colspan=2 valign=bottom><font size=-2>%s</font></td><td colspan=4>%s</td></tr>\n",
         $Person["aktualisierung"],$mailstring);

      // Homepages
      $sql="select adresse,name from StAgHP where uid=$persid";
      $emails=mysql_query($sql,$db);
      if ($email=@mysql_fetch_array($emails)){ 
           $mailstring='<a href="'.$email["adresse"].'">'.$email["name"]."</a>";
        while ($email=@mysql_fetch_array($emails)) 
           $mailstring .= '<br><a href="'.$email["adresse"].'">'.$email["name"]."</a>";
        printf("<tr><td colspan=2></td><td colspan=4>%s</td></tr>\n",$mailstring);
      }
      if ($Person["kommentar"])
        printf("<tr><td colspan=6>%s</td></tr>\n",$Person["kommentar"]);
    }
    echo "</table>\n";
  } else {?>
  <p>Leider nichts gefunden.</p>
  <p><a href="<?php echo $PHP_SELF?>?aktion=anzeige<?php echo $penne?>">Hier gehts zur&uuml;ck zum Anfang</a></p>
  <?php }
} else if ($aktion=="menue"){

  $sql="select jahrgang from StAgJg group by jahrgang order by jahrgang";
  $result=mysql_query($sql,$db);
  if ($result){
      while($myrow=mysql_fetch_array($result)){
        printf("<a href=\"%s?aktion=anzeige%s&jahrgang=%s\">%s</a><br>\n",$PHP_SELF,$penne,$myrow["jahrgang"],$myrow["jahrgang"]);
    }
  }
} else { 
  $sql="select jahrgang from StAgJg group by jahrgang order by jahrgang";
  $result=mysql_query($sql,$db);
  if ($result){
?>
<table border=0><tr><td align=center>
<form method="get" action="<?php echo $PHP_SELF?>">
  <input type="hidden" name="aktion" value="anzeige">
<?php if (isset($penne)) echo "  <input type=\"hidden\" name=\"penne\" value=\"ja\">";?>
  <select name="jahrgang">
<?php
      while($myrow=mysql_fetch_array($result)){
        printf("<option>%s\n",$myrow["jahrgang"]);
   
    }?>
</select><br>
<input type="submit" value="Ok">
</form></td></tr></table> <?php
  }
}
include('ende.php');?>
