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
