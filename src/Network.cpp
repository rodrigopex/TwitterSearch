/*
 * Network.cpp
 *
 *  Created on: Dec 26, 2012
 *      Author: rsarmentopeixoto
 */

#include "Network.h"

RPXNetwork::RPXNetwork() {
}

RPXNetwork::~RPXNetwork() {
}

void RPXNetwork::loadURL(QUrl url) {
	connect(&m_manager, SIGNAL(finished(QNetworkReply*)),
	        this, SLOT(replyFinished(QNetworkReply*)));
	m_manager.get(QNetworkRequest(url));
}

void RPXNetwork::replyFinished(QNetworkReply * reply) {
	disconnect(&m_manager, SIGNAL(finished(QNetworkReply*)),
		        this, SLOT(replyFinished(QNetworkReply*)));
	m_data = QString(reply->readAll());
	emit this->dataReady(m_data);
	reply->deleteLater();
}
