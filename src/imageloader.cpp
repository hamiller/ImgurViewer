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

#include "imageloader.hpp"

#include "imageprocessor.hpp"

#include <bb/ImageData>

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>


void ImageLoader::loadBigImage()
{
	m_loading = true;
	emit loadingChanged();

	qDebug() << "FMI ########## start loading " << m_imageUrl_orig;
	QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this); // up to 6 connections at a time

	const QUrl url(m_imageUrl);
	QNetworkRequest request(url);

	QNetworkReply* reply = networkAccessManager->get(request);
	connect(reply, SIGNAL(finished()), this, SLOT(onReplyFinished()));
}

void ImageLoader::load()
{
	m_loading = true;
    emit loadingChanged();

    qDebug() << "FMI ########## start loading " << m_imageUrl;
    QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this); // up to 6 connections at a time

    const QUrl url(m_imageUrl);
    QNetworkRequest request(url);

    QNetworkReply* reply = networkAccessManager->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(onReplyFinished()));
}

/**
 * ImageLoader::onReplyFinished()
 *
 * Handler for the signal indicating the response for the previous network request.
 *
 * If the result was a success, it will start the thread of constructing the QImage object.
 */

void ImageLoader::onReplyFinished()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QString response;
    if (reply) {
        if (reply->error() == QNetworkReply::NoError) {
            const int available = reply->bytesAvailable();
            if (available > 0) {
                const QByteArray data(reply->readAll());

                // Setup the image processing thread
                ImageProcessor *imageProcessor = new ImageProcessor(data);
                m_thread = new QThread(this);

                // Move the image processor to the worker thread
                imageProcessor->moveToThread(m_thread);

                // Invoke ImageProcessor's start() slot as soon as the worker thread has started
                connect(m_thread, SIGNAL(started()), imageProcessor, SLOT(start()));

                // Delete the worker thread automatically after it has finished
                connect(m_thread, SIGNAL(finished()), m_thread, SLOT(deleteLater()));

                /*
                 * Invoke our onProcessingFinished slot after the processing has finished.
                 * Since imageProcessor and 'this' are located in different threads we use 'QueuedConnection' to
                 * allow a cross-thread boundary invocation. In this case the QImage parameter is copied in a thread-safe way
                 * from the worker thread to the main thread.
                 */
                connect(imageProcessor, SIGNAL(finished(QImage)), this, SLOT(onImageProcessingFinished(QImage)), Qt::QueuedConnection);

                // Terminate the thread after the processing has finished
                connect(imageProcessor, SIGNAL(finished(QImage)), m_thread, SLOT(quit()));

                m_thread->start();
            }
        } else {
            m_label = tr("Error: %1 status: %2").arg(reply->errorString(), reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString());
            emit labelChanged();

            m_loading = false;
            emit loadingChanged();
        }

        reply->deleteLater();
    } else {
        m_label = tr("Download failed. Check internet connection");
        emit labelChanged();

        m_loading = false;
        emit loadingChanged();
    }
}

/**
 * ImageLoader::onImageProcessingFinished(const QImage&)
 *
 * Handler for the signal indicating the result of the image processing.
 */
void ImageLoader::onImageProcessingFinished(const QImage &image)
{
	try
	{
		if (!image.isNull()) {
			if (image.size().height() > 0) {
				m_image = bb::cascades::Image(fromQImage(image));
			}
			emit imageChanged();

			m_label.clear();
			emit labelChanged();
		}

		m_loading = false;

		emit loadingChanged();
	}
	catch (...)
	{
		qDebug() << "FMI ##### AAAAAAAAAAAAAAAAAAAAAAAAAAAAAHHHHH!!!!";
	}
}
