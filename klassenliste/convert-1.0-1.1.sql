# $Id: convert-1.0-1.1.sql,v 1.5 2004/07/14 23:57:35 keinstein Exp $
#
# $log$

alter table StAg 
  add login varchar(255) not null default '',
  modify pw varchar(255),
  charset utf8,
  type=BDB;
update StAg set login=id,aktualisierung=aktualisierung;
alter table StAg
  add unique login (login);


alter table StAgMail 
  add Name varchar(255) default null,
  add Link bool not null default 0,
  add Encode bool not null default 1,
  add MailFormular bool not null default 1,
  charset utf8,
  type=BDB;

update StAgMail set encode=0,Link=1;
update StAgMail set name='F&uuml;r Spam' where id=1;

alter table StAgTel 
  add aid int(11) default null after uid,
  add kommentar varchar(40),
  charset utf8,
  type=BDB;

insert into StAgTel (uid,aid,vorwahl,telefon) 
  select uid,id,vorwahl,telefon from StAgAdr 
    where vorwahl is not null or telefon is not null;

alter table StAgAdr 
  modify plz varchar(255) default null,
  modify ort varchar(255) default null,
  drop vorwahl, 
  drop telefon,
  charset utf8,
  type=BDB;

alter table StAgJg
  modify klasse varchar(255),
  charset utf8,
  type=BDB;
update StAgJg set klasse="" where klasse="12" or klasse="1" or klasse="0"
update StAgJg set klasse=concat(klasse,"-Zug") where length(klasse)>0;

alter table StAgHP 
  charset utf8,
  type=BDB;
