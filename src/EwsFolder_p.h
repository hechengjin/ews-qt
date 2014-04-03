#ifndef EWSFOLDER_P_H
#define EWSFOLDER_P_H

#include "EwsFolder.h"

#include <QObject>

#include "wsdl_Services.h"

namespace Ews {

class FolderPrivate
{
public:
    FolderPrivate();
    FolderPrivate(const T__FolderType &value);
    virtual ~FolderPrivate();

    T__FolderType folder;
    Folder::WellKnownFolderName wellKnownFolderName;
    EffectiveRights effectiveRights;
    QList<Permission> permissions;
    QHash<QString, QString> changes;
    Connection *connection;
};

}

#endif // EWSFOLDER_P_H
