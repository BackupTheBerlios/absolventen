<?php

require('requires.inc');

if (!$PHP_AUTH_USER || !$PHP_AUTH_PW) authenticate();

//echo $aktion . "\n";

switch ($aktion) {
      case 'Abbrechen':unset($id);unset($wirklich);
      case '':
      case 'menue':
      case 'anzeige':
      case 'Bearbeiten':
      case 'bearbeiten': include('bearbeiten.php');break;
      case 'Löschen': include('loeschen.php'); break;
      case 'Ändern':include('aendern.php');break;
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
      case 'Termin bearbeiten':
      case 'termine': include('termine.php');break;
      case 'Termin hinzufügen':
      case 'Termin löschen':
      case 'Termin ändern':include('tbearbeiten.php');break;
      case 'persönliche Termine':Personentermine_bearbeiten();break;
      case 'Einladungen bearbeiten':include('einladungen.php');break;
      case 'Einladungen ändern':include('ebearbeiten.php');break;
      default: include('index.html');
}
?>
