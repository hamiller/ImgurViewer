/*
 * albumloader.hpp
 *
 *  Created on: 02.07.2013
 *      Author: florian
 */

#ifndef ALBUMLOADER_HPP_
#define ALBUMLOADER_HPP_

#include "abstractloader.hpp"
#include "AlbumPic.h"


class AlbumLoader : public AbstractLoader
{
	Q_OBJECT

public:

	AlbumLoader(const QString &imageUrl, const QString &imageUrl_orig, const QString &titel, QObject* parent = 0) : AbstractLoader(imageUrl, imageUrl_orig, titel, parent) {}
	AlbumLoader(std::list<AlbumPic*> *albumPics, const QString &imageUrl, const QString &imageUrl_orig, const QString &titel, QObject* parent = 0) : AbstractLoader(imageUrl, imageUrl_orig, titel, parent), m_albumPics(albumPics) {}
	~AlbumLoader() {}

	virtual void load();

private:
	std::list<AlbumPic*> *m_albumPics;

private Q_SLOTS:
    /*
     * Response handler for the network operation.
     */
    void onReplyFinished();

    /*
     * Response handler for the image process operation.
     */
    void onImageProcessingFinished(const QImage &image);
};


#endif /* ALBUMLOADER_HPP_ */
