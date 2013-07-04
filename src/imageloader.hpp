
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
