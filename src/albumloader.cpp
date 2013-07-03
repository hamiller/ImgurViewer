/*
 * albumloader.cpp
 *
 *  Created on: 02.07.2013
 *      Author: florian
 */
#include "albumloader.hpp"

#include "imageprocessor.hpp"


void AlbumLoader::load()
{
//	m_loading = true;
//	emit loadingChanged();
//
//	// iterate through the pics in the album and download them
//	std::list<AlbumPic>::iterator i;
//	for (i = m_albumPics->begin(); i != m_albumPics->end(); ++i) {
//		i.load();
//	}

}


void AlbumLoader::onReplyFinished()
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
void AlbumLoader::onImageProcessingFinished(const QImage &image)
{
	try
	{
		if (image.size().height() > 0) {
			m_image = bb::cascades::Image(fromQImage(image));
			if (m_imageUrl.endsWith(".gif"))
				m_type = 2;
			else
				m_type = 0;
		}
		else {
			m_type = 1;
		}
		emit imageChanged();

		m_label.clear();
		emit labelChanged();

		emit titleChanged();

		m_loading = false;

		emit loadingChanged();
	}
	catch (...)
	{
	}
}
