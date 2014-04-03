#ifndef EWSSYNCFOLDERITEMSREPLY_P_H
#define EWSSYNCFOLDERITEMSREPLY_P_H

#include <QObject>

#include "reply_p.h"
#include "syncfolderitemsreply.h"
#include "wsdl_Services.h"

namespace Ews {

class SyncFolderItemsReplyPrivate : public ReplyPrivate
{
    Q_OBJECT
public:
    SyncFolderItemsReplyPrivate(KDSoapJob *job);

    void processJob(KDSoapJob *job);

    QString messageText;
    QString responseCode;
    QString syncState;
    bool includesLastItemInRange;
    QStringList deleteItems;

};

}

#endif // EWSSYNCFOLDERITEMSREPLY_P_H
