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


function  Fehlermeldung($error) {
   echo "Schade! Leider ist ein Fehler aufgetreten.\n<p>";
   echo "Uns wurde folgendes gemeldet:\n<br>$error.\n<p>";?>
Das beste w~e, Sie setzen sich mit dem Seitenbetreuer
unter der Email <a href="mailto:schlemmi@psynet.net">schlemmi@psynet.net</a>
in Verbindung.
<?php
   include('ende.php');
   die;

}

$mysql_daten['Nutzer']='www';
$mysql_daten['Passwort']='web';
$mysql_daten['Rechner']='localhost';
$mysql_daten['DB']='stag';

switch ($aktion) {
      case 'Abbrechen':unset($id);unset($wirklich);
      case '':
      case 'menue':
      case 'anzeige': include('anzeige.php');break;
      case 'Löschen': include('loeschen.php');break;
      case 'Bearbeiten':
      case 'bearbeiten': include('bearbeiten.php');break;
      case 'Ändern':include('aendern.php');break;
      case 'Jahrgang hinzufügen':
      case 'Jahrgang löschen':
      case 'Jahrgang ändern':include('jgaendern.php');break;
      case 'Adresse hinzufügen':
      case 'Adresse löschen':
      case 'Adresse ändern':include('adraendern.php');break;
      case 'Telefonnummer hinzufügen':
      case 'Telefonnummer löschen':
      case 'Telefonnummer ändern':include('telaendern.php');break;
      case 'Email hinzufügen':
      case 'Email löschen':
      case 'Email ändern':include('mailaendern.php');break;
      case 'WWW-Adresse hinzufügen':
      case 'WWW-Adresse löschen':
      case 'WWW-Adresse ändern':include('hpaendern.php');break;
      case 'Hinzufügen':
      case 'hinzufuegen':include('hinzufuegen.php');break;
      default: include('index.html');
}
?>
