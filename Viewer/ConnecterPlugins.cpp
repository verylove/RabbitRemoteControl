#include "ConnecterPlugins.h"
#include <QDebug>
#include "ConnectThread.h"
#include "RabbitCommonLog.h"

CConnecterPlugins::CConnecterPlugins(CPluginFactory *parent)
    : CConnecter(parent),
      m_bExit(false),
      m_pThread(nullptr)
{}

CConnecterPlugins::~CConnecterPlugins()
{
    if(m_pThread)
    {
        m_pThread->wait();
        delete m_pThread;
    }
    qDebug() << this << this->metaObject()->className();
}

int CConnecterPlugins::OnRun()
{
    //LOG_MODEL_DEBUG("CConnecterBackThread", "Current thread: 0x%X", QThread::currentThreadId());
    int nRet = -1;
    CConnect* pConnect = InstanceConnect();
    
    do{
        CConnect* pConnect = InstanceConnect();
        if(nullptr == pConnect) break;
        
        nRet = pConnect->Initialize();
        if(nRet) break;
        
        nRet = pConnect->Connect();
        if(nRet) break;
        
        while (!m_bExit) {
            try {
                // 0 : continue
                // 1: exit
                // < 0: error
                nRet = pConnect->Process();
                if(nRet) break;
            }  catch (...) {
                LOG_MODEL_ERROR("ConnecterBackThread", "process fail:%d", nRet);
                break;
            }
        }
        
    }while (0);

    emit sigDisconnected();

    pConnect->Clean();
    delete pConnect;
    qDebug() << "CConnecterPlugins::OnRun() end";
    return nRet;
}

int CConnecterPlugins::Connect()
{
    int nRet = 0;
    m_pThread = new CConnectThread(this);
    if(m_pThread)
        m_pThread->start();
    
    nRet = OnConnect();
    return nRet;
}

int CConnecterPlugins::DisConnect()
{
    int nRet = 0;
    m_bExit = true;
    nRet = OnDisConnect();
    
    return nRet;
}

int CConnecterPlugins::OnConnect()
{
    return 0;
}

int CConnecterPlugins::OnDisConnect()
{
    emit sigDisconnected();
    return 0;
}
