<?php
function  Fehlermeldung($error) {
   echo "Schade! Leider ist ein Fehler aufgetreten.\n<p>";
   echo "Uns wurde folgendes gemeldet:\n<br>$error.\n<p>";?>
Das Beste w&auml;re, Sie setzen sich mit dem Seitenbetreuer
unter der Email <a href="mailto:T.Schlemmer@mathe.tu-freiberg.de">T.Schlemmer@mathe.tu-freiberg.de</a>
in Verbindung.
<?php
   include('ende.php');
   die;

}
?>
