#pragma once

//////////////////////////////////////////////////////////////////////////////////

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif

#ifndef WINVER
#define WINVER 0x0501
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0501
#endif

#ifndef _WIN32_IE
#define _WIN32_IE 0x0501
#endif

#define _ATL_ATTRIBUTES
#define _AFX_ALL_WARNINGS
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS

//////////////////////////////////////////////////////////////////////////////////

//MFC 文件
#include <AfxWin.h>
#include <AfxExt.h>
#include <AfxCmn.h>
#include <AfxDisp.h>

//////////////////////////////////////////////////////////////////////////////////

//组件头文件
#include "..\..\..\SDKCondition.h"

#ifdef SDK_CONDITION

//////////////////////////////////////////////////////////////////////////////////
//开发环境
#include "..\..\..\开发库\Include\GameServiceHead.h"

//////////////////////////////////////////////////////////////////////////////////
//链接代码
//
#ifndef _DEBUG
#ifndef _UNICODE
#pragma comment (lib,"../../../开发库/lib/Ansi/KernelEngine.lib")
#else
#pragma comment (lib,"../../../开发库/lib/Unicode/KernelEngine.lib")
#endif
#else
#ifndef _UNICODE
#pragma comment (lib,"../../../开发库/lib/Ansi/KernelEngineD.lib")
#else
#pragma comment (lib,"../../../开发库/lib/Unicode/KernelEngineD.lib")
#endif
#endif

//////////////////////////////////////////////////////////////////////////////////

#else

//////////////////////////////////////////////////////////////////////////////////
//系统环境

#include "..\..\..\..\系统模块\服务器组件\游戏服务\GameServiceHead.h"

#ifndef _DEBUG
#ifndef _UNICODE
#pragma comment (lib,"../../../../系统模块/链接库/Ansi/KernelEngine.lib")
#else
#pragma comment (lib,"../../../../系统模块/链接库/Unicode/KernelEngine.lib")
#endif
#else
#ifndef _UNICODE
#pragma comment (lib,"../../../../系统模块/链接库/Ansi/KernelEngineD.lib")
#else
#pragma comment (lib,"../../../../系统模块/链接库/Unicode/KernelEngineD.lib")
#endif
#endif

//////////////////////////////////////////////////////////////////////////////////

#endif


// 消息头
#include "..\消息定义\CMD_Game.h"
#include "..\消息定义\DebugHead.h"

#ifndef _UNICODE
	#error "本程序不支持多字节版本，必须使用Unicode版本编译。"
#endif
	