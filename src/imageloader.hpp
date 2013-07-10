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

#ifndef IMAGELOADER_HPP
#define IMAGELOADER_HPP

#include <QByteArray>
#include "abstractloader.hpp"
#include <bb/ImageData>
#include <QSemaphore>

class ImageLoader
	: public AbstractLoader
{
	Q_OBJECT

public:
    ImageLoader(const QString &imageUrl, const QString &imageUrl_orig, const QString &titel, const int type, QObject* parent = 0)
    	: AbstractLoader(imageUrl, imageUrl_orig, titel, type, parent) {}
    ~ImageLoader() {}

    virtual void load();
	virtual void loadBigImage();

private Q_SLOTS:
	void onReplyFinished();
    void onImageProcessingFinished(const QImage &image);
};

#endif
