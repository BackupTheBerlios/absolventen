<?php if (!$db = @mysql_connect($mysql_daten['Rechner'], $mysql_daten['Nutzer'], $mysql_daten['Passwort'])){
  authenticate();
}

mysql_select_db($mysql_daten['Datenbank'],$db);

if ($terminid)
{
  for ($i=0;$id[$i];$i++) { 
    if ($eingeladen[$id[$i]] || $antwort[$id[$i]] || $teilnahme[$id[$i]])
    { 
      $sql=sprintf("select eingeladen,antwort,status from Einladung where termin=%d and uid=%d",$terminid,$id[$i]);
      $Einl=mysql_query($sql,$db);
      if ($Einladung=@mysql_fetch_array($Einl)){
        $Komma="";
        $sql="update Einladung set ";
        switch ($eingeladen[$id[$i]]) {
          case "ja" : {
                        $sql .= "eingeladen=now()";
                        $Komma = ",";
                        break;
                      }
          case "nein" : {
                          $sql .= "eingeladen=NULL";
                          $Komma = ",";
                          break;
                        }
        }
        switch ($antwort[$id[$i]]) {
          case "ja" : {
                        $sql .= $Komma . "antwort=now()";
                        $Komma = ",";
                        break;
                      }
          case "nein" : {
                          $sql .= $Komma ."antwort=NULL";
                          $Komma = ",";
                          break;
                        }
        }
        switch ($teilnahme[$id[$i]]) {
          case "nein" : {
                          $sql .= $Komma ."status=0";
                          $Komma = ",";
                          break;
                        }
	  default:     {
                          $sql .= sprintf("%sstatus=%d",$Komma,$teilnahme[$id[$i]]);
                          $Komma = ",";
                          break;
	               }
        }
        $sql .= sprintf(" where termin=%d and uid=%d",$terminid,$id[$i]);
      } // Datensatz schon vorhanden
      else {
        $sql = sprintf("insert into Einladung (termin,uid,eingeladen,antwort,status) values (%d,%d,%s,%s,%d)",
               $terminid,$id[$i],
               $eingeladen[$id[$i]]=="ja"?"now()":"NULL",
               $antwort[$id[$i]]=="ja"?"now()":"NULL",
               $teilnahme[$id[$i]]=="ja"?1:0);
      }
      mysql_query($sql,$db);
    }
  }
  include('einladungen.php');
}

