/* Copyright (c) 2012 Research In Motion Limited.
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

#include "app.hpp"

#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/data/JsonDataAccess>
#include <bb/cascades/ImageView>
#include <list>

using namespace bb::cascades;

//const char* const App::galleryUrl = "http://imgur.com/gallery/";
const char* const App::galleryUrl = "https://api.imgur.com/3/gallery/";
//https://api.imgur.com/3/gallery/hot/viral/0.json
//https://api.imgur.com/3/gallery/hot/viral/0.json
//const char* const ImageLoader::pictureUrl = "https://api.imgur.com/3/image/";
const char* const App::pictureUrl = "http://i.imgur.com/";
const char* const App::clientId = "Client-ID d99014129d28197";

App::App(QObject *parent)
	: QObject(parent)
	, m_model(new QListDataModel<QObject*>())
	, iml(NULL)
{
	// Register custom type to QML
	qmlRegisterType<AbstractLoader>();

	m_model->setParent(this);

	// Create the UI
	QmlDocument* qml = QmlDocument::create("asset:///main.qml").parent(this);
	qml->setContextProperty("_app", this);

	root = qml->createRootObject<AbstractPane>();

	Application::instance()->setScene(root);
}

void App::loadGallery(QString type, QString sort, QString page)
{
	qDebug() << "FMI ############ LOAD GALLERY";
	m_model->clear();
	emit modelChanged();

	// Creates the network request and sets the destination URL.
	const QUrl url(galleryUrl + type + "/" + sort + "/page/" + page + ".json");
	loadJson(url);
}

void App::loadSubreddit(QString subreddit, QString sort, QString page)
{
	qDebug() << "FMI ############ LOAD SUBREDDIT";

	m_model->clear();
	emit modelChanged();

	// Creates the network request and sets the destination URL.
	const QUrl url(galleryUrl + QString("r/" + subreddit + "/" + sort + "/page/" + page + ".json"));
	loadJson(url);
}

void App::loadJson(QUrl url)
{
	QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this); // up to 6 connections at a time
	QNetworkRequest request(url);
	request.setRawHeader("Authorization", clientId);

	QSslConfiguration sslConfig = request.sslConfiguration();
	sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
	sslConfig.setPeerVerifyDepth(1);
	sslConfig.setProtocol(QSsl::TlsV1);
	sslConfig.setSslOption(QSsl::SslOptionDisableSessionTickets, true);

	request.setSslConfiguration(sslConfig);

	QEventLoop eventLoop;
	connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(jsonReceived(QNetworkReply*)));
	connect(this, SIGNAL(creationDone()), &eventLoop, SLOT(quit()));

	// Sends the HTTP request.
	networkAccessManager->get(request);
	eventLoop.exec();

	qDebug() << "FMI ######### done loading!!";
	loadImages();
}

void App::loadBigImage(QVariantList indexPath)
{
	iml = 0;
	emit imageChanged();

	this->currentIndex = indexPath;

	QObject* o = qvariant_cast<QObject*>(m_model->data(indexPath));
	AbstractLoader *bigImage = qobject_cast<AbstractLoader*>(o);
	if (bigImage->type() == 0 || bigImage->type() == 2)
	{
		iml = new ImageLoader(bigImage->origImageUrl(), bigImage->origImageUrl(), bigImage->title(), this);
		connect(iml, SIGNAL(titleChanged()), this, SLOT(displayImage()));
		iml->load();
	}
//	else
//	{
//		// hm, this is not an image, instead something different
//		// -> lets get the next level of json infos
//		QUrl url(bigImage->origImageUrl());
//		loadJson(url);
//	}
}

void App::loadNext()
{
	int currentSize = this->currentIndex[0].toInt();
	if (currentSize < m_model->size() - 1)
	{
		this->currentIndex[0].setValue(currentSize + 1);
		loadBigImage(this->currentIndex);
	}
}

void App::loadPrev()
{
	int currentSize = this->currentIndex[0].toInt();
	if (currentSize > 0)
	{
		this->currentIndex[0].setValue(currentSize - 1);
		loadBigImage(this->currentIndex);
	}
}

void App::loadImages()
{
	// Call the load() method for each ImageLoader instance inside the model
	qDebug() << "FMI ######## model size:" << m_model->size();
	for (int row = 0; row < m_model->size(); ++row)
	{
		qDebug() << "FMI ######## load picture " << row;
		qobject_cast<AbstractLoader*>(m_model->value(row))->load();

	}
}

bb::cascades::DataModel* App::model() const
{
	return m_model;
}

/*
 * Received gallery json file, now parse the data
 */
