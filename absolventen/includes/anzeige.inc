<?php 
function anzeige_kopf () { ?>
<table border=1>
<tr><th colspan=7><font size=+2>Jahrgang $jahrgang</th></tr>
<tr align=left><th></th><th>Geburtsname</th><th>Vorname</th><th colspan=2>Adresse erster Teil</th><th>Vorwahl</th><th>Telefon</th></tr>
<tr align=left><th></th><th></th><th>aktueller Name</th><th>PLZ</th><th>Ort</th><th colspan=2></th></tr>
<tr align=left><th></th><th colspan=2></th><th colspan=2>Adresse zweiter Teil</th><th colspan=2></th></tr>
<tr align=left><th></th><th></th><th>Akad. Grad</th><th colspan=2>Geschlecht</th><th></th><th></th></tr>
<tr align=left><th></th><th></th><th>Zeit</th><th colspan=2>Studiengang</th><th colspan=2>Geburtsdatum</th></tr>
<tr align=left><th></th><th colspan=2><font size=-2>letzte &Auml;nderung</font></th><th colspan=4>Email</th></tr>
<tr align=left><th></th><th colspan=2></th><th colspan=4>Homepage</th></tr>
<tr align=left><th></th><th colspan=6>Bemerkungen</th><tr>
<?php 
}

function anzeige_formular($anz,$id) {
global $PHP_SELF;
?>
 Bitte den zu bearbeitenden Datensatz auswählen! <p>
<?php for ($Buchstabe=ord('A');$Buchstabe<=ord('Z');$Buchstabe++) {
     echo '<a href='.$PHP_SELF.'?aktion='.urlencode($anz)
       .($anz=="Einladungen bearbeiten"?"&terminid=$id":"")
       .'&where_modus=direkt&where=geburtsname%20regexp%20%22%5e%5b'
       .chr($Buchstabe).chr($Buchstabe+ord('a')-ord('A'))
       .'%5d%22or%20aktueller_name%20regexp%20%22%5e%5b'
       .chr($Buchstabe).chr($Buchstabe+ord('a')-ord('A'))
       .'%5d%22>'.chr($Buchstabe)."</a> \n";}
     echo '<a href='.$PHP_SELF.'?aktion='.urlencode($anz)
       .($anz=="Einladungen bearbeiten"?"&terminid=$id":"")
       .'&where_modus=direkt&where=geburtsname%20regexp'
       .'%20%22%5e%5b%5eA-Za-z%5d%22%20or%20aktueller_name%20regexp'
       .'%20%22%5e%5b%5eA-Za-z%5d%22>sonstige</a>'."\n";
?><p>
<form method="post" action="<?=$PHP_SELF?>">
<input type=hidden name=aktion value="<?=$anz?>">
<input type=text size=40 name="where"><br>
<table border=0>
<tr><td><input type=radio name="where_modus" value="genau"></td>
    <td>Exakte &Uuml;bereinstimmung</td></tr>
<tr><td><input type=radio name="where_modus" value="regexp"></td>
    <td>Regul&auml;rer Ausdruck</td></tr>
<tr><td><input type=radio name="where_modus" value="like"></td>
    <td>SQL-"LIKE"</td></tr>
<tr><td><input type=radio name="where_modus" value="soundex"></td>
    <td>&Auml;hnlicher Name</td></tr>
<tr><td><input type=radio name="where_modus" value="direkt"></td>
    <td>SQL-WHERE-Klausel</td></tr>
</table>
<input type=submit value="Suchen"><input type=reset value="Abbrechen">
</form><p>
<?php 
}

