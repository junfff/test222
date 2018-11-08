/*==============================================================*/
/* DBMS name:      ORACLE Version 11g                           */
/* Created on:     2018/11/8 12:01:00                           */
/*==============================================================*/


alter table JMaccount
   drop constraint FK_JMACCOUN_ACCOUNT_JMUSR;

alter table JMusr
   drop constraint FK_JMUSR_USR_JMAPP;

drop index Account2_FK;

drop table JMaccount cascade constraints;

drop table JMapp cascade constraints;

drop index usr_FK;

drop table JMusr cascade constraints;
