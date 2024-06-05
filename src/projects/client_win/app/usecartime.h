#ifndef USECARTIME_H
#define USECARTIME_H

#include <qobject.h>
#include <qdatetime.h>

class UseCarTime : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QDate useCarDate READ useCarDate WRITE setUseCarDate)
	Q_PROPERTY(QTime useCarTime READ useCarTime WRITE setUseCarTime)
	Q_PROPERTY(QDate returnCarDate READ returnCarDate WRITE setReturnCarDate)
	Q_PROPERTY(QTime returnCarTime READ returnCarTime WRITE setReturnCarTime)
public:
	Q_INVOKABLE UseCarTime(QObject* parent = nullptr);
	Q_INVOKABLE UseCarTime(const UseCarTime& other);
	Q_INVOKABLE ~UseCarTime();

	Q_INVOKABLE QDate useCarDate();
	Q_INVOKABLE QTime useCarTime();
	Q_INVOKABLE QDate returnCarDate();
	Q_INVOKABLE QTime returnCarTime();
	Q_INVOKABLE void setUseCarDate(QDate date);
	Q_INVOKABLE void setUseCarTime(QTime time);
	Q_INVOKABLE void setReturnCarDate(QDate date);
	Q_INVOKABLE void setReturnCarTime(QTime time);

private:
	QDate _useCarDate;
	QTime _useCarTime;
	QDate _returnCarDate;
	QTime _returnCarTime;
};

Q_DECLARE_METATYPE(UseCarTime)

#endif // !USECARTIME_H
