#ifndef EWSSYNCFOLDERITEMSREPLY_P_H
#define EWSSYNCFOLDERITEMSREPLY_P_H

#include <QObject>

#include "EwsReply_p.h"
#include "EwsSyncFolderItemsReply.h"
#include "wsdl_Services.h"

class EwsSyncFolderItemsReplyPrivate : public EwsReplyPrivate
{
    Q_OBJECT
public:
    EwsSyncFolderItemsReplyPrivate(KDSoapJob *job);

    QString messageText;
    QString responseCode;
    QString syncState;
    bool includesLastItemInRange;
    QList<EwsMessage> m_createMessages;
    QStringList deleteItems;

public slots:
    void syncFolderItemsDone(KDSoapJob *job);
    void syncFolderItemsError(const KDSoapMessage &fault);
};

#endif // EWSSYNCFOLDERITEMSREPLY_P_H
