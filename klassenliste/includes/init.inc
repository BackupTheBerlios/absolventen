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

iconv_set_encoding("internal_encoding","utf-8");

if (eregi("utf-8",$_SERVER['HTTP_ACCEPT_CHARSET'])) {
  iconv_set_encoding("input_encoding","utf-8");  
} else {
  iconv_set_encoding("input_encoding","iso-8859-1");
}

if ($_SESSION['zeichensatz']) {
  iconv_set_encoding("input_encoding",$_SESSION['zeichensatz']);
} else {
  $_SESSION['zeichensatz']=iconv_get_encoding('input_encoding');
}
iconv_set_encoding("output_encoding",$_SESSION['zeichensatz']);

ob_start("ob_iconv_handler");



if (isset($HTTP_POST_VARS['layout']))
   $_SESSION['layoutid']=$HTTP_POST_VARS['layout'];
if (isset($HTTP_GET_VARS['layout'])) 
   $_SESSION['layoutid']=$HTTP_GET_VARS['layout'];
if (!ereg('^[0-9a-zA-Z_]*$',$_SESSION['layoutid'])) $_SESSION['layoutid']="";

if ($HTTP_POST_VARS['aktion']) $aktion=$HTTP_POST_VARS['aktion'];
else $aktion=$HTTP_GET_VARS['aktion'];

?>