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
  $sql="select id,uid,adresse from StAgMail order by id";
  $erg=mysql_query($sql,$db);
  header("Content-Type: application/StAg-klassenliste-dump; charset=iso-8859-1");
#  header("Content-Type: text/plain; charset=iso-8859-1");
  while ($satz=@mysql_fetch_array($erg)){
    printf("%d\t%d\t%s\n",
      $satz["id"],$satz["uid"],
      $satz["adresse"]?"'".$satz["adresse"]."'":"NULL");
#      $satz["name"]?"'".$satz["name"]."'":"NULL");
  }
} else { 
  include("anfang.php");
  include("pwabfrage.php");
  include("ende.php");
}?>
     
