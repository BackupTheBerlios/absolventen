<?php /* $Id: mystripslashes.inc,v 1.2 2004/07/19 22:38:44 keinstein Exp $
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

$Log: mystripslashes.inc,v $
Revision 1.2  2004/07/19 22:38:44  keinstein
Kodierung von HTML-eigenen Zeichen im Extra-Schritt
damit kein einzelnes & übrigbleibt
Frage: haben wir jetzt alle HTML-Entitäten?

Revision 1.1  2004/07/15 11:57:49  keinstein
Funktion zum dekodieren der HTTP_POST/HTTP_GET-Eingaben.

*/ 


function mystripslashes($daten) {
  $conversion_table=Array( 
			  // und nun die anderen Zeichen "normalisieren"
			  '&nbsp;' => ' ',
			  '&iexcl;' => '¡',
			  '&cent;' => '¢',
			  '&pound;' => '£',
			  '&curren;' => '¤',
			  '&yen;' => '¥',
			  '&brvbar;' => '¦',
			  '&sect;' => '§',
			  '&uml;' => '¨',
			  '&copy;' => '©',
			  '&ordf;' => 'ª',
			  '&laquo;' => '«',
			  '&not;' => '¬',
			  '&shy;' => '­',
			  '&reg;' => '®',
			  '&macr;' => '¯',
			  '&deg;' => '°',
			  '&plusmn;' => '±',
			  '&sup2;' => '²',
			  '&sup3;' => '³',
			  '&acute;' => '´',
			  '&micro;' => 'µ',
			  '&para;' => '¶',
			  '&middot;' => '·',
			  '&cedil;' => '¸',
			  '&sup1;' => '¹',
			  '&ordm;' => 'º',
			  '&raquo;' => '»',
			  '&frac14;' => '¼',
			  '&frac12;' => '½',
			  '&frac34;' => '¾',
			  '&iquest;' => '¿',
			  '&Agrave;' => 'À',
			  '&Aacute;' => 'Á',
			  '&Acirc;' => 'Â',
			  '&Atilde;' => 'Ã',
			  '&Auml;' => 'Ä',
			  '&Aring;' => 'Å',
			  '&AElig;' => 'Æ',
			  '&Ccedil;' => 'Ç',
			  '&Egrave;' => 'È',
			  '&Eacute;' => 'É',
			  '&Ecirc;' => 'Ê',
			  '&Euml;' => 'Ë',
			  '&Igrave;' => 'Ì',
			  '&Iacute;' => 'Í',
			  '&Icirc;' => 'Î',
			  '&Iuml;' => 'Ï',
			  '&ETH;' => 'Ð',
			  '&Ntilde;' => 'Ñ',
			  '&Ograve;' => 'Ò',
			  '&Oacute;' => 'Ó',
			  '&Ocirc;' => 'Ô',
			  '&Otilde;' => 'Õ',
			  '&Ouml;' => 'Ö',
			  '&times;' => '×',
			  '&Oslash;' => 'Ø',
			  '&Ugrave;' => 'Ù',
			  '&Uacute;' => 'Ú',
			  '&Ucirc;' => 'Û',
			  '&Uuml;' => 'Ü',
			  '&Yacute;' => 'Ý',
			  '&THORN;' => 'Þ',
			  '&szlig;' => 'ß',
			  '&agrave;' => 'à',
			  '&aacute;' => 'á',
			  '&acirc;' => 'â',
			  '&atilde;' => 'ã',
			  '&auml;' => 'ä',
			  '&aring;' => 'å',
			  '&aelig;' => 'æ',
			  '&ccedil;' => 'ç',
			  '&egrave;' => 'è',
			  '&eacute;' => 'é',
			  '&ecirc;' => 'ê',
			  '&euml;' => 'ë',
			  '&igrave;' => 'ì',
			  '&iacute;' => 'í',
			  '&icirc;' => 'î',
			  '&iuml;' => 'ï',
			  '&eth;' => 'ð',
			  '&ntilde;' => 'ñ',
			  '&ograve;' => 'ò',
			  '&oacute;' => 'ó',
			  '&ocirc;' => 'ô',
			  '&otilde;' => 'õ',
			  '&ouml;' => 'ö',
			  '&divide;' => '÷',
			  '&oslash;' => 'ø',
			  '&ugrave;' => 'ù',
			  '&uacute;' => 'ú',
			  '&ucirc;' => 'û',
			  '&uuml;' => 'ü',
			  '&yacute;' => 'ý',
			  '&thorn;' => 'þ',
			  '&yuml;' => 'ÿ',
			  '&Alpha;' => 'Α',
			  '&alpha;' => 'α',
			  '&Beta;' => 'Β',
			  '&beta;' => 'β',
			  '&Gamma;' => 'Γ',
			  '&gamma;' => 'γ',
			  '&Delta;' => 'Δ',
			  '&delta;' => 'δ',
			  '&Epsilon;' => 'Ε',
			  '&epsilon;' => 'ε',
			  '&Zeta;' => 'Ζ',
			  '&zeta;' => 'ζ',
			  '&Eta;' => 'Η',
			  '&eta;' => 'η',
			  '&Theta;' => 'Θ',
			  '&theta;' => 'θ',
			  '&Iota;' => 'Ι',
			  '&iota;' => 'ι',
			  '&Kappa;' => 'Κ',
			  '&kappa;' => 'κ',
			  '&Lambda;' => 'Λ',
			  '&lambda;' => 'λ',
			  '&Mu;' => 'Μ',
			  '&mu;' => 'μ',
			  '&Nu;' => 'Ν',
			  '&nu;' => 'ν',
			  '&Xi;' => 'Ξ',
			  '&xi;' => 'ξ',
			  '&Omicron;' => 'Ο',
			  '&omicron;' => 'ο',
			  '&Pi;' => 'Π',
			  '&pi;' => 'π',
			  '&Rho;' => 'Ρ',
			  '&rho;' => 'ρ',
			  '&Sigma;' => 'Σ',
			  '&sigmaf;' => 'ς',
			  '&sigma;' => 'σ',
			  '&Tau;' => 'Τ',
			  '&tau;' => 'τ',
			  '&Upsilon;' => 'Υ',
			  '&upsilon;' => 'υ',
			  '&Phi;' => 'Φ',
			  '&phi;' => 'φ',
			  '&Chi;' => 'Χ',
			  '&chi;' => 'χ',
			  '&Psi;' => 'Ψ',
			  '&psi;' => 'ψ',
			  '&Omega;' => 'Ω',
			  '&omega;' => 'ω',
			  '&thetasym;' => 'ϑ',
			  '&upsih;' => 'ϒ',
			  '&piv;' => 'ϖ',
			  '&forall;' => '∀',
			  '&part;' => '∂',
			  '&exist;' => '∃',
			  '&empty;' => '∅',
			  '&nabla;' => '∇',
			  '&isin;' => '∈',
			  '&notin;' => '∉',
			  '&ni;' => '∋',
			  '&prod;' => '∏',
			  '&sum;' => '∑',
			  '&minus;' => '−',
			  '&lowast;' => '∗',
			  '&radic;' => '√',
			  '&prop;' => '∝',
			  '&infin;' => '∞',
			  '&ang;' => '∠',
			  '&and;' => '⊥',
			  '&or;' => '⊦',
			  '&cap;' => '∩',
			  '&cup;' => '∪',
			  '&int;' => '∫',
			  '&there4;' => '∴',
			  '&sim;' => '∼',
			  '&cong;' => '≅',
			  '&asymp;' => '≈',
			  '&ne;' => '≠',
			  '&equiv;' => '≡',
			  '&le;' => '≤',
			  '&ge;' => '≥',
			  '&sub;' => '⊂',
			  '&sup;' => '⊃',
			  '&nsub;' => '⊄',
			  '&sube;' => '⊆',
			  '&supe;' => '⊇',
			  '&oplus;' => '⊕',
			  '&otimes;' => '⊗',
			  '&perp;' => '⊥',
			  '&sdot;' => '⋅',
			  '&loz;' => '◊',
			  '&lceil;' => '⌈',
			  '&rceil;' => '⌉',
			  '&lfloor;' => '⌊',
			  '&rfloor;' => '⌋',
			  '&lang;' => '〈',
			  '&rang;' => '〉',
			  '&larr;' => '←',
			  '&uarr;' => '↑',
			  '&rarr;' => '→',
			  '&darr;' => '↓',
			  '&harr;' => '↔',
			  '&crarr;' => '↵',
			  '&lArr;' => '⇐',
			  '&uArr;' => '⇑',
			  '&rArr;' => '⇒',
			  '&dArr;' => '⇓',
			  '&hArr;' => '⇔',
			  '&bull;' => '•',
			  '&hellip;' => '…',
			  '&prime;' => '′',
			  '&oline;' => '‾',
			  '&frasl;' => '⁄',
			  '&weierp;' => '℘',
			  '&image;' => 'ℑ',
			  '&real;' => 'ℜ',
			  '&trade;' => '™',
			  '&euro;' => '€',
			  '&alefsym;' => 'ℵ',
			  '&spades;' => '♠',
			  '&clubs;' => '♣',
			  '&hearts;' => '♥',
			  '&diams;' => '♦',
			  '&ensp;' => ' ',
			  '&emsp;' => ' ',
			  '&thinsp;' => ' ',
			  '&zwnj;' => '‌',
			  '&zwj;' => '‍',
			  '&lrm;' => '‎',
			  '&rlm;' => '‏',
			  '&ndash;' => '–',
			  '&mdash;' => '—',
			  '&lsquo;' => '‘',
			  '&rsquo;' => '’',
			  '&sbquo;' => '‚',
			  '&ldquo;' => '“',
			  '&rdquo;' => '”',
			  '&bdquo;' => '„',
			  '&dagger;' => '†',
			  '&Dagger;' => '‡',
			  '&permil;' => '‰',
			  '&lsaquo;' => '‹',
			  '&rsaquo;' => '›'
			  );

  $encodemap= array(
			  // diverse Zeichen müssen einfach kodiert werden:
			  '<'     => '&lt;',
			  '>'     => '&gt;',
			  '"'     => '&quot;',
			  // & wird auch kodiert, damit es gültiges XML wird. 
			  '&'     => '&amp;');

  // konvertierungstabelle, die aber an den 4 htmlspecialchars lücken hat.
  // geht das auch eleganter?
  $convmap = array ( 0x0001, 0x0021, 0, 0xffff,
		     0x0023, 0x0025, 0, 0xffff,
		     0x0027, 0x003b, 0, 0xffff,
		     0x003d, 0x003d, 0, 0xffff,
		     0x003f, 0xffff, 0, 0xffff);
  $enddaten=array();
  while(list($name, $wert) = each($daten))
    if (get_magic_quotes_gpc()) {
      $enddaten[$name]=strtr(mb_decode_numericentity(strtr(stripslashes($wert),
							   $conversion_table),
						     $convmap),
			     $encodemap);
    } else {
      $enddaten[$name]=strtr(mb_decode_numericentity(strtr($wert,
							   $conversion_table),
						     $convmap),
			     $encodemap);
    }
  return $enddaten;
}

?>
