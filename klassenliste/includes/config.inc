<?php /* $Id: config.inc,v 1.5 2004/07/15 11:31:23 keinstein Exp $
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

$Log: config.inc,v $
Revision 1.5  2004/07/15 11:31:23  keinstein
Allgemein: global für globale Variablen

*/ 


/* Zeichensätze 

diese werden in exakt dieser Reihenfolge überprüft. */
global $zeichensaetze;
$zeichensaetze=array("UTF-8","ISO-8859-15", "ISO-8859-1", "ISO-8859-2");

/* Klassen */
global $klasse;
$klasse=array('Kurssystem' => '',
	      'A-Zug'      => 'A-Zug',
	      'B-Zug'      => 'B-Zug',
	      'B1-Zug'     => 'B1-Zug',
	      'B2-Zug'     => 'B2-Zug',
	      'B3-Zug'     => 'B3-Zug',
	      'C-Zug'      => 'C-Zug',
	      'S-Zug'      => 'S-Zug');

/* MySQL */
global $mysql_daten;
$mysql_daten=array('Nutzer'   => 'www',
		   'Passwort' => '',
		   'Rechner'  => '',
                   'DB'       => 'stag',
                /* Namen der einzelnen Tabellen */
		   'PersTab'  => 'StAg',
                   'AdrTab'   => 'StAgAdr',
                   'TelTab'   => 'StAgTel',
                   'JgTab'    => 'StAgJg',
		   'EmailTab' => 'StAgMail',
		   'HPTab'    => 'StAgHP');

/* Erlaube/setzte einige Tags für Kommentare 
   Format ist für preg_replace, also Perl-Syntax 
   Das Format wird getestet, gespeichert und bei der Anzeige dann 
   formatiert. */

/* Bilder:
   [img src="url://irgend.was/" width="xxx" height="xxx" alt="alternativ"]
*/
global $kommentar_tags_suche;
$kommentar_tags_suche[0]='/[[]img src=&quot;([^] \t\n]*)&quot;[ \t\n]+width=&quot;([0-9]*)&quot;[ \t\n]+height=&quot;([0-9]*)&quot;[ \t\n]alt=&quot;([^]]*)&quot;[]]/e';
global $kommentar_tag_check;
$kommentar_tag_check[0]='check_image($1,$2,$3,$4);';
global $kommentar_tag_ersetze;
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
