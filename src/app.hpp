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

#ifndef APP_HPP
#define APP_HPP

#include "imageloader.hpp"

#include <bb/cascades/AbstractPane>
#include <QtCore/QObject>
#include <QtCore/QVector>
#include <bb/cascades/QListDataModel>

class App : public QObject
{
    Q_OBJECT

    // The model that contains the progress and image data
    Q_PROPERTY(bb::cascades::DataModel* model READ model NOTIFY modelChanged)
    Q_PROPERTY(QString html READ html NOTIFY imageChanged)
    Q_PROPERTY(QVariant image READ image NOTIFY imageChanged)
    Q_PROPERTY(QString imageTitle READ imageTitle NOTIFY imageChanged)
    Q_PROPERTY(QUrl imageUrl READ imageUrl NOTIFY imageChanged)
    Q_PROPERTY(int type READ type NOTIFY imageChanged)


public:
    App(QObject *parent = 0);

    // This method is called to start the loading of all images.
    Q_INVOKABLE void loadBigImage(QVariantList indexPath);
    Q_INVOKABLE void loadGallery(QString type, QString sort, QString page);
    Q_INVOKABLE void loadSubreddit(QString subreddit, QString sort, QString page);
    Q_INVOKABLE void loadNext();
    Q_INVOKABLE void loadPrev();
    Q_INVOKABLE void listBottomReached();


Q_SIGNALS:
	void imageChanged();
	void modelChanged();
	void creationDone();

private:
	bb::cascades::AbstractPane *root;
    void loadImages(int start);
    void loadJson(QUrl url);
    bb::cascades::QListDataModel<QObject*>* m_model;		// The model that contains the progress and image data for the listview
    bb::cascades::QListDataModel<QObject*>* m_wholeModel;	// The model with all picture data form json
    AbstractLoader* iml;
    QVariantList currentIndex; 								// index of selected path in listview
    int currentPosition;

    bb::cascades::DataModel* model() const;					// The accessor method for the property
    QString html() const;
	QVariant image() const;
	QString imageTitle() const;
	QUrl imageUrl() const;
	int type() const; 										// 0 = normal image, 1 = album, 2 = animated gif

    static const char* const galleryUrl;
	static const char* const clientId;
	static const char* const pictureUrl;

private slots:
    void jsonReceived(QNetworkReply * reply);
    void displayImage();
};


#endif
