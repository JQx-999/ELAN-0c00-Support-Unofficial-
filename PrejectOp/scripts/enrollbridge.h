#pragma once
#include <QObject>
#include <QThread>

extern "C" {
    #include "enroll_handler.h"
}

class EnrollWorker : public QObject {
    Q_OBJECT
    public slots:
        void run() {
            emit enrollStarted();
            int result = enroll_start();
            if (result == 0)    emit fingerprintAdded();
            else if (result == -1) emit existingFinger();
            else    emit scanError();
        }
    signals:
        void enrollStarted();
        void fingerprintAdded();
        void existingFinger();
        void scanError();
};

class EnrollBridge : public QObject {
    Q_OBJECT
    public:
        explicit EnrollBridge(QObject *parent = nullptr) : QObject(parent) {
            worker = new EnrollWorker();
            worker->moveToThread(&thread);
            connect(&thread,    &QThread::started,  worker, &EnrollWorker::run);
            connect(worker,     &EnrollWorker::fingerprintAdded,    this,   &EnrollBridge::fingerprintAdded);
            connect(worker,     &EnrollWorker::existingFinger,    this,   &EnrollBridge::existingFinger);
            connect(worker,     &EnrollWorker::scanError,    this,   &EnrollBridge::scanError);
            connect(worker,     &EnrollWorker::enrollStarted,    this,   &EnrollBridge::enrollStarted);

        }

        ~EnrollBridge() {
            thread.quit();
            thread.wait();
        }

        Q_INVOKABLE void startScan() {
            if (!thread.isRunning()) {
                thread.start();
            } else {
                thread.quit();
                thread.wait();
                thread.start();
            }
        }
        signals:
            void enrollStarted();
            void fingerprintAdded();
            void existingFinger();
            void scanError();
        private:
            EnrollWorker *worker;
            QThread thread;
};