<?php
  function  authenticate()  {
    Header( "WWW-authenticate: Basic realm=\"Authentifikation.\"");
    Header( "HTTP/1.0  401  Unauthorized");
    include('anfang.php');
    echo  "<font size=7 color=red><blink>Zugriff verweigert.</blink></font>\n";
    include('ende.php');
    exit;
  }

?>
