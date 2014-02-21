#ifndef ILWISTESTCLASS_H
#define ILWISTESTCLASS_H

#include <QObject>

class IlwisTestCase : public QObject
{
    Q_OBJECT
public:
    explicit IlwisTestCase(const QString& name, const QString& module, QObject *parent = 0);
    QString name() const;
    QString module() const;
private:
    QString _name;
    QString _module;
    
signals:
    
public slots:
    
};

#endif // ILWISTESTCLASS_H
