alter table StAg 
  add login varchar(255) not null default '';
update StAg set login=id;
alter table StAg
  add unique login (login);


alter table StAgMail 
  add Name varchar(255) default null,
  add Link bool not null default 0,
  add Encode bool not null default 1,
  add Formular bool not null default 1;
update StAgMail set encode=0,Link=1;

alter table StAgTel 
  add aid int(11) default null after uid,
  add kommentar varchar(40);
insert into StAgTel (uid,aid,vorwahl,telefon) 
  select uid,id,vorwahl,telefon from StAgAdr 
    where vorwahl is not null or telefon is not null;
alter table StAgAdr 
  drop vorwahl, 
  drop telefon;

update StAgMail set name='F&uuml;r Spam' where id=1;
