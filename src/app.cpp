#include "app.hpp"

#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/data/JsonDataAccess>
#include <bb/cascades/ImageView>
#include <list>
#include <bb/data/XmlDataAccess>

using namespace bb::cascades;

//const char* const App::galleryUrl = "http://imgur.com/gallery/";
const char* const App::galleryUrl = "https://api.imgur.com/3/gallery/";
//https://api.imgur.com/3/gallery/hot/viral/0.json
//https://api.imgur.com/3/gallery/hot/viral/0.json
//const char* const ImageLoader::pictureUrl = "https://api.imgur.com/3/image/";
const char* const App::pictureUrl = "http://i.imgur.com/";
const char* const App::clientId = "Client-ID d99014129d28197";
const int listIncrease = 12;


App::App(QObject *parent)
	: QObject(parent)
	, m_model(new QListDataModel<QObject*>())
	, m_wholeModel(new QListDataModel<QObject*>())
	, iml(NULL)
	, currentPosition(0)
	, m_modelSubreddits(new GroupDataModel())
{
	// Register custom type to QML
	qmlRegisterType<AbstractLoader>();

	QVariantList currentEntries = readXMLEntries();
	m_modelSubreddits->insertList(currentEntries);

	m_model->setParent(this);
	m_wholeModel->setParent(this);

	// Create the UI
	QmlDocument* qml = QmlDocument::create("asset:///main.qml").parent(this);
	qml->setContextProperty("_app", this);

	root = qml->createRootObject<AbstractPane>();

	Application::instance()->setScene(root);
}

void App::loadGallery(QString type, QString sort, QString page)
{
	qDebug() << "FMI ############ LOAD GALLERY type:"<< type << " sort:" << " page:" << page;
	m_model->clear();
	m_wholeModel->clear();
	currentPosition = 0;

	// Creates the network request and sets the destination URL.
	const QUrl url(galleryUrl + type + "/" + sort + "/page/" + page + ".json");
	loadJson(url);
}

void App::loadSubreddit(QString subreddit, QString sort, QString page)
{
	qDebug() << "FMI ############ LOAD SUBREDDIT - subreddit:" << subreddit << " sort:" << " page:" << page;
	m_model->clear();
	m_wholeModel->clear();
	currentPosition = 0;

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
	loadImages(0);
}

void App::listBottomReached()
{
	qDebug() << "FMI ######### listBottomReached!!";
	loadImages(currentPosition +1);
}

void App::loadBigImage(QVariantList indexPath)
{
	this->currentIndex = indexPath;

	QObject* o = qvariant_cast<QObject*>(m_model->data(indexPath));
	AbstractLoader *bigImage = qobject_cast<AbstractLoader*>(o);
	qDebug()<< "FMI +++++++++++++++ " << bigImage->origImageUrl() << ", " << bigImage->origImageUrl() << ", " << bigImage->title() << ", " << bigImage->type();

	iml = bigImage;
	iml->image() = 0;
	displayImage();

	if (bigImage->type() == 0 || bigImage->type() == 2)
	{
		connect(iml, SIGNAL(imageChanged()), this, SLOT(displayImage()));
		iml->loadBigImage();
	}
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


void App::loadImages(int start)
{
	int stop = start + listIncrease;
	// Call the load() method for each ImageLoader instance inside the model
	qDebug() << "FMI ######## model size:" << m_model->size() << " reading " << start << "->" << stop;
	int row = start;
	for (; row < stop && row < m_wholeModel->size(); ++row)
	{
		qDebug() << "FMI ######## load picture " << row;
		AbstractLoader *loader = qobject_cast<AbstractLoader*>(m_wholeModel->value(row));
		loader->load();

		m_model->append(loader);

		currentPosition++;
	}
	emit modelChanged();
}


bb::cascades::DataModel* App::model() const
{
	return m_model;
}

bb::cascades::GroupDataModel* App::modelSubreddit() const
{
	return m_modelSubreddits;
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
		for (QList<QVariant>::iterator it = jsonvaList.begin(); (it != jsonvaList.end()); it++)
		{
			QVariantMap image = it->toMap();
			QString title = image["title"].toString();
			bool is_album = image["is_album"].toBool();
			QString link = image["link"].toString();

			if (!is_album)
			{
				QString linkLittle = image["link"].toString().insert(link.length() - 4, "b");
				qDebug() << "FMI ######### adding pic   " << link;
				m_wholeModel->append(new ImageLoader(linkLittle, link, title, 0, this));
			}
			else
			{
				QString linkLittle = pictureUrl + image["cover"].toString()+ "b.jpg";
				qDebug() << "FMI ######### adding album " << link;
				m_wholeModel->append(new ImageLoader(linkLittle, link, title, 1, this));
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
	int result = 1;
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
}

void App::subRedditCreate(QString const subreddit)
{
	qDebug() << "FMI #### create " << subreddit;
	QVariantList currentEntries = readXMLEntries();

	// create new entry
	QVariantMap newEntry;
	newEntry["title"] = QVariant(subreddit);
	currentEntries.append(newEntry);

	saveXMLEntries(currentEntries);

	m_modelSubreddits->clear();
	m_modelSubreddits->insertList(currentEntries);
	emit modelSubredditChanged();
}

void App::subRedditEdit(QString oldSubreddit, QString newSubreddit)
{
	qDebug() << "FMI #### edit " << oldSubreddit << "->" << newSubreddit;
	subRedditDelete(oldSubreddit);
	subRedditCreate(newSubreddit);
}

void App::subRedditDelete(QString subreddit)
{
	qDebug() << "FMI #### delete " << subreddit;
	QVariantList currentEntries = readXMLEntries();

	// search entry
	for (QVariantList::iterator it = currentEntries.begin(); it != currentEntries.end(); it++)
	{
		QVariantMap itemMap = (*it).toMap();
		if (QString::compare(itemMap["title"].toString(), subreddit) == 0)
		{
			qDebug() << "FMI #####################" << itemMap["title"].toString() << " matched. Deleting...";
			currentEntries.erase(it);
			break;
		}

	}

	saveXMLEntries(currentEntries);

	m_modelSubreddits->clear();
	m_modelSubreddits->insertList(currentEntries);
	emit modelSubredditChanged();
}

QVariantList App::readXMLEntries()
{
	QVariantList result;
	// Load the XML data from local file
	bb::data::XmlDataAccess xda;
	QVariant temp = xda.load("app/native/assets/models/subreddits.xml", "/root/listItem");
	QVariantList currentEntries = temp.value<QVariantList>();

	if (xda.hasError()) {
		bb::data::DataAccessError error = xda.error();
		qDebug() << "#########  XML loading error: " << error.errorType() << ": " << error.errorMessage();
	}
	else
	{
		result = currentEntries;
	}
	return result;
}

void App::saveXMLEntries(QVariantList currentEntries)
{
	QVariantMap topLevel;
	topLevel[".root"] = QVariant("root");
	topLevel["listItem"] = QVariant(currentEntries);
	QVariant myData = QVariant(topLevel);

	// save new entry
	bb::data::XmlDataAccess xda;
	xda.save(myData, "app/native/assets/models/subreddits.xml");
	if (xda.hasError()) {
		bb::data::DataAccessError error = xda.error();
		qDebug() << "#########  XML writing error: " << error.errorType() << ": " << error.errorMessage();
	}
}
