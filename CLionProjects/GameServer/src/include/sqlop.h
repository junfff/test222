//
// Created by ljf on 11/7/18.
//



#ifndef GAMESERVER_SQLOP_H
#define GAMESERVER_SQLOP_H






/* Result Sets Interface */
#ifndef SQL_CRSR
#  define SQL_CRSR
struct sql_cursor
{
    unsigned int curocn;
    void *ptr1;
    void *ptr2;
    unsigned int magic;
};
typedef struct sql_cursor sql_cursor;
typedef struct sql_cursor SQL_CURSOR;
#endif /* SQL_CRSR */

/* Thread Safety */
typedef void * sql_context;
typedef void * SQL_CONTEXT;

/* Object support */
struct sqltvn
{
    unsigned char *tvnvsn;
    unsigned short tvnvsnl;
    unsigned char *tvnnm;
    unsigned short tvnnml;
    unsigned char *tvnsnm;
    unsigned short tvnsnml;
};
typedef struct sqltvn sqltvn;

struct sqladts
{
    unsigned int adtvsn;
    unsigned short adtmode;
    unsigned short adtnum;
    sqltvn adttvn[1];
};
typedef struct sqladts sqladts;

static struct sqladts sqladt = {
        1,1,0,
};

/* Binding to PL/SQL Records */
struct sqltdss
{
    unsigned int tdsvsn;
    unsigned short tdsnum;
    unsigned char *tdsval[1];
};
typedef struct sqltdss sqltdss;
static struct sqltdss sqltds =
        {
                1,
                0,
        };

/* File name & Package Name */
struct sqlcxp
{
    unsigned short fillen;
    char  filnam[9];
};
static const struct sqlcxp sqlfpn =
        {
                8,
                "sqlop.pc"
        };


static unsigned int sqlctx = 20555;


static struct sqlexd {
    unsigned long  sqlvsn;
    unsigned int   arrsiz;
    unsigned int   iters;
    unsigned int   offset;
    unsigned short selerr;
    unsigned short sqlety;
    unsigned int   occurs;
    const short *cud;
    unsigned char  *sqlest;
    const char  *stmt;
    sqladts *sqladtp;
    sqltdss *sqltdsp;
    unsigned char  **sqphsv;
    unsigned long  *sqphsl;
    int   *sqphss;
    short **sqpind;
    int   *sqpins;
    unsigned long  *sqparm;
    unsigned long  **sqparc;
    unsigned short  *sqpadto;
    unsigned short  *sqptdso;
    unsigned int   sqlcmax;
    unsigned int   sqlcmin;
    unsigned int   sqlcincr;
    unsigned int   sqlctimeout;
    unsigned int   sqlcnowait;
    int   sqfoff;
    unsigned int   sqcmod;
    unsigned int   sqfmod;
    unsigned int   sqlpfmem;
    unsigned char  *sqhstv[8];
    unsigned long  sqhstl[8];
    int   sqhsts[8];
    short *sqindv[8];
    int   sqinds[8];
    unsigned long  sqharm[8];
    unsigned long  *sqharc[8];
    unsigned short  sqadto[8];
    unsigned short  sqtdso[8];
} sqlstm = {13,8};

// Prototypes
extern "C" {
void sqlcxt (void **, unsigned int *,
             struct sqlexd *, const struct sqlcxp *);
void sqlcx2t(void **, unsigned int *,
             struct sqlexd *, const struct sqlcxp *);
void sqlbuft(void **, char *);
void sqlgs2t(void **, char *);
void sqlorat(void **, unsigned int *, void *);
}

