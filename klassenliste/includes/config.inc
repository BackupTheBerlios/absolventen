<?php /* $Id: config.inc,v 1.6 2004/07/19 22:23:46 keinstein Exp $
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
Revision 1.6  2004/07/19 22:23:46  keinstein
globale Variablen nach $GLOBALS
BB-Code geschrieben

Revision 1.5  2004/07/15 11:31:23  keinstein
Allgemein: global für globale Variablen

*/ 


/* Zeichensätze 

diese werden in exakt dieser Reihenfolge überprüft. */
$GLOBALS['mod_absolventen_glob']['zeichensätze']=array("UTF-8","ISO-8859-15", "ISO-8859-1", "ISO-8859-2");

/* Bereiche */

$GLOBALS['mod_absolventen_glob']['jahrgang']['von']=1550;
$GLOBALS['mod_absolventen_glob']['jahrgang']['bis']=date("Y")+5;

/* Klassen */

$GLOBALS['mod_absolventen_glob']['klasse']=array('Kurssystem' => '',
	      'A-Zug'      => 'A-Zug',
	      'B-Zug'      => 'B-Zug',
	      'B1-Zug'     => 'B1-Zug',
	      'B2-Zug'     => 'B2-Zug',
	      'B3-Zug'     => 'B3-Zug',
	      'C-Zug'      => 'C-Zug',
	      'S-Zug'      => 'S-Zug');

/* MySQL */

$GLOBALS['mod_absolventen_glob']['mysql']=array('Nutzer'   => 'www',
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

/* Includepath für PEAR */


//ini_set('include_path', ini_get('include_path') . ':/usr/share/pear');

require_once("PEAR.php");
require_once("HTML/BBCodeParser.php");

class kommentar_code_class {
  var $parser= NULL;   
  var $tagsmatch=array('!<img (src="([^"]*)" |width="([^"]*)" |height="([^"]*)" )*/>!e');
  var $tagsreplace=array('"[img".("\\3"?" w=\\3":"").("\\4"?" h=\\4":"")."]".str_replace("&","&amp;","\\2") . "[/img]"');
  var $tagscheckmatch=array('!<img (src="([^"]*)" |width="([^"]*)" |height="([^"]*)" )*/>!e');
  var $tagscheckreplace=array('$this->image_check("\\2","\\3","\\4")');
  var $fehler="";

  function kommentar_code_class() {
    $this->parser=new HTML_BBCodeParser(array ( 'filters' => 'Images', 
						'quotestyle' => 'double',
						'quotewhat' => 'all',
						'open' => '[',
						'close' => ']',
						'xmlclose' => true
						));
  }

  // Erlaubt ein paar zusätzliche Attribute im Text
  function parse($kommentar) {
    $kommentar=$this->parser->qparse($kommentar);
    return preg_replace($this->tagscheckmatch,$this->tagscheckreplace,$kommentar);
  }

  function backparse($kommentar) {
    return preg_replace($this->tagsmatch,$this->tagsreplace,$kommentar);
  }

  function image_check($url,$breite,$hoehe) {
    $url=str_replace("&amp;","&",trim($url));
    if (!preg_match('!^http://!',$url) || (!$fd=@fopen($url,"rb"))) {
      $this->fehler = "Die Adresse des Bildes ".str_replace("&","&amp;",$url). " ist ungültig.";
      return "[img".($breite?" w=".$breite:"").($hoehe?" h=".$hoehe:"")."]".str_replace("&","&amp;",$url)."[/img]";
    }
    
    $maxlen=10241;
    $bild="";
    do {
      $daten = fread($fd,$maxlen);
      $maxlen -= strlen($daten);
      $bild .= $daten;
    } while ($maxlen>0 && !feof($fd));
    
    if (!feof($fd)) {
      fclose($fd);
      $this->fehler = "Das Bild $url ist zu groß. Es sind nur Bilder bis zu 10kB erlaubt.";
      return "[img".($breite?" w=".$breite:"").($hoehe?" h=".$hoehe:"")."]".str_replace("&","&amp;",$url)."[/img]";
    }
    fclose($fd);

    // wenn gd geladen ist 
    $gdload=1;
    if (!extension_loaded('gd')) {
      if (!@dl('gd.so')) {
        $gdload=0;
      }
    }
    if ($gdload) {
      $bildres=imagecreatefromstring($bild);
      $orighoehe=imagesy($bildres);
      $origbreite=imagesx($bildres);
    } else {
      if (!$size=@getimagesize($url)) {
	$orighoehe=20;
	$origbreite=20;
      } else {
	$orighoehe=$size[1];
	$origbreite=$size[0];
	unset($size);
      }
    }

    if (!$breite) {
      if ($hoehe) $breite=($origbreite*$hoehe+($orighoehe/2))/$orighoehe;
      else {
	$breite=$origbreite;
	$hoehe=$orighoehe;
      }
    }
    if (!$hoehe) $hoehe=($orighoehe*$breite+($origbreite/2))/$origbreite;

    $endbreite=$hoehe;
    $endhoehe=$breite;
    $scale=1.0;

    if ($breite > 200) {
      $scale=(200.00 /$breite);
      $endbreite=200;
      $endhoehe=$hoehe*$scale;
    }
    if ($hoehe > 200.00/$scale) {
      $scale=(200.00 /$hoehe);
      $endbreite=$breite*$scale;
      $endhoehe=200;
    }
    return sprintf('<img src="%s" width="%d" height="%d" />',$url,$endbreite,$endhoehe);
  }
  
  function getfehler(){
    return $this->fehler;
  }

}

?>