function anzeige_person($Person,$anz,$id) {

  global $db;
  global $PHP_SELF;

  $persid=$Person["id"];
  $sql="select anfang,plz,ort,ende,vorwahl,telefon from Adressen "
        ."where Adressen.uid=$persid order by aktiv desc"; 
  $Adressen=db_anfrage($sql,$db);
  $Zeilen=0;
  echo "<tr><td colspan=7 align=center><IMG SRC=\"../../sonstbild/fahne.gif\""
       . " HEIGHT=5 WIDTH=700 ALIGN=CENTER></td></tr>\n";
  
// Namen und Adressen bzw. Telefon-Nummern  
  if ($Adresse=@db_array_holen($Adressen)){    
    printf("<tr><td rowspan=4>");
    switch ($anz) {
      case 'bearbeiten' :
        printf("<form method=\"get\" action=\"%s\">",$PHP_SELF);
           $Zeilen++;
        printf("<input type=\"hidden\" name=\"id\" value=\"%s\">",$persid);
        echo "<input type=\"submit\" name=\"aktion\" value=\"Bearbeiten\"><br> ";
        echo "<input type=\"submit\" name=\"aktion\" value=\"L&ouml;schen\"></form>";
	break;
      case 'Einladungen bearbeiten' :
        printf("<input type=\"hidden\" name=\"id[]\" value=\"%s\">",$persid);
        if ($Person["eingeladen"]) {
          echo "Eingeladen am ".$Person["eingeladen"];
          echo " <nobr><input type=checkbox name=\"eingeladen[$persid]\" value=\"nein\"> NICHT eingeladen</nobr><br>";
        } else 
          echo " <nobr><input type=\"checkbox\" name=\"eingeladen[$persid]\" value=\"ja\"> Einladen</nobr><br>";
        if ($Person["antwort"]) {
          echo "Antwort am ".$Person["antwort"];
          echo " <nobr><input type=checkbox name=\"antwort[$persid]\" value=\"nein\"> KEINE Antwort </nobr><br>";
        } else 
          echo " <nobr><input type=\"checkbox\" name=\"antwort[$persid]\" value=\"ja\"> Antwort</nobr><br>";
        if ($Person["status"]) {
          echo "Teilnahme mit " . $Person["status"] . " Personen";
          echo " <nobr><input type=checkbox name=\"teilnahme[$persid]\" value=\"nein\"> KEINE Teilnahme</nobr><br>";
        } else 
          echo " <nobr><input type=\"checkbox\" name=\"teilnahme[$persid]\" value=\"1\"> Teilnahme</nobr><br>";
	break;
    }
    printf("</td><td>%s</td><td>%s</td><td colspan=2>%s</td><td>%s</td>"
           . "<td>%s</td></tr>\n",
           $Person["geburtsname"],$Person["vorname"],$Adresse["anfang"],
	   $Adresse["vorwahl"],$Adresse["telefon"]);
    printf("<tr valign=top><td></td><td>%s</td><td>%s</td><td>%s</td>"
           . "<td colspan=2></td></tr>\n",
           $Person["aktueller_name"],$Adresse["plz"],$Adresse["ort"]);$Zeilen++;
    if ($Person["ende"]) {
      printf("<tr><td colspan=2></td><td colspan=2>%s</td><td colspan=2></td>"
             . "</tr>",$Adresse["ende"]);$Zeilen++;
    }

    // weitere Adressen
    while ($Adresse=@db_array_holen($Adressen)){    
      echo "<tr valign=top>"; if ($Zeilen>=4) echo "<td></td>";
      printf("<td colspan=2></td><td colspan=2>%s</td><td>%s</td><td>%s</td></tr>\n",
         $Adresse["anfang"],$Adresse["vorwahl"],$Adresse["telefon"]);$Zeilen++;
      echo "<tr valign=top>"; if ($Zeilen>=4) echo "<td></td>";
      printf("<td colspan=2></td><td>%s</td><td>%s</td>"
             . "<td colspan=2></td></tr>\n",
             $Adresse["plz"],$Adresse["ort"]);$Zeilen++;
      if ($Adresse["ende"]) {
        echo "<tr>"; if ($Zeilen>=4) echo "<td></td>";
        printf("<td colspan=2></td><td colspan=2>%s</td>"
	       . "<td colspan=2></td></tr>\n",
               $Adresse["ende"]);$Zeilen++;
      }
    }
  } else
  {
    // Keine Adressen
    printf("<tr><td rowspan=4>");
    switch ($anz) {
      case 'bearbeiten' :
        printf("<form method=\"get\" action=\"%s\">",$PHP_SELF);
           $Zeilen++;
        printf("<input type=\"hidden\" name=\"id\" value=\"%s\">",$persid);
        echo "<input type=\"submit\" name=\"aktion\" value=\"Bearbeiten\"><br> ";
        echo "<input type=\"submit\" name=\"aktion\" value=\"L&ouml;schen\"></form>";
	break;
      case 'Einladungen bearbeiten' :
        printf("<input type=\"hidden\" name=\"id[]\" value=\"%s\">",$persid);
        if ($Person["eingeladen"]) {
          echo "Eingeladen am ".$Person["eingeladen"];
          echo " <nobr><input type=checkbox name=\"eingeladen[$persid]\" value=\"nein\"> NICHT eingeladen</nobr><br>";
        } else 
          echo " <nobr><input type=\"checkbox\" name=\"eingeladen[$persid]\" value=\"ja\"> Einladen</nobr><br>";
        if ($Person["antwort"]) {
          echo "Antwort am ".$Person["antwort"];
          echo " <nobr><input type=checkbox name=\"antwort[$persid]\" value=\"nein\"> KEINE Antwort </nobr><br>";
        } else 
          echo " <nobr><input type=\"checkbox\" name=\"antwort[$persid]\" value=\"ja\"> Antwort</nobr><br>";
        if ($Person["status"]) {
          echo "Teilnahme mit " . $Person["status"] . " Personen";
          echo " <nobr><input type=checkbox name=\"teilnahme[$persid]\" value=\"nein\"> KEINE Teilnahme</nobr><br>";
        } else 
          echo " <nobr><input type=\"checkbox\" name=\"teilnahme[$persid]\" value=\"1\"> Teilnahme</nobr><br>";
	break;
    }
    printf("</td><td>%s</td><td>%s</td><td colspan=2></td><td></td>"
           . "<td></td></tr>\n",$Person["geburtsname"],$Person["vorname"]);
    printf("<tr><td></td><td>%s</td><td></td><td colspan=2></td></tr>\n",
       $Person["aktueller_name"]);$Zeilen++;
  }
  
  // weitere Telefon-Nummern
  $sql="select vorwahl,telefon from Telefon where uid=$persid";
  $Adressen=db_anfrage($sql,$db);    
  while ($Adresse=@db_array_holen($Adressen)) {
    echo "<tr>"; if ($Zeilen>=4) echo "<td></td>";
    printf("<td colspan=4></td><td>%s</td><td>%s</td>\n",
    $Adresse["vorwahl"],$Adresse["telefon"]);$Zeilen++;
  }
  
  // akad. Grad / Titel und Geschlecht
  $geschlecht="";
  switch ($Person["geschlecht"]){
     case 1: $geschlecht="männlich";break;
     case 2: $geschlecht="weiblich";break;
  }	

  echo "<tr>"; if ($Zeilen>=4) echo "<td></td>";
  printf("</td><td></td><td>%s</td><td colspan=2>%s</td><td></td></tr>\n",
          $Person["grad"],$geschlecht);$Zeilen++;

  // Studiendauer und -fach
  echo "<tr>"; if ($Zeilen>=4) echo "<td></td>";
  printf("<td></td><td>%d-%d</td><td colspan=2>%s</td>"
         . "<td colspan=2 align=right>%s</td></tr>\n",
        $Person["von"],$Person["bis"],$Person["studiengang"],
	$Person["geburtsdatum"]);$Zeilen++;

  // Emails  
  $sql="select adresse from EMail where uid=$persid";
  $emails=db_anfrage($sql,$db);
  if ($email=@db_array_holen($emails)) {
    $mailstring='<a href="mailto:'.$email["adresse"].'">'
	 . $email["adresse"]."</a>"; 
	 while ($email=@db_array_holen($emails)) 
         $mailstring .= '<br><a href="mailto:'.$email["adresse"].'">'
         . $email["adresse"]."</a>";
  } else $mailstring="";
  echo "<tr>"; if ($Zeilen>=4) echo "<td></td>";
  printf("<td colspan=\"2\" valign=\"bottom\"><font size=-2>%s</font></td>"
       . "<td colspan=4>%s</td></tr>\n",
       $Person["aktualisierung"],$mailstring);$Zeilen++;
  

  // Homepages
  $sql="select adresse,name from HP where uid=$persid";
  $emails=db_anfrage($sql,$db);
  if ($email=@db_array_holen($emails)) {
       $mailstring='<a href="'.$email["adresse"].'">'.$email["name"]."</a>";
    while ($email=@db_array_holen($emails)) 
       $mailstring .= '<br><a href="'.$email["adresse"].'">'
       . $email["name"]."</a>";
    echo "<tr>"; if ($Zeilen>=4) echo "<td></td>";
    printf("<td colspan=2></td><td colspan=4>%s</td></tr>\n",$mailstring);
      $Zeilen++;
  }

  // Zusatzbemerkungen
  if ($Person["kommentar"]){
    echo "<tr>"; if ($Zeilen>=4) echo "<td></td>";
    printf("<tr><td></td><td colspan=6>%s</td></tr>\n",
       $Person["kommentar"]);$Zeilen++;
  }
       
  while ($Zeilen<4) {echo "<tr><td colspan=7></td></tr>";$Zeilen++;}
}


