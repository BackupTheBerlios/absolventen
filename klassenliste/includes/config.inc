<?php

/* Zeichensätze 

diese werden in exakt dieser Reihenfolge überprüft. */

$zeichensaetze=array("UTF-8","ISO-8859-15", "ISO-8859-1", "ISO-8859-2");

/* Klassen */
$klasse=array('Kurssystem' => '',
	      'A-Zug'      => 'A-Zug',
	      'B-Zug'      => 'B-Zug',
	      'B1-Zug'     => 'B1-Zug',
	      'B2-Zug'     => 'B2-Zug',
	      'B3-Zug'     => 'B3-Zug',
	      'C-Zug'      => 'C-Zug',
	      'S-Zug'      => 'S-Zug');

/* MySQL */
$mysql_daten['Nutzer']='www';
$mysql_daten['Passwort']='web';
$mysql_daten['Rechner']='localhost';
$mysql_daten['DB']='stag';

/* Erlaube/setzte einige Tags für Kommentare 
   Format ist für preg_replace, also Perl-Syntax 
   Das Format wird getestet, gespeichert und bei der Anzeige dann 
   formatiert. */

/* Bilder:
   [img src="url://irgend.was/" width="xxx" height="xxx" alt="alternativ"]
*/
$kommentar_tags_suche[0]='/[[]img src=&quot;([^] \t\n]*)&quot;[ \t\n]+width=&quot;([0-9]*)&quot;[ \t\n]+height=&quot;([0-9]*)&quot;[ \t\n]alt=&quot;([^]]*)&quot;[]]/e';
$kommentar_tag_check[0]='check_image($1,$2,$3,$4);';
$kommentar_tag_ersetze[0]='<img src="$1" width="$2" height="$3" alt="$4" />';

/* Funktionen für Bilder */
function check_image($url,$breite,$hoehe,$alt){
 
  /* hier sollte noch eine Größenbeschränkung rein */
  
  if ($breite > 200 && $hoehe<$breite) {
    $hoehe=($hoehe*200)/$breite;
    $breite=200;
  }

  if ($hoehe > 200) {
    $breite=($breite*200)/$hoehe;
    $hoehe=200;
  }

  return sprintf('[img src="%s" width="%d" height="%d" alt="%s"]',
		 $url,$breite,$hoehe,$alt); 
}

?>