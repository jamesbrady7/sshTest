#include "customobject.h"

CustomObject::CustomObject(QObject *parent) : QObject(parent), m_value(0) {
}

CustomObject::CustomObject(const QString &name, int value,
                           const QString& address,
                           const QString& schoolName,
                           const QString& schoolAddress,
                           bool isGreat,
                           QObject *parent)
    : m_name(name), m_value(value), m_address(std::unique_ptr<QString>(new QString(address))),
      m_school(std::unique_ptr<School>(new School(schoolName, schoolAddress, isGreat)))
      , QObject(parent)  {
}

QString CustomObject::name() const {
    return m_name;
}

void CustomObject::setName(const QString &name) {
    m_name = name;
}

int CustomObject::value() const {
    return m_value;
}

void CustomObject::setValue(int value) {
    m_value = value;
}

QString CustomObject::address() const {
    return *m_address;
}

void CustomObject::setAddress(const QString& address) {
    m_address = std::unique_ptr<QString>(new QString(address));
}

School CustomObject::school() const {
    return *m_school;
}

School* CustomObject::changeSchool() {
    return m_school.get();
}

void CustomObject::setSchool(const School& address) {
    m_school = std::unique_ptr<School>(new School(address));
}

// Serialization operator for CustomObject
QDataStream &operator<<(QDataStream &out, const CustomObject &obj) {
    out << obj.name() << obj.value() << obj.address() << obj.school();
    return out;
}

// Deserialization operator for CustomObject
QDataStream &operator>>(QDataStream &in, CustomObject &obj) {
    QString name;
    int value;
    QString address;
    School school;
    in >> name >> value >> address >> school;
    obj.setName(name);
    obj.setValue(value);
    obj.setAddress(address);
    obj.setSchool(school);
    return in;
}