die;
{
  $sql="select Personen.id as id,aktueller_name,geburtsname,vorname,kommentar,DATE_FORMAT(aktualisierung,'%d.%m.%Y %T') as aktualisierung,von,bis,studiengang,"
  . " DATE_FORMAT(geburtsdatum,'%d.%m.%Y') as geburtsdatum,geschlecht,grad,Einladung.status as status,eingeladen,antwort from Personen left outer join Einladung on (Personen.id=Einladung.uid and Einladung.termin=$terminid)"
   . " order by geburtsname,vorname,aktueller_name";
  echo $sql;
  $Personen=mysql_query($sql,$db);
  if ($Person=@mysql_fetch_array($Personen)){
    $persid=$Person["id"];
    echo "<form method=\"post\" action=\"$PHP_SELF\">\n";
    echo "<input type=\"hidden\" name=\"terminid\" value=\"$terminid\">";
    echo "<table border=1>\n";
    echo "<tr><th colspan=7><font size=+2>Jahrgang $jahrgang</th></tr>\n";
    echo "<tr align=left><th></th><th>Geburtsname</th><th>Vorname</th><th colspan=2>Adresse erster Teil</th><th>Vorwahl</th><th>Telefon</th></tr>\n";
    echo "<tr align=left><th></th><th></th><th>aktueller Name</th><th>PLZ</th><th>Ort</th><th colspan=2></th></tr>\n";
    echo "<tr align=left><th></th><th colspan=2></th><th colspan=2>Adresse zweiter Teil</th><th colspan=2></th></tr>\n";
    echo "<tr align=left><th></th><th></th><th>Akad. Grad</th><th>Geschlecht</th><th></th></tr>\n";
    echo "<tr align=left><th></th><th></th><th>Zeit</th><th colspan=2>Studiengang</th><th colspan=2>Geburtsdatum</th></tr>\n";
    echo "<tr align=left><th></th><th colspan=2><font size=-2>letzte &Auml;nderung</font></th><th colspan=4>Email</th></tr>\n";
    echo "<tr align=left><th></th><th colspan=2></th><th colspan=4>Homepage</th></tr>\n";
    echo "<tr align=left><th></th><th colspan=6>Bemerkungen</th><tr>\n";
    echo "<tr><td colspan=7 align=center><IMG SRC=\"../sonstbild/fahne.gif\" HEIGHT=5 WIDTH=700 ALIGN=CENTER></td></tr>\n";
    $sql="select anfang,plz,ort,ende,vorwahl,telefon from Adressen "
        ."where Adressen.uid=$persid"; 
    $Adressen=mysql_query($sql,$db);$Zeilen=0;
  if ($Adresse=@mysql_fetch_array($Adressen)){    
    echo "<tr><td rowspan=4>";$Zeilen++;
    printf("<input type=\"hidden\" name=\"id[]\" value=\"%s\">",$persid);
    if ($Person["eingeladen"]) {
      echo "Eingeladen am ".$Person["eingeladen"];
      echo "<nobr><input type=checkbox name=\"eingeladen[$persid]\" value=\"nein\"> NICHT eingeladen<br>";
    } else 
      echo "<nobr><input type=\"checkbox\" name=\"eingeladen[$persid]\" value=\"ja\"> Einladen</nobr><br>";
    if ($Person["antwort"]) {
      echo "Antwort am ".$Person["antwort"];
      echo "<nobr><input type=checkbox name=\"antwort[$persid]\" value=\"nein\"> KEINE Antwort <br>";
    } else 
      echo "<nobr><input type=\"checkbox\" name=\"antwort[$persid]\" value=\"ja\"> Antwort</nobr><br>";
    if ($Person["status"] & 1) {
      echo "Teilname ";
      echo "<nobr><input type=checkbox name=\"teilnahme[$persid]\" value=\"nein\"> KEINE Teilnahme<br>";
    } else 
      echo "<nobr><input type=\"checkbox\" name=\"teilnahme[$persid]\" value=\"ja\"> Teilnahme</nobr><br>";
    printf("</td><td>%s</td><td>%s</td><td colspan=2>%s</td><td>%s</td><td>%s</td></tr>\n",
         $Person["geburtsname"],$Person["vorname"],$Adresse["anfang"],$Adresse["vorwahl"],$Adresse["telefon"]);
       printf("<tr valign=top><td></td><td>%s</td><td>%s</td><td>%s</td><td colspan=2></td></tr>\n",
         $Person["aktueller_name"],$Adresse["plz"],$Adresse["ort"]);$Zeilen++;
       if ($Person["ende"]) {
         printf("<tr><td colspan=2></td><td colspan=2>%s</td><td colspan=2></td></tr>",
               $Adresse["ende"]);$Zeilen++;}
       while ($Adresse=@mysql_fetch_array($Adressen)){    
         echo "<tr valign=top>"; if ($Zeilen>=4) echo "<td></td>";
         printf("<td></td><td colspan=2>%s</td><td>%s</td><td>%s</td></tr>\n",
           $Adresse["anfang"],$Adresse["vorwahl"],$Adresse["telefon"]);$Zeilen++;
         echo "<tr valign=top>"; if ($Zeilen>=4) echo "<td></td>";
         printf("<td></td><td></td><td>%s</td><td>%s</td><td colspan=2></td></tr>\n",
           $Adresse["plz"],$Adresse["ort"]);$Zeilen++;
         if ($Person["ende"]) {
           echo "<tr>"; if ($Zeilen>=4) echo "<td></td>";
           printf("<td colspan=2></td><td colspan=2>%s</td><td colspan=2></td></tr>\n",
               $Adresse["ende"]);$Zeilen++;
         }
      }
    }else{
    echo "<tr><td rowspan=4>";$Zeilen++;
    printf("<input type=\"hidden\" name=\"id[]\" value=\"%s\">",$persid);
    if ($Person["eingeladen"]) {
      echo "Eingeladen am ".$Person["eingeladen"];
      echo "<nobr><input type=checkbox name=\"eingeladen[$persid]\" value=\"nein\"> NICHT eingeladen<br>";
    } else 
      echo "<nobr><input type=\"checkbox\" name=\"eingeladen[$persid]\" value=\"ja\"> Einladen</nobr><br>";
    if ($Person["antwort"]) {
      echo "Antwort am ".$Person["antwort"];
      echo "<nobr><input type=checkbox name=\"antwort[$persid]\" value=\"nein\"> KEINE Antwort <br>";
    } else 
      echo "<nobr><input type=\"checkbox\" name=\"antwort[$persid]\" value=\"ja\"> Antwort</nobr><br>";
    if ($Person["status"] & 1) {
      echo "Teilname ";
      echo "<nobr><input type=checkbox name=\"teilnahme[$persid]\" value=\"nein\"> KEINE Teilnahme<br>";
    } else 
      echo "<nobr><input type=\"checkbox\" name=\"teilnahme[$persid]\" value=\"ja\"> Teilnahme</nobr><br>";
      printf("</td><td>%s</td><td>%s</td><td colspan=2></td><td></td><td></td></tr>\n",$Person["geburtsname"],$Person["vorname"]);
      printf("<tr><td></td><td>%s</td><td></td><td colspan=2></td></tr>\n",
         $Person["aktueller_name"]);$Zeilen++;
    }
    $sql="select vorwahl,telefon from Telefon where uid=$persid";
    $Adressen=mysql_query($sql,$db);    
    while ($Adresse=@mysql_fetch_array($Adressen)) {
      echo "<tr>"; if ($Zeilen>=4) echo "<td></td>";
      printf("<td colspan=3></td><td>%s</td><td>%s</td>\n",$Adresse["vorwahl"],$Adresse["telefon"]);$Zeilen++;
    }
    $geschlecht="";
    switch ($Person["geschlecht"]){
       case 1: $geschlecht="männlich";break;
       case 2: $geschlecht="weiblich";break;
    }	

    echo "<tr>"; if ($Zeilen>=4) echo "<td></td>";
    printf("</td><td></td><td>%s</td><td>%s</td><td></td></tr>",$Person["grad"],$geschlecht);$Zeilen++;
    echo "<tr>"; if ($Zeilen>=4) echo "<td></td>";
    printf("<td></td><td>%d-%d</td><td colspan=2>%s</td><td colspan=2 align=right>%s</td></tr>",
          $Person["von"],$Person["bis"],$Person["studiengang"],$Person["geburtsdatum"]);$Zeilen++;

    // Emails  
    $sql="select adresse from EMail where uid=$persid";
    $emails=mysql_query($sql,$db);
    if ($email=@mysql_fetch_array($emails)) 
           $mailstring='<a href="mailto:'.$email["adresse"].'">'.$email["adresse"]."</a>"; else $mailstring="";
    while ($email=@mysql_fetch_array($emails)) 
         $mailstring .= '<br><a href="mailto:'.$email["adresse"].'">'.$email["adresse"]."</a>";
    echo "<tr>"; if ($Zeilen>=4) echo "<td></td>";
    printf("<td colspan=\"2\" valign=\"bottom\"><font size=-2>%s</font></td><td colspan=4>%s</td></tr>\n",
       $Person["aktualisierung"],$mailstring);$Zeilen++;

    // Homepages
    $sql="select adresse,name from HP where uid=$persid";
    $emails=mysql_query($sql,$db);
    if ($email=@mysql_fetch_array($emails)) {
         $mailstring='<a href="'.$email["adresse"].'">'.$email["name"]."</a>";
    while ($email=@mysql_fetch_array($emails)) 
         $mailstring .= '<br><a href="'.$email["adresse"].'">'.$email["name"]."</a>";
    echo "<tr>"; if ($Zeilen>=4) echo "<td></td>";
    printf("<td colspan=2></td><td colspan=4>%s</td></tr>\n",$mailstring);$Zeilen++;
    }
    if ($Person["kommentar"]){
      echo "<tr>"; if ($Zeilen>=4) echo "<td></td>";
      printf("<tr><td></td><td colspan=6>%s</td></tr>\n",
       $Person["kommentar"]);$Zeilen++;}
    while($Person=mysql_fetch_array($Personen)){
      $persid=$Person["id"];
      while ($Zeilen<4) {echo "<tr><td colspan=7></td></tr>";$Zeilen++;}
      $Zeilen=0;
      echo "<tr><td colspan=7 align=center><IMG SRC=\"../../sonstbild/fahne.gif\" HEIGHT=5 WIDTH=700 ALIGN=CENTER></td></tr>\n";
      $sql="select anfang,plz,ort,ende,vorwahl,telefon from Adressen "
          ."where uid=$persid"; 
      $Adressen=mysql_query($sql,$db);
      if ($Adresse=@mysql_fetch_array($Adressen)){    
    echo "<tr valign=top><td rowspan=4>";$Zeilen++;
    printf("<input type=\"hidden\" name=\"id[]\" value=\"%s\">",$persid);
    if ($Person["eingeladen"]) {
      echo "Eingeladen am ".$Person["eingeladen"];
      echo "<nobr><input type=checkbox name=\"eingeladen[$persid]\" value=\"nein\"> NICHT eingeladen<br>";
    } else 
      echo "<nobr><input type=\"checkbox\" name=\"eingeladen[$persid]\" value=\"ja\"> Einladen</nobr><br>";
    if ($Person["antwort"]) {
      echo "Antwort am ".$Person["antwort"];
      echo "<nobr><input type=checkbox name=\"antwort[$persid]\" value=\"nein\"> KEINE Antwort <br>";
    } else 
      echo "<nobr><input type=\"checkbox\" name=\"antwort[$persid]\" value=\"ja\"> Antwort</nobr><br>";
    if ($Person["status"] & 1) {
      echo "Teilname ";
      echo "<nobr><input type=checkbox name=\"teilnahme[$persid]\" value=\"nein\"> KEINE Teilnahme<br>";
    } else 
      echo "<nobr><input type=\"checkbox\" name=\"teilnahme[$persid]\" value=\"ja\"> Teilnahme</nobr><br>";
         printf("</td><td>%s</td><td>%s</td><td colspan=2>%s</td><td>%s</td><td>%s</td></tr>\n",
           $Person["geburtsname"],$Person["vorname"],$Adresse["anfang"],$Adresse["vorwahl"],$Adresse["telefon"]);
         printf("<tr valign=top><td></td><td>%s</td><td>%s</td><td>%s</td><td colspan=2></td></tr>\n",
           $Person["aktueller_name"],$Adresse["plz"],$Adresse["ort"]);$Zeilen++;
         if ($Person["ende"]) {
           printf("<tr><td colspan=2></td><td colspan=2>%s</td><td colspan=2></td></tr>",
                 $Adresse["ende"]);$Zeilen++;}
         while ($Adresse=@mysql_fetch_array($Adressen)){    
           echo "<tr valign=top>"; if ($Zeilen>=4) echo "<td></td>";
           printf("<td></td><td></td><td colspan=2>%s</td><td>%s</td><td>%s</td></tr>\n",
             $Adresse["anfang"],$Adresse["vorwahl"],$Adresse["telefon"]);$Zeilen++;
           echo "<tr valign=top>"; if ($Zeilen>=4) echo "<td></td>";
           printf("<td></td><td></td><td>%s</td><td>%s</td><td colspan=2></td></tr>\n",
             $Adresse["plz"],$Adresse["ort"]);$Zeilen++;
           if ($Person["ende"]) {
             echo "<tr>"; if ($Zeilen>=4) echo "<td></td>";
             printf("<td colspan=2></td><td colspan=2>%s</td><td colspan=2></td></tr>",
                 $Adresse["ende"]);$Zeilen++;}
         }
      }else{
    echo "<tr><td rowspan=4>";$Zeilen++;
    printf("<input type=\"hidden\" name=\"id[]\" value=\"%s\">",$persid);
    if ($Person["eingeladen"]) {
      echo "Eingeladen am ".$Person["eingeladen"];
      echo "<nobr><input type=checkbox name=\"eingeladen[$persid]\" value=\"nein\"> NICHT eingeladen<br>";
    } else 
      echo "<nobr><input type=\"checkbox\" name=\"eingeladen[$persid]\" value=\"ja\"> Einladen</nobr><br>";
    if ($Person["antwort"]) {
      echo "Antwort am ".$Person["antwort"];
      echo "<nobr><input type=checkbox name=\"antwort[$persid]\" value=\"nein\"> KEINE Antwort <br>";
    } else 
      echo "<nobr><input type=\"checkbox\" name=\"antwort[$persid]\" value=\"ja\"> Antwort</nobr><br>";
    if ($Person["status"] & 1) {
      echo "Teilname ";
      echo "<nobr><input type=checkbox name=\"teilnahme[$persid]\" value=\"nein\"> KEINE Teilnahme<br>";
    } else 
      echo "<nobr><input type=\"checkbox\" name=\"teilnahme[$persid]\" value=\"ja\"> Teilnahme</nobr><br>";
	printf("</td><td>%s</td><td>%s</td><td colspan=2></td><td></td><td></td></tr>\n",
           $Person["geburtsname"],$Person["vorname"]);
        printf("<tr><td></td><td>%s</td><td></td><td colspan=2></td></tr>\n",
           $Person["aktueller_name"]);$Zeilen++;
      }
      $sql="select vorwahl,telefon from Telefon where uid=$persid";
      $Adressen=mysql_query($sql,$db);    
      while ($Adresse=@mysql_fetch_array($Adressen)) {
        echo "<tr>"; if ($Zeilen>=4) echo "<td></td>";
        printf("<td colspan=4></td><td>%s</td><td>%s</td>\n",$Adresse["vorwahl"],$Adresse["telefon"]);$Zeilen++;}

      $geschlecht="";
      switch ($Person["geschlecht"]){
         case 1: $geschlecht="männlich";break;
         case 2: $geschlecht="weiblich";break;
      }	

      echo "<tr>"; if ($Zeilen>=4) echo "<td></td>";
      printf("<td></td><td>%s</td><td>%s</td><td></td></tr>",$Person["grad"],$geschlecht);$Zeilen++;
      echo "<tr>"; if ($Zeilen>=4) echo "<td></td>";
      printf("<td></td><td>%d-%d</td><td colspan=2>%s</td><td colspan=2 align=right>%s</td></tr>",
          $Person["von"],$Person["bis"],$Person["studiengang"],$Person["geburtsdatum"]);$Zeilen++;

      // Emails  
      $sql="select adresse from EMail where uid=$persid";
      $emails=mysql_query($sql,$db);
      if ($email=@mysql_fetch_array($emails)) 
           $mailstring='<a href="mailto:'.$email["adresse"].'">'.$email["adresse"]."</a>"; else $mailstring="";
      while ($email=@mysql_fetch_array($emails)) 
           $mailstring .= '<br><a href="mailto:'.$email["adresse"].'">'.$email["adresse"]."</a>";
      echo "<tr>"; if ($Zeilen>=4) echo "<td></td>";
      printf("<td colspan=2><font size=-2>%s</font></td><td colspan=4>%s</td></tr>\n",
         $Person["aktualisierung"],$mailstring);$Zeilen++;

      // Homepages
      $sql="select adresse,name from HP where uid=$persid";
      $emails=mysql_query($sql,$db);
      if ($email=@mysql_fetch_array($emails)) {
           $mailstring='<a href="'.$email["adresse"].'">'.$email["name"]."</a>"; 
        while ($email=@mysql_fetch_array($emails)) 
           $mailstring .= '<br><a href="'.$email["adresse"].'">'.$email["name"]."</a>";
        echo "<tr>"; if ($Zeilen>=4) echo "<td></td>";
        printf("<td colspan=2></td><td colspan=4>%s</td></tr>\n",$mailstring);$Zeilen++;
      }
      if ($Person["kommentar"]){
        echo "<tr>"; if ($Zeilen>=4) echo "<td></td>";
        printf("<td colspan=6>%s</td></tr>\n",$Person["kommentar"]);$Zeilen++;}
    }
    echo "</table><table border=0><tr><td align=center>\n";
    echo "</td></tr></table>\n";
    echo "</form>";
    include('ende.php');
  } else {?>
  <p>Leider nichts gefunden.</p>
  <p><a href="<?php echo $PHP_SELF?>?aktion=bearbeiten$penne">Hier gehts zur&uuml;ck zum Anfang</a></p>
  <?php }
}
#include('ende.php');
?>
