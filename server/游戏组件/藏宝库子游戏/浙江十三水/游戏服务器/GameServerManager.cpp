#include "StdAfx.h"
#include "Resource.h"
#include "Tableframesink.h"
#include "GameServerManager.h"
#include "..\消息定义\CMD_Thirteen.h"

//////////////////////////////////////////////////////////////////////////
//机器定义
#define ANDROID_SERVICE_DLL_NAME	TEXT("ThirteenZJAndroid.dll")	//组件名字

//////////////////////////////////////////////////////////////////////////

//构造函数
CGameServiceManager::CGameServiceManager(void)
{
	//控件变量
	m_pDlgCustomRule=NULL;

	//内核属性
	m_GameServiceAttrib.wKindID=KIND_ID;
	m_GameServiceAttrib.wChairCount=GAME_PLAYER;
	m_GameServiceAttrib.wSupporType=(GAME_GENRE_GOLD|GAME_GENRE_SCORE|GAME_GENRE_MATCH|GAME_GENRE_EDUCATE|GAME_GENRE_PERSONAL);

	//功能标志
	m_GameServiceAttrib.cbDynamicJoin=TRUE;
	m_GameServiceAttrib.cbAndroidUser=TRUE;
	m_GameServiceAttrib.cbOffLineTrustee = TRUE;

	//服务属性
	m_GameServiceAttrib.dwServerVersion=VERSION_SERVER;
	m_GameServiceAttrib.dwClientVersion=VERSION_CLIENT;
	
	lstrcpyn(m_GameServiceAttrib.szGameName,GAME_NAME,CountArray(m_GameServiceAttrib.szGameName));
	lstrcpyn(m_GameServiceAttrib.szClientEXEName,TEXT("ThirteenZJ.EXE"),CountArray(m_GameServiceAttrib.szClientEXEName));
	lstrcpyn(m_GameServiceAttrib.szServerDLLName,TEXT("ThirteenZJServer.DLL"),CountArray(m_GameServiceAttrib.szServerDLLName));
	
	return;
}

//析构函数
CGameServiceManager::~CGameServiceManager(void)
{
	SafeDelete(m_pDlgCustomRule);
}

//接口查询
VOID * CGameServiceManager::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IGameServiceManager,Guid,dwQueryVer);
	QUERYINTERFACE(IGameServiceCustomRule,Guid,dwQueryVer);
	//QUERYINTERFACE(IGameServicePersonalRule, Guid, dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IGameServiceManager,Guid,dwQueryVer);

	return NULL;
}

//创建游戏桌
VOID * CGameServiceManager::CreateTableFrameSink(REFGUID Guid, DWORD dwQueryVer)
{
	//建立对象
	CTableFrameSink * pTableFrameSink=NULL;
	try
	{
		pTableFrameSink=new CTableFrameSink();
		if (pTableFrameSink==NULL) throw TEXT("创建失败");
		void * pObject=pTableFrameSink->QueryInterface(Guid,dwQueryVer);
		if (pObject==NULL) throw TEXT("接口查询失败");
		return pObject;
	}
	catch (...) {}

	//清理对象
	SafeDelete(pTableFrameSink);

	return NULL;
}

//创建机器
VOID * CGameServiceManager::CreateAndroidUserItemSink(REFGUID Guid, DWORD dwQueryVer)
{
	try
	{
		//加载模块
		if (m_hDllInstance==NULL)
		{
			m_hDllInstance=AfxLoadLibrary(ANDROID_SERVICE_DLL_NAME);
			if (m_hDllInstance==NULL) throw TEXT("机器人服务模块不存在");
		}

		//寻找函数
		ModuleCreateProc * CreateProc=(ModuleCreateProc *)GetProcAddress(m_hDllInstance,"CreateAndroidUserItemSink");
		if (CreateProc==NULL) throw TEXT("机器人服务模块组件不合法");

		//创建组件
		return CreateProc(Guid,dwQueryVer);
	}
	catch(...) {}
	return NULL;
}

//创建数据
VOID * CGameServiceManager::CreateGameDataBaseEngineSink(REFGUID Guid, DWORD dwQueryVer)
{
	return NULL;
}
//获取属性
bool CGameServiceManager::GetServiceAttrib(tagGameServiceAttrib & GameServiceAttrib)
{
	GameServiceAttrib=m_GameServiceAttrib;
	return true;
}

//参数修改
bool CGameServiceManager::RectifyParameter(tagGameServiceOption & GameServiceOption)
{
	//效验参数
	ASSERT(&GameServiceOption!=NULL);
	if (&GameServiceOption==NULL) return false;

	//积分调整
	GameServiceOption.lCellScore=__max(1L,GameServiceOption.lCellScore);

	//金币房间
	//金币游戏
	if (GameServiceOption.wServerType&(GAME_GENRE_GOLD|SCORE_GENRE_POSITIVE))
	{
		GameServiceOption.lMinTableScore=__max(GameServiceOption.lCellScore*36,GameServiceOption.lMinTableScore);
	}

	//积分上限
	if (GameServiceOption.lRestrictScore!=0L)
	{
		GameServiceOption.lRestrictScore=__max(GameServiceOption.lRestrictScore,GameServiceOption.lMinTableScore);
	}

	//积分下限
	if (GameServiceOption.wServerType&GAME_GENRE_PERSONAL)
	{
		GameServiceOption.lMinTableScore=__max((LONGLONG)(GameServiceOption.lCellScore*108*3),GameServiceOption.lMinTableScore);
	}
	
	return true;
}

