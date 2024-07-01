#include "customobject.h"

void serializeObject(const CustomObject &obj, const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open file for writing";
        return;
    }

    QDataStream out(&file);

    // Serialize object
    out << obj;
    file.close();
}

void deserializeObject(CustomObject &obj, const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file for reading";
        return;
    }

    QDataStream in(&file);

    // Deserialize object
    in >> obj;
    file.close();
}

int main(int argc, char *argv[])
{


    return a.exec();
}
