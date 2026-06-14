#pragma once
#include <QObject>
#include <QThread>


extern "C" {
#include "usb_handler.h"
}

class UsbWorker : public QObject {
    Q_OBJECT
public slots:
    void run() {
        emit scanStarted();
        int result = usb_start();
        if (result == 0)      emit matchSuccess();
        else if (result == 1) emit wrongFinger();
        else if (result == -1) emit scanTimeout();
        else                  emit scanError();
    }
signals:
    void scanStarted();
    void matchSuccess();
    void wrongFinger();
    void scanTimeout();
    void scanError();
};

class UsbBridge : public QObject {
    Q_OBJECT

public:
    explicit UsbBridge(QObject *parent = nullptr) : QObject(parent) {
        worker = new UsbWorker();
        worker->moveToThread(&thread);
        connect(&thread,  &QThread::started,        worker, &UsbWorker::run);
        connect(worker,   &UsbWorker::matchSuccess, this,   &UsbBridge::matchSuccess);
        connect(worker,   &UsbWorker::wrongFinger,  this,   &UsbBridge::wrongFinger);
        connect(worker,   &UsbWorker::scanTimeout,  this,   &UsbBridge::scanTimeout);
        connect(worker,   &UsbWorker::scanError,    this,   &UsbBridge::scanError);
        connect(worker, &UsbWorker::scanStarted, this, &UsbBridge::scanStarted);
    }

    ~UsbBridge() {
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
    void scanStarted();
    void matchSuccess();
    void wrongFinger();
    void scanTimeout();
    void scanError();

private:
    UsbWorker *worker;
    QThread    thread;
};