/*
* Copyright (c) 2015,郑州联睿电子科技有限公司
* All rights reserved.
* 
* 文件名称：locadef.h
* 文件标识：
* 摘    要：公司常见定义
* 
* 当前版本：0.1
* 作    者：何雪锋
* 完成日期：2015.02.24
*/

#ifndef _LOCADEF_H_
#define _LOCADEF_H_

typedef	enum
{
	LOCA_OK = 0,
	LOCA_FAULT,		//执行过程中发生错误
	LOCA_ERROR		//输入参数有误
}loca_status;

#endif