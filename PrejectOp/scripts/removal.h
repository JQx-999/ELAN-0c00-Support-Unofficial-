#ifndef REMOVAL_H
#define REMOVAL_H

#include <QObject>
#include <QFile>
#include <QDebug>

class Removal : public QObject {
    Q_OBJECT
    public:
        Q_INVOKABLE void removeFile(const QString &path) {
            QFile file(path);
            if (!file.exists()) {
                qDebug() << "File does not exist";
                emit fileNotExist();
                return;
            }
            if (file.remove()) {
                qDebug() << "File removed successfully";
                emit fileRemoved();
            } else {
                qDebug() << "Failed to remove file";
                emit scanError();
            }
        }
    signals:
        void scanError();
        void fileNotExist();
        void fileRemoved();
};
#endif