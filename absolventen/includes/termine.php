<?php if (!$db = @mysql_connect($mysql_daten['Rechner'], $mysql_daten['Nutzer'], $mysql_daten['Passwort'])){
  authenticate();
}

if ($aktion=="termine") $aktion="Termine";
include('anfang.php');
echo "<H2>$aktion</H2>";
//echo "<br> $db <br>";

mysql_select_db($mysql_daten['Datenbank'],$db);

if ($id) {
  $sql="select name,if(datum_von is null,NULL,DATE_FORMAT(datum_von,'%d.%m.%Y %T')) as datum_von"
        .",if(datum_bis is null,NULL,DATE_FORMAT(datum_bis,'%d.%m.%Y %T')) as datum_bis from Termine where id=$id";
  $result=mysql_query($sql,$db);
  if ($Termin=@mysql_fetch_array($result)){
?>
<H3>Termin</H3>
<table border=2>
<tr align=center><td>
<?php if (!($aktion=="Termin löschen")) { ?>
<form method="post" action="<?php echo $PHP_SELF ?>">
<input type="hidden" name="id" value="<?php echo $id ?>">
<?php if (isset($penne)) {?>
<input type="hidden" name="penne" value="ja">
<?php } ?>
<table border="0">
<tr><td>Beschreibung</td><td align=center><textarea cols=30 rows=5 name="name"><?php echo str_replace("<br>","",$Termin["name"])?></textarea>
<tr><td>Zeitspanne</td><td align=center><nobr>von <input type="text" maxlength=22 size=22 name="datum_von" value="<?php echo $Termin["datum_von"];?>"></nobr>
<nobr>bis <input type="text" maxlength=22 size=22 name="datum_bis" value="<?php echo $Termin["datum_bis"];?>"></td></tr>
<tr align=center><td colspan=2>
<input type="submit" name="aktion" value="Termin &auml;ndern"> <input type="reset" value="Zur&uuml;cksetzen">
</td></tr>
</table>
</form>
<?php } else { ?>
<table border="0">
<tr><td>Beschreibung</td><td align=center><?php echo htmlspecialchars($Termin["name"]) ?>
<tr><td>Zeitspanne</td><td align=center><nobr>von <?php echo $Termin["datum_von"];?></nobr>
<nobr>bis <?php echo $Termin["datum_bis"];?></td></tr>
</table>
<?php } ?>
</table><br>
<?php 
    if ($aktion=="Termin löschen") { ?>
<<?php echo $dividier ?> width=50%><br>
<form action="<?php echo $PHP_SELF?>">
<input type="hidden" name="id" value="<?php echo $id ?>">
Soll dieser Termin wirklich gelöscht werden?<br>
<nobr><input type="radio" name="wirklich" value="ja"> Ja</nobr>
<nobr><input type="radio" name="wirklich" value="nein"> Nein</nobr><br>
<input type="submit" name="aktion" value="Termin löschen"> <input type="reset" value="Zur&uuml;cksetzen">
</form>
<?php }
    else {?>
<form method="post" action="<?php echo $PHP_SELF ?>">
<input type="hidden" name="terminid" value="<?php echo $id ?>">
<input type="submit" name="aktion" value="Einladungen bearbeiten">
</form>
<?php
    }
  } // Termin vorhanden    
  else {
?>
Der Datensatz wurde leider nicht gefunden.<br>
Beginnen Sie <a href="<?php echo $PHP_SELF?>?aktion=bearbeiten$penne">hier</a> noch einmal!
<?php
  }
  include("ende.php"); // Personen vorhanden (else)
} // Einzelner Datensatz
else {
  echo "Bitte den zu bearbeitende Termin ausw&auml;hlen!\n";

  $sql="select id,name,DATE_FORMAT(datum_von,'%d.%m.%Y %T')as datum_von"
        .",DATE_FORMAT(datum_bis,'%d.%m.%Y %T')as datum_bis from Termine order by datum_von";
  $Termine=mysql_query($sql,$db);?>
<table border=1>
<tr align=left><th>id</th><th></th><th>von</th><th>bis</th><th>Beschreibung</th><th>gesamt</th><th>eingeladen</th><th>best&auml;tigt</th><th>angenommen</th></tr>
<?php 
  while ($Termin=@mysql_fetch_array($Termine)) {
    $terminid=$Termin["id"];
    $sql="select count(*) as anzahl from Einladung "
        ."where Einladung.termin=$terminid";
    $Einladungen=mysql_query($sql,$db);
    if (!($Einladung=@mysql_fetch_array($Einladungen))) $Einladung["anzahl"]=0;?>
<tr><td><?=$terminid?></td><td><form method="get" action="<?php echo $PHP_SELF;?>">
<input type="hidden" name="id" value="<?php echo $terminid;?>">
<input type="submit" name="aktion" value="Termin bearbeiten"><br>
<input type="submit" name="aktion" value="Termin l&ouml;schen"></form>
</td><td><?php echo $Termin["datum_von"];?></td><td><?php echo $Termin["datum_bis"];?></td><td><?php echo $Termin["name"];?></td><td><?php printf("%d", $Einladung["anzahl"]);?></td>
<?php
    $sql="select count(*) as anzahl from Einladung "
        ."where Einladung.termin=$terminid and eingeladen is not null";
    $Einladungen=mysql_query($sql,$db);
    if (!($Einladung=@mysql_fetch_array($Einladungen))) $Einladung["anzahl"]=0;
    printf("<td>%d</td>",$Einladung["anzahl"]);
    $sql="select count(*) as anzahl from Einladung "
        ."where Einladung.termin=$terminid and antwort is not null";
    $Einladungen=mysql_query($sql,$db);
    if (!($Einladung=@mysql_fetch_array($Einladungen))) $Einladung["anzahl"]=0;
    printf("<td>%d</td>",$Einladung["anzahl"]);
    $sql="select sum(status) as anzahl from Einladung "
        ."where Einladung.termin=$terminid and (status)";
    $Einladungen=mysql_query($sql,$db);
    if (!($Einladung=@mysql_fetch_array($Einladungen))) $Einladung["anzahl"]=0;
    printf("<td>%d</td></tr>\n",$Einladung["anzahl"]);
  } // Termine vorhanden
?>
</table>
<H3>Termin hinzuf&uuml;gen</H3>
<table border=2>
<tr align=center><td>
<form method="post" action="<?php echo $PHP_SELF ?>">
<?php if (isset($penne)) { ?>
<input type="hidden" name="penne" value="ja">
<?php } ?>
<table border="0">
<tr><td>Beschreibung</td><td align=center><textarea cols=30 rows=5 name="name"></textarea></td></tr>
<tr><td>Zeitspanne</td><td align=center><nobr>von <input type="text" maxlength=22 size=22 name="datum_von"></nobr>
<nobr>bis <input type="text" maxlength=22 size=22 name="datum_bis"></td></tr>
<tr align=center><td colspan=2>
<input type="submit" name="aktion" value="Termin hinzuf&uuml;gen"> <input type="reset" value="Zur&uuml;cksetzen">
</td></tr>
</table>
</form>
</table>
<?php
  include("ende.php");
} // einzelner Termin (else)
?>
