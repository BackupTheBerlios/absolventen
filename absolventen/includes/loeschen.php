<?php


if (!$db = @mysql_connect($mysql_daten['Rechner'], $mysql_daten['Nutzer'], $mysql_daten['Passwort'])){
  authenticate();
}



mysql_select_db($mysql_daten['Datenbank'],$db);
if ($id) {
      if ($wirklich != "ja")
         {
        include('anfang.php');

        $sql="select id,aktueller_name,geburtsname,vorname,kommentar,DATE_FORMAT(aktualisierung,'%d.%m.%Y %T') as aktualisierung,von,bis,studiengang,"
            . " DATE_FORMAT(geburtsdatum,'%d.%m.%Y')as geburtsdatum from Personen"
               . " where id=$id"
               . " order by geburtsname,vorname,aktueller_name";
        $Personen=mysql_query($sql,$db);
        if ($Person=@mysql_fetch_array($Personen)){
          $persid=$Person["id"];
          echo "<form action=\"".$PHP_SELF."\"><table border=0><tr><td align=center><table border=1>\n";
 if (isset($penne)) {?>
<input type="hidden" name="penne" value="ja">
<?php }
          echo "<tr><th colspan=6><font size=+2>Jahrgang $jahrgang</th></tr>\n";
          echo "<tr align=left><th>Geburtsname</th><th>Vorname</th><th colspan=2>Adresse erster Teil</th><th>Vorwahl</th><th>Telefon</th></tr>\n";
          echo "<tr align=left><th></th><th>aktueller Name</th><th>PLZ</th><th>Ort</th><th colspan=2></th></tr>\n";
          echo "<tr align=left><th colspan=2></th><th colspan=2>Adresse zweiter Teil</th><th colspan=2></th></tr>\n";
          echo "<tr align=left><th></th><th>Zeit</th><th colspan=2>Studiengang</th><th colspan=2>Geburtsdatum</th></tr>\n";
          echo "<tr align=left><th colspan=2><font size=-2>letzte &Auml;nderung</font></th><th colspan=4>Email</th></tr>\n";
          echo "<tr align=left><th colspan=2></th><th colspan=4>Homepage</th></tr>\n";
          echo "<tr align=left><th colspan=6>Bemerkungen</th><tr>\n";
          echo "<tr><td colspan=6 align=center><IMG SRC=\"../sonstbild/fahne.gif\" HEIGHT=5 WIDTH=700 ALIGN=CENTER></td></tr>\n";
          $sql="select anfang,plz,ort,ende,vorwahl,telefon from Adressen "
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
          $sql="select vorwahl,telefon from Telefon where uid=$persid";
          $Adressen=mysql_query($sql,$db);    
          while ($Adresse=@mysql_fetch_array($Adressen)) 
            printf("<tr><td colspan=4></td><td>%s</td><td>%s</td>\n",$Adresse["vorwahl"],$Adresse["telefon"]);

          printf("<tr><td></td><td>%d-%d</td><td colspan=2>%s</td><td colspan=2 align=right>%s</td></tr>",
           $Person["von"],$Person["bis"],$Person["studiengang"],$Person["geburtsdatum"]);

          // Emails  
          $sql="select adresse from EMail where uid=$persid";
          $emails=mysql_query($sql,$db);
          if ($email=@mysql_fetch_array($emails)) 
                 $mailstring='<a href="mailto:'.$email["adresse"].'">'.$email["adresse"]."</a>"; else $mailstring="";
          while ($email=@mysql_fetch_array($emails)) 
               $mailstring .= '<br><a href="mailto:'.$email["adresse"].'">'.$email["adresse"]."</a>";
          printf("<tr><td colspan=\"2\" valign=\"bottom\"><font size=-2>%s</font></td><td colspan=4>%s</td></tr>\n",
             $Person["aktualisierung"],$mailstring);

          // Homepages
          $sql="select adresse,name from HP where uid=$persid";
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
          echo "</table></td></tr>\n";
          echo "<tr><td align=center><input type=\"radio\" name=\"wirklich\" value=\"ja\">";
          echo "Diese Daten sollen wirklich gel&ouml;scht werden (bitte zum L&ouml;schen ankreuzen. </td></tr>";
          echo "<tr><td align=center><input type=\"submit\" name=\"aktion\" value=\"L&ouml;schen\"> ";
          echo "<input type=\"submit\" name=\"aktion\" value=\"Abbrechen\"></td></tr></table>";
          echo "<input type=\"hidden\" name=\"id\" value=\"$id\"></form>";
        }
      } else {
          $sql="delete from Einladung where uid=$id";
          mysql_query($sql,$db);
          $sql="delete from HP where uid=$id";
          mysql_query($sql,$db);
          $sql="delete from Adressen where uid=$id";
          mysql_query($sql,$db);
          $sql="delete from Telefon where uid=$id";
          mysql_query($sql,$db);
          $sql="delete from EMail where uid=$id";
          mysql_query($sql,$db);
          $sql="delete from Personen where id=$id";
          mysql_query($sql,$db);
          unset($id);unset($wirklich);unset($werte);unset($anfrage);
          include('bearbeiten.php');
      }
    } else { include('index.html');die;
}
//include('ende.php'); 
  
?>