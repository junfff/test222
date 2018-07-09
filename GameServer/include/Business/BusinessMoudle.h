/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：Businessmoudle.h
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年07月09日 16:04(Monday) 
 *   描    述：
 *
 ================================================================*/


#pragma once
#include "IBusiness.h"

int bus_len;
extern IBusiness *bus_set;//声明

void Business_Init();
void Business_Deinit();
int Business_Process(int id,char *buf);
