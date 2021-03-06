//! @author: Kang Lin(kl222@126.com)

#include "PluginFactoryFreeRdp.h"
#include <QDebug>
#include <QApplication>
#include "RabbitCommonDir.h"
#include "ConnecterFreeRdp.h"

CPluginFactoryFreeRdp::CPluginFactoryFreeRdp(QObject *parent)
    : CPluginFactory(parent)
{
#if defined (_DEBUG) || !defined(BUILD_SHARED_LIBS)
    Q_INIT_RESOURCE(translations_FreeRdp);
#endif

    QString szTranslatorFile = RabbitCommon::CDir::Instance()->GetDirTranslations()
            + "/FreeRdp_" + QLocale::system().name() + ".qm";
    if(!m_Translator.load(szTranslatorFile))
        qCritical() << "Open translator file fail:" << szTranslatorFile;
    qApp->installTranslator(&m_Translator);
}

CPluginFactoryFreeRdp::~CPluginFactoryFreeRdp()
{
    qApp->removeTranslator(&m_Translator);
    qDebug() << "CPluginFactoryFreeRdp::~CPluginFactoryFreeRdp()";
#if defined (_DEBUG) || !defined(BUILD_SHARED_LIBS)
    Q_INIT_RESOURCE(translations_FreeRdp);
#endif
}

const QString CPluginFactoryFreeRdp::Name() const
{
    return "FreeRdp";
}

const QString CPluginFactoryFreeRdp::Description() const
{
    return tr("RDP(Windows remote desktop protol): Access remote desktops such as windows.");
}

const QString CPluginFactoryFreeRdp::Protol() const
{
    return "RDP";
}

const QIcon CPluginFactoryFreeRdp::Icon() const
{
    return QIcon(":/image/Windows");
}

CConnecter* CPluginFactoryFreeRdp::CreateConnecter(const QString &szProtol)
{
    if(Id() == szProtol)
    {   
        return new CConnecterFreeRdp(this);
    }
    return nullptr;
}
