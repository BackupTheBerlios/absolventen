<?php
/* Grundlegendes Setup */
$startzeit=ereg_replace("^0.([0-9]*) ([0-9]*)$","\\2.\\1",microtime())*1000.;
$version="1.1 (Status: alpha)";
session_start();

chdir('includes');
require_once('includes.inc');

function mystripslashes($daten) {
  while(list($name, $wert) = each($daten))
    $enddaten[$name]=htmlspecialchars(stripslashes($wert));
  return $enddaten;
}

$db=new mysqldb;
$db->connect($mysql_daten['Rechner'],$mysql_daten['Nutzer'],
	     $mysql_daten['Passwort']);
$db->selectdb($mysql_daten['DB']);

if (!$aktion) $aktion="jgauswahl";

switch($aktion) {
 case 'logout': logout($db); break;
 case 'dologin':   tue_login(mystripslashes($HTTP_POST_VARS),$db);
		   break;
}

seitenanfang();
switch ($aktion) {
 case 'jganzeige': if (ereg('^[0-9]*$',$HTTP_GET_VARS['jahrgang'])) {
		      anzeige_jg($HTTP_GET_VARS['jahrgang'],$db);
		      break;
                   } 
 case 'logout':  
 case 'jgauswahl': select_jgs($db);
		   break;

 case 'login':     anzeige_login();
		   break;

 case 'dologin':   if (!isset($_SESSION['uid'])) {
                     anzeige_login(mystripslashes($HTTP_POST_VARS)); 
		     break;
                   }
 case 'bearbmenu': bearb_menu($db);
		   break;

 case 'hinzufuegen': personen::formular();
		     break;

 case 'persformaendern': persdatenform($db);
		         break;
 case 'persdbneu':
 case 'persdbaendern': persdatenaendern($db,mystripslashes($HTTP_POST_VARS));
		       break;
 case 'austragen': austragen($db, mystripslashes($HTTP_POST_VARS));
                   break;
		       
 case 'jgform':      untertabdatenform(new jg($db));
                     break;

 
 case 'jgdbneu':		      
 case 'jgdbaendern': untertabdatenaendern(new jg($db),mystripslashes($HTTP_POST_VARS));
		     break;
 
 case 'jgdbloeschen': untertabdatenloeschen(new jg($db),
				      mystripslashes($HTTP_POST_VARS));
		      break;
 
   
 case 'adrform':      untertabdatenform(new adresse($db));
		      break;

 case 'adrdbneu':		      
 case 'adrdbaendern': untertabdatenaendern(new adresse($db),mystripslashes($HTTP_POST_VARS));
		      break;
 
 case 'adrdbloeschen': untertabdatenloeschen(new adresse($db),
					    mystripslashes($HTTP_POST_VARS));
		       break;
 
 case 'mailform':     untertabdatenform(new email($db));
		      break;

 case 'maildbneu':		      
 case 'maildbaendern': untertabdatenaendern(new email($db),mystripslashes($HTTP_POST_VARS));
		       break;
 
 case 'maildbloeschen': untertabdatenloeschen(new email($db),
					    mystripslashes($HTTP_POST_VARS));
		        break;
 
 case 'hpform':       untertabdatenform(new homepage($db));
		      break;

 case 'hpdbneu':		      
 case 'hpdbaendern': untertabdatenaendern(new homepage($db),mystripslashes($HTTP_POST_VARS));
		     break;
 
 case 'hpdbloeschen': untertabdatenloeschen(new homepage($db),
					    mystripslashes($HTTP_POST_VARS));
		      break;
 case 'telform':      untertabdatenform(new telefon($db));
		      break;

 case 'teldbneu':		      
 case 'teldbaendern': untertabdatenaendern(new telefon($db),mystripslashes($HTTP_POST_VARS));
		      break;
 
 case 'teldbloeschen': untertabdatenloeschen(new telefon($db),
					    mystripslashes($HTTP_POST_VARS));
		       break;
 case 'email' : mailsenden($db,$HTTP_POST_VARS);
   break;

   
}
seitenende();
	  ?>