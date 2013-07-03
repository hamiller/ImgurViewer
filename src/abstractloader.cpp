/*
 * abstractloader.cpp
 *
 *  Created on: 02.07.2013
 *      Author: florian
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
