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

#include "message.h"
#include "request.h"

#include <QDebug>

using namespace Ews;

Message::Message(/*const ESoapElement &rootElement*/) :
    m_size(0),
    m_isRead(false),
    m_isResponseRequested(false),
    m_isDeliveryReceiptRequested(false),
    m_isDraft(false),
    m_isFromMe(false),
    m_isResend(false),
    m_isUnmodified(false),
    m_isReminderSet(false),
    m_reminderMinutesBeforeStart(0),
    m_hasAttachments(false)
{
//    ESoapElement element;

//    element = rootElement.firstChildElement();
//    while (!element.isNull()) {
//        if (element.equalNS(QLatin1String("ItemId"), EWS_TYPES_NS)) {
//            m_id = element.attribute(QLatin1String("Id"));
//            m_changeKey = element.attribute(QLatin1String("ChangeKey"));
//        } else if (element.equalNS(QLatin1String("ParentFolderId"), EWS_TYPES_NS)) {
//            m_parentId = element.attribute(QLatin1String("Id"));
//            m_parentChangeKey = element.attribute(QLatin1String("ChangeKey"));
//        } else if (element.equalNS(QLatin1String("ItemClass"), EWS_TYPES_NS)) {
//            m_itemClass = element.text();
//        } else if (element.equalNS(QLatin1String("Subject"), EWS_TYPES_NS)) {
//            m_subject = element.text();
//        } else if (element.equalNS(QLatin1String("DateTimeReceived"), EWS_TYPES_NS)) {
//            m_dateTimeReceived = QDateTime::fromString(element.text(), Qt::ISODate);
//        } else if (element.equalNS(QLatin1String("DateTimeSent"), EWS_TYPES_NS)) {
//            m_dateTimeSent = QDateTime::fromString(element.text(), Qt::ISODate);
//        } else if (element.equalNS(QLatin1String("DateTimeCreated"), EWS_TYPES_NS)) {
//            m_dateTimeCreated = QDateTime::fromString(element.text(), Qt::ISODate);
//        } else if (element.equalNS(QLatin1String("Size"), EWS_TYPES_NS)) {
//            m_size = element.text().toInt();
//        } else if (element.equalNS(QLatin1String("HasAttachments"), EWS_TYPES_NS)) {
//            m_hasAttachments = element.text() == QLatin1String("true");
//        } else if (element.equalNS(QLatin1String("Importance"), EWS_TYPES_NS)) {
//            m_importance = element.text();
//        } else if (element.equalNS(QLatin1String("InReplyTo"), EWS_TYPES_NS)) {
//            m_inReplyTo = element.text();
//        } else if (element.equalNS(QLatin1String("ConversationIndex"), EWS_TYPES_NS)) {
//            m_conversationIndex = element.text();
//        } else if (element.equalNS(QLatin1String("ConversationTopic"), EWS_TYPES_NS)) {
//            m_conversationTopic = element.text();
//        } else if (element.equalNS(QLatin1String("InternetMessageId"), EWS_TYPES_NS)) {
//            m_internetMessageId = element.text();
//        } else if (element.equalNS(QLatin1String("IsRead"), EWS_TYPES_NS)) {
//            m_isRead = element.text() == QLatin1String("true");
//        } else if (element.equalNS(QLatin1String("IsResponseRequested"), EWS_TYPES_NS)) {
//            m_isResponseRequested = element.text() == QLatin1String("true");
//        } else if (element.equalNS(QLatin1String("IsReadReceiptRequested"), EWS_TYPES_NS)) {
//            m_isReadReceiptRequested = element.text() == QLatin1String("true");
//        } else if (element.equalNS(QLatin1String("IsDeliveryReceiptRequested"), EWS_TYPES_NS)) {
//            m_isDeliveryReceiptRequested = element.text() == QLatin1String("true");
//        } else if (element.equalNS(QLatin1String("References"), EWS_TYPES_NS)) {
//            m_references = element.text();
//        } else if (element.equalNS(QLatin1String("Sender"), EWS_TYPES_NS)) {
//            m_sender = EmailAddress(element.firstChildElement());
//        } else if (element.equalNS(QLatin1String("From"), EWS_TYPES_NS)) {
//            m_from = EmailAddress(element.firstChildElement());
//        } else if (element.equalNS(QLatin1String("ReceivedBy"), EWS_TYPES_NS)) {
//            m_receivedBy = EmailAddress(element.firstChildElement());
//        } else if (element.equalNS(QLatin1String("ReceivedRepresenting"), EWS_TYPES_NS)) {
//            m_receivedRepresenting = EmailAddress(element.firstChildElement());
//        } else if (element.equalNS(QLatin1String("IsDraft"), EWS_TYPES_NS)) {
//            m_isDraft = element.text() == QLatin1String("true");
//        } else if (element.equalNS(QLatin1String("IsFromMe"), EWS_TYPES_NS)) {
//            m_isFromMe = element.text() == QLatin1String("true");
//        } else if (element.equalNS(QLatin1String("IsResend"), EWS_TYPES_NS)) {
//            m_isResend = element.text() == QLatin1String("true");
//        } else if (element.equalNS(QLatin1String("IsSubmitted"), EWS_TYPES_NS)) {
//            m_isSubmitted = element.text() == QLatin1String("true");
//        } else if (element.equalNS(QLatin1String("IsUnmodified"), EWS_TYPES_NS)) {
//            m_isUnmodified = element.text() == QLatin1String("true");
//        } else if (element.equalNS(QLatin1String("Body"), EWS_TYPES_NS)) {
//            m_body = element.text();
//        } else if (element.equalNS(QLatin1String("Sensitivity"), EWS_TYPES_NS)) {
//            m_sensivity = element.text();
//        } else if (element.equalNS(QLatin1String("ReminderIsSet"), EWS_TYPES_NS)) {
//            m_isReminderSet = element.text() == QLatin1String("true");
//        } else if (element.equalNS(QLatin1String("ReminderMinutesBeforeStart"), EWS_TYPES_NS)) {
//            m_reminderMinutesBeforeStart = element.text().toInt();
//        } else if (element.equalNS(QLatin1String("DisplayCc"), EWS_TYPES_NS)) {
//            m_displayCC = element.text();
//        } else if (element.equalNS(QLatin1String("DisplayTo"), EWS_TYPES_NS)) {
//            m_displayTo = element.text();
//        } else if (element.equalNS(QLatin1String("Culture"), EWS_TYPES_NS)) {
//            m_culture = element.text();
//        } else if (element.equalNS(QLatin1String("EffectiveRights"), EWS_TYPES_NS)) {
//            m_effectiveRights = EwsEffectiveRights(element);
//        } else if (element.equalNS(QLatin1String("LastModifiedName"), EWS_TYPES_NS)) {
//            m_lastModifiedName = element.text();
//        } else if (element.equalNS(QLatin1String("LastModifiedTime"), EWS_TYPES_NS)) {
//            m_lastModifiedTime = QDateTime::fromString(element.text(), Qt::ISODate);
//        } else {
//            // TODO create PermissionSet class
//            qWarning() << Q_FUNC_INFO << "element unknown" << element.nodeName() << element.text();
//        }

//        element = element.nextSiblingElement();
//    }
}

