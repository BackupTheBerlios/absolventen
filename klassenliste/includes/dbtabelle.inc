<?php /* $Id: dbtabelle.inc,v 1.4 2004/07/25 17:31:44 keinstein Exp $

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

$log$
*/ 

class dbtabelle {
  var $db;
  var $Werte;
  var $Qresult;
  var $dbfehler = array();

  /**************
   * Prototypen *
   **************/

  // Zentrale SQL-Query-Verwaltung
  // $funktion: string    -- Typ der Anfrage
  // $args: verschiedenes -- Einzusetzende Argumente
  // Rückgabewert: vollständiger Text der SQL-Anfrage
  function sql($funktion,$args=0) {
    return "select 1";
  }
  
  // Einfüge-Operationen
  // $daten: Array mit eizufügenden Werten
  // Rückgabewert: id des Datensatzes oder
  //               im Fehlerfall Wert <= 0
  function insert($daten) {
    return -1;
  }

  // Änderungsoperation
  // $daten: Array mit neuen Werten
  // Rückgabewert: siehe update_backend
  function update($daten) {
    return -1;
  }

  // Standardausgabe (ohne Zusatzparameter) für große Tabelle
  // $daten: Array        -- Werte für die Ausgabe
  // $erstespalte: string -- ggf. komplette Management-Spalte
  function normprint($daten,$erstespalte=false) {
  }

  // Eingabeformular darstellen
  //
  // $neu: true,  wenn neue Daten einzugeben sind
  //       false, wenn Formular für Änderungen ausgegeben wird
  // $daten: Array: Vorbelegungen der Felder
  // $fehler: Array: Fehlermeldungen zu den einzlnen Feldern
  function formular($neu,$daten=array(),$fehler=array()) {
  }

  // Eingabe auf Plausibilität prüfen
  //
  // $daten: Array mit Eingabe-Werten der einzelnen Felder
  // $neu:   Wie bei forumlar().
  // Rückgabewert: Array mit Feld => 'Fehlermeldung'
  function checkdaten($daten,$neu) {
    return array('checkdaten' => 'Nicht implementiert');
  }

  /**************
   * Funktionen *
   **************/

  // Konstruktor
  function dbtabelle (&$h_db) {
    $this->db=&$h_db;
  }

  // Datenbank übernehmen
  function dbset(&$hdb) {
    $this->db=&$hdb;
  }

  // Speicher für Query-Result freigeben
  function puffer_leeren() {
    if ($this->Qresult) {
      $this->db->puffer_leeren($this->Qresult);
      $this->Qresult=0;
    }
    $this->dbfehler=array();
  }

  // Nach erstem Datensatz von $person suchen
  function erste_person($person){
    return $this->select_backend($this->sql('erste_person',$person));
  }

  // Aktuellen Datensatz aus der Datenbank holen
  function diese($id){
    return $this->select_backend($this->sql('diese', $id));
   }

  // Gemeinsamer Teil von select-Funktionen
  function select_backend($sql) {
    $this->puffer_leeren();
    if (!$this->Qresult=$this->db->query($sql)){
      fehler('dbtabelle-&gt;select_backend(' . $sql . ')');
      return false;
    }
    $this->Werte=$this->db->fetch_array($this->Qresult);
    return ($this->Werte && true);
  }

  // Nächsten Datensatz aus der Ressource holen
  function naechste(){
    return $this->Werte=$this->db->fetch_array($this->Qresult);
  }

  // Service-Funktion für Einfügeoperationen
  function insert_backend($sql,$uid=0) {
    if (!$this->db->query_direkt($sql)) {
      $this->dbfehler[]=array('funktion' =>
			      "dbtabelle-&gt;insert_backend(" . $sql . "," . $uid . ")",
			      'nr' => $this->db->fehlernr(),
			      'text' => $this->db->fehlertext());
      return -2;
    } 
    $id=$this->db->insert_id();
    if ($uid) {
      $person=new personen($this->db);
      $person->aktualisiere_akt($uid);
      $person->puffer_leeren();
    }
    return $id;
  }

  // Service-Funktion für Änderungsoperationen
  function update_backend($sql,$uid=0) {
    if (!$this->db->query_direkt($sql)) {
      $this->dbfehler[]=array('funktion' =>
			     "adresse-&gt;update_backend(" . $sql . ",". $uid . ")",
			      'nr' => $this->db->fehlernr(),
			      'text' => $this->db->fehlertext());
      return -2;
    }
    if ($uid) {
      $person=new personen($this->db);
      $person->aktualisiere_akt($uid);
      $person->puffer_leeren();
    }
    return 0;
  }

  // Datensatz löschen
  function loeschen($id,$uid=0){
    $this->puffer_leeren();
    if ($id) {
      $query=$this->sql('loeschen',$id);
    } else {
      if ($uid) {
	$query=$this->sql('persloeschen',$uid);
      } else return -3;
    }
    if (!$this->Qresult=$this->db->query_direkt($query)) {
      fehler("dbtabelle-&gt;loeschen(" . $id . ")");
      return -2;
    }
    if ($uid) {
      $person=new personen($this->db);
      $person->aktualisiere_akt($uid);
      $person->puffer_leeren();
    }
    @$this->puffer_leeren();
    return 0;
  }

  /* die einzelnen Felder der Person */

  function id() {
    return isset($this->Werte["id"])?$this->Werte["id"]:false;
  }

  function uid() {
    return isset($this->Werte["uid"])?$this->Werte["uid"]:false;
  }

  // Änderungs-Formular für aktuellen Datensatz ausgeben
  function datenformular() {
    $this->formular(false,$this->Werte);
  }

}
?>