//获取配置
bool CGameServiceManager::SaveCustomRule(LPBYTE pcbCustomRule, WORD wCustonSize)
{
	//效验状态
	ASSERT(m_pDlgCustomRule!=NULL);
	if (m_pDlgCustomRule==NULL) return false;

	//变量定义
	ASSERT(wCustonSize>=sizeof(tagCustomRule));
	tagCustomRule * pCustomRule=(tagCustomRule *)pcbCustomRule;

	//获取配置
	if (m_pDlgCustomRule->GetCustomRule(*pCustomRule)==false)
	{
		return false;
	}

	return true;
}

//默认配置
bool CGameServiceManager::DefaultCustomRule(LPBYTE pcbCustomRule, WORD wCustonSize)
{
	//变量定义
	ASSERT(wCustonSize>=sizeof(tagCustomRule));
	tagCustomRule * pCustomRule=(tagCustomRule *)pcbCustomRule;

	//设置变量
	pCustomRule->cbTimeStartGame=30;
	pCustomRule->cbTimeCallBanker=20;
	pCustomRule->cbTimeSetChip=20;
	pCustomRule->cbTimeRangeCard=60;
	pCustomRule->cbTimeShowCard=10;

	pCustomRule->lRoomStorageStart = 1000;
	pCustomRule->lRoomStorageMax1 = 2000;
	pCustomRule->lRoomStorageMax2 = 5000;
	pCustomRule->lRoomStorageMul1 = 40;
	pCustomRule->lRoomStorageMul2 = 60;
	pCustomRule->lRoomStorageDeduct = 0;
	
	pCustomRule->lRobotBankGet = 1000;
	pCustomRule->lRobotBankGetBanker = 5000;
	pCustomRule->lRobotBankStoMul = 10;
	pCustomRule->lRobotScoreMin = 1000;
	pCustomRule->lRobotScoreMax = 10000;

	pCustomRule->bHaveBanker = false;
	pCustomRule->cbPlayerCount = 4;
	pCustomRule->cbMaCard = 0;
	pCustomRule->cbTongHuaMode = 0;
	return true;
}

//创建窗口
HWND CGameServiceManager::CreateCustomRule(CWnd * pParentWnd, CRect rcCreate, LPBYTE pcbCustomRule, WORD wCustonSize)
{
	//创建窗口
	if (m_pDlgCustomRule==NULL)
	{
		m_pDlgCustomRule=new CDlgCustomRule;
	}

	//创建窗口
	if (m_pDlgCustomRule->m_hWnd==NULL)
	{
		//设置资源
		AfxSetResourceHandle(GetModuleHandle(m_GameServiceAttrib.szServerDLLName));

		//创建窗口
		m_pDlgCustomRule->Create(IDD_CUSTOM_RULE,pParentWnd);

		//还原资源
		AfxSetResourceHandle(GetModuleHandle(NULL));
	}

	//设置变量
	ASSERT(wCustonSize>=sizeof(tagCustomRule));
	m_pDlgCustomRule->SetCustomRule(*((tagCustomRule *)pcbCustomRule));

	//显示窗口
	m_pDlgCustomRule->SetWindowPos(NULL,rcCreate.left,rcCreate.top,rcCreate.Width(),rcCreate.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);

	return m_pDlgCustomRule->GetSafeHwnd();
	return NULL;
}
//获取配置
bool CGameServiceManager::SavePersonalRule(LPBYTE pcbPersonalRule, WORD wPersonalSize)
{
	//效验状态
	ASSERT(m_pDlgPersonalRule != NULL);
	if (m_pDlgPersonalRule == NULL) return false;

	//变量定义
	ASSERT(wPersonalSize >= sizeof(tagPersonalRule));
	tagPersonalRule * pPersonalRule = (tagPersonalRule *)pcbPersonalRule;

	//获取配置
	if (m_pDlgPersonalRule->GetPersonalRule(*pPersonalRule) == false)
	{
		return false;
	}

	return true;
}

//默认配置
bool CGameServiceManager::DefaultPersonalRule(LPBYTE pcbPersonalRule, WORD wPersonalSize)
{

	return true;
}

//创建窗口
HWND CGameServiceManager::CreatePersonalRule(CWnd * pParentWnd, CRect rcCreate, LPBYTE pcbPersonalRule, WORD wPersonalSize)
{
	//创建窗口
	if (m_pDlgPersonalRule == NULL)
	{
		m_pDlgPersonalRule = new CDlgPersonalRule;
	}

	//创建窗口
	if (m_pDlgPersonalRule->m_hWnd == NULL)
	{
		//设置资源
		AfxSetResourceHandle(GetModuleHandle(m_GameServiceAttrib.szServerDLLName));

		//创建窗口
		m_pDlgPersonalRule->Create(IDD_PERSONAL_RULE, pParentWnd);

		//还原资源
		AfxSetResourceHandle(GetModuleHandle(NULL));
	}

	//设置变量
	ASSERT(wPersonalSize >= sizeof(tagPersonalRule));
	m_pDlgPersonalRule->SetPersonalRule(*((tagPersonalRule *)pcbPersonalRule));

	//显示窗口
	m_pDlgPersonalRule->SetWindowPos(NULL, rcCreate.left, rcCreate.top, rcCreate.Width(), rcCreate.Height(), SWP_NOZORDER | SWP_SHOWWINDOW);

	return m_pDlgPersonalRule->GetSafeHwnd();
}
//////////////////////////////////////////////////////////////////////////////////

//建立对象函数
extern "C" __declspec(dllexport) VOID * CreateGameServiceManager(const GUID & Guid, DWORD dwInterfaceVer)
{
	static CGameServiceManager GameServiceManager;
	return GameServiceManager.QueryInterface(Guid,dwInterfaceVer);
}

//////////////////////////////////////////////////////////////////////////
