// Base.cpp : һ��TCP�Ĳ�����
//����PurenessScopeServer�Ĳ��Ժ�ʹ��
//add by freeeyes
//2011-09-20

#include "BaseCommand.h"
#include "IObject.h"

static const char *g_szDesc      = "XML����ģ��";       //ģ�����������
static const char *g_szName      = "XML����";           //ģ�������
static const char *g_szModuleKey = "XMLParse";          //ģ���Key

#ifdef WIN32
#ifdef TEST_TCP_BUILD_DLL
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllimport)
#endif
#else
#define DECLDIR
#endif

extern "C"
{
  DECLDIR int LoadModuleData(CServerObject* pServerObject);
  DECLDIR int UnLoadModuleData();
  DECLDIR const char* GetDesc();
  DECLDIR const char* GetName();
  DECLDIR const char* GetModuleKey();
  DECLDIR int DoModuleMessage(uint16 u2CommandID, IBuffPacket* pBuffPacket, IBuffPacket* pReturnBuffPacket);
  DECLDIR bool GetModuleState(uint32& u4ErrorID);
}

static CBaseCommand g_BaseCommand;
CServerObject*      g_pServerObject = NULL;

int LoadModuleData(CServerObject* pServerObject)
{
  g_pServerObject = pServerObject;
  OUR_DEBUG((LM_INFO, "[Base LoadModuleData] Begin.\n"));
  if(g_pServerObject != NULL)
  {
    g_BaseCommand.SetServerObject(pServerObject);	
  }
  else
  {
    OUR_DEBUG((LM_INFO, "[Base LoadModuleData] pServerObject is NULL.\n"));
  }

  IMessageManager* pMessageManager = g_pServerObject->GetMessageManager();
  if(NULL != pMessageManager)
  {
    pMessageManager->AddClientCommand(COMMAND_BASE, &g_BaseCommand, g_szName);
    pMessageManager->AddClientCommand(CLIENT_LINK_CONNECT, &g_BaseCommand, g_szName);
    pMessageManager->AddClientCommand(CLIENT_LINK_CDISCONNET, &g_BaseCommand, g_szName);
	pMessageManager->AddClientCommand(CLINET_LINK_SENDTIMEOUT, &g_BaseCommand, g_szName);
  }
  else
  {
    OUR_DEBUG((LM_INFO, "[Base LoadModuleData] pMessageManager = NULL.\n"));
  }

  //��ʾ��ܹ����߳�ID
  OUR_DEBUG((LM_INFO, "[Base LoadModuleData] *********************************.\n"));

  uint32 u4WorkThread = pMessageManager->GetWorkThreadCount();
  OUR_DEBUG((LM_INFO, "[Base LoadModuleData] WorkThreadCount=%d.\n", u4WorkThread));

  for(uint32 u4Index = 0; u4Index < u4WorkThread; u4Index++)
  {
	  OUR_DEBUG((LM_INFO, "[Base LoadModuleData] WorkThreadID=%d.\n", pMessageManager->GetWorkThreadByIndex(u4Index)));
  }

  OUR_DEBUG((LM_INFO, "[Base LoadModuleData] *********************************.\n"));
  g_BaseCommand.Init_XML();
  OUR_DEBUG((LM_INFO, "[Base LoadModuleData] End.\n"));

  return 0;
}

int UnLoadModuleData()
{
  OUR_DEBUG((LM_INFO, "[Base UnLoadModuleData] Begin.\n"));
  if(g_pServerObject != NULL)
  {
    IMessageManager* pMessageManager = g_pServerObject->GetMessageManager();
    if(NULL != pMessageManager)
    {
      pMessageManager->DelClientCommand(COMMAND_BASE, &g_BaseCommand);
      pMessageManager->DelClientCommand(CLIENT_LINK_CONNECT, &g_BaseCommand);
      pMessageManager->DelClientCommand(CLIENT_LINK_CDISCONNET, &g_BaseCommand);
	  pMessageManager->DelClientCommand(CLINET_LINK_SENDTIMEOUT, &g_BaseCommand);
      pMessageManager = NULL;
    }
  }
  OUR_DEBUG((LM_INFO, "[Base UnLoadModuleData] End.\n"));
  return 0;
}

const char* GetDesc()
{
  return g_szDesc;
}

const char* GetName()
{
  return g_szName;
}

const char* GetModuleKey()
{
  return g_szModuleKey;
}

//����ģ���ĵ��ýӿ�
int DoModuleMessage(uint16 u2CommandID, IBuffPacket* pBuffPacket, IBuffPacket* pReturnBuffPacket)
{
  return 0;
}

//�������ʹ�ã����ڿ�ܶ�ʱѲ����״̬
//Ĭ�����ﷵ��true���������Ҫ�Կ���ڲ�ϸ������ء�
//��������ʵ��֮�����ݴ���Ĳ�ͬ������false��ͬʱ������ErrorID
//��ܻ����������ã������ʼ���ָ��������
bool GetModuleState(uint32& u4ErrorID)
{
	return true;
}
