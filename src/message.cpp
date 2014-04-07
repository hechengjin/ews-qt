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

#include "message_p.h"

#include <QDebug>

using namespace Ews;

Message::Message()
{
}

Message::~Message()
{

}

Message::Message(const Message &)
{

}

Message &Message::operator=(const Message &message)
{
    d_ptr = message.d_ptr;
    return *this;
}

Message::Message(MessagePrivate &d)
    : Item(d)
{

}

QString Message::id() const
{
    Q_D(const Message);
    return d->message.itemId().id();
}

QString Message::changeKey() const
{
    Q_D(const Message);
    return d->message.itemId().changeKey();
}

QString Message::parentFolderId() const
{
    Q_D(const Message);
    return d->message.parentFolderId().id();
}

QString Message::parentFolderChangeKey() const
{
    // TODO
    Q_D(const Message);
    return d->message.parentFolderId().changeKey();
}

QString Message::itemClass() const
{
    Q_D(const Message);
    return d->message.itemClass().value();
}

QString Message::sensivity() const
{
    // TODO
    return m_sensivity;
}

QDateTime Message::dateTimeReceived() const
{
    Q_D(const Message);
    return d->message.dateTimeReceived();
}

QDateTime Message::dateTimeSent() const
{
    Q_D(const Message);
    return d->message.dateTimeSent();
}

QDateTime Message::dateTimeCreated() const
{
    Q_D(const Message);
    return d->message.dateTimeCreated();
}

int Message::size() const
{
    Q_D(const Message);
    return d->message.size();
}

QString Message::importance() const
{
    // TODO
    return m_importance;
}

QString Message::inReplyTo() const
{
    Q_D(const Message);
    return d->message.inReplyTo();
}

QByteArray Message::conversationIndex() const
{
    Q_D(const Message);
    return d->message.conversationIndex();
}

QString Message::conversationTopic() const
{
    Q_D(const Message);
    return d->message.conversationTopic();
}

QString Message::internetMessageId() const
{
    Q_D(const Message);
    return d->message.internetMessageId();
}

bool Message::isRead() const
{
    Q_D(const Message);
    return d->message.isRead();
}

bool Message::isResponseRequested() const
{
    Q_D(const Message);
    return d->message.isResponseRequested();
}

bool Message::isReadReceiptRequested() const
{
    Q_D(const Message);
    return d->message.isReadReceiptRequested();
}

bool Message::isDeliveryReceiptRequested() const
{
    Q_D(const Message);
    return d->message.isDeliveryReceiptRequested();
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
    Q_D(const Message);
    return d->message.isSubmitted();
}

bool Message::isDraft() const
{
    Q_D(const Message);
    return d->message.isDraft();
}

bool Message::isFromMe() const
{
    Q_D(const Message);
    return d->message.isFromMe();
}

bool Message::isResend() const
{
    Q_D(const Message);
    return d->message.isResend();
}

bool Message::isUnmodified() const
{
    Q_D(const Message);
    return d->message.isUnmodified();
}

bool Message::isReminderSet() const
{
    Q_D(const Message);
    return d->message.reminderIsSet();
}

int Message::reminderMinutesBeforeStart() const
{
    Q_D(const Message);
    // TODO check this one
    return d->message.reminderMinutesBeforeStart().value().toInt();
}

QString Message::displayTo() const
{
    Q_D(const Message);
    return d->message.displayTo();
}

QString Message::displayCC() const
{
    Q_D(const Message);
    return d->message.displayCc();
}

bool Message::hasAttachments() const
{
    Q_D(const Message);
    return d->message.hasAttachments();
}

QString Message::culture() const
{
    Q_D(const Message);
    return d->message.culture();
}

EffectiveRights Message::effectiveRights() const
{
    return m_effectiveRights;
}

QString Message::lastModifiedName() const
{
    Q_D(const Message);
    return d->message.lastModifiedName();
}

QDateTime Message::lastModifiedTime() const
{
    Q_D(const Message);
    return d->message.lastModifiedTime();
}

QString Message::body() const
{
    return m_body;
}


MessagePrivate::MessagePrivate()
{

}

MessagePrivate::MessagePrivate(const T__MessageType &itemType)
    : ItemPrivate(itemType)
    , message(itemType)
{

}