// Forms Interface
static const int IAPSUCC = 0;
static const int IAPFAIL = 1403;
static const int IAPFTL  = 535;
extern "C" { void sqliem(unsigned char *, signed int *); }

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* cud (compilation unit data) array */
static const short sqlcud0[] =
        {13,4130,871,0,0,
         5,0,0,0,0,0,27,68,0,0,4,4,0,1,0,1,97,0,0,1,10,0,0,1,10,0,0,1,10,0,0,
         36,0,0,2,114,0,3,83,0,0,8,8,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,97,0,0,
         1,97,0,0,1,3,0,0,1,97,0,0,
         83,0,0,3,0,0,30,86,0,0,0,0,0,1,0,
         98,0,0,4,46,0,5,95,0,0,2,2,0,1,0,1,97,0,0,1,97,0,0,
         121,0,0,5,34,0,2,105,0,0,1,1,0,1,0,1,97,0,0,
         140,0,0,6,108,0,4,117,0,0,7,1,0,1,0,2,97,0,0,2,97,0,0,2,97,0,0,2,97,0,0,2,97,0,
         0,2,3,0,0,1,97,0,0,
         183,0,0,0,0,0,27,143,0,0,4,4,0,1,0,1,97,0,0,1,10,0,0,1,10,0,0,1,10,0,0,
         214,0,0,8,70,0,4,188,0,0,4,1,0,1,0,2,3,0,0,2,9,0,0,2,9,0,0,1,3,0,0,
         245,0,0,9,0,0,30,198,0,0,0,0,0,1,0,
        };


//#include "pch.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

//#include "sqlca.h"





//DEPTNO                                                                        NOT NULL NUMBER(2)
//DNAME                                                                         NOT NULL VARCHAR2(14)
//LOC                                                                                    VARCHAR2(13)


/* EXEC SQL INCLUDE sqlca;
 */
/*
 * $Header: sqlca.h 24-apr-2003.12:50:58 mkandarp Exp $ sqlca.h
 */

/* Copyright (c) 1985, 2003, Oracle Corporation.  All rights reserved.  */

/*
NAME
  SQLCA : SQL Communications Area.
FUNCTION
  Contains no code. Oracle fills in the SQLCA with status info
  during the execution of a SQL stmt.
NOTES
  **************************************************************
  ***                                                        ***
  *** This file is SOSD.  Porters must change the data types ***
  *** appropriately on their platform.  See notes/pcport.doc ***
  *** for more information.                                  ***
  ***                                                        ***
  **************************************************************

  If the symbol SQLCA_STORAGE_CLASS is defined, then the SQLCA
  will be defined to have this storage class. For example:

    #define SQLCA_STORAGE_CLASS extern

  will define the SQLCA as an extern.

  If the symbol SQLCA_INIT is defined, then the SQLCA will be
  statically initialized. Although this is not necessary in order
  to use the SQLCA, it is a good pgming practice not to have
  unitialized variables. However, some C compilers/OS's don't
  allow automatic variables to be init'd in this manner. Therefore,
  if you are INCLUDE'ing the SQLCA in a place where it would be
  an automatic AND your C compiler/OS doesn't allow this style
  of initialization, then SQLCA_INIT should be left undefined --
  all others can define SQLCA_INIT if they wish.

  If the symbol SQLCA_NONE is defined, then the SQLCA variable will
  not be defined at all.  The symbol SQLCA_NONE should not be defined
  in source modules that have embedded SQL.  However, source modules
  that have no embedded SQL, but need to manipulate a sqlca struct
  passed in as a parameter, can set the SQLCA_NONE symbol to avoid
  creation of an extraneous sqlca variable.

MODIFIED
    lvbcheng   07/31/98 -  long to int
    jbasu      12/12/94 -  Bug 217878: note this is an SOSD file
    losborne   08/11/92 -  No sqlca var if SQLCA_NONE macro set
  Clare      12/06/84 - Ch SQLCA to not be an extern.
  Clare      10/21/85 - Add initialization.
  Bradbury   01/05/86 - Only initialize when SQLCA_INIT set
  Clare      06/12/86 - Add SQLCA_STORAGE_CLASS option.
*/

#ifndef SQLCA
#define SQLCA 1

struct   sqlca
{
    /* ub1 */ char    sqlcaid[8];
    /* b4  */ int     sqlabc;
    /* b4  */ int     sqlcode;
    struct
    {
        /* ub2 */ unsigned short sqlerrml;
        /* ub1 */ char           sqlerrmc[70];
    } sqlerrm;
    /* ub1 */ char    sqlerrp[8];
    /* b4  */ int     sqlerrd[6];
    /* ub1 */ char    sqlwarn[8];
    /* ub1 */ char    sqlext[8];
};

#ifndef SQLCA_NONE
#ifdef   SQLCA_STORAGE_CLASS
SQLCA_STORAGE_CLASS struct sqlca sqlca
#else
struct sqlca sqlca
#endif

#ifdef  SQLCA_INIT
= {
         {'S', 'Q', 'L', 'C', 'A', ' ', ' ', ' '},
         sizeof(struct sqlca),
         0,
         { 0, {0}},
         {'N', 'O', 'T', ' ', 'S', 'E', 'T', ' '},
         {0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}
         }
#endif
;
#endif

#endif

/* end SQLCA */


//定义变量 宿主变量
/* EXEC SQL BEGIN DECLARE SECTION; */


const char *serversid = "ljf/jkui9789@orcl";//prco编译器借用了c语言的数据类型语法而已
const char *appName = "JMapp";
int deptno;
char dname[20];
char loc[20];
char ch;

int deptno2;
char dname2[20];
char loc2[20];

int deptno3;
/* varchar dname3[20]; */
struct { unsigned short len; unsigned char arr[20]; } dname3;
//struct { unsigned short len; unsigned char arr[20]; } dname3;
/* varchar loc3[20]; */
struct { unsigned short len; unsigned char arr[20]; } loc3;
//proc认识varchar


struct account_info{
    char  accountId[64];
    char uuid[64];
    char  name[32];
    char mobilephone[64];
    char  email[64];
    short sex;
    char   pwd[64];
};

struct account_info tmpInfo;
/* EXEC SQL END DECLARE SECTION; */



void checksqlcode(const char *str){
    int ret = sqlca.sqlcode;
    if(ret != 0)
    {
        printf("check %s , error = %d \n",str,ret);
        exit(ret);
    }
    printf("check %s , ok ! \n ",str);
}


int sql_insert(struct account_info *info) {

    /* EXEC SQL connect : serversid; */

    {
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 4;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )10;
        sqlstm.offset = (unsigned int  )5;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (unsigned char  *)serversid;
        sqlstm.sqhstl[0] = (unsigned long )0;
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         short *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned long )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqphsv = sqlstm.sqhstv;
        sqlstm.sqphsl = sqlstm.sqhstl;
        sqlstm.sqphss = sqlstm.sqhsts;
        sqlstm.sqpind = sqlstm.sqindv;
        sqlstm.sqpins = sqlstm.sqinds;
        sqlstm.sqparm = sqlstm.sqharm;
        sqlstm.sqparc = sqlstm.sqharc;
        sqlstm.sqpadto = sqlstm.sqadto;
        sqlstm.sqptdso = sqlstm.sqtdso;
        sqlstm.sqlcmax = (unsigned int )100;
        sqlstm.sqlcmin = (unsigned int )2;
        sqlstm.sqlcincr = (unsigned int )1;
        sqlstm.sqlctimeout = (unsigned int )0;
        sqlstm.sqlcnowait = (unsigned int )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    }


    checksqlcode("connect");