function anzeige($anz="",$id=0) {

  global $aktion;
  global $db;
  global $where;
  global $where_modus;
  global $PHP_SELF;

  if (!$anz) $anz=$aktion;
  if (!$db) db_verbinden();

  
  anzeige_formular($anz,$id);
  
  if (!$where) { 
    $where="geburtsname regexp '^[aA]' or aktueller_name regexp '^[aA]'"; 
    $where_modus="direkt"; 
  }
  
  if (!ereg("(direkt|regexp|genau|like|soundex)",$where_modus)) 
       $where_modus = "genau";
  switch ($where_modus) {       
      case "genau": $where_modus="=";
      case "regexp":
      case "like":$where = sprintf("(geburtsname %s '%s' or aktueller_name "
                    . "%s '%s' or vorname %s '%s')",$where_modus,$where,
		    $where_modus,$where,$where_modus,$where); 
                  break;
      case "soundex": $where = sprintf("(soundex(geburtsname) = soundex('%s') "
                        . "or soundex(aktueller_name) = soundex('%s') or "
			. "soundex(vorname) = soundex('%s'))",
                        $where,$where,$where);
                      break;
      case "direkt": $where = "(".stripslashes($where).")";
                     break;
  }
  switch ($anz) {
     case "bearbeiten":
          $sql="select id,aktueller_name,geburtsname,vorname,kommentar,"
 	       . "DATE_FORMAT(aktualisierung,'%d.%m.%Y %T') as "
	       . "aktualisierung,von,bis,"
 	       . "studiengang,DATE_FORMAT(geburtsdatum,'%d.%m.%Y') as "
	       . "geburtsdatum,"
               . "geschlecht,grad from Personen where ".$where
               . " order by geburtsname,vorname,aktueller_name";
          break;
     case "Einladungen bearbeiten":
          $sql="select id,aktueller_name,geburtsname,vorname,kommentar,"
 	       . "DATE_FORMAT(aktualisierung,'%d.%m.%Y %T') as "
	       . "aktualisierung,von,bis,"
 	       . "studiengang,DATE_FORMAT(geburtsdatum,'%d.%m.%Y') as "
	       . "geburtsdatum, DATE_FORMAT(eingeladen,'%d.%m.%Y') as "
	       . "eingeladen, DATE_FORMAT(antwort,'%d.%m.%Y') as "
	       . "antwort, status,"
               . "geschlecht,grad from Personen,Einladung where "
	       . $where . " and Einladung.termin=$id and "
	       . "Personen.id=Einladung.uid"
               . " order by geburtsname,vorname,aktueller_name";
          echo "<form method=post action=\"$PHP_SELF\">\n";
	  echo "<input type=hidden name=\"terminid\" value=$id>\n";
	  echo "<input type=hidden name=\"where\" value=\""
	      . htmlspecialchars($where) . "\">\n";
	  echo "<input type=hidden name=\"where_modus\" value=\"$where_modus\">\n";
	  break;
  }
  
  $Personen=db_anfrage($sql,$db);
  if ($Person=@db_array_holen($Personen)){
    anzeige_kopf();
    anzeige_person($Person,$anz,$id);
    while($Person=mysql_fetch_array($Personen))
      anzeige_person($Person,$anz,$id);
      
    echo "</table><table border=0><tr><td align=center>\n";
    echo "</td></tr></table>\n";
    if ($anz=="Einladungen bearbeiten")
      echo "<input type=submit name=aktion value=\"Einladungen ändern\">"
         ." <input type=reset value=\"Zurücksetzen\"></form>"; 
     else
      hinzufuegen();
  } else {?>
  <p>Leider nichts gefunden.</p>
  <p><a href="<?php echo $PHP_SELF?>?aktion=<?=$anz?><?=$penne?>">Hier gehts zur&uuml;ck zum Anfang</a></p>
  <?php 
    if (!$anz=="Einladungen bearbeiten") hinzufuegen();
  }
}?>
