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

#ifndef IMAGELOADER_HPP
#define IMAGELOADER_HPP

#include <QByteArray>
#include "abstractloader.hpp"
#include <bb/ImageData>
#include <QSemaphore>

/*
 * This class retrieves an image from the web, then converts the binary
 * data into a bb::cascades::Image and makes it available through a property.
 */
class ImageLoader : public AbstractLoader
{
	Q_OBJECT

public:
    /*
     * Creates a new image loader.
     *
     * @param imageUrl The url to load the image from.
     * @param imageUrl_orig is the original url of the image
     */
    ImageLoader(const QString &imageUrl, const QString &imageUrl_orig, const QString &titel, QObject* parent = 0) : AbstractLoader(imageUrl, imageUrl_orig, titel, parent) {}
    ~ImageLoader() {}

    virtual void load();

//private:
//    static QSemaphore sem(2);

private Q_SLOTS:
    /*
     * Response handler for the network operation.
     */
    void onReplyFinished(QNetworkReply* reply);

    /*
     * Response handler for the image process operation.
     */
    void onImageProcessingFinished(const QImage &image);

};

#endif