//    APPNAME										VARCHAR2(16)
//    ACCOUNTID										VARCHAR2(64)
//    UUID									       NOT NULL VARCHAR2(64)
//    NAME											VARCHAR2(64)
//    MOBILEPHONE										VARCHAR2(64)
//    EMAIL											VARCHAR2(64)
//    SEX											NUMBER(38)
//    PWD											VARCHAR2(64)


    //插入数据 - 曾
    memcpy(&tmpInfo,info, sizeof(tmpInfo));
    /* EXEC SQL insert into JMusr(appname,accountId,uuid,name,mobilephone,email,sex,pwd) values(:appName,:tmpInfo.accountId,:tmpInfo.uuid,:tmpInfo.name,:tmpInfo.mobilephone,:tmpInfo.email,:tmpInfo.sex,:tmpInfo.pwd); */

    {
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 8;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.stmt = "insert into JMusr (appname,accountId,uuid,name,mobilepho\
ne,email,sex,pwd) values (:b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7)";
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )36;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (unsigned char  *)appName;
        sqlstm.sqhstl[0] = (unsigned long )0;
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         short *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned long )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqhstv[1] = (unsigned char  *)(tmpInfo.accountId);
        sqlstm.sqhstl[1] = (unsigned long )64;
        sqlstm.sqhsts[1] = (         int  )0;
        sqlstm.sqindv[1] = (         short *)0;
        sqlstm.sqinds[1] = (         int  )0;
        sqlstm.sqharm[1] = (unsigned long )0;
        sqlstm.sqadto[1] = (unsigned short )0;
        sqlstm.sqtdso[1] = (unsigned short )0;
        sqlstm.sqhstv[2] = (unsigned char  *)(tmpInfo.uuid);
        sqlstm.sqhstl[2] = (unsigned long )64;
        sqlstm.sqhsts[2] = (         int  )0;
        sqlstm.sqindv[2] = (         short *)0;
        sqlstm.sqinds[2] = (         int  )0;
        sqlstm.sqharm[2] = (unsigned long )0;
        sqlstm.sqadto[2] = (unsigned short )0;
        sqlstm.sqtdso[2] = (unsigned short )0;
        sqlstm.sqhstv[3] = (unsigned char  *)(tmpInfo.name);
        sqlstm.sqhstl[3] = (unsigned long )32;
        sqlstm.sqhsts[3] = (         int  )0;
        sqlstm.sqindv[3] = (         short *)0;
        sqlstm.sqinds[3] = (         int  )0;
        sqlstm.sqharm[3] = (unsigned long )0;
        sqlstm.sqadto[3] = (unsigned short )0;
        sqlstm.sqtdso[3] = (unsigned short )0;
        sqlstm.sqhstv[4] = (unsigned char  *)(tmpInfo.mobilephone);
        sqlstm.sqhstl[4] = (unsigned long )64;
        sqlstm.sqhsts[4] = (         int  )0;
        sqlstm.sqindv[4] = (         short *)0;
        sqlstm.sqinds[4] = (         int  )0;
        sqlstm.sqharm[4] = (unsigned long )0;
        sqlstm.sqadto[4] = (unsigned short )0;
        sqlstm.sqtdso[4] = (unsigned short )0;
        sqlstm.sqhstv[5] = (unsigned char  *)(tmpInfo.email);
        sqlstm.sqhstl[5] = (unsigned long )64;
        sqlstm.sqhsts[5] = (         int  )0;
        sqlstm.sqindv[5] = (         short *)0;
        sqlstm.sqinds[5] = (         int  )0;
        sqlstm.sqharm[5] = (unsigned long )0;
        sqlstm.sqadto[5] = (unsigned short )0;
        sqlstm.sqtdso[5] = (unsigned short )0;
        sqlstm.sqhstv[6] = (unsigned char  *)&(tmpInfo.sex);
        sqlstm.sqhstl[6] = (unsigned long )sizeof(short);
        sqlstm.sqhsts[6] = (         int  )0;
        sqlstm.sqindv[6] = (         short *)0;
        sqlstm.sqinds[6] = (         int  )0;
        sqlstm.sqharm[6] = (unsigned long )0;
        sqlstm.sqadto[6] = (unsigned short )0;
        sqlstm.sqtdso[6] = (unsigned short )0;
        sqlstm.sqhstv[7] = (unsigned char  *)(tmpInfo.pwd);
        sqlstm.sqhstl[7] = (unsigned long )64;
        sqlstm.sqhsts[7] = (         int  )0;
        sqlstm.sqindv[7] = (         short *)0;
        sqlstm.sqinds[7] = (         int  )0;
        sqlstm.sqharm[7] = (unsigned long )0;
        sqlstm.sqadto[7] = (unsigned short )0;
        sqlstm.sqtdso[7] = (unsigned short )0;
        sqlstm.sqphsv = sqlstm.sqhstv;
        sqlstm.sqphsl = sqlstm.sqhstl;
        sqlstm.sqphss = sqlstm.sqhsts;
        sqlstm.sqpind = sqlstm.sqindv;
        sqlstm.sqpins = sqlstm.sqinds;
        sqlstm.sqparm = sqlstm.sqharm;
        sqlstm.sqparc = sqlstm.sqharc;
        sqlstm.sqpadto = sqlstm.sqadto;
        sqlstm.sqptdso = sqlstm.sqtdso;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    }


    checksqlcode("insert JMusr");

    /* EXEC SQL commit work release; */

    {
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 8;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )83;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    }



    return sqlca.sqlcode;
}

