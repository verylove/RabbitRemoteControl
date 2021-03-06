//! @author: Kang Lin(kl222@126.com)

#ifndef CCLIPBOARDFREERDP_H
#define CCLIPBOARDFREERDP_H

#include <QObject>
#include "freerdp/freerdp.h"
#include "freerdp/client/cliprdr.h"
#include "freerdp/client/rdpgfx.h"
#include "ClipboardMimeData.h"

class CConnectFreeRdp;
class CClipboardFreeRdp : public QObject
{
    Q_OBJECT
public:
    explicit CClipboardFreeRdp(CConnectFreeRdp *parent = nullptr);
    virtual ~CClipboardFreeRdp();
    
    int Init(CliprdrClientContext *context, bool bEnable);
    int UnInit(CliprdrClientContext* context, bool bEnable);
    
    static UINT cb_cliprdr_monitor_ready(CliprdrClientContext* context,
                                     const CLIPRDR_MONITOR_READY* monitorReady);
    static UINT cb_cliprdr_server_capabilities(CliprdrClientContext* context,
                                      const CLIPRDR_CAPABILITIES* capabilities);
    static UINT cb_cliprdr_server_format_list(CliprdrClientContext* context,
                                         const CLIPRDR_FORMAT_LIST* formatList);
    static UINT
    cb_cliprdr_server_format_list_response(CliprdrClientContext* context,
                        const CLIPRDR_FORMAT_LIST_RESPONSE* formatListResponse);
    static UINT
    cb_cliprdr_server_format_data_request(CliprdrClientContext* context,
                          const CLIPRDR_FORMAT_DATA_REQUEST* formatDataRequest);
    static UINT
    cb_cliprdr_server_format_data_response(CliprdrClientContext* context,
                        const CLIPRDR_FORMAT_DATA_RESPONSE* formatDataResponse);
    static UINT
    cb_cliprdr_server_file_contents_request(CliprdrClientContext* context,
                      const CLIPRDR_FILE_CONTENTS_REQUEST* fileContentsRequest);
    
    static UINT cb_cliprdr_send_data_response(CliprdrClientContext *context, BYTE* data, int size);
    
    static UINT SendClientFormatList(CliprdrClientContext *context);
    static UINT SendDataRequest(CliprdrClientContext* context, UINT32 formatId);
    
public Q_SLOTS:
    virtual void slotClipBoardChange();
    
private:
    CConnectFreeRdp* m_pConnect;
    CliprdrClientContext* m_pClipboard;
    CClipboardMimeData* m_pMimeData;
};

#endif // CCLIPBOARDFREERDP_H
