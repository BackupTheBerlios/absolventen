-- MySQL dump 9.10
--
-- Host: localhost    Database: stag
-- ------------------------------------------------------
-- Server version	4.0.18-log

--
-- Table structure for table `StAg`
--

CREATE TABLE StAg (
  id int(11) unsigned NOT NULL auto_increment,
  aktueller_name varchar(40) NOT NULL default '',
  geburtsname varchar(40) NOT NULL default '',
  vorname varchar(40) NOT NULL default '',
  kommentar text,
  pw varchar(255) default NULL,
  aktualisierung timestamp(14) NOT NULL,
  login varchar(255) NOT NULL default '',
  PRIMARY KEY  (id),
  UNIQUE KEY login (login),
  KEY name (geburtsname,vorname,aktueller_name)
) TYPE=BerkeleyDB COMMENT='Personendaten';

--
-- Table structure for table `StAgAdr`
--

CREATE TABLE StAgAdr (
  id int(11) NOT NULL auto_increment,
  uid int(11) NOT NULL default '0',
  anfang varchar(255) default NULL,
  plz varchar(255) default NULL,
  ort varchar(255) default NULL,
  ende varchar(255) default NULL,
  PRIMARY KEY  (id),
  KEY uid (uid),
  KEY adresse (uid,plz,ort)
) TYPE=BerkeleyDB;

--
-- Table structure for table `StAgHP`
--

CREATE TABLE StAgHP (
  id int(11) NOT NULL auto_increment,
  uid int(11) NOT NULL default '0',
  adresse varchar(255) default NULL,
  name varchar(255) default NULL,
  PRIMARY KEY  (id),
  KEY uid (uid)
) TYPE=BerkeleyDB;

--
-- Table structure for table `StAgJg`
--

CREATE TABLE StAgJg (
  id int(11) NOT NULL auto_increment,
  uid int(11) NOT NULL default '0',
  jahrgang year(4) NOT NULL default '0000',
  klasse varchar(255) default NULL,
  drin int(11) NOT NULL default '0',
  PRIMARY KEY  (id),
  KEY uid (uid),
  KEY kljg (jahrgang,klasse,drin)
) TYPE=BerkeleyDB;

--
-- Table structure for table `StAgMail`
--

CREATE TABLE StAgMail (
  id int(11) NOT NULL auto_increment,
  uid int(11) NOT NULL default '0',
  adresse varchar(255) default NULL,
  Name varchar(255) default NULL,
  Link tinyint(1) NOT NULL default '0',
  Encode tinyint(1) NOT NULL default '1',
  MailFormular tinyint(1) NOT NULL default '1',
  PRIMARY KEY  (id),
  KEY uid (uid)
) TYPE=BerkeleyDB;

--
-- Table structure for table `StAgTel`
--

CREATE TABLE StAgTel (
  id int(11) NOT NULL auto_increment,
  uid int(11) NOT NULL default '0',
  aid int(11) default NULL,
  vorwahl varchar(30) default NULL,
  telefon varchar(30) default NULL,
  kommentar varchar(40) default NULL,
  PRIMARY KEY  (id),
  KEY uid (uid)
) TYPE=BerkeleyDB;


