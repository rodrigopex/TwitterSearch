// Default empty project template
#include "TwitterSearch.hpp"
#include <qdebug.h>

TwitterSearch::TwitterSearch(Application *app) :
		QObject(app) {
	qRegisterMetaType<GroupDataModel *>("GroupDataModel *");
	m_model = new GroupDataModel();
	m_model->setSortedAscending(false);

	/*
	 * Esse 'e o modo de fazer a coisa estaticamente!
	 JsonDataAccess jda;
	 QString path = "app/native/assets/models/search.json";
	 QVariant jsonData = jda.load(path);

	 m_model->insertList(jsonData.toMap()["results"].toList());
	 */

	QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
	qml->setContextProperty("_controller", this);

	AbstractPane *root = qml->createRootObject<AbstractPane>();
	app->setScene(root);
}

GroupDataModel * TwitterSearch::model() {
	return m_model;
}

void TwitterSearch::searchKey(QString key) {
	QString urlStr = QString("http://search.twitter.com/search.json?q=%1").arg(key.trimmed());
	m_network.loadURL(QUrl(urlStr));
	connect(&m_network, SIGNAL(dataReady(QString)), this,
			SLOT(onNewDataModelReady(QString)));
}

void TwitterSearch::onNewDataModelReady(QString data) {
	disconnect(&m_network, SIGNAL(dataReady(QString)), this,
				SLOT(onNewDataModelReady(QString)));
	JsonDataAccess jda;
	QVariant jsonData = jda.loadFromBuffer(data);
	m_model->clear();
	m_model->insertList(jsonData.toMap()["results"].toList());
	emit this->onModelChanged(); //funcinou sem o emit

}
