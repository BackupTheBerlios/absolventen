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

*/ ?><?
function  db_abfrage($sql) {// Funktion mit Rückgabewert
   global $db;
   $result = mysql_query($sql,$db);
   return $result;
}

function  db_verbindung($host = "localhost", $user="www142", $pass="3jun78") {
   echo "${user}:${pass}@$host <br>";
// Funktion mit default-Parametern
   $db = mysql_connect($host, $username, $password);
   echo gettype($db);
   return $db;
}


?>