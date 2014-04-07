#ifndef ITEM_H
#define ITEM_H

#include <QString>
#include <QSharedDataPointer>

#include "export.h"

namespace Ews {

class ItemPrivate;
class EWS_EXPORT Item
{
public:
//    void setMimeContent( const T__MimeContentType& mimeContent );
//    T__MimeContentType mimeContent() const;
//    void setItemId( const T__ItemIdType& itemId );
//    T__ItemIdType itemId() const;
//    void setParentFolderId( const T__FolderIdType& parentFolderId );
//    T__FolderIdType parentFolderId() const;
//    void setItemClass( const T__ItemClassType& itemClass );
//    T__ItemClassType itemClass() const;
    void setSubject(const QString &subject);
    QString subject() const;

//    void setSensitivity( const T__SensitivityChoicesType& sensitivity );
//    T__SensitivityChoicesType sensitivity() const;
//    void setBody( const T__BodyType& body );
//    T__BodyType body() const;
//    void setAttachments( const T__NonEmptyArrayOfAttachmentsType& attachments );
//    T__NonEmptyArrayOfAttachmentsType attachments() const;
//    void setDateTimeReceived( const KDDateTime& dateTimeReceived );
//    KDDateTime dateTimeReceived() const;
    void setSize(int size);
    int size() const;
//    void setCategories( const T__ArrayOfStringsType& categories );
//    T__ArrayOfStringsType categories() const;
//    void setImportance( const T__ImportanceChoicesType& importance );
//    T__ImportanceChoicesType importance() const;
    void setInReplyTo( const QString& inReplyTo );
    QString inReplyTo() const;
    void setIsSubmitted( bool isSubmitted );
    bool isSubmitted() const;
    void setIsDraft( bool isDraft );
    bool isDraft() const;
    void setIsFromMe( bool isFromMe );
    bool isFromMe() const;
    void setIsResend( bool isResend );
    bool isResend() const;
    void setIsUnmodified( bool isUnmodified );
    bool isUnmodified() const;
//    void setInternetMessageHeaders( const T__NonEmptyArrayOfInternetHeadersType& internetMessageHeaders );
//    T__NonEmptyArrayOfInternetHeadersType internetMessageHeaders() const;
//    void setDateTimeSent( const KDDateTime& dateTimeSent );
//    KDDateTime dateTimeSent() const;
//    void setDateTimeCreated( const KDDateTime& dateTimeCreated );
//    KDDateTime dateTimeCreated() const;
//    void setResponseObjects( const T__NonEmptyArrayOfResponseObjectsType& responseObjects );
//    T__NonEmptyArrayOfResponseObjectsType responseObjects() const;
//    void setReminderDueBy( const KDDateTime& reminderDueBy );
//    KDDateTime reminderDueBy() const;
    void setReminderIsSet( bool reminderIsSet );
    bool reminderIsSet() const;
//    void setReminderMinutesBeforeStart( const T__ReminderMinutesBeforeStartType& reminderMinutesBeforeStart );
//    T__ReminderMinutesBeforeStartType reminderMinutesBeforeStart() const;
    void setDisplayCc( const QString& displayCc );
    QString displayCc() const;
    void setDisplayTo( const QString& displayTo );
    QString displayTo() const;
    void setHasAttachments( bool hasAttachments );
    bool hasAttachments() const;
//    void setExtendedProperty( const QList< T__ExtendedPropertyType >& extendedProperty );
//    QList< T__ExtendedPropertyType > extendedProperty() const;
    void setCulture( const QString& culture );
    QString culture() const;
//    void setEffectiveRights( const T__EffectiveRightsType& effectiveRights );
//    T__EffectiveRightsType effectiveRights() const;
    void setLastModifiedName( const QString& lastModifiedName );
    QString lastModifiedName() const;
//    void setLastModifiedTime( const KDDateTime& lastModifiedTime );
//    KDDateTime lastModifiedTime() const;

    Item();
    virtual ~Item();

public:
    Item(const Item &);
    Item &operator=(const Item &);

protected:
    Item(ItemPrivate &d);
    QSharedDataPointer<ItemPrivate> d_ptr;

protected:
    EWS_DECLARE_PRIVATE(Item)
};

}

#endif // ITEM_H
