// Default empty project template
#include "TwitterSearch.hpp"
#include <qdebug.h>

TwitterSearch::TwitterSearch(Application *app) :
		QObject(app) {
	qRegisterMetaType<GroupDataModel *>("GroupDataModel *");
	m_model = new GroupDataModel();
	m_model->setSortedAscending(false);

	connect(app, SIGNAL(thumbnail()), this, SLOT(createCover()));

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

void TwitterSearch::searchKey(QString rawKey) {
	QString key = rawKey.trimmed();
	this->saveSearchKey(key);
	QString urlStr = QString("http://search.twitter.com/search.json?q=%1").arg(
			key);
	QUrl url(urlStr);
	m_network.loadURL(url);
	connect(&m_network, SIGNAL(dataReady(QString)), this,
			SLOT(onNewDataModelReady(QString)));
}

void TwitterSearch::saveSearchKey(QString key) {
	QSettings settings;
	QStringList recents =
			settings.value("recents", QVariant(QStringList())).toStringList();
	qDebug() << recents;
	if (!recents.contains(key, Qt::CaseInsensitive)) {
		recents.append(key);
		recents.sort();
		settings.setValue("recents", QVariant(recents));
//		settings.sync();
	}
}

void TwitterSearch::createCover() {
	qDebug() << "creating cover";
	QVariantList lastTweetIndexPath = m_model->first();
	QVariantMap lastTweet = m_model->data(lastTweetIndexPath).toMap();
	if (lastTweet.size() > 0) {
		QmlDocument *qmlCover =
				QmlDocument::create("asset:///cover.qml").parent(this);
		QDeclarativePropertyMap * qdpm = new QDeclarativePropertyMap;
		qdpm->insert("from_user", lastTweet["from_user"]);
		qdpm->insert("created_at", lastTweet["created_at"]);
		qdpm->insert("text", lastTweet["text"]);
		qmlCover->setContextProperty("lastTweet", qdpm);
		Container *rootContainer = qmlCover->createRootObject<Container>();
		SceneCover *cover = SceneCover::create().content(rootContainer);
		Application::instance()->setCover(cover);
	}
}

void TwitterSearch::onNewDataModelReady(QString data) {
	disconnect(&m_network, SIGNAL(dataReady(QString)), this,
			SLOT(onNewDataModelReady(QString)));
	JsonDataAccess jda;
	QVariant jsonData = jda.loadFromBuffer(data);
	m_model->clear();
	m_model->insertList(jsonData.toMap()["results"].toList());
	emit this->onModelChanged();

}
