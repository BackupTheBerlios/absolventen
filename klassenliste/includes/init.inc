<?php /* $Id: init.inc,v 1.3 2004/07/19 22:29:51 keinstein Exp $
Copyright (c) 2000-2004 SchlemmerSoft (Tobias Schlemmer)

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

$Log: init.inc,v $
Revision 1.3  2004/07/19 22:29:51  keinstein
globale Variablen nach $GLOBALS
mb_conver_variables verwendet glob. Var. zeichensätze

Revision 1.2  2004/07/15 11:43:14  keinstein
Rekodierung mit mb_*
eigene ob-Callback-Funktion
$_SESSION umbenannt
$GLOBALS['mod_absolventen_glob']['version'] gesetzt


*/ 

function ob_absolventen_handler($buffer, $status=0) {
  if (!eregi('UTF-8',$_SESSION['mod_absolventen']['zeichensatz'])) {
    $convmap=array(0x0100,0xffff,0,0xffff);
    return mb_output_handler(mb_encode_numericentity($buffer,$convmap,"UTF-8"),$status);
  } else return mb_output_handler($buffer, $status);
}


if (!empty($iconvnutzung)) {

  iconv_set_encoding("internal_encoding","utf-8");

  if (eregi("utf-8",$_SERVER['HTTP_ACCEPT_CHARSET'])) {
    iconv_set_encoding("input_encoding","utf-8");  
  } else {
    iconv_set_encoding("input_encoding","iso-8859-1");
  }

  if (isset($_SESSION['mod_absolventen']['zeichensatz'])) {
    iconv_set_encoding("input_encoding",$_SESSION['mod_absolventen']['zeichensatz']);
  } else {
    $_SESSION['mod_absolventen']['zeichensatz']=iconv_get_encoding('input_encoding');
  }
  iconv_set_encoding("output_encoding",$_SESSION['mod_absolventen']['zeichensatz']);

  ob_start("ob_iconv_handler");
} else {
  if (empty($_SESSION['mod_absolventen']['zeichensatz'])) 
  {
    if (eregi("utf-8",$_SERVER['HTTP_ACCEPT_CHARSET'])) {
      $_SESSION['mod_absolventen']['zeichensatz']="UTF-8";
    } else {
      $_SESSION['mod_absolventen']['zeichensatz']="ISO-8859-1";
    }
  }

  mb_http_output($_SESSION['mod_absolventen']['zeichensatz']);
  mb_internal_encoding("UTF-8");
  mb_convert_variables("UTF-8",
		       implode(",",$GLOBALS['mod_absolventen_glob']['zeichensätze']),
		       $GLOBALS['mod_absolventen_glob']['post'],
		       $GLOBALS['mod_absolventen_glob']['get']);
  ob_start("ob_absolventen_handler" /* "mb_output_handler" */);
}

if (isset($GLOBALS['mod_absolventen_glob']['post']['layout']))
   $_SESSION['mod_absolventen']['layoutid']=$GLOBALS['mod_absolventen_glob']['post']['layout'];
if (isset($GLOBALS['mod_absolventen_glob']['get']['layout'])) 
   $_SESSION['mod_absolventen']['layoutid']=$GLOBALS['mod_absolventen_glob']['get']['layout'];
if (!(isset($_SESSION['mod_absolventen']['layoutid']) && 
	    ereg('^[0-9a-zA-Z_]*$',$_SESSION['mod_absolventen']['layoutid']))) 
    $_SESSION['mod_absolventen']['layoutid']="";

if (isset($GLOBALS['mod_absolventen_glob']['post']['aktion'])) $aktion=$GLOBALS['mod_absolventen_glob']['post']['aktion'];
else $aktion=isset($GLOBALS['mod_absolventen_glob']['get']['aktion'])?$GLOBALS['mod_absolventen_glob']['get']['aktion']:"";

$GLOBALS['mod_absolventen_glob']['version']="1.1 (Status: beta)";


?>
