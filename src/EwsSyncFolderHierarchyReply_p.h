#ifndef EWSSYNCFOLDERHIERARCHYREPLY_P_H
#define EWSSYNCFOLDERHIERARCHYREPLY_P_H

#include <QObject>

#include "wsdl_Services.h"

class EwsSyncFolderHierarchyReplyPrivate : public QObject
{
    Q_OBJECT
public:
    EwsSyncFolderHierarchyReplyPrivate();

    QString messageText;
    QString responseCode;
    QString syncState;
    bool includesLastFolderInRange;
    QList<EwsFolder> createFolders;
    QList<EwsFolder> updateFolders;
    QStringList deleteFolders;

public slots:
    void syncFolderHierarchyDone(const TNS__SyncFolderHierarchyResponseType &response);
    void syncFolderHierarchyError(const KDSoapMessage &fault);
};

#endif // EWSSYNCFOLDERHIERARCHYREPLY_P_H