void App::jsonReceived(QNetworkReply * reply)
{
	bb::data::JsonDataAccess jda;

	if (reply->error() == QNetworkReply::NoError)
	{
		int available = reply->bytesAvailable();
		QString replyString;

		if (available > 0)
		{
			int bufSize = sizeof(char) * available + sizeof(char);
			QByteArray buffer(bufSize, 0);
			reply->read(buffer.data(), available);
			replyString = QString::fromUtf8(buffer);
		}

		QVariantMap jsonva = jda.loadFromBuffer(replyString).toMap();
		QVariantList jsonvaList = jsonva.find("data")->toList();

		if (jda.hasError())
		{
			bb::data::DataAccessError error = jda.error();
			qDebug() << "FMI ######### JSON loading error: " << error.errorType() << ": " << error.errorMessage();
			qDebug() << replyString;
			return;
		}

		// iterate list
		int i = 0;
		for (QList<QVariant>::iterator it = jsonvaList.begin(); (it != jsonvaList.end() && i < 20); it++)
		{
			QVariantMap image = it->toMap();
			QString title = image["title"].toString();
			bool is_album = image["is_album"].toBool();
			QString link = image["link"].toString();

			if (!is_album)
			{
				QString linkLittle = image["link"].toString().insert(link.length() - 4, "b");
				qDebug() << "FMI ######### adding pic   " << link;
				m_model->append(new ImageLoader(linkLittle, link, title, this));
			}
			else
			{
				if (image.find("images") != image.end())
				{
					qDebug() << "FMI ######### adding album " << link;
//					std::list<AlbumPic*> *albumPics = NULL;
//					// we are already in an album, not in the gallery
//					QVariantList jsonAlbumList = image.find("images")->toList();
//					for (QList<QVariant>::iterator ait = jsonAlbumList.begin(); ait != jsonAlbumList.end(); ait++)
//					{
//						QVariantMap albumImage = ait->toMap();
//
//						QString description = albumImage["description"].toString();
//						QString albumPicUrl = albumImage["link"].toString();
//						albumPics->push_back(new AlbumPic(albumPicUrl, description));
//					}
//					m_model->append(new AlbumLoader(albumPics, link, link, title, this));
				}
				else
				{
					QString linkLittle = pictureUrl + image["cover"].toString()+ "b.jpg";
					qDebug() << "FMI ######### adding album " << link;
					m_model->append(new ImageLoader(linkLittle, link, title, this));
				}
			}
			i++;
		}
	}
	else
		qDebug() << "FMI ######### error: " << reply->errorString();

	reply->deleteLater();
	emit creationDone();
}

QVariant App::image() const
{
	QVariant result = "";
	if (iml)
	{ // check pointer
		result = iml->image();
	}

	return result;
}

QString App::imageTitle() const
{
	QString result = "";
	if (iml)
	{ // check pointer
		result = iml->title();
	}

	return result;
}

QUrl App::imageUrl() const
{
	QUrl result;
	if (iml)
	{ // check pointer
		result.setUrl(iml->origImageUrl());
	}
	return result;
}

int App::type() const
{
	int result;
	if (iml)
	{ // check pointer
		result = iml->type();
	}
	return result;
}

QString App::html() const
{
	QString result = QString("<html><header></header><body></body>");
	if (type() == 0 || type() == 2)
	{
		result = QString("<html><header></header><body><img src=\"" + imageUrl().toString() + "\"  width=\"100%\"/></body>");
	}
	else if (type() == 1)  {
		result = QString("<head><meta http-equiv=\"refresh\" content=\"0; URL=" + imageUrl().toString() + "\"></head>");
	}

	return result;
}

void App::displayImage()
{
	emit imageChanged();
	emit imageTitleChanged();
	emit imageUrlChanged();
}
