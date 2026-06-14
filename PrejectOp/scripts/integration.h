#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <QObject>
#include <QFile>




class FileInt : public QObject {
    Q_OBJECT
    public:
        Q_INVOKABLE void copyFile(const QString &source, const QString &destination) {
            if (QFile::exists(destination)) {
                emit fileAlreadyThere();
                return;
            }


            bool success = QFile::copy(source, destination);
            if (success) {
                emit filePlaced();

            } else {
                emit scanError();
            }

        }
    signals:
        void scanError();
        void fileAlreadyThere();
        void filePlaced();
};

#endif