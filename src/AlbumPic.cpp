/* Copyright (c) 2013 Florian Miess sinnix.de.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "AlbumPic.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>

AlbumPic::AlbumPic(QString link, QString description) : m_link(link), m_description(description)
{
}

AlbumPic::~AlbumPic()
{
}

QVariant AlbumPic::image() const
{
	return m_image;
}

QString AlbumPic::link() const
{
	return m_link;
}

QString AlbumPic::description() const
{
	return m_description;
}

void AlbumPic::load()
{
//	QNetworkAccessManager* netManager = new QNetworkAccessManager(this);
//
//	qDebug() << "FMI ########## loading album " << m_imageUrl;
//	const QUrl url(m_imageUrl);
//	QNetworkRequest request(url);
//
//	QNetworkReply* reply = netManager->get(request);
//	connect(reply, SIGNAL(finished()), this, SLOT(onReplyFinished()));

}
