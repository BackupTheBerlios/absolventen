<?php
function Personentermine_anzeigen($id,$daten=0) {
  global $db;
  global $PHP_SELF;
  if (!$daten) {
    $sql="select termin,status,name,"
        ."DATE_FORMAT(eingeladen,'%d.%m.%Y') as eingeladen,"
	."DATE_FORMAT(antwort,'%d.%m.%Y') as antwort,"
        ."DATE_FORMAT(datum_von,'%d.%m.%Y %T') as dv,"
        ."DATE_FORMAT(datum_bis,'%d.%m.%Y %T') as db"
        ." from Einladung,Termine where Einladung.uid=$id"
        ." and Einladung.termin=Termine.id order by datum_von,datum_bis";
    $query=mysql_query($sql,$db);
  }?>
<table border=2>
<?php
  while ($daten=($query?@mysql_fetch_array($query):$daten)){?>
<tr align=center><td><?=$daten["name"]?><br>
<?=$daten["dv"] . ($daten["db"]?" bis ":"") . $daten["db"] ?>

<form method=post action="<?=$PHP_SELF?>">
<p><table border=0>
<tr><td>Eingeladen:</td><td><input type=text name=eingeladen size=10 value="<?=$daten["eingeladen"]?>"></td></tr>
<tr><td>Antwort:</td><td><input type=text name=antwort size=10 value="<?=$daten["antwort"]?>"></td></tr>
<tr><td>Anzahl:</td><td><input type=text name=status size=2 value="<?=$daten["status"]?>"></td></tr>
</table>
<?php if ($daten["termin"]) { echo "<input type=hidden name=termin value=\"" . 
      $daten["termin"] . "\">"; } ?>
<input type=hidden name=aktion value="persönliche Termine">
<input type=hidden name=uid value="<?=$id?>">
<input type=submit name=knopf value="<?=($daten["knopf"]?$daten["$knopf"]:"Eintragung ändern")?>"> <?php
if ($query) { ?>
<input type=submit name=knopf value="Eintragung löschen">
<?php } ?>
<input type=reset value="Zurücksetzen">
</form></td></tr>
<?php
  } 
  if ($query) { 
    $sql="select name,id from Termine left outer join Einladung"
        ." on (Termine.id=Einladung.termin and Einladung.uid=$id)"
	." where Einladung.termin is null order by name";
    $query=mysql_query($sql,$db);
    if ($daten=@mysql_fetch_array($query)) {
    ?>
<tr align=center><td>
<form method=post action="<?=$PHP_SELF?>">
<select name=termin>
<option value=<?=$daten["id"]?>><?=$daten["name"]?>
<?php while ($daten=@mysql_fetch_array($query))
        printf("<option value=%d>%s\n",$daten["id"],$daten["name"]); ?>
</select>

<p><table border=0>
<tr><td>Eingeladen:</td><td><input type=text name=eingeladen size=10></td></tr>
<tr><td>Antwort:</td><td><input type=text name=antwort size=10></td></tr>
<tr><td>Anzahl:</td><td><input type=text name=status size=2></td></tr>
</table>
<input type=hidden name=uid value="<?=$id?>">
<input type=hidden name=aktion value="persönliche Termine">
<input type=submit name=knopf value="Eintragung hinzufügen"> 
<input type=reset value="Zurücksetzen">
</form></td></tr><?php }}
  echo "</table>";
}

function Personentermine_bearbeiten () {
  global $HTTP_POST_VARS;
  global $db;
  db_verbinden();
  if (!$HTTP_POST_VARS["uid"]) die;
  if (!ereg("Eintragung (hinzufügen|löschen|ändern)",$HTTP_POST_VARS["knopf"])
	  || ($HTTP_POST_VARS["knopf"]=="Eingtragung hinzufügen" && 
	  !$HTTP_POST_VARS["termin"] && !$HTTP_POST_VARS["uid"] &&
	  !$HTTP_POST_VARS["eingeladen"] && !$HTTP_POST_VARS["antwort"] &&
          !$HTTP_POST_VARS["status"]))	  
  {
    anfang();
    Persondentermine_anzeigen($HTTP_POST_VARS["uid"]);
    ende();
  }
  if (!$HTTP_POST_VARS["termin"] && $HTTP_POST_VARS["knopf"]
	  == "Eintragung löschen") die;
  if ( ($HTTP_POST_VARS["knopf"]=="Eingtragung ändern" && 
	  $HTTP_POST_VARS["termin"] && !$HTTP_POST_VARS["uid"] &&
	  !$HTTP_POST_VARS["eingeladen"] && !$HTTP_POST_VARS["antwort"] &&
          !$HTTP_POST_VARS["status"]) ) 
	    $HTTP_POST_VARS["knopf"]="Eintragung löschen" ;
  if (ereg("^([0-9]{1,2})[\.,]([0-9]{1,2})[\.,]([0-9]{2,4})$",
      $HTTP_POST_VARS["eingeladen"],$datum)) 
    $eingeladen="'" . $datum[3] . "-" . $datum[2] . "-" . $datum[1] . "'"; 
  else
    $eingeladen="NULL";
  if (ereg("^([0-9]{1,2})[\.,]([0-9]{1,2})[\.,]([0-9]{2,4})$",
      $HTTP_POST_VARS["antwort"],$datum)) 
    $antwort="'" . $datum[3] . "-" . $datum[2] . "-" . $datum[1] . "'"; 
  else
    $antwort="NULL";

  switch ($HTTP_POST_VARS["knopf"]) {
    case "Eintragung hinzufügen":
	    $sql=sprintf("insert into Einladung (termin,uid,eingeladen,antwort,"
	     ."status) values (%d,%d,%s,%s,%d)",$HTTP_POST_VARS["termin"],
	     $HTTP_POST_VARS["uid"],$eingeladen,$antwort,
	     $HTTP_POST_VARS["status"]);break;
    case "Eintragung ändern":
	    $sql=sprintf("update Einladung set eingeladen=%s,"
	       . "antwort=%s,status=%d where uid=%d and termin=%d",
	     $eingeladen,$antwort,
	     $HTTP_POST_VARS["status"],$HTTP_POST_VARS["uid"],
	     $HTTP_POST_VARS["termin"]);break;
    case "Eintragung löschen":
            $sql=sprintf("delete from Einladung where uid=%d and termin=%d",
	         $HTTP_POST_VARS["uid"],$HTTP_POST_VARS["termin"]);break;
  }
  db_anfrage($sql);
#  include('bearbeiten.php');
  anfang();
  Personentermine_anzeigen($HTTP_POST_VARS["uid"]);
  ende();
}
?>
