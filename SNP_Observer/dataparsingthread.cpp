#include "dataparsingthread.h"

DataParsingThread::DataParsingThread(QString fileLocation, QThread *parent) : QThread(parent), selectedFilePath(fileLocation){

}

void DataParsingThread::run(){
    //emit statusMessage("Data parsing starting...");
    QFile sFile(selectedFilePath);
    if(!sFile.open(QIODevice::ReadOnly)){
        //emit errorData("Error opening file...");
    }
    QTextStream in(&sFile);
    while (!in.atEnd()){
        fileData = in.readLine();
        //emit statusMessage(fileData);
        //QThread::msleep(300);
        if(fileData.contains("#")){
            //emit statusMessage(fileData);
        }
        else if(fileData.contains("rsid")){
            //Do nothing for now
        }
        else{
            splitList = fileData.split("\t");
            i_SnpCount++;

            //Get eye color based and the rs12913832 SNP.
            if(splitList.at(0) == "rs12913832"){
                if(splitList.at(3) == "A" && splitList.at(4) == "G"){
                    eyeColor = "Brown - rs12913832";
                }
                else if(splitList.at(3) == "A" && splitList.at(4) == "A"){
                    eyeColor = "Brown 80 - rs12913832";
                }
                else if(splitList.at(3) == "G" && splitList.at(4) == "G"){
                    eyeColor = "Blue - rs12913832";
                }
                else{
                    eyeColor = "";
                }
            }

            //Check for the presence of the Y sex chromosome
            if(splitList.at(0) == "rs13447378"){
                if(splitList.at(0) == "rs13447378"){
                    gender = "XY - rs13447378";
                }
                else{
                    gender = "XX - rs13447378";
                }
            }

            //Sun sensitivity
            if(splitList.at(0) == "rs1015362"){
                if(splitList.at(3) == "G" && splitList.at(4) == "G"){
                    sunSensitivity = "2-4x higher risk of sun sensitivity - rs1015362";
                }
                else if(splitList.at(3) == "C" && splitList.at(4) == "C"){
                    sunSensitivity = "2-4x higher risk of sun sensitivity - rs1015362";
                }
                else if(splitList.at(3) == "A" && splitList.at(4) == "A"){
                    sunSensitivity = "Probably tans instead of freckles and sunburns - rs1015362";
                }
                else if(splitList.at(3) == "A" && splitList.at(4) == "G"){
                    sunSensitivity = "2-4x higher risk of sun sensitivity - rs1015362";
                }
            }

            //Peanut allergy
            if(splitList.at(0) == "rs7192"){
                if(splitList.at(3) == "G" && splitList.at(4) == "G"){
                    peanutAllergy = "No increaded risk of peanut allergy - rs7192";
                }
                else if(splitList.at(3) == "G" && splitList.at(4) == "T"){
                    peanutAllergy = "1.7x increased risk for developing a peanut allergy - rs7192";
                }
                else if(splitList.at(3) == "T" && splitList.at(4) == "T"){
                    peanutAllergy = "3x higher risk for developing a peanut allergy - rs7192";
                }
                else{
                    peanutAllergy = "No data found - rs7192";
                }
            }

            //Count deletions
            if(splitList.at(3) == "D"){
                deletionCount++;
            }
            //Count insertions
            else if(splitList.at(3) == "I"){
                insertionCount++;
            }
        }
    }
    sFile.close();
    //qDebug() << "Done parsing file.....";
    //emit statusMessage("Data parsing complete");
    emit statusMessage("SNP Count: " + QString::number(i_SnpCount));
    emit deletionResults("SNP Deletion Count: " + QString::number(deletionCount));
    emit insertionResults("SNP Insertion Count: " + QString::number(insertionCount));
    emit statusMessage("Eye Color: " + eyeColor);
    emit statusMessage("Sex Chromosomes: " + gender);
    emit statusMessage("Sun Sensitivity: " + sunSensitivity);
    emit statusMessage("Peanut Allergy: " + peanutAllergy);

    deletionCount = 0;
    insertionCount = 0;
    eyeColor = "";
    i_SnpCount = 0;
    gender = "";
    sunSensitivity = "";
    peanutAllergy = "";
}
