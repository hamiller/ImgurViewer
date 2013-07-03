/*
 * AlbumPic.h
 *
 *  Created on: 03.07.2013
 *      Author: florian
 */

#ifndef ALBUMPIC_H_
#define ALBUMPIC_H_

#include <QString>
#include <QVariant>

class AlbumPic
{
public:
	AlbumPic(QString link, QString description);
	virtual ~AlbumPic();

	void load();
	QVariant image() const;
	QString link() const;
	QString description() const;

private:
	QVariant m_image;
	QString m_link;
	QString m_description;
};

#endif /* ALBUMPIC_H_ */
