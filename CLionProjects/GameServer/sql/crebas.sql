/*==============================================================*/
/* DBMS name:      ORACLE Version 11g                           */
/* Created on:     2018/11/7 17:14:33                           */
/*==============================================================*/


alter table JMaccount
   drop constraint FK_JMACCOUN_ACCOUNT2_JMUSR;

alter table JMusr
   drop constraint FK_JMUSR_ACCOUNT_JMACCOUN;

alter table JMusr
   drop constraint FK_JMUSR_USR_JMAPP;

drop index Account2_FK;

drop table JMaccount cascade constraints;

drop table JMapp cascade constraints;

drop index Account_FK;

drop index usr_FK;

drop table JMusr cascade constraints;

/*==============================================================*/
/* Table: JMaccount                                             */
/*==============================================================*/
create table JMaccount 
(
   accountId            VARCHAR2(32)         not null,
   uuid                 VARCHAR2(64),
   name                 VARCHAR2(32),
   mobilephone          INTEGER,
   email                VARCHAR2(32),
   sex                  INTEGER,
   constraint PK_JMACCOUNT primary key (accountId)
);

/*==============================================================*/
/* Index: Account2_FK                                           */
/*==============================================================*/
create index Account2_FK on JMaccount (
   uuid ASC
);

/*==============================================================*/
/* Table: JMapp                                                 */
/*==============================================================*/
create table JMapp 
(
   appName              VARCHAR2(16)         not null,
   constraint PK_JMAPP primary key (appName)
);

/*==============================================================*/
/* Table: JMusr                                                 */
/*==============================================================*/
create table JMusr 
(
   uuid                 VARCHAR2(64)         not null,
   appName              VARCHAR2(16),
   accountId            VARCHAR2(32),
   constraint AK_UUID_JMUSR unique (uuid)
);

/*==============================================================*/
/* Index: usr_FK                                                */
/*==============================================================*/
create index usr_FK on JMusr (
   appName ASC
);

/*==============================================================*/
/* Index: Account_FK                                            */
/*==============================================================*/
create index Account_FK on JMusr (
   accountId ASC
);

alter table JMaccount
   add constraint FK_JMACCOUN_ACCOUNT2_JMUSR foreign key (uuid)
      references JMusr (uuid);

alter table JMusr
   add constraint FK_JMUSR_ACCOUNT_JMACCOUN foreign key (accountId)
      references JMaccount (accountId);

alter table JMusr
   add constraint FK_JMUSR_USR_JMAPP foreign key (appName)
      references JMapp (appName);

