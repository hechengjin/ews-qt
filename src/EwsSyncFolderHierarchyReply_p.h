#ifndef EWSSYNCFOLDERHIERARCHYREPLY_P_H
#define EWSSYNCFOLDERHIERARCHYREPLY_P_H

#include <QObject>

#include "EwsReply_p.h"
#include "EwsSyncFolderHierarchyReply.h"

#include "wsdl_Services.h"

class EwsSyncFolderHierarchyReplyPrivate : public EwsReplyPrivate
{
    Q_OBJECT
public:
    EwsSyncFolderHierarchyReplyPrivate(KDSoapJob *job);

    QString messageText;
    QString responseCode;
    QString syncState;
    bool includesLastFolderInRange = false;
    QList<EwsFolder> createFolders;
    QList<EwsFolder> updateFolders;
    QStringList deleteFolders;

public slots:
    void syncFolderHierarchyDone(KDSoapJob *job);
    void syncFolderHierarchyError(const KDSoapMessage &fault);
};

#endif // EWSSYNCFOLDERHIERARCHYREPLY_P_H
