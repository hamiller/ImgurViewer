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

#ifndef ABSTRACTLOADER_HPP_
#define ABSTRACTLOADER_HPP_

#include <bb/cascades/Image>
#include <QObject>
#include <QVariant>
#include <QString>
#include <QImage>
#include <QThread>
#include <QNetworkAccessManager>

class AbstractLoader : public QObject
{
	Q_OBJECT

    Q_PROPERTY(QVariant image READ image NOTIFY imageChanged)
    Q_PROPERTY(QString label READ label NOTIFY labelChanged)
    Q_PROPERTY(QString title READ title NOTIFY labelChanged)
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged)


protected:
    bb::cascades::Image m_image;
    bool m_loading;
    QString m_imageUrl;
    QString m_imageUrl_orig;
    QString m_title;
    QString m_label;
    int m_type;
    QSet<AbstractLoader *> _subObjects;

    // The thread context that processes the image
    QPointer<QThread> m_thread;
    bb::ImageData fromQImage(const QImage &qImage);


public:
    AbstractLoader(const QString &imageUrl, const QString &imageUrl_orig, const QString &titel, const int type, QObject* parent = 0)
		: QObject(parent)
		, m_loading(false)
		, m_imageUrl(imageUrl)
    	, m_imageUrl_orig(imageUrl_orig)
		, m_title(titel)
		, m_type(type) {}
    virtual ~AbstractLoader(){}
	template <class T> friend inline T myqobject_cast(AbstractLoader *object);

	virtual void load() = 0;
	virtual void loadBigImage() = 0;

	QVariant image() const;
	QString label() const;
	QString title() const;
	bool loading() const;
	QString currentImageUrl() const;
	QString origImageUrl() const;
	int type() const;

	void finished(const QImage &image);


Q_SIGNALS:
	// The change notification signals of the properties
	void imageChanged();
	void labelChanged();
	void loadingChanged();
	void finished();
};

template <class T>
inline T myqobject_cast(AbstractLoader *base)
{
    if (dynamic_cast<T>(base))
        return dynamic_cast<T>(base);
    foreach(AbstractLoader *myqobject, base->_subObjects) {
        T returnValue = myqobject_cast<T>(myqobject);
        if (returnValue != T())
            return returnValue;
    }
    return dynamic_cast<T>(base); // not found
}

#endif /* ABSTRACTLOADER_HPP_ */
