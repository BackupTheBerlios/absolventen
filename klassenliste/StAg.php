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

*/ 
if ($passwort){
  $db=mysql_connect("localhost","www142",$passwort);
  mysql_select_db($mysql_daten['DB'],$db);

  $sql="select id,aktueller_name,geburtsname,vorname,kommentar,pw,aktualisierung from StAg order by id";
  $erg=mysql_query($sql,$db);
  header("Content-Type: application/StAg-klassenliste-dump; charset=iso-8859-1");
  while ($satz=@mysql_fetch_array($erg)){
    printf("insert into StAg values (%d,'%s','%s','%s',%s,%s,%s);\n",
      $satz["id"],AddSlashes($satz["aktueller_name"]),
      AddSlashes($satz["geburtsname"]),AddSlashes($satz["vorname"]),
      $satz["kommentar"]?"'".AddSlashes($satz["kommentar"])."'":"NULL",
      $satz["pw"]?"'".AddSlashes($satz["pw"])."'":"NULL",AddSlashes($satz["aktualisierung"]));
  }

  $sql="select id,uid,anfang,plz,ort,ende,vorwahl,telefon from StAgAdr order by id";
  $erg=mysql_query($sql,$db);
  while ($satz=@mysql_fetch_array($erg)){
    printf("insert into StAgAdr values (%d,%d,%s,'%s','%s',%s,%s,%s);\n",
      $satz["id"],$satz["uid"],
      $satz["anfang"]?"'".AddSlashes($satz["anfang"])."'":"NULL",
      AddSlashes($satz["plz"]),AddSlashes($satz["ort"]),
      $satz["ende"]?"'".AddSlashes($satz["ende"])."'":"NULL",
      $satz["vorwahl"]?"'".AddSlashes($satz["vorwahl"])."'":"NULL",
      $satz["telefon"]?"'".AddSlashes($satz["aktualisierung"])."'":"NULL");
  }
 
  $sql="select id,uid,adresse,name from StAgHP order by id";
  $erg=mysql_query($sql,$db);
  while ($satz=@mysql_fetch_array($erg)){
    printf("insert into StAgHP values (%d,%d,%s,%s);\n",
      $satz["id"],$satz["uid"],
      $satz["adresse"]?"'".AddSlashes($satz["adresse"])."'":"NULL",
      $satz["name"]?"'".AddSlashes($satz["name"])."'":"NULL");
  }
 
  $sql="select id,uid,jahrgang, klasse,drin from StAgJg order by id";
  $erg=mysql_query($sql,$db);
  while ($satz=@mysql_fetch_array($erg)){
    printf("insert into StAgJg values (%d,%d,%d,'%s',%d);\n",
      $satz["id"],$satz["uid"],$satz["jahrgang"],$satz["klasse"],$satz["drin"]);
  }
 
  $sql="select id,uid,adresse from StAgMail order by id";
  $erg=mysql_query($sql,$db);
  while ($satz=@mysql_fetch_array($erg)){
    printf("insert into StAgMail values (%d,%d,%s);\n",
      $satz["id"],$satz["uid"],
      $satz["adresse"]?"'".AddSlashes($satz["adresse"])."'":"NULL");
  }
 
  $sql="select id,uid,vorwahl,telefon from StAgTel order by id";
  $erg=mysql_query($sql,$db);
  while ($satz=@mysql_fetch_array($erg)){
    printf("insert into StAgTel values (%d,%d,%s,%s);\n",
      $satz["id"],$satz["uid"],
      $satz["vorwahl"]?"'".AddSlashes($satz["vorwahl"])."'":"NULL",
      $satz["telefon"]?"'".AddSlashes($satz["aktualisierung"])."'":"NULL");
  }
} else { 
  include("anfang.php");
  include("pwabfrage.php");
  include("ende.php");
}?>
     