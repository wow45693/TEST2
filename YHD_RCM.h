/******************************************************************************
*																			  *
* Copyright (C) 2018 YiHuaTimeTechnology                                      *
*                                                                             *
* YHD_RCM.h     YH �˿��������ӿ�ͷ�ļ�										  *
*               Version 1.0  --  2018.10.29                                   *
*                                                                             *
******************************************************************************/

#ifndef YHD_RCM_H
#define YHD_RCM_H

#include "YHD_Common.h"


// �˿���RCM�ӿڰ汾
#define YHD_VER_RCM									"1.0"

// �豸���
#define YHD_DEV_CLASS_RCM							"RCM"		// �˿���

// ֧�ֵ���󿨲���
#define YHD_RCM_SLOT_MAX_NUM						(5)			// ��󿨲���

// ������Ϣ��󳤶�
#define YHD_RCM_SLOTINFO_MAX_LENGTH					(64)		// ��󳤶�

// ���۲�λ
#define YHD_RCM_SLOTNUM_1							(1)			// ����1
#define YHD_RCM_SLOTNUM_2							(2)			// ����2
#define YHD_RCM_SLOTNUM_3							(3)			// ����3
#define YHD_RCM_SLOTNUM_4							(4)			// ����4
#define YHD_RCM_SLOTNUM_5							(5)			// ����5
#define YHD_RCM_SLOTNUM_END							(15)		// ���̿���

// ��λ״̬
#define YHD_RCM_SLOT_STATUS_NOTPRESENT				(0)			// �������޿�
#define YHD_RCM_SLOT_STATUS_PRESENT					(1)			// �������п�

// �忨״̬	
#define YHD_RCM_STATUS_NOTCLEAR						(0)			// δ�忨
#define YHD_RCM_STATUS_CLEAR						(1)			// ���忨

// ������״̬
#define YHD_RCM_RETAINSTATU_FULL					(1)			// ��������
#define YHD_RCM_RETAINSTATU_HIGH					(2)			// ������High
#define YHD_RCM_RETAINSTATU_OK						(3)			// ������״̬����
#define YHD_RCM_RETAINSTATU_MISSING					(4)			// �����䲻��λ

#pragma pack(push,1)

// �˿���״̬�ṹ��
typedef struct tagRCMStatus
{ 
	int		iDataSize;										// ״̬��Ϣ�ṹ���С
	int		iDevStatus;										// Ӳ���豸��״̬������ȡֵ�ο�YHD_DEVSTA_***
	int		iSlotStatus[YHD_RCM_SLOT_MAX_NUM];				// ����״̬, ����ȡֵ�ο�YHD_RCM_SLOT_STATUS_***
	int		iRetainBinStatus;								// ������״̬������ֵ�ο���YHD_RCM_RETAINSTATU_***
	int		iClearCardStatus;								// �忨״̬������ֵ�ο���YHD_RCM_STATUS_***
	int		iSlotPosition;									// ����λ��, ����ȡֵ�ι���YHD_RCM_SLOT_***

	tagRCMStatus()
	{
		memset(this, 0x00, sizeof(*this));
		iDataSize = sizeof(*this);
	}
}DRCMStatus, *LPDRCMStatus; 

// ������Ϣ�ṹ��
typedef struct tagRCMSlotInfo
{
	int iSlotStatu;											// ����״̬ ����ȡֵ�ο�YHD_RCM_SLOT_STATUS_***
	char szSlotInfo[YHD_RCM_SLOTINFO_MAX_LENGTH];			// ������Ϣ

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
///////////////				�˿����ӿ�����			//////////////////////
//////////////////////////////////////////////////////////////////////////

// ���ܣ����豸״̬
// ������
//	 - dHandle��In�������豸Ψһ�豸���
//	 - lpStatus��In���豸״̬��Ϣ������
// ���أ�
//	 - int: Out��YHD_SUCCESS��ʾ�ɹ���������ʾʧ��
int  YHD_RCM_GetStatus(DHANDLE dHandle, LPDRCMStatus lpStatus);

// ���ܣ���λ�豸
// ������
//	 - dHandle��In�������豸Ψһ�豸���
// ���أ�
//	 - int: Out��YHD_SUCCESS��ʾ�ɹ���������ʾʧ��
int	 YHD_RCM_Reset(DHANDLE dHandle);

// ���ܣ�׼��ָ����λ�Ŀ���
// ������
//	  - dHandle��In�������豸Ψһ�豸���
//	  - iSlotNum��In��ָ���Ŀ��۲�λ������ȡֵ�ο�YHD_RCM_SLOTNUM_***
// ���أ�
//	 - int: Out��YHD_SUCCESS��ʾ�ɹ���������ʾʧ��
int YHD_RCM_PrepareSlot(DHANDLE dHandle, int iSlotNum);

// ���ܣ��̿�
// ������
//	  - dHandle��In�������豸Ψһ�豸���
// ���أ�
//	 - int: Out��YHD_SUCCESS��ʾ�ɹ���������ʾʧ��
int YHD_RCM_Retain(DHANDLE dHandle);

// ���ܣ��첽�˿�
// ������
//	  - dHandle��In�������豸Ψһ�豸���
// ���أ�
//	 - int: Out��YHD_SUCCESS��ʾ�ɹ���������ʾʧ��
int YHD_RCM_Eject(DHANDLE dHandle);

// ���ܣ�����ָ��һ�����۵���Ϣ
// ������
//	  - dHandle��In�������豸Ψһ�豸���
//	  - dSlotInfo��In��������Ϣ
//	  - iCount��In�����۸���
// ���أ�
//	 - int: Out��YHD_SUCCESS��ʾ�ɹ���������ʾʧ��
int YHD_RCM_SetSlotInfo(DHANDLE dHandle, const DRCMSlotInfo dSlotInfo[YHD_RCM_SLOT_MAX_NUM], int iCount);

// ���ܣ���ȡ���п�����Ϣ
// ������
//	  - dHandle��In�������豸Ψһ�豸���
//	  - dSlotInfo��Out��������Ϣ
//	  - rCount��Out�����۸���
// ���أ�
//	 - int: Out��YHD_SUCCESS��ʾ�ɹ���������ʾʧ��
int YHD_RCM_GetSlotInfo(DHANDLE dHandle, DRCMSlotInfo dSlotInfo[YHD_RCM_SLOT_MAX_NUM], int& rCount);

#ifdef __cplusplus
}       /*extern "C"*/
#endif

#endif