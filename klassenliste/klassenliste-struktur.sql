# phpMyAdmin MySQL-Dump
# http://phpwizard.net/phpMyAdmin/
#
# Host: db.schlemmi.f2s.com:3306 Database : schlemmi

# --------------------------------------------------------
#
# Table structure for table 'StAg'
#

CREATE TABLE StAg (
   id int(11) NOT NULL auto_increment,
   aktueller_name varchar(40) NOT NULL,
   geburtsname varchar(40) NOT NULL,
   vorname varchar(40) NOT NULL,
   kommentar text,
   pw varchar(15),
   aktualisierung timestamp(14),
   PRIMARY KEY (id),
   KEY name (geburtsname, vorname, aktueller_name)
);


# --------------------------------------------------------
#
# Table structure for table 'StAgAdr'
#

CREATE TABLE StAgAdr (
   id int(11) NOT NULL auto_increment,
   uid int(11) DEFAULT '0' NOT NULL,
   anfang varchar(255),
   plz varchar(25) NOT NULL,
   ort varchar(40) NOT NULL,
   ende varchar(255),
   vorwahl varchar(30),
   telefon varchar(30),
   PRIMARY KEY (id),
   KEY uid (uid),
   KEY adresse (uid, plz, ort)
);


# --------------------------------------------------------
#
# Table structure for table 'StAgHP'
#

CREATE TABLE StAgHP (
   id int(11) NOT NULL auto_increment,
   uid int(11) DEFAULT '0' NOT NULL,
   adresse varchar(255),
   name varchar(255),
   PRIMARY KEY (id),
   KEY uid (uid)
);


# --------------------------------------------------------
#
# Table structure for table 'StAgJg'
#

CREATE TABLE StAgJg (
   id int(11) NOT NULL auto_increment,
   uid int(11) DEFAULT '0' NOT NULL,
   jahrgang year(4) DEFAULT '0000' NOT NULL,
   klasse char(2) NOT NULL,
   drin int(11) DEFAULT '0' NOT NULL,
   PRIMARY KEY (id),
   KEY uid (uid),
   KEY kljg (jahrgang, klasse, drin)
);


# --------------------------------------------------------
#
# Table structure for table 'StAgMail'
#

CREATE TABLE StAgMail (
   id int(11) NOT NULL auto_increment,
   uid int(11) DEFAULT '0' NOT NULL,
   adresse varchar(255),
   PRIMARY KEY (id),
   KEY uid (uid)
);


# --------------------------------------------------------
#
# Table structure for table 'StAgTel'
#

CREATE TABLE StAgTel (
   id int(11) NOT NULL auto_increment,
   uid int(11) DEFAULT '0' NOT NULL,
   vorwahl varchar(30),
   telefon varchar(30),
   PRIMARY KEY (id),
   KEY uid (uid)
);


