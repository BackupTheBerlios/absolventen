<?php /* $Id: main.inc,v 1.1 2004/07/15 11:56:40 keinstein Exp $
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

$Log: main.inc,v $
Revision 1.1  2004/07/15 11:56:40  keinstein
Hauptprogramm. Skript ruft das ganze dan wie ein Modul auf


*/ 

/* Grundlegendes Setup */
$startzeit=ereg_replace("^0.([0-9]*) ([0-9]*)$","\\2.\\1",microtime())*1000.;

/* Sitzung starten? */
if (empty($sessionstartfalse))
     session_start();

/* Module laden */
require_once('includes.inc');


if (!isset($db)) {
  $db=new mysqldb;
  $db->connect($mysql_daten['Rechner'],$mysql_daten['Nutzer'],
	       $mysql_daten['Passwort']);
  $db->selectdb($mysql_daten['DB']);
}

if (!empty($_SESSION['mod_absolventen']['uid'])) {
  $person=new personen($db);
  if (!$person->diese($_SESSION['mod_absolventen']['uid'])) {
    logout($db);
  }
  unset($person);
} 

if (!$aktion || (empty($_SESSION['mod_absolventen']['uid']) && 
		 (!in_array($aktion,array('jgauswahl',
					  'jganzeige',
					  'login',
					  'dologin',
					  'email',
					  'hinzufuegen',
					  'persdbneu'
					  ))))){
  $aktion="jgauswahl";
}


switch($aktion) {
 case 'logout': logout($db); break;
 case 'dologin':   tue_login(mystripslashes($HTTP_POST_VARS),$db);
   break;
}

seitenanfang();
switch ($aktion) {
 case 'jganzeige': 
   if (ereg('^[0-9]*$',$HTTP_GET_VARS['jahrgang'])) 
     {
       anzeige_jg($HTTP_GET_VARS['jahrgang'],$db);
       break;
     } 
 case 'logout':  
 case 'jgauswahl': 
   select_jgs($db);
   break;
   
 case 'login':     anzeige_login();
   break;
   
 case 'dologin':   if (!isset($_SESSION['mod_absolventen']['uid'])) {
   anzeige_login(mystripslashes($HTTP_POST_VARS)); 
   unset($_SESSION['mod_absolventen']['name']);
   break;
 }
 case 'bearbmenu': bearb_menu($db);
   break;
   
 case 'hinzufuegen': personen::formular(true);
   break;
   
 case 'persformaendern': persdatenform($db);
   break;
 case 'persdbneu': persdatenaendern($db,mystripslashes($HTTP_POST_VARS),true);
   break;
 case 'persdbaendern': persdatenaendern($db,mystripslashes($HTTP_POST_VARS),false);
   break;
 case 'austragen': austragen($db, mystripslashes($HTTP_POST_VARS));
   break;
   
 case 'jgform':      untertabdatenform(new jg($db));
   break;
 case 'jgdbneu': untertabdatenaendern(new jg($db),mystripslashes($HTTP_POST_VARS),true);
   break;
 case 'jgdbaendern': untertabdatenaendern(new jg($db),mystripslashes($HTTP_POST_VARS),false);
   break;
 case 'jgdbloeschen': untertabdatenloeschen(new jg($db),
					    mystripslashes($HTTP_POST_VARS));
   break;
   
   
 case 'adrform':      untertabdatenform(new adresse($db));
   break;
 case 'adrdbneu': untertabdatenaendern(new adresse($db),mystripslashes($HTTP_POST_VARS),true);
   break;
 case 'adrdbaendern': untertabdatenaendern(new adresse($db),mystripslashes($HTTP_POST_VARS),false);
   break;
 case 'adrdbloeschen': untertabdatenloeschen(new adresse($db),
					     mystripslashes($HTTP_POST_VARS));
   break;
   
 case 'mailform':     untertabdatenform(new email($db));
   break;
 case 'maildbneu': untertabdatenaendern(new email($db),mystripslashes($HTTP_POST_VARS),true);
   break;
 case 'maildbaendern': untertabdatenaendern(new email($db),mystripslashes($HTTP_POST_VARS),false);
   break;
 case 'maildbloeschen': untertabdatenloeschen(new email($db),
					      mystripslashes($HTTP_POST_VARS));
   break;
   
 case 'hpform':       untertabdatenform(new homepage($db));
   break;
 case 'hpdbneu': untertabdatenaendern(new homepage($db),mystripslashes($HTTP_POST_VARS),true);
   break;
 case 'hpdbaendern': untertabdatenaendern(new homepage($db),mystripslashes($HTTP_POST_VARS),false);
   break;
 case 'hpdbloeschen': untertabdatenloeschen(new homepage($db),
					    mystripslashes($HTTP_POST_VARS));
   break;
   
 case 'telform':      untertabdatenform(new telefon($db));
   break;
 case 'teldbneu': untertabdatenaendern(new telefon($db),mystripslashes($HTTP_POST_VARS),true);
   break;
 case 'teldbaendern': untertabdatenaendern(new telefon($db),mystripslashes($HTTP_POST_VARS),false);
   break;
 case 'teldbloeschen': untertabdatenloeschen(new telefon($db),
					     mystripslashes($HTTP_POST_VARS));
   break;
   
 case 'email' : mailsenden($db,$HTTP_POST_VARS);
   break;
	    
   
}
seitenende();

ob_end_flush()
?>