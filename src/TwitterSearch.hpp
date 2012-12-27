// Default empty project template
#ifndef TwitterSearch_HPP_
#define TwitterSearch_HPP_

#include <QObject>
#include <bb/data/JsonDataAccess>
#include <bb/cascades/GroupDataModel>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/Container>
#include <bb/cascades/SceneCover>
#include <qvariant.h>
#include <QSettings>

#include "Network.h"

using namespace bb::cascades;
using namespace bb::data;

class TwitterSearch: public QObject {
	Q_OBJECT
	Q_PROPERTY(GroupDataModel * model READ model NOTIFY onModelChanged);
public:
	TwitterSearch(Application *app);
	virtual ~TwitterSearch() {
	}
	Q_INVOKABLE
	GroupDataModel * model();
	Q_INVOKABLE
	void searchKey(QString rawKey);
	void saveSearchKey(QString key);
signals:
	void onModelChanged();
public slots:
	void onNewDataModelReady(QString data);
	void createCover();
private:
	GroupDataModel * m_model;
	Network m_network;

};

#endif /* TwitterSearch_HPP_ */
