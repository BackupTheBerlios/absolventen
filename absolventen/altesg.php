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
      case 'L�schen': include('loeschen.php'); break;
      case '�ndern':include('aendern.php');break;
      case 'Adresse hinzuf�gen':
      case 'Adresse l�schen':
      case 'Adresse �ndern':include('adraendern.php');break;
      case 'Telefonnummer hinzuf�gen':
      case 'Telefonnummer l�schen':
      case 'Telefonnummer �ndern':include('telaendern.php');break;
      case 'Email hinzuf�gen':
      case 'Email l�schen':
      case 'Email �ndern':include('mailaendern.php');break;
      case 'WWW-Adresse hinzuf�gen':
      case 'WWW-Adresse l�schen':
      case 'WWW-Adresse �ndern':include('hpaendern.php');break;
      case 'Hinzuf�gen':
      case 'hinzufuegen':include('hinzufuegen.php');break;
      case 'Termin bearbeiten':
      case 'termine': include('termine.php');break;
      case 'Termin hinzuf�gen':
      case 'Termin l�schen':
      case 'Termin �ndern':include('tbearbeiten.php');break;
      case 'pers�nliche Termine':Personentermine_bearbeiten();break;
      case 'Einladungen bearbeiten':include('einladungen.php');break;
      case 'Einladungen �ndern':include('ebearbeiten.php');break;
      default: include('index.html');
}
?>
