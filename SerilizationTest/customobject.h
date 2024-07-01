#ifndef CUSTOMOBJECT_H
#define CUSTOMOBJECT_H

#include <QObject>
#include <QDataStream>
#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QVector>
#include <memory>

class School {
public:
    School(const QString& name = "", const QString& address  = "", bool isGreat = false) :
        m_schoolName(name),
        m_schoolAddress(address),
        m_isGreat(isGreat){
    }

    QString toString() const {
        QString names;
        for(const QString& name : m_names) {
            names += "\n" + name;
        }

        return QString("School Name: %1, School Address: %2, Is School Great: %3, The Students Names Are:").
                arg(m_schoolName).
                arg(m_schoolAddress).
                arg((m_isGreat ? "True" : "False")) + names;
    }

    QVector<QString>& names() {
        return m_names;
    }

    friend QDataStream& operator<<(QDataStream& out, const School& school) {
        out << school.m_schoolName
            << school.m_schoolAddress
            << school.m_isGreat
            << school.m_names;
    }

    friend QDataStream& operator>>(QDataStream& in, School& school) {
        in >> school.m_schoolName
           >> school.m_schoolAddress
           >> school.m_isGreat
           >> school.m_names;
    }

private:
    QString m_schoolName;
    QString m_schoolAddress;
    QVector<QString> m_names;
    bool m_isGreat;
};

class CustomObject : public QObject
{
    Q_OBJECT
public:
    explicit CustomObject(QObject *parent = nullptr);
    CustomObject(const QString &name, int value, const QString& address,
                 const QString& schoolName,
                 const QString& schoolAddress,
                 bool isGreat,
                 QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    int value() const;
    void setValue(int value);

    QString address() const;
    void setAddress(const QString& address);

    School school() const;
    School* changeSchool();
    void setSchool(const School& address);

    // Override the stream operators for serialization
    friend QDataStream &operator<<(QDataStream &out, const CustomObject &obj);
    friend QDataStream &operator>>(QDataStream &in, CustomObject &obj);
    virtual ~CustomObject() {
    }

private:
    QString m_name;
    std::unique_ptr<QString> m_address;
    std::unique_ptr<School> m_school;
    int m_value;
};

#endif // CUSTOMOBJECT_H
