{?>
 Bitte den zu bearbeitenden Datensatz auswählen! <p>
<?php for ($Buchstabe=ord('A');$Buchstabe<=ord('Z');$Buchstabe++) {
     echo '<a href='.$PHP_SELF.'?aktion=bearbeiten&where_modus=direkt&where=geburtsname%20regexp%20%22%5e%5b'.chr($Buchstabe).chr($Buchstabe+ord('a')-ord('A')).'%5d%22or%20aktueller_name%20regexp%20%22%5e%5b'.chr($Buchstabe).chr($Buchstabe+ord('a')-ord('A')).'%5d%22>'.chr($Buchstabe)."</a> \n";}
     echo '<a href='.$PHP_SELF.'?aktion=bearbeiten&where_modus=direkt&where=geburtsname%20regexp%20%22%5e%5b%5eA-Za-z%5d%22%20or%20aktueller_name%20regexp%20%22%5e%5b%5eA-Za-z%5d%22>sonstige</a>'."\n";
?><p>
<form method="post" action="<?=$PHP_SELF?>">
<input type=hidden name=aktion value=bearbeiten>
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
    if (!$where) { $where="geburtsname regexp '^[aA]' or aktueller_name regexp '^[aA]'"; $where_modus="direkt"; }
    if (!ereg("(direkt|regexp|genau|like|soundex)",$where_modus)) 
       $where_modus = "genau";
    switch ($where_modus) {       
      case "genau": $where_modus="=";
      case "regexp":
      case "like":$where = sprintf("(geburtsname %s '%s' or aktueller_name %s '%s' or vorname %s '%s')",$where_modus,$where,$where_modus,$where,$where_modus,$where); break;
      case "soundex": $where = sprintf("(soundex(geburtsname) = soundex('%s') or soundex(aktueller_name) = soundex('%s') or soundex(vorname) = soundex('%s'))",
           $where,$where,$where);break;
      case "direkt": $where = "(".stripslashes($where).")";break;
    }
    $sql="select id,aktueller_name,geburtsname,vorname,kommentar,DATE_FORMAT(aktualisierung,'%d.%m.%Y %T') as aktualisierung,von,bis,studiengang,"
  . " DATE_FORMAT(geburtsdatum,'%d.%m.%Y')as geburtsdatum,geschlecht,grad from Personen"
   . " where ".$where
   . " order by geburtsname,vorname,aktueller_name";
