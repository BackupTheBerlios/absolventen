<?php if (!$db = @mysql_connect($mysql_daten['Rechner'], $mysql_daten['Nutzer'], $mysql_daten['Passwort'])){
  authenticate();
}
mysql_select_db($mysql_daten['Datenbank'],$db);

function tloeschen($id,$wirklich,$mysql_daten,$db,$PHP_SELF){
  if (!$id) {
    $aktion="termine";
    include("termine.php");
    die;
  }
  switch ($wirklich) {
    case 'nein':{ 
                  $aktion="Termin bearbeiten";
                  include("termine.php");
                }
    case 'ja':  {
                  $sql="delete from Einladung where termin = $id";
                  mysql_query($sql);
                  $sql="delete from Termine where id = $id";
                  mysql_query($sql);
                  $id=0;
                  $aktion="termine";
                  include("termine.php");
                }
    default:    {
                  $aktion="Termin löschen";
                  include("termine.php");
                }
  }
}

function hinzufuegen($id,$mysql_daten,$db,$PHP_SELF)
{
  if (!$mysql_daten["name"]) $Fehler="Die Beschreibung fehlt.";
  if ($mysql_daten["datum_von"] && !ereg("^([0-9]{1,2}[\\.,]){2}[0-9]{2,4}( [0-9]{1,2}[\\.,:][0-9]{1,2}([\\.,:][0-9]{1,2}){0,1}){0,1}$",$mysql_daten["datum_von"])) $Fehler="Das Anfangsdatum muss numerisch angegeben werden oder wurde falsch eingegeben.";
  if ($mysql_daten["datum_bis"] && !ereg("^([0-9]{1,2}[\\.,]){2}[0-9]{2,4}( [0-9]{1,2}[\\.,:][0-9]{1,2}([\\.,:][0-9]{1,2}){0,1}){0,1}$",$mysql_daten["datum_bis"])) $Fehler="Das Abschlussdatum muss numerisch angegeben werden oder wurde falsch eingegeben.";
  if ($Fehler) {
     include('anfang.php'); 
     echo "<H2>$aktion</H2>";?>
<font color="#FF0000"><blink>Ung&uuml;ltige Eingabe</blink><br>
<?php echo $Fehler ?></font>
<table border=2>
<tr align=center><td>
<form method="post" action="<?php echo $PHP_SELF;?>">
<?php if (isset($penne)) { ?>
<input type="hidden" name="penne" value="ja">
<?php } ?>
<table border=0>
<tr><td>Beschreibung</td><td align=center><textarea cols=30 rows=5 name="name"><?php echo htmlspecialchars($mysql_daten["name"]) ?></textarea></td></tr>
<tr><td>Zeitspanne</td><td align=center><nobr>von <input type="text" maxlength=22 size=22 name="datum_von" value="<?php echo $mysql_daten["datum_von"] ?>"></nobr>  <nobr>bis <input type="text" maxlength=22 size=22 name="datum_bis" value="<?php echo $mysql_daten["datum_bis"] ?>"></nobr></td></tr>
<tr align=center><td colspan=2><input type="submit" name="aktion" value="Termin hinzuf&uuml;gen"> <input type="reset" value="Zur&uuml;cksetzen"></td></tr>
</table>
</form>
</table>
<?php include("ende.php");
    die;
  }
  if ($mysql_daten["datum_von"]) {
    ereg("^([0-9]{1,2})[\\.,]([0-9]{1,2})[\\.,]([0-9]{2,4})( ([0-9]{1,2})[\\.,:]([0-9]{1,2})([\\.,:]([0-9]{1,2})){0,1}){0,1}$",$mysql_daten["datum_von"],$dvon);
    //  0  alles
    //  1  Tag
    //  2  Monat
    //  3  Jahr
    //  4  Uhrzeit
    //  5  Stunde 
    //  6  Minute
    //  7  Trennzeichen + Sekunde
    //  8  Sekunde
    
    $dvneu=sprintf("\"%d-%d-%d %d:%d:%d\"",$dvon[3],$dvon[2],$dvon[1],$dvon[5],$dvon[6],$dvon[8]);
  } else $dvneu="NULL";
  if ($mysql_daten["datum_bis"]) {
    ereg("^([0-9]{1,2})[\\.,]([0-9]{1,2})[\\.,]([0-9]{2,4})( ([0-9]{1,2})[\\.,:]([0-9]{1,2})([\\.,:]([0-9]{1,2})){0,1}){0,1}$",$mysql_daten["datum_bis"],$dvon);
  if (($dvon[5]=="")&&($dvon[6]=="")&&($dvon[8]=="")) { $dvon[5]=23;$dvon[6]=59;$dvon[8]=59;}
    $dbneu=sprintf("\"%d-%d-%d %d:%d:%d\"",$dvon[3],$dvon[2],$dvon[1],$dvon[5],$dvon[6],$dvon[8]);
  } else $dbneu="NULL";
  $sql=sprintf("insert into Termine (name,datum_von,datum_bis) values ('%s',%s,%s)",($mysql_daten["name"]),$dvneu,$dbneu);
  mysql_query($sql,$db);
  $aktion="Termin bearbeiten";
  $id=mysql_insert_id($db);
  include("termine.php");
}

