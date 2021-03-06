//! @author: Kang Lin(kl222@126.com)

#ifndef CCONNECTTIGERVNC_H
#define CCONNECTTIGERVNC_H

#include "Connect.h"
#include "Parameter.h"
#include "network/TcpSocket.h"
#include "rfb/CConnection.h"
#include "rfb/UserPasswdGetter.h"
#include "rfb/UserMsgBox.h"

class CConnecterTigerVnc;
class CConnectTigerVnc : public CConnect,
        public rfb::CConnection,
        public rdr::FdInStreamBlockCallback,
        public rfb::UserPasswdGetter,
        public rfb::UserMsgBox
{
    Q_OBJECT

public:
    explicit CConnectTigerVnc(CConnecterTigerVnc* pConnecter,
                              QObject *parent = nullptr);
    virtual ~CConnectTigerVnc() override;
    
    virtual int SetParamter(void *pPara) override;

public Q_SLOTS:
    // Please call SetParamter before call Connect
    virtual int Connect() override;
    virtual int Process() override;
    virtual int Disconnect() override;
    
    virtual void slotClipBoardChange() override;
    
public:
    // FdInStreamBlockCallback methods
    void blockCallback() override;

    // Callback when socket is ready (or broken)
    //static void socketEvent(FL_SOCKET fd, void *data);

    // CConnection callback methods
    virtual void initDone() override;

    // CMsgHandler interface
public:
    virtual void framebufferUpdateEnd() override;
    virtual void dataRect(const rfb::Rect &r, int encoding) override;
    virtual void setColourMapEntries(int firstColour, int nColours, rdr::U16* rgbs) override;
    virtual void bell() override;
    virtual void setCursor(int width, int height, const rfb::Point& hotspot,
                              const rdr::U8* data) override;
    
    virtual void handleClipboardRequest() override;
    virtual void handleClipboardAnnounce(bool available) override;
    virtual void handleClipboardData(unsigned int format, const char *data, size_t length) override;
    
    virtual void getUserPasswd(bool secure, char** user, char** password) override;
    virtual bool showMsgBox(int flags, const char *title, const char *text) override;
    
signals:
    
public Q_SLOTS:
    virtual void slotMousePressEvent(QMouseEvent*) override;
    virtual void slotMouseReleaseEvent(QMouseEvent*) override;
    virtual void slotMouseMoveEvent(QMouseEvent*) override;
    virtual void slotWheelEvent(QWheelEvent*) override;
    virtual void slotKeyPressEvent(QKeyEvent*) override;
    virtual void slotKeyReleaseEvent(QKeyEvent*) override;
    
private:
    network::Socket* m_pSock;
    
    quint32 TranslateRfbKey(quint32 inkey,bool modifier);   
    
public:
    enum COLOR_LEVEL {
        Full,
        Medium,
        Low,
        VeryLow
    };

    class strPara : public CParameter{
    public:
        QString szServerName;
        
        bool bShared;
        bool bBufferEndRefresh;
        bool bSupportsDesktopResize;
        
        bool bAutoSelect;
        COLOR_LEVEL nColorLevel;
        int nEncoding;
        bool bCompressLevel;
        int nCompressLevel;
        bool bNoJpeg;
        int nQualityLevel;
    };

private:
    strPara* m_pPara;
    void autoSelectFormatAndEncoding();
    void updatePixelFormat();

    bool m_bWriteClipboard;
};

#endif // CCONNECTTIGERVNC_H
