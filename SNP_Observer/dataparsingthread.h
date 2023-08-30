#ifndef DATAPARSINGTHREAD_H
#define DATAPARSINGTHREAD_H


#include <QThread>
#include <QObject>
#include <QFileInfo>
#include <QFileDialog>

class DataParsingThread: public QThread{
    Q_OBJECT

public:
    DataParsingThread(QString, QThread *parent = 0);
    void run();

signals:
    void statusMessage(QString);
    void deletionResults(QString);
    void insertionResults(QString);

public slots:

private:
    QString selectedFilePath = "";
    QString fileData = "";
    QStringList splitList;
    QStringList alleleOne;
    QStringList alleleTwo;
    QString eyeColor = "";
    QString gender = "";
    QString sunSensitivity = "";
    QString peanutAllergy = "";

    int deletionCount = 0;
    int insertionCount = 0;
    int i_SnpCount = 0;

    bool eyeColorFound = false;
    bool genderFound = false;
    bool sunSensitivityFound = false;
    bool peanutAllergyFound = false;
};

#endif // DATAPARSINGTHREAD_H
