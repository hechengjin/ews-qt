#ifndef EWSSYNCFOLDERITEMSREPLY_P_H
#define EWSSYNCFOLDERITEMSREPLY_P_H

#include <QObject>

#include "EwsSyncFolderItemsReply.h"
#include "wsdl_Services.h"

class EwsSyncFolderItemsReplyPrivate : public QObject
{
    Q_OBJECT
public:
    EwsSyncFolderItemsReplyPrivate();

    QString messageText;
    QString responseCode;
    QString syncState;
    bool includesLastFolderInRange;
    QList<EwsMessage> m_createMessages;

public slots:
    void syncFolderItemsDone(const TNS__SyncFolderItemsResponseType& syncFolderItemsResult);
    void syncFolderItemsError(const KDSoapMessage &fault);
};

#endif // EWSSYNCFOLDERITEMSREPLY_P_H
