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

class mysqldb {
  var $dbname;
  var $server;
  var $login;
  var $password;
  var $db;
  
  function mysqldb() {
    $this->dbserver="";
    $this->server="";
    $this->login="";
    $this->password="";
  }
  
  function connect($my_server,$my_login,$my_password) {
    $this->server=$my_server;
    $this->login=$my_login;
    $this->password=$my_password;
    $this->db=mysql_connect($this->server,$this->login,$this->password);
  }

  function selectdb($dbname) {
    $this->dbname=$dbname;
    mysql_select_db($dbname,$this->db);
  }

  function query($sql) {
    return mysql_query($sql,$this->db);
  }

  function puffer_leeren($puffer){
    return mysql_free_result($puffer);
  }

  function fetch_array($qu){
    return mysql_fetch_array($qu,$this->db);
  }
  
  function insert_id() {
    return mysql_insert_id($this->db);
  }

  function transaction_start() {
    $x=$this->query("start transaction");
    echo $x;
    return $x;
  }

  function transaction_stop() {
    return $this->query("end");
  }

  function rollback() {
    return $this->query("rollback");
  }

  function commit () {
    return $this->query("commit");
  }
}
?>