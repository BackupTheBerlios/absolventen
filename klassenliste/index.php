<?php /* $Id: index.php,v 1.7 2004/07/19 22:14:16 keinstein Exp $
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

$Log: index.php,v $
Revision 1.7  2004/07/19 22:14:16  keinstein
globale Variablen php_self, get und post initialisieren

Revision 1.6  2004/07/14 23:58:15  keinstein
Minimale Aufrufmöglichkeit des Skriptes (standalone)


*/ 

/* Referenz auf Formular-Variablen setzen */
/* Falls die Variablen künstlich verändert werden sollen: "&" weglassen */

$GLOBALS['mod_absolventen_glob']['php_self']=$_SERVER['PHP_SELF'];

$GLOBALS['mod_absolventen_glob']['get']=&$_GET;
$GLOBALS['mod_absolventen_glob']['post']=&$_POST;

chdir('includes');
require('main.inc');

?>
