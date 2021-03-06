/*
 * Copyright (C) 2012-2013, Freescale Semiconductor, Inc. All Rights Reserved.
 * THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
 * BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
 * Freescale Semiconductor, Inc.
 *
 */

#include "stdafx.h"
#include "ExceptionHandle.h"
#include "DeviceManager.h"

IMPLEMENT_DYNCREATE(CMyExceptionHandler, CWinThread)

CMyExceptionHandler::CMyExceptionHandler()
{
	m_bAutoDelete = FALSE; //Don't destroy the object at thread termination
}

CMyExceptionHandler::~CMyExceptionHandler()
{
}

DWORD CMyExceptionHandler::Open()
{
	_hStartEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL); //Auto reset, nosignal
	if( _hStartEvent == NULL )
	{
		LogMsg(LOG_MODULE_MFGTOOL_LIB, LOG_LEVEL_FATAL_ERROR, _T("CMyExceptionHandler::Open()--Create _hStartEvent failed"));
		return MFGLIB_ERROR_NO_MEMORY;
	}
	m_hMapMsgMutex = ::CreateMutex(NULL, FALSE, NULL);
	if( m_hMapMsgMutex == NULL )
	{
		LogMsg(LOG_MODULE_MFGTOOL_LIB, LOG_LEVEL_FATAL_ERROR, _T("CMyExceptionHandler::Open()--Create m_hMapMsgMutex failed"));
		return MFGLIB_ERROR_NO_MEMORY;
	}

	DWORD dwErrCode = ERROR_SUCCESS;
	if( CreateThread() != 0 ) //create CMyExceptionHandler thread successfully
	{
		::WaitForSingleObject(_hStartEvent, INFINITE);
	}
	else //create DeviceManager thread failed
	{
		dwErrCode = GetLastError();
		LogMsg(LOG_MODULE_MFGTOOL_LIB, LOG_LEVEL_FATAL_ERROR, _T("CMyExceptionHandler::Open()--Create CMyExceptionHandler thread failed(error: %d)"), dwErrCode);
		::CloseHandle(m_hMapMsgMutex);
		::CloseHandle(_hStartEvent);
		return MFGLIB_ERROR_THREAD_CREATE_FAILED;
	}

	LogMsg(LOG_MODULE_MFGTOOL_LIB, LOG_LEVEL_NORMAL_MSG, _T("CMyExceptionHandler thread is running"));

	// clean up
	::CloseHandle(_hStartEvent);
	_hStartEvent = NULL;

	return MFGLIB_ERROR_SUCCESS;
}

void CMyExceptionHandler::Close()
{
	// Post a KILL event to kill Exception Handler thread
	PostThreadMessage(WM_MSG_EXCEPTION_EVENT, KillExceptionHandlerThread, 0);
	// Wait for the Exception Handler thread to die before returning
	WaitForSingleObject(m_hThread, INFINITE);
	
	::CloseHandle(m_hMapMsgMutex);
	m_hMapMsgMutex = NULL;
	
	LogMsg(LOG_MODULE_MFGTOOL_LIB, LOG_LEVEL_NORMAL_MSG, _T("Exception Handler thread is closed"));
	m_hThread = NULL;
}

BOOL CMyExceptionHandler::InitInstance()
{
	SetEvent(_hStartEvent);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CMyExceptionHandler, CWinThread)
    ON_THREAD_MESSAGE(WM_MSG_EXCEPTION_EVENT, OnMsgExceptionEvent)
END_MESSAGE_MAP()

void CMyExceptionHandler::OnMsgExceptionEvent(WPARAM ExceptionType, LPARAM desc)
{
	if(KillExceptionHandlerThread == ExceptionType)
	{
		PostQuitMessage(0);
		LogMsg(LOG_MODULE_MFGTOOL_LIB, LOG_LEVEL_NORMAL_MSG, _T("CMyExceptionHandler::OnMsgExceptionEvent() - KillExceptionHandlerThread"));
		return;
	}
	else
	{
		CString msg = (LPCTSTR)desc;
		BSTR bstr_msg;
		
		SysFreeString((BSTR)desc);

		Sleep(50);

		WaitForSingleObject(m_hMapMsgMutex, INFINITE);
		std::map<CString, int>::iterator it = g_pDeviceManager->mapMsg.find(msg);
		if(it == g_pDeviceManager->mapMsg.end())
		{
			LogMsg(LOG_MODULE_MFGTOOL_LIB, LOG_LEVEL_NORMAL_MSG, _T("Device remove at advance, don't need to handle this exception, just return"));
			ReleaseMutex(m_hMapMsgMutex);
			return;
		}

		switch(ExceptionType)
		{
		case DeviceArriveBeforVolumeRemove:
			LogMsg(LOG_MODULE_MFGTOOL_LIB, LOG_LEVEL_NORMAL_MSG, _T("DeviceArriveBeforVolumeRemove exception handling"));
			g_pDeviceManager->mapMsg.erase(it);
			ReleaseMutex(m_hMapMsgMutex);
			bstr_msg = msg.AllocSysString();
			g_pDeviceManager->PostThreadMessage(WM_MSG_DEV_EVENT, (WPARAM)(DeviceManager::DEVICE_ARRIVAL_EVT), (LPARAM)bstr_msg);
			break;
		case DeviceArriveButEnumFailed:
			LogMsg(LOG_MODULE_MFGTOOL_LIB, LOG_LEVEL_NORMAL_MSG, _T("DeviceArriveButEnumFailed exception handling"));
			g_pDeviceManager->mapMsg.erase(it);
			ReleaseMutex(m_hMapMsgMutex);
			bstr_msg = msg.AllocSysString();
			g_pDeviceManager->PostThreadMessage(WM_MSG_DEV_EVENT, (WPARAM)(DeviceManager::DEVICE_ARRIVAL_EVT), (LPARAM)bstr_msg);
			break;
		default:
			LogMsg(LOG_MODULE_MFGTOOL_LIB, LOG_LEVEL_NORMAL_MSG, _T("Unknown exception type"));
			ReleaseMutex(m_hMapMsgMutex);
			break;
		}
	}
}


