#pragma once
#include <QObject>
#include <QThread>

extern "C" {
    #include "remove_handler.h"
}

class RemoveWorker : public QObject {
    Q_OBJECT
    public slots:
        void run() {
            emit removeStarted();
            int result = remove_start();
            if (result == 0) emit fingerprintRemoved();
            else emit scanError();
        }
    signals:
        void removeStarted();
        void fingerprintRemoved();
        void scanError();
};

class RemoveBridge : public QObject {
    Q_OBJECT
    public:
        explicit RemoveBridge(QObject *parent = nullptr) : QObject(parent) {
            worker = new RemoveWorker();
            worker->moveToThread(&thread);
            connect(&thread,    &QThread::started,  worker, &RemoveWorker::run);
            connect(worker, &RemoveWorker::fingerprintRemoved,  this,   &RemoveBridge::fingerprintRemoved);
            connect(worker, &RemoveWorker::scanError,   this,   &RemoveBridge::scanError);
            connect(worker, &RemoveWorker::removeStarted,   this,   &RemoveBridge::removeStarted);
        }

        ~RemoveBridge() {
            thread.quit();
            thread.wait();
        }

        Q_INVOKABLE void startRemove() {
            if (!thread.isRunning()) {
                thread.start();
            } else {
                thread.quit();
                thread.wait();
                thread.start();
            }
        }
        signals:
            void removeStarted();
            void fingerprintRemoved();
            void scanError();
        private:
            RemoveWorker *worker;
            QThread thread;
};