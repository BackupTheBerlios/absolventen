# MySQL dump 7.1
#
# Host: localhost    Database: altesg
#--------------------------------------------------------
# Server version	3.22.32

#
# Table structure for table 'Adressen'
#
CREATE TABLE Adressen (
  id int(11) DEFAULT '0' NOT NULL auto_increment,
  uid int(11) DEFAULT '0' NOT NULL,
  anfang varchar(255),
  plz varchar(25) DEFAULT '' NOT NULL,
  ort varchar(40) DEFAULT '' NOT NULL,
  ende varchar(255),
  vorwahl varchar(30),
  telefon varchar(30),
  aktiv int(11),
  PRIMARY KEY (id),
  KEY uid (uid),
  KEY adresse (uid,plz,ort)
);

#
# Table structure for table 'EMail'
#
CREATE TABLE EMail (
  id int(11) DEFAULT '0' NOT NULL auto_increment,
  uid int(11) DEFAULT '0' NOT NULL,
  adresse varchar(255),
  PRIMARY KEY (id),
  KEY uid (uid)
);

#
# Table structure for table 'Einladung'
#
CREATE TABLE Einladung (
  termin int(11) DEFAULT '0' NOT NULL,
  uid int(11) DEFAULT '0' NOT NULL,
  eingeladen date,
  antwort date,
  status tinyint(4)
);

#
# Table structure for table 'HP'
#
CREATE TABLE HP (
  id int(11) DEFAULT '0' NOT NULL auto_increment,
  uid int(11) DEFAULT '0' NOT NULL,
  adresse varchar(255),
  name varchar(255),
  PRIMARY KEY (id),
  KEY uid (uid)
);

#
# Table structure for table 'Personen'
#
CREATE TABLE Personen (
  id int(11) DEFAULT '0' NOT NULL auto_increment,
  aktueller_name varchar(40) DEFAULT '' NOT NULL,
  geburtsname varchar(40) DEFAULT '' NOT NULL,
  vorname varchar(40) DEFAULT '' NOT NULL,
  kommentar text,
  aktualisierung timestamp(14),
  von year(4),
  bis year(4),
  geburtsdatum date,
  studiengang varchar(40),
  grad varchar(20),
  geschlecht tinyint(4),
  PRIMARY KEY (id),
  KEY name (geburtsname,vorname,aktueller_name)
);

#
# Table structure for table 'Telefon'
#
CREATE TABLE Telefon (
  id int(11) DEFAULT '0' NOT NULL auto_increment,
  uid int(11) DEFAULT '0' NOT NULL,
  vorwahl varchar(30),
  telefon varchar(30),
  PRIMARY KEY (id),
  KEY uid (uid)
);

#
# Table structure for table 'Termine'
#
CREATE TABLE Termine (
  id int(11) DEFAULT '0' NOT NULL auto_increment,
  name varchar(255),
  datum_von datetime,
  datum_bis datetime,
  PRIMARY KEY (id)
);

