#ifndef EWSFOLDER_P_H
#define EWSFOLDER_P_H

#include "EwsFolder.h"

#include <QObject>

#include "wsdl_Services.h"

class EwsFolderPrivate
{
public:
    void setData(const T__FolderType &value);
    virtual ~EwsFolderPrivate();

    T__FolderType folder;
    EwsFolder::WellKnownFolderName wellKnownFolderName;
//    QString id;
//    QString changeKey;
//    QString folderClass;
//    QString parentId;
//    QString parentChangeKey;
//    QString displayName;
//    EwsEffectiveRights effectiveRights;
//    int totalCount;
//    int unreadCount;
//    int childFolderCount;
    QList<EwsPermission> permissions;
    QHash<QString, QString> changes;
    EwsConnection *connection;
};

#endif // EWSFOLDER_P_H
