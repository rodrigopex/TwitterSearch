/*
 * Network.h
 *
 *  Created on: Dec 26, 2012
 *      Author: rsarmentopeixoto
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include <qobject.h>
#include <QtNetwork>

class RPXNetwork: public QObject {
Q_OBJECT
public:
	RPXNetwork();
	virtual ~RPXNetwork();
	void loadURL(QUrl url);
	QString getData();
signals:
	void dataReady(QString data);
public slots:
	void replyFinished(QNetworkReply*);
private:
	QNetworkAccessManager m_manager;
	QString m_data;
};

#endif /* NETWORK_H_ */
