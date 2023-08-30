#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H


#include <QObject>
#include <QWidget>

//File Ops Libs
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
//#include <QThread>
//#include <QProcess>
//#include <QDebug>
//#include <QMessageBox>
//#include <QDirIterator>
#include <QString>
#include <QDateTime>
#include <QThread>
//#include <QStandardPaths>
#include "dataparsingthread.h"

class MainController:  public QWidget{
    Q_OBJECT

public:
    MainController(QWidget *parent = nullptr);

signals:
    void selectedFileName2Qml(QString s_FileName);
    void fileDataComments(QString fileDataComment);
    void errorData(QString errData);

public slots:
    void selectAFile();
    void startParseDataThread();
    void updateThreadParsingStatus(QString);
    void collectDeletionResults(QString);
    void collectInsertionResults(QString);
    void threadFinished();

private:
    QString selectedFile = "";
    QString selectedFileName = "";
    QString selectedFilePath = "";
    QString fileData = "";

    QStringList splitList;
    QStringList alleleOne;
    QStringList alleleTwo;

    int deletionCount = 0;
    int insertionCount = 0;

    DataParsingThread *dataParsingThread;
};


#endif // MAINCONTROLLER_H