QString Message::id() const
{
    return m_id;
}

QString Message::changeKey() const
{
    return m_changeKey;
}

QString Message::parentFolderId() const
{
    return m_parentId;
}

QString Message::parentFolderChangeKey() const
{
    return m_parentChangeKey;
}

QString Message::itemClass() const
{
    return m_itemClass;
}

QString Message::subject() const
{
    return m_subject;
}

QString Message::sensivity() const
{
    return m_sensivity;
}

QDateTime Message::dateTimeReceived() const
{
    return m_dateTimeReceived;
}

QDateTime Message::dateTimeSent() const
{
    return m_dateTimeSent;
}

QDateTime Message::dateTimeCreated() const
{
    return m_dateTimeCreated;
}

int Message::size() const
{
    return m_size;
}

QString Message::importance() const
{
    return m_importance;
}

QString Message::inReplyTo() const
{
    return m_inReplyTo;
}

QString Message::conversationIndex() const
{
    return m_conversationIndex;
}

QString Message::conversationTopic() const
{
    return m_conversationTopic;
}

QString Message::internetMessageId() const
{
    return m_internetMessageId;
}

bool Message::isRead() const
{
    return m_isRead;
}

bool Message::isResponseRequested() const
{
    return m_isResponseRequested;
}

bool Message::isReadReceiptRequested() const
{
    return m_isReadReceiptRequested;
}

bool Message::isDeliveryReceiptRequested() const
{
    return m_isDeliveryReceiptRequested;
}

QString Message::references() const
{
    return m_references;
}

EmailAddress Message::sender() const
{
    return m_sender;
}

EmailAddress Message::from() const
{
    return m_from;
}

EmailAddress Message::receivedBy() const
{
    return m_receivedBy;
}

EmailAddress Message::receivedRepresenting() const
{
    return m_receivedRepresenting;
}

bool Message::isSubmitted() const
{
    return m_isSubmitted;
}

bool Message::isDraft() const
{
    return m_isDraft;
}

bool Message::isFromMe() const
{
    return m_isFromMe;
}

bool Message::isResend() const
{
    return m_isResend;
}

bool Message::isUnmodified() const
{
    return m_isUnmodified;
}

bool Message::isReminderSet() const
{
    return m_isReminderSet;
}

int Message::reminderMinutesBeforeStart() const
{
    return m_reminderMinutesBeforeStart;
}

QString Message::displayTo() const
{
    return m_displayTo;
}

QString Message::displayCC() const
{
    return m_displayCC;
}

bool Message::hasAttachments() const
{
    return m_hasAttachments;
}

QString Message::culture() const
{
    return m_culture;
}

EffectiveRights Message::effectiveRights() const
{
    return m_effectiveRights;
}

QString Message::lastModifiedName() const
{
    return m_lastModifiedName;
}

QDateTime Message::lastModifiedTime() const
{
    return m_lastModifiedTime;
}

QString Message::body() const
{
    return m_body;
}