function aendern($id,$mysql_daten,$db,$PHP_SELF)
{
  if (!$mysql_daten["name"]) $Fehler="Die Beschreibung fehlt.";
  if ($mysql_daten["datum_von"] && !ereg("^([0-9]{1,2}[\\.,]){2}[0-9]{2,4}( [0-9]{1,2}[\\.,:][0-9]{1,2}([\\.,:][0-9]{1,2}){0,1}){0,1}$",$mysql_daten["datum_von"])) $Fehler="Das Anfangsdatum muss numerisch angegeben werden oder wurde falsch eingegeben.";
  if ($mysql_daten["datum_bis"] && !ereg("^([0-9]{1,2}[\\.,]){2}[0-9]{2,4}( [0-9]{1,2}[\\.,:][0-9]{1,2}([\\.,:][0-9]{1,2}){0,1}){0,1}$",$mysql_daten["datum_bis"])) $Fehler="Das Abschlussdatum muss numerisch angegeben werden oder wurde falsch eingegeben.";
  if ($Fehler) {
     include('anfang.php'); 
     echo "<H2>$aktion</H2>";?>
<font color="#FF0000"><blink>Ung&uuml;ltige Eingabe</blink><br>
<?php echo $Fehler ?></font>
<table border=2>
<tr align=center><td>
<form method="post" action="<?php echo $PHP_SELF;?>">
<?php if (isset($penne)) { ?>
<input type="hidden" name="penne" value="ja">
<?php } ?>
<table border=0>
<tr><td>Beschreibung</td><td align=center><textarea cols=30 rows=5 name="name"><?php echo htmlspecialchars($mysql_daten["name"]) ?></textarea></td></tr>
<tr><td>Zeitspanne</td><td align=center><nobr>von <input type="text" maxlength=22 size=22 name="datum_von" value="<?php echo $mysql_daten["datum_von"] ?>"></nobr>  <nobr>bis <input type="text" maxlength=22 size=22 name="datum_bis" value="<?php echo $mysql_daten["datum_bis"] ?>"></nobr></td></tr>
<tr align=center><td colspan=2><input type="submit" name="aktion" value="Termin hinzuf&uuml;gen"> <input type="reset" value="Zur&uuml;cksetzen"></td></tr>
</table>
</form>
</table>
<?php include("ende.php");
    die;
  }
  if ($mysql_daten["datum_von"]) {
    ereg("^([0-9]{1,2})[\\.,]([0-9]{1,2})[\\.,]([0-9]{2,4})( ([0-9]{1,2})[\\.,:]([0-9]{1,2})([\\.,:]([0-9]{1,2})){0,1}){0,1}$",$mysql_daten["datum_von"],$dvon);
    //  0  alles
    //  1  Tag
    //  2  Monat
    //  3  Jahr
    //  4  Uhrzeit
    //  5  Stunde 
    //  6  Minute
    //  7  Trennzeichen + Sekunde
    //  8  Sekunde
    
    $dvneu=sprintf("\"%d-%d-%d %d:%d:%d\"",$dvon[3],$dvon[2],$dvon[1],$dvon[5],$dvon[6],$dvon[8]);
  } else $dvneu="NULL";
  if ($mysql_daten["datum_bis"]) {
    ereg("^([0-9]{1,2})[\\.,]([0-9]{1,2})[\\.,]([0-9]{2,4})( ([0-9]{1,2})[\\.,:]([0-9]{1,2})([\\.,:]([0-9]{1,2})){0,1}){0,1}$",$mysql_daten["datum_bis"],$dvon);
  if (($dvon[5]=="")&&($dvon[6]=="")&&($dvon[8]=="")) { $dvon[5]=23;$dvon[6]=59;$dvon[8]=59;}
    $dbneu=sprintf("\"%d-%d-%d %d:%d:%d\"",$dvon[3],$dvon[2],$dvon[1],$dvon[5],$dvon[6],$dvon[8]);
  } else $dbneu="NULL";
  $sql=sprintf("update Termine set name='%s',datum_von=%s,datum_bis=%s where id=%d",($mysql_daten["name"]),$dvneu,$dbneu,$id);
  mysql_query($sql,$db);
  $aktion="Termin bearbeiten";
  include("termine.php");
}

//echo "<br> $db <br>";
$mysql_daten["datum_von"]=$datum_von;
$mysql_daten["datum_bis"]=$datum_bis;
$mysql_daten["name"]=$name;

$Fehler="";

switch ($aktion) {
  case "Termin löschen":tloeschen($id,$wirklich,$mysql_daten,$db,$PHP_SELF);break;
  case "Termin hinzufügen":hinzufuegen($id,$mysql_daten,$db,$PHP_SELF);break;
  case "Termin ändern":aendern($id,$mysql_daten,$db,$PHP_SELF);break; 
}
