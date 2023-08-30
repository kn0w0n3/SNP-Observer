#include "maincontroller.h"

MainController::MainController(QWidget *parent) : QWidget(parent){

}

void MainController::selectAFile(){
    selectedFile = QFileDialog::getOpenFileName(Q_NULLPTR, tr("Select File"), "/home");
    QFileInfo fileInfo(selectedFile);
    selectedFileName = fileInfo.fileName().trimmed();
    emit selectedFileName2Qml(selectedFileName);
    selectedFilePath = fileInfo.filePath().trimmed();
}

void MainController::startParseDataThread(){
    QDateTime dateTime = dateTime.currentDateTime();
    QString dateTimeString = dateTime.toString("yyyy-MM-dd h:mm:ss ap");
    emit fileDataComments("Data parsing starting @ " + dateTimeString + "\n");

    dataParsingThread = new DataParsingThread(selectedFilePath);
    connect(dataParsingThread, &DataParsingThread::insertionResults, this, &MainController::collectInsertionResults);
    connect(dataParsingThread, &DataParsingThread::deletionResults, this, &MainController::collectDeletionResults);
    connect(dataParsingThread, &DataParsingThread::statusMessage, this, &MainController::updateThreadParsingStatus);
    connect(dataParsingThread, &DataParsingThread::finished, this, &MainController::threadFinished);
    dataParsingThread->start();
}

void MainController::updateThreadParsingStatus(QString message){
    emit fileDataComments(message);
}

void MainController::collectDeletionResults(QString d_Result){
    emit fileDataComments(d_Result);
}

void MainController::collectInsertionResults(QString i_Result){
    emit fileDataComments(i_Result);
}

void MainController::threadFinished(){
    QDateTime dateTime = dateTime.currentDateTime();
    QString dateTimeString = dateTime.toString("yyyy-MM-dd h:mm:ss ap");
    emit fileDataComments("\nData parsing completed @ " + dateTimeString);
}
