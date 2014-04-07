/*
 * Copyright (C) 2013 Daniel Nicoletti <dantti12@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 */

#ifndef EWSMESSAGE_H
#define EWSMESSAGE_H

#include "export.h"
#include "item.h"
#include "emailaddress.h"
#include "effectiverights.h"

#include <QDateTime>

namespace Ews {

class MessagePrivate;
class EWS_EXPORT Message : public Item
{
public:
//    void setSender( const T__SingleRecipientType& sender );
//    T__SingleRecipientType sender() const;
//    void setToRecipients( const T__ArrayOfRecipientsType& toRecipients );
//    T__ArrayOfRecipientsType toRecipients() const;
//    void setCcRecipients( const T__ArrayOfRecipientsType& ccRecipients );
//    T__ArrayOfRecipientsType ccRecipients() const;
//    void setBccRecipients( const T__ArrayOfRecipientsType& bccRecipients );
//    T__ArrayOfRecipientsType bccRecipients() const;
    void setIsReadReceiptRequested( bool isReadReceiptRequested );
    bool isReadReceiptRequested() const;
    void setIsDeliveryReceiptRequested( bool isDeliveryReceiptRequested );
    bool isDeliveryReceiptRequested() const;
    void setConversationIndex( const QByteArray& conversationIndex );
    QByteArray conversationIndex() const;
    void setConversationTopic( const QString& conversationTopic );
    QString conversationTopic() const;
//    void setFrom( const T__SingleRecipientType& from );
//    T__SingleRecipientType from() const;
    void setInternetMessageId( const QString& internetMessageId );
    QString internetMessageId() const;
    void setIsRead( bool isRead );
    bool isRead() const;
    void setIsResponseRequested( bool isResponseRequested );
    bool isResponseRequested() const;
    void setReferences( const QString& references );
    QString references() const;
//    void setReplyTo( const T__ArrayOfRecipientsType& replyTo );
//    T__ArrayOfRecipientsType replyTo() const;
//    void setReceivedBy( const T__SingleRecipientType& receivedBy );
//    T__SingleRecipientType receivedBy() const;
//    void setReceivedRepresenting( const T__SingleRecipientType& receivedRepresenting );
//    T__SingleRecipientType receivedRepresenting() const;

    QString id() const;
    QString changeKey() const;
    QString parentFolderId() const;
    QString parentFolderChangeKey() const;
    QString itemClass() const;
//    QString subject() const;
    QString sensivity() const;
    QDateTime dateTimeReceived() const;
    QDateTime dateTimeSent() const;
    QDateTime dateTimeCreated() const;
    int size() const;
    QString importance() const;
    QString inReplyTo() const;

    // Message
    EmailAddress sender() const;
    EmailAddress from() const;
    EmailAddress receivedBy() const;
    EmailAddress receivedRepresenting() const;
    bool isSubmitted() const;
    bool isDraft() const;
    bool isFromMe() const;
    bool isResend() const;
    bool isUnmodified() const;
    bool isReminderSet() const;
    int reminderMinutesBeforeStart() const;
    QString displayTo() const;
    QString displayCC() const;
    bool hasAttachments() const;
    QString culture() const;
    EffectiveRights effectiveRights() const;
    QString lastModifiedName() const;
    QDateTime lastModifiedTime() const;
    QString body() const;

private:
//    QString m_id;
//    QString m_changeKey;
//    QString m_parentId;
//    QString m_parentChangeKey;
//    QString m_itemClass;
//    QString m_subject;
    QString m_sensivity;
//    QDateTime m_dateTimeReceived;
//    QDateTime m_dateTimeSent;
//    QDateTime m_dateTimeCreated;
//    int m_size;
    QString m_importance;
//    QString m_inReplyTo;

//    QByteArray m_conversationIndex;
//    QString m_conversationTopic;
//    QString m_internetMessageId;
//    bool m_isRead;
//    bool m_isResponseRequested;
//    bool m_isReadReceiptRequested;
//    bool m_isDeliveryReceiptRequested;
    QString m_references;
    EmailAddress m_sender;
    EmailAddress m_from;
    EmailAddress m_receivedBy;
    EmailAddress m_receivedRepresenting;
//    bool m_isSubmitted;
//    bool m_isDraft;
//    bool m_isFromMe;
//    bool m_isResend;
//    bool m_isUnmodified;
//    bool m_isReminderSet;
//    int m_reminderMinutesBeforeStart;
//    QString m_displayTo;
//    QString m_displayCC;
//    bool m_hasAttachments;
//    QString m_culture;
    EffectiveRights m_effectiveRights;
//    QString m_lastModifiedName;
//    QDateTime m_lastModifiedTime;
    QString m_body;

public:
    Message();
    virtual ~Message();

    Message(const Message &);
    Message &operator=(const Message &);

protected:
    Message(MessagePrivate &d);

private:
    friend class SyncFolderItemsReplyPrivate;
    EWS_DECLARE_PRIVATE(Message)
};

}

#endif // EWSMESSAGE_H
