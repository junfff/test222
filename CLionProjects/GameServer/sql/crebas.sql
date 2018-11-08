/*==============================================================*/
/* DBMS name:      ORACLE Version 11g                           */
/* Created on:     2018/11/8 14:45:12                           */
/*==============================================================*/


alter table JMusr
   drop constraint FK_JMUSR_USR_JMAPP;

drop table JMapp cascade constraints;

drop table JMusr cascade constraints;

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
   appName              VARCHAR2(16),
   accountId            VARCHAR2(64),
   uuid                 VARCHAR2(64)         not null,
   name                 VARCHAR2(64),
   mobilephone          VARCHAR2(64),
   email                VARCHAR2(64),
   sex                  SMALLINT,
   pwd                  VARCHAR2(64),
   constraint PK_JMUSR primary key (uuid)
);

alter table JMusr
   add constraint FK_JMUSR_USR_JMAPP foreign key (appName)
      references JMapp (appName);

