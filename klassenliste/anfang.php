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

*/  $startzeit=ereg_replace("^0.([0-9]*) ([0-9]*)$","\\2.\\1",microtime())*1000.;?>
<html>
<head>
   <META http-equiv="PICS-Label" content='(PICS-1.1 "http://www.icra.org/ratingsv02.html" l gen true for "http://www.schlemmi.f2s.com" r (cz 1 lc 1 nz 1 oz 1 vz 1) "http://www.rsac.org/ratingsv01.html" l gen true for "http://www.schlemmi.f2s.com" r (n 0 s 0 v 0 l 1))'> 
  <title><?php if (isset($penne)) {$penne="&penne=ja"; ?>ehemalige Sch&uuml;ler
<?php } else {?>Klassenlisten von St. Augustin<?php }?></title>
<?php if (isset($penne)) {?>
<link rel=stylesheet type="text/css" href="http://www.uni-leipzig.de/~stag/css/standard.css">
<script language="JavaScript">
var br = 0;if(navigator.appVersion.substring(0,1) >= "4" && self.location != top.location){br = 1;}
</script>
<?php $dividier="img src=\"http://www.uni-leipzig.de/~stag/graphics/dividier.gif\" border=\"0\" alt=\"\" height=\"2\" align=\"center\"";} else $dividier='hr'; ?>
<?php if ($target) echo "   <base target=\"$target\">\n";?>
</head>
<?php if (isset($penne)) {?>
<body text="#000000" bgcolor="#FFFFF0" link="#0000AD" alink="#AD0000" vlink="#0000AD" onLoad="window.defaultStatus='ehemalige Sch&uuml;ler'; return true">
<?php } else {?>
<body background="../sonstbild/gewebe3.gif" bgcolor=#440055 text=#FFFF88 link=#D3EEFF alink=#FFFFFF vlink=#DDDD00>
<?php } ?>
<center>
<?php if (!($aktion=="menue")) echo "<H1>Klassenlisten von St. Augustin</H1>";?>
