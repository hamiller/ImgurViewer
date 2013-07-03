/*
 * AlbumPic.cpp
 *
 *  Created on: 03.07.2013
 *      Author: florian
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
