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
#include "albumloader.hpp"

#include <bb/cascades/AbstractPane>
#include <QtCore/QObject>
#include <QtCore/QVector>
#include <bb/cascades/QListDataModel>

class App : public QObject
{
    Q_OBJECT

    // The model that contains the progress and image data
    Q_PROPERTY(bb::cascades::DataModel* model READ model NOTIFY modelChanged)
    Q_PROPERTY(QVariant image READ image NOTIFY imageChanged)
    Q_PROPERTY(QString imageTitle READ imageTitle NOTIFY imageTitleChanged)
    Q_PROPERTY(QUrl imageUrl READ imageUrl NOTIFY imageUrlChanged)
    Q_PROPERTY(int type READ type NOTIFY typeChanged)


public:
    App(QObject *parent = 0);

    // This method is called to start the loading of all images.
    Q_INVOKABLE void loadBigImage(QVariantList indexPath);
    Q_INVOKABLE void loadGallery(QString type, QString page);
    Q_INVOKABLE void loadNext();

Q_SIGNALS:
	void imageChanged();
	void imageTitleChanged();
	void modelChanged();
	void imageUrlChanged();
	void typeChanged();

private:
	bb::cascades::AbstractPane *root;

    void loadImages();
    void loadJson(QUrl url);


    // The accessor method for the property
    bb::cascades::DataModel* model() const;

    // The model that contains the progress and image data
    bb::cascades::QListDataModel<QObject*>* m_model;

    QVariant image() const;
    QString imageTitle() const;
    QUrl imageUrl() const;
    // 0 = normal image, 1 = animated gif, 2 = album
    int type() const;
    AbstractLoader* iml;
    QVariantList currentIndex;

    static const char* const galleryUrl;


private slots:
    void jsonReceived(QNetworkReply * reply);
    void displayImage();
};


#endif
