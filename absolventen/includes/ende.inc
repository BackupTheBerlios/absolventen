<?php
function ende()
{
  global $aktion;
  global $dividier;
  global $startzeit;
  global $PHP_SELF;

  echo "<p><$dividier";
  if (!($aktion=="menue")) echo '  width="50%"'; else echo ' width="95%"';
          echo "><p>\n";
  echo "<a href=\"$PHP_SELF?aktion=anzeige\">Abfrage</a>\n";
  if ($aktion=="menue") echo "<br>\n";
  echo "<a href=\"$PHP_SELF?aktion=bearbeiten\">Bearbeiten</a>\n";
  if ($aktion=="menue") echo "<br>\n";
  echo "<a href=\"$PHP_SELF?aktion=hinzufuegen\">Hinzuf&uuml;gen</a>\n";
  if ($aktion=="menue") echo "<br>\n";
  echo "<a href=\"$PHP_SELF?aktion=termine\">Termine</a>\n";
  echo "<p><$dividier";
  if (!($aktion=="menue")) echo' width="50%"'; else echo ' width="95%"';
      echo"><p>\n";
  echo "<a href=\"http://www.psynet.net/schlemmi\">";
  if (!($aktion=="menue")) echo "Homepage von ";
  echo "Schlemmi </a>\n";
  if (!($aktion=="menue"))
  {
    echo "<p><$dividier width=\"50%\"><p>\n";
    echo "Alt-ESG-ler Version 1.0<br>\n";
    echo "<address>&copy; 2000 <a href=\"mailto:schlemmi@psynet.net\">SchlemmerSoft (Tobias schlemmer)</a></address>\n";
    printf("<font size=-3>Rechenzeit: %.3f ms</font>",(ereg_replace("^0(.)([0-9]*) ([0-9]*)$","\\3\\1\\2",microtime())-$startzeit)*1000.0);

  } ?>
</center>
</body>
</html>
<?php } ?>
