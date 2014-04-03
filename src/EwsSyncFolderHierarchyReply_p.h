#ifndef EWSSYNCFOLDERHIERARCHYREPLY_P_H
#define EWSSYNCFOLDERHIERARCHYREPLY_P_H

#include <QObject>

#include "EwsReply_p.h"
#include "EwsSyncFolderHierarchyReply.h"

#include "wsdl_Services.h"

namespace Ews {

class SyncFolderHierarchyReplyPrivate : public ReplyPrivate
{
    Q_OBJECT
public:
    SyncFolderHierarchyReplyPrivate(KDSoapJob *job);

    void processJob(KDSoapJob *job);

    QString messageText;
    QString responseCode;
    QString syncState;
    bool includesLastFolderInRange = false;
    QList<Folder> createFolders;
    QList<Folder> updateFolders;
    QStringList deleteFolders;
};

}

#endif // EWSSYNCFOLDERHIERARCHYREPLY_P_H
