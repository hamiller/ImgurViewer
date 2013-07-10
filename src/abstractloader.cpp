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

#include "abstractloader.hpp"

#include <bb/ImageData>


QVariant AbstractLoader::image() const
{
	return QVariant::fromValue(m_image);
}

QString AbstractLoader::label() const
{
    return m_label;
}

QString AbstractLoader::title() const
{
	return m_title;
}

bool AbstractLoader::loading() const
{
    return m_loading;
}

QString AbstractLoader::currentImageUrl() const
{
	return m_imageUrl;
}

QString AbstractLoader::origImageUrl() const
{
	return m_imageUrl_orig;
}

int AbstractLoader::type() const
{
	return m_type;
}

bb::ImageData AbstractLoader::fromQImage(const QImage &qImage)
{
	bb::ImageData imageData(bb::PixelFormat::RGBA_Premultiplied, qImage.width(), qImage.height());

	unsigned char *dstLine = imageData.pixels();
	for (int y = 0; y < imageData.height(); y++)
	{
		unsigned char * dst = dstLine;
		for (int x = 0; x < imageData.width(); x++)
		{
			QRgb srcPixel = qImage.pixel(x, y);
			*dst++ = qRed(srcPixel);
			*dst++ = qGreen(srcPixel);
			*dst++ = qBlue(srcPixel);
			*dst++ = qAlpha(srcPixel);
		}
		dstLine += imageData.bytesPerLine();
	}

	return imageData;
}
