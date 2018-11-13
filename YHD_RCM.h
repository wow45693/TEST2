/******************************************************************************
*																			  *
* Copyright (C) 2018 YiHuaTimeTechnology                                      *
*                                                                             *
* YHD_RCM.h     YH 退卡器驱动接口头文件										  *
*               Version 1.0  --  2018.10.29                                   *
*                                                                             *
******************************************************************************/

#ifndef YHD_RCM_H
#define YHD_RCM_H

#include "YHD_Common.h"


// 退卡器RCM接口版本
#define YHD_VER_RCM									"1.0"

// 设备类别
#define YHD_DEV_CLASS_RCM							"RCM"		// 退卡器

// 支持的最大卡槽数
#define YHD_RCM_SLOT_MAX_NUM						(5)			// 最大卡槽数

// 卡槽信息最大长度
#define YHD_RCM_SLOTINFO_MAX_LENGTH					(64)		// 最大长度

// 卡槽槽位
#define YHD_RCM_SLOTNUM_1							(1)			// 卡槽1
#define YHD_RCM_SLOTNUM_2							(2)			// 卡槽2
#define YHD_RCM_SLOTNUM_3							(3)			// 卡槽3
#define YHD_RCM_SLOTNUM_4							(4)			// 卡槽4
#define YHD_RCM_SLOTNUM_5							(5)			// 卡槽5
#define YHD_RCM_SLOTNUM_END							(15)		// 永吞卡槽

// 槽位状态
#define YHD_RCM_SLOT_STATUS_NOTPRESENT				(0)			// 卡槽内无卡
#define YHD_RCM_SLOT_STATUS_PRESENT					(1)			// 卡槽内有卡

// 清卡状态	
#define YHD_RCM_STATUS_NOTCLEAR						(0)			// 未清卡
#define YHD_RCM_STATUS_CLEAR						(1)			// 已清卡

// 回收箱状态
#define YHD_RCM_RETAINSTATU_FULL					(1)			// 回收箱满
#define YHD_RCM_RETAINSTATU_HIGH					(2)			// 回收箱High
#define YHD_RCM_RETAINSTATU_OK						(3)			// 回收箱状态正常
#define YHD_RCM_RETAINSTATU_MISSING					(4)			// 回收箱不在位

#pragma pack(push,1)

// 退卡器状态结构体
typedef struct tagRCMStatus
{ 
	int		iDataSize;										// 状态信息结构体大小
	int		iDevStatus;										// 硬件设备的状态，具体取值参考YHD_DEVSTA_***
	int		iSlotStatus[YHD_RCM_SLOT_MAX_NUM];				// 卡槽状态, 具体取值参考YHD_RCM_SLOT_STATUS_***
	int		iRetainBinStatus;								// 回收箱状态，具体值参考宏YHD_RCM_RETAINSTATU_***
	int		iClearCardStatus;								// 清卡状态，具体值参考庞YHD_RCM_STATUS_***
	int		iSlotPosition;									// 卡槽位置, 具体取值参故事YHD_RCM_SLOT_***

	tagRCMStatus()
	{
		memset(this, 0x00, sizeof(*this));
		iDataSize = sizeof(*this);
	}
}DRCMStatus, *LPDRCMStatus; 

// 卡槽信息结构体
typedef struct tagRCMSlotInfo
{
	int iSlotStatu;											// 卡槽状态 具体取值参考YHD_RCM_SLOT_STATUS_***
	char szSlotInfo[YHD_RCM_SLOTINFO_MAX_LENGTH];			// 卡槽信息

	tagRCMSlotInfo()
	{
		memset(this, 0x00, sizeof(tagRCMSlotInfo));
	}
}DRCMSlotInfo, *LPDRCMSlotInfo;

#pragma pack(pop)

#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////////////////////////
///////////////				退卡器接口命令			//////////////////////
//////////////////////////////////////////////////////////////////////////

// 功能：查设备状态
// 参数：
//	 - dHandle：In，操作设备唯一设备句柄
//	 - lpStatus：In，设备状态信息机构体
// 返回：
//	 - int: Out，YHD_SUCCESS表示成功，其它表示失败
int  YHD_RCM_GetStatus(DHANDLE dHandle, LPDRCMStatus lpStatus);

// 功能：复位设备
// 参数：
//	 - dHandle：In，操作设备唯一设备句柄
// 返回：
//	 - int: Out，YHD_SUCCESS表示成功，其它表示失败
int	 YHD_RCM_Reset(DHANDLE dHandle);

// 功能：准备指定槽位的卡槽
// 参数：
//	  - dHandle：In，操作设备唯一设备句柄
//	  - iSlotNum：In，指定的卡槽槽位，具体取值参考YHD_RCM_SLOTNUM_***
// 返回：
//	 - int: Out，YHD_SUCCESS表示成功，其它表示失败
int YHD_RCM_PrepareSlot(DHANDLE dHandle, int iSlotNum);

// 功能：吞卡
// 参数：
//	  - dHandle：In，操作设备唯一设备句柄
// 返回：
//	 - int: Out，YHD_SUCCESS表示成功，其它表示失败
int YHD_RCM_Retain(DHANDLE dHandle);

// 功能：异步退卡
// 参数：
//	  - dHandle：In，操作设备唯一设备句柄
// 返回：
//	 - int: Out，YHD_SUCCESS表示成功，其它表示失败
int YHD_RCM_Eject(DHANDLE dHandle);

// 功能：设置指定一个卡槽的信息
// 参数：
//	  - dHandle：In，操作设备唯一设备句柄
//	  - dSlotInfo：In，卡槽信息
//	  - iCount：In，卡槽个数
// 返回：
//	 - int: Out，YHD_SUCCESS表示成功，其它表示失败
int YHD_RCM_SetSlotInfo(DHANDLE dHandle, const DRCMSlotInfo dSlotInfo[YHD_RCM_SLOT_MAX_NUM], int iCount);

// 功能：获取所有卡槽信息
// 参数：
//	  - dHandle：In，操作设备唯一设备句柄
//	  - dSlotInfo：Out，卡槽信息
//	  - rCount：Out，卡槽个数
// 返回：
//	 - int: Out，YHD_SUCCESS表示成功，其它表示失败
int YHD_RCM_GetSlotInfo(DHANDLE dHandle, DRCMSlotInfo dSlotInfo[YHD_RCM_SLOT_MAX_NUM], int& rCount);

#ifdef __cplusplus
}       /*extern "C"*/
#endif

#endif