int sql_update(struct account_info *info){

    tmpInfo = *info;
    // 修改数据  - 改
    /* EXEC SQL update JMusr set accountId=:tmpInfo.accountId  where uuid=:tmpInfo.uuid; */

    {
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 8;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.stmt = "update JMusr  set accountId=:b0 where uuid=:b1";
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )98;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (unsigned char  *)(tmpInfo.accountId);
        sqlstm.sqhstl[0] = (unsigned long )64;
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         short *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned long )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqhstv[1] = (unsigned char  *)(tmpInfo.uuid);
        sqlstm.sqhstl[1] = (unsigned long )64;
        sqlstm.sqhsts[1] = (         int  )0;
        sqlstm.sqindv[1] = (         short *)0;
        sqlstm.sqinds[1] = (         int  )0;
        sqlstm.sqharm[1] = (unsigned long )0;
        sqlstm.sqadto[1] = (unsigned short )0;
        sqlstm.sqtdso[1] = (unsigned short )0;
        sqlstm.sqphsv = sqlstm.sqhstv;
        sqlstm.sqphsl = sqlstm.sqhstl;
        sqlstm.sqphss = sqlstm.sqhsts;
        sqlstm.sqpind = sqlstm.sqindv;
        sqlstm.sqpins = sqlstm.sqinds;
        sqlstm.sqparm = sqlstm.sqharm;
        sqlstm.sqparc = sqlstm.sqharc;
        sqlstm.sqpadto = sqlstm.sqadto;
        sqlstm.sqptdso = sqlstm.sqtdso;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    }


    checksqlcode("update JMusr");

    return sqlca.sqlcode;
}

int sql_delete(struct account_info *info){

    tmpInfo = *info;
    //数据删除 - 删
    /* EXEC SQL delete JMusr where uuid=:tmpInfo.uuid; */

    {
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 8;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.stmt = "delete  from JMusr  where uuid=:b0";
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )121;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (unsigned char  *)(tmpInfo.uuid);
        sqlstm.sqhstl[0] = (unsigned long )64;
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         short *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned long )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqphsv = sqlstm.sqhstv;
        sqlstm.sqphsl = sqlstm.sqhstl;
        sqlstm.sqphss = sqlstm.sqhsts;
        sqlstm.sqpind = sqlstm.sqindv;
        sqlstm.sqpins = sqlstm.sqinds;
        sqlstm.sqparm = sqlstm.sqharm;
        sqlstm.sqparc = sqlstm.sqharc;
        sqlstm.sqpadto = sqlstm.sqadto;
        sqlstm.sqptdso = sqlstm.sqtdso;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    }


    checksqlcode("delete JMusr");

    return sqlca.sqlcode;
}


int sql_select(struct account_info *info){

    tmpInfo = *info;
    //const char *accountId,const char *uuid,const char *pwd,const char *name,const char *email,int mobilephone,int sex) {
    // 获取数据 - 查
    /* EXEC SQL select uuid, pwd, name, email, mobilephone, sex into :tmpInfo.uuid, :tmpInfo.pwd, :tmpInfo.name, :tmpInfo.email, :tmpInfo.mobilephone, :tmpInfo.sex from JMusr where accountId = :tmpInfo.accountId; */

    {
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 8;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.stmt = "select uuid ,pwd ,name ,email ,mobilephone ,sex into :b0\
,:b1,:b2,:b3,:b4,:b5  from JMusr where accountId=:b6";
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )140;
        sqlstm.selerr = (unsigned short)1;
        sqlstm.sqlpfmem = (unsigned int  )0;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (unsigned char  *)(tmpInfo.uuid);
        sqlstm.sqhstl[0] = (unsigned long )64;
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         short *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned long )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqhstv[1] = (unsigned char  *)(tmpInfo.pwd);
        sqlstm.sqhstl[1] = (unsigned long )64;
        sqlstm.sqhsts[1] = (         int  )0;
        sqlstm.sqindv[1] = (         short *)0;
        sqlstm.sqinds[1] = (         int  )0;
        sqlstm.sqharm[1] = (unsigned long )0;
        sqlstm.sqadto[1] = (unsigned short )0;
        sqlstm.sqtdso[1] = (unsigned short )0;
        sqlstm.sqhstv[2] = (unsigned char  *)(tmpInfo.name);
        sqlstm.sqhstl[2] = (unsigned long )32;
        sqlstm.sqhsts[2] = (         int  )0;
        sqlstm.sqindv[2] = (         short *)0;
        sqlstm.sqinds[2] = (         int  )0;
        sqlstm.sqharm[2] = (unsigned long )0;
        sqlstm.sqadto[2] = (unsigned short )0;
        sqlstm.sqtdso[2] = (unsigned short )0;
        sqlstm.sqhstv[3] = (unsigned char  *)(tmpInfo.email);
        sqlstm.sqhstl[3] = (unsigned long )64;
        sqlstm.sqhsts[3] = (         int  )0;
        sqlstm.sqindv[3] = (         short *)0;
        sqlstm.sqinds[3] = (         int  )0;
        sqlstm.sqharm[3] = (unsigned long )0;
        sqlstm.sqadto[3] = (unsigned short )0;
        sqlstm.sqtdso[3] = (unsigned short )0;
        sqlstm.sqhstv[4] = (unsigned char  *)(tmpInfo.mobilephone);
        sqlstm.sqhstl[4] = (unsigned long )64;
        sqlstm.sqhsts[4] = (         int  )0;
        sqlstm.sqindv[4] = (         short *)0;
        sqlstm.sqinds[4] = (         int  )0;
        sqlstm.sqharm[4] = (unsigned long )0;
        sqlstm.sqadto[4] = (unsigned short )0;
        sqlstm.sqtdso[4] = (unsigned short )0;
        sqlstm.sqhstv[5] = (unsigned char  *)&(tmpInfo.sex);
        sqlstm.sqhstl[5] = (unsigned long )sizeof(short);
        sqlstm.sqhsts[5] = (         int  )0;
        sqlstm.sqindv[5] = (         short *)0;
        sqlstm.sqinds[5] = (         int  )0;
        sqlstm.sqharm[5] = (unsigned long )0;
        sqlstm.sqadto[5] = (unsigned short )0;
        sqlstm.sqtdso[5] = (unsigned short )0;
        sqlstm.sqhstv[6] = (unsigned char  *)(tmpInfo.accountId);
        sqlstm.sqhstl[6] = (unsigned long )64;
        sqlstm.sqhsts[6] = (         int  )0;
        sqlstm.sqindv[6] = (         short *)0;
        sqlstm.sqinds[6] = (         int  )0;
        sqlstm.sqharm[6] = (unsigned long )0;
        sqlstm.sqadto[6] = (unsigned short )0;
        sqlstm.sqtdso[6] = (unsigned short )0;
        sqlstm.sqphsv = sqlstm.sqhstv;
        sqlstm.sqphsl = sqlstm.sqhstl;
        sqlstm.sqphss = sqlstm.sqhsts;
        sqlstm.sqpind = sqlstm.sqindv;
        sqlstm.sqpins = sqlstm.sqinds;
        sqlstm.sqparm = sqlstm.sqharm;
        sqlstm.sqparc = sqlstm.sqharc;
        sqlstm.sqpadto = sqlstm.sqadto;
        sqlstm.sqptdso = sqlstm.sqtdso;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    }


    checksqlcode("select JMaccount");

    strcpy(info->uuid,tmpInfo.uuid);
    strcpy(info->accountId,tmpInfo.accountId);
    strcpy(info->pwd,tmpInfo.pwd);
    strcpy(info->name,tmpInfo.name);
    strcpy(info->email,tmpInfo.email);
    strcpy(info->mobilephone,tmpInfo.mobilephone);
    info->sex = tmpInfo.sex;

    return sqlca.sqlcode;
}




int main_sql()
{

    int ret = 0;//c语言语法
    //printf("serversid = %s \n", serversid);

    cout << "serversid:" << serversid << endl;

    //连接数据库 嵌入式 sql语言中 使用 宿主变量使用 :
    /* EXEC SQL connect : serversid; */

    {
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 8;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )10;
        sqlstm.offset = (unsigned int  )183;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (unsigned char  *)serversid;
        sqlstm.sqhstl[0] = (unsigned long )0;
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         short *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned long )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqphsv = sqlstm.sqhstv;
        sqlstm.sqphsl = sqlstm.sqhstl;
        sqlstm.sqphss = sqlstm.sqhsts;
        sqlstm.sqpind = sqlstm.sqindv;
        sqlstm.sqpins = sqlstm.sqinds;
        sqlstm.sqparm = sqlstm.sqharm;
        sqlstm.sqparc = sqlstm.sqharc;
        sqlstm.sqpadto = sqlstm.sqadto;
        sqlstm.sqptdso = sqlstm.sqtdso;
        sqlstm.sqlcmax = (unsigned int )100;
        sqlstm.sqlcmin = (unsigned int )2;
        sqlstm.sqlcincr = (unsigned int )1;
        sqlstm.sqlctimeout = (unsigned int )0;
        sqlstm.sqlcnowait = (unsigned int )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    }


    checksqlcode("connect");

    //宿主变量赋值   如何在 sql 语言使用 宿主变量 :
    deptno = 50;
    strcpy(dname,"60dname");
    strcpy(loc,"60loc");

    /*

   //插入数据 - 曾

   EXEC SQL insert into dept(deptno,dname,loc) values(:deptno,:dname,:loc);
   checksqlcode("insert");
   EXEC SQL commit;



   printf("any key continue , update \n");
   printf("please enter you loc:");
   // 修改数据  - 改


   scanf_s("%s",&loc,20);
   EXEC SQL update dept set loc=:loc where deptno=:deptno;
   checksqlcode("update");
   EXEC SQL commit;


   //数据删除 - 删
   printf("any key continue , delete \n");
   ch = getchar();
   ch = getchar();

   EXEC SQL delete dept where deptno=:deptno;
   checksqlcode("delete");
   EXEC SQL commit;

   */

    // 获取数据 - 查
    printf("any key continue , select \n");
    ch = getchar();


    /* EXEC SQL select deptno, dname, loc into :deptno3, :dname3, :loc3 from dept where deptno = :deptno; */

    {
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 8;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.stmt = "select deptno ,dname ,loc into :b0,:b1,:b2  from dept wh\
ere deptno=:b3";
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )214;
        sqlstm.selerr = (unsigned short)1;
        sqlstm.sqlpfmem = (unsigned int  )0;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (unsigned char  *)&deptno3;
        sqlstm.sqhstl[0] = (unsigned long )sizeof(int);
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         short *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned long )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqhstv[1] = (unsigned char  *)&dname3;
        sqlstm.sqhstl[1] = (unsigned long )22;
        sqlstm.sqhsts[1] = (         int  )0;
        sqlstm.sqindv[1] = (         short *)0;
        sqlstm.sqinds[1] = (         int  )0;
        sqlstm.sqharm[1] = (unsigned long )0;
        sqlstm.sqadto[1] = (unsigned short )0;
        sqlstm.sqtdso[1] = (unsigned short )0;
        sqlstm.sqhstv[2] = (unsigned char  *)&loc3;
        sqlstm.sqhstl[2] = (unsigned long )22;
        sqlstm.sqhsts[2] = (         int  )0;
        sqlstm.sqindv[2] = (         short *)0;
        sqlstm.sqinds[2] = (         int  )0;
        sqlstm.sqharm[2] = (unsigned long )0;
        sqlstm.sqadto[2] = (unsigned short )0;
        sqlstm.sqtdso[2] = (unsigned short )0;
        sqlstm.sqhstv[3] = (unsigned char  *)&deptno;
        sqlstm.sqhstl[3] = (unsigned long )sizeof(int);
        sqlstm.sqhsts[3] = (         int  )0;
        sqlstm.sqindv[3] = (         short *)0;
        sqlstm.sqinds[3] = (         int  )0;
        sqlstm.sqharm[3] = (unsigned long )0;
        sqlstm.sqadto[3] = (unsigned short )0;
        sqlstm.sqtdso[3] = (unsigned short )0;
        sqlstm.sqphsv = sqlstm.sqhstv;
        sqlstm.sqphsl = sqlstm.sqhstl;
        sqlstm.sqphss = sqlstm.sqhsts;
        sqlstm.sqpind = sqlstm.sqindv;
        sqlstm.sqpins = sqlstm.sqinds;
        sqlstm.sqparm = sqlstm.sqharm;
        sqlstm.sqparc = sqlstm.sqharc;
        sqlstm.sqpadto = sqlstm.sqadto;
        sqlstm.sqptdso = sqlstm.sqtdso;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    }


    checksqlcode("select");
    printf("select : deptno2 = %d , dname2 = %s , loc2 = %s . \n",deptno3,dname3.arr,loc3.arr);




    printf("any key continue , quit \n");
    ch = getchar();

    /* EXEC SQL commit work release; */

    {
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 13;
        sqlstm.arrsiz = 8;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )245;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    }


    printf("hello... ");



    return ret;
}



#endif //GAMESERVER_SQLOP_H
