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

unset($mysql_daten);
require_once('config.inc');
require_once('init.inc');
require_once('mysqldb.inc');
require_once('dbtabelle.inc');
require_once('jahrgang.inc');
require_once('personen.inc');
require_once('adressen.inc');
require_once('telefon.inc');
require_once('hp.inc');
require_once('email.inc');

require_once('anzeige.inc');
require_once('login.inc');
require_once('bearbeiten.inc');

echo $layoutid;
unset($layout);
if (file_exists("layout" . $_SESSION['layoutid'] . ".inc")) 
     include("layout" . $_SESSION['layoutid'] . ".inc");
else {
  echo "default";
  $layoutid="";
  include("layout.inc");
}
?>