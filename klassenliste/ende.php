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
  echo "<p><$dividier";
 if (!($aktion=="menue")) echo '  width="50%"'; else echo ' width="95%"';
	  echo "><p>\n";
  echo "<a href=\"$PHP_SELF?aktion=anzeige$penne\">Abfrage</a>\n";
  if ($aktion=="menue") echo "<br>\n";
  echo "<a href=\"$PHP_SELF?aktion=bearbeiten$penne\">Bearbeiten</a>\n";
  if ($aktion=="menue") echo "<br>\n";
  echo "<a href=\"$PHP_SELF?aktion=hinzufuegen$penne\">Hinzuf&uuml;gen</a>\n";
  echo "<p><$dividier";
  if (!($aktion=="menue")) echo' width="50%"'; else echo ' width="95%"';
      echo"><p>\n";
  echo "<a href=\"http://www.uni-leipzig.de/~stag/\">";
  if (isset($penne)){?>
<a href="http://www.uni-leipzig.de/~stag/start.htm" <?php 
#onClick="if(br==1){parent.Navigation.MenuClick(1)}" onmouseover="if(br==1){parent.Navigation.MenuMoveOn(1); window.status='zur Homepage'; return true}" onmouseout="if(br==1){parent.Navigation.MenuMoveOff(1)}
?>"><?php 
if (!($aktion==menue)) echo "zur&uuml;ck zur"; ?> Homepage<?php
   } else {
  if (!($aktion=="menue")) echo "Gymnasium ";
  echo "St. Augustin";
  if (!($aktion=="menue")) echo " zu Grimma";}
  echo "</a>\n<br>\n";
  echo "<a href=\"http://www.psynet.net/schlemmi\">";
  if (!($aktion=="menue")) echo "Homepage von ";
  echo "Schlemmi </a>\n";
  if (!($aktion=="menue")) 
  { 
    echo "<p><$dividier width=\"50%\"><p>\n";
    echo "Klassenliste Version 1.0<br>\n";
    echo "<address>&copy; 2000 <a href=\"mailto:Tobias.Schlemmer@web.de\">SchlemmerSoft (Tobias schlemmer)</a><br>
<font size=-1>Dieses Programm steht unter der <a href=\"http://www.gnu.org/copyleft/gpl.html\">GPL</a></font></address>\n";
    printf("<font size=-3>Rechenzeit: %.3f ms</font>",ereg_replace("^0.([0-9]*) ([0-9]*)$","\\2.\\1",microtime())*1000.-$startzeit);
    if (isset($penne)) { ?>
<!--INC:"reference.inc"--><div align="center"><font size="-2" color="#000000">
<br>Gymnasium St.Augustin zu Grimma - Homepage
<br>www.uni-leipzig.de/~stag
</font></div><!--/INC:"reference.inc"-->
<?php } 
    echo "<p>Besonderer Dank gilt <a href=\"http://www.f2s.com\">Freedom2Surf</a> f&uuml;r die Bereitstellung des WWW-Servers mit MySQL-Datenbank.";
  }
?>
</center>
</body>
</html>
