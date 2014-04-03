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
//#include "ESoapElement.h"
#include "emailaddress.h"
#include "effectiverights.h"

#include <QDateTime>

namespace Ews {

class EWS_EXPORT Message
{
public:
    Message(/*const ESoapElement &rootElement*/);

    QString id() const;
    QString changeKey() const;
    QString parentFolderId() const;
    QString parentFolderChangeKey() const;
    QString itemClass() const;
    QString subject() const;
    QString sensivity() const;
    QDateTime dateTimeReceived() const;
    QDateTime dateTimeSent() const;
    QDateTime dateTimeCreated() const;
    int size() const;
    QString importance() const;
    QString inReplyTo() const;

    // Message
    QString conversationIndex() const;
    QString conversationTopic() const;
    QString internetMessageId() const;
    bool isRead() const;
    bool isResponseRequested() const;
    bool isReadReceiptRequested() const;
    bool isDeliveryReceiptRequested() const;
    QString references() const;
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
    QString m_id;
    QString m_changeKey;
    QString m_parentId;
    QString m_parentChangeKey;
    QString m_itemClass;
    QString m_subject;
    QString m_sensivity;
    QDateTime m_dateTimeReceived;
    QDateTime m_dateTimeSent;
    QDateTime m_dateTimeCreated;
    int m_size;
    QString m_importance;
    QString m_inReplyTo;

    QString m_conversationIndex;
    QString m_conversationTopic;
    QString m_internetMessageId;
    bool m_isRead;
    bool m_isResponseRequested;
    bool m_isReadReceiptRequested;
    bool m_isDeliveryReceiptRequested;
    QString m_references;
    EmailAddress m_sender;
    EmailAddress m_from;
    EmailAddress m_receivedBy;
    EmailAddress m_receivedRepresenting;
    bool m_isSubmitted;
    bool m_isDraft;
    bool m_isFromMe;
    bool m_isResend;
    bool m_isUnmodified;
    bool m_isReminderSet;
    int m_reminderMinutesBeforeStart;
    QString m_displayTo;
    QString m_displayCC;
    bool m_hasAttachments;
    QString m_culture;
    EffectiveRights m_effectiveRights;
    QString m_lastModifiedName;
    QDateTime m_lastModifiedTime;
    QString m_body;
};

}

#endif // EWSMESSAGE_H
