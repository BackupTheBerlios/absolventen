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

switch ($aktion) {
 case 'jganzeige': if (ereg('^[0-9]*$',$HTTP_GET_VARS['jahrgang'])) {
                      seitenanfang();
		      anzeige_jg($HTTP_GET_VARS['jahrgang'],$db);
		      seitenende();
                   } 
                   break;

 case 'logout':    session_destroy();
		   unset($_SESSION['uid']);
		   unset($_SESSION['name']);
		   session_start();
 case 'jgauswahl': seitenanfang();
                   select_jgs($db);
		   seitenende();
		   break;

 case 'login':     seitenanfang();
                   anzeige_login();
		   seitenende();
		   break;

 case 'dologin':   seitenanfang();
                   tue_login(mystripslashes($HTTP_POST_VARS),$db);
		   seitenende();
		   break;

 case 'bearbmenu': seitenanfang();
                   bearb_menu($db);
		   seitenende();
		   break;

 case 'hinzufuegen': seitenanfang();
                     personen::formular();
		     seitenende();
		     break;

 case 'persformaendern': seitenanfang();
                     persdatenform($db);
		     seitenende();
		     break;
 case 'persdbneu':
 case 'persdbaendern': seitenanfang();
                       persdatenaendern($db,mystripslashes($HTTP_POST_VARS));
		       seitenende();
                       break;
		       
 case 'jgform':      seitenanfang();
                     untertabdatenform(new jg($db));
                     seitenende();
                     break;

 
 case 'jgdbneu':		      
 case 'jgdbaendern': seitenanfang();
                     jgdatenaendern($db,mystripslashes($HTTP_POST_VARS));
		     seitenende();
		     break;
 
 case 'jgdbloeschen': seitenanfang();
                      jgdatenloeschen(new jg($db),
				      mystripslashes($HTTP_POST_VARS));
		      seitenende();
		      break;
 
   
 case 'adrform':      seitenanfang();
                      untertabdatenform(new adresse($db));
		      seitenende();
		      break;

 case 'adrdbneu':		      
 case 'adrdbaendern': seitenanfang();
                     adrdatenaendern($db,mystripslashes($HTTP_POST_VARS));
		     seitenende();
		     break;
 
 case 'adrdbloeschen': seitenanfang();
                      untertabdatenloeschen(new adresse($db),
					    mystripslashes($HTTP_POST_VARS));
		      seitenende();
		      break;
 
   
}
	  ?>