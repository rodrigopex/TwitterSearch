// Default empty project template
#include "TwitterSearch.hpp"
#include <qdebug.h>

TwitterSearch::TwitterSearch(Application *app) :
		QObject(app) {
	qRegisterMetaType<GroupDataModel *>("GroupDataModel *");
	qRegisterMetaType<ArrayDataModel *>("ArrayDataModel *");
	m_model = new GroupDataModel;
	m_model->setSortedAscending(false);

	m_recentsModel = new ArrayDataModel;

	QSettings settings;
	m_recents = settings.value("recents", QVariant(QVariantList())).toList();
	this->filterRecents("");
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
	QVariant vKey(key.toLower());
	//m_recents = settings.value("recents", QVariant(QVariantList())).toList();
	qDebug() << m_recents;
	if (!m_recents.contains(vKey)) {
		m_recents.insert(0, vKey);
		settings.setValue("recents", QVariant(m_recents));
		settings.sync();
	} else {
		m_recents.move(m_recents.indexOf(vKey), 0);
	}
	m_recentsModel->clear();
	m_recentsModel->insert(0, m_recents);
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

bool lessThanTweet(const QVariant& a, const QVariant& b) {
	return a.toMap()["created_at"].toDate() < b.toMap()["created_at"].toDate();
}

void TwitterSearch::onNewDataModelReady(QString data) {
	disconnect(&m_network, SIGNAL(dataReady(QString)), this,
			SLOT(onNewDataModelReady(QString)));
	JsonDataAccess jda;
	QVariant jsonData = jda.loadFromBuffer(data);
	m_model->clear();
	QVariantList results = jsonData.toMap()["results"].toList();
	QVariantList resultsWDate;
	foreach(QVariant tweet, results){
		QVariantMap tweetWDate = tweet.toMap();
		tweetWDate["created_at"] = QVariant(QDate::fromString(tweetWDate["created_at"].toString()));
		resultsWDate.append(QVariant(tweetWDate));
	}
	qSort(resultsWDate.begin(), resultsWDate.end(), lessThanTweet);
	m_model->insertList(resultsWDate);
	emit this->onModelChanged();
}

ArrayDataModel * TwitterSearch::recentsModel() {
	return m_recentsModel;
}

void TwitterSearch::filterRecents(QString key) {
	m_recentsModel->clear();
	QString tmp = key.toLower();
	foreach(QVariant vr, m_recents){
		if((vr.toString()).startsWith(tmp)) {
			m_recentsModel->append(vr);
		}
	}
}

void TwitterSearch::clearRecents() {
	QSettings settings;
	settings.clear();
	m_recents.clear();
}
