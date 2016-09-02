/*
Copyright 2016 Luca Angioloni

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "hashchecker.h"
#include "ui_hashchecker.h"

HashChecker::HashChecker(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HashChecker)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    DragNDropEnabled = false;
    ui->InstructionLabel->setText("Write the hash to check and pick the algorythm.");
    height = ui->imageLabel->height();
    width = ui->imageLabel->width();
    Algorythm = QCryptographicHash::Sha1;

    QObject::connect(this, SIGNAL(startCheck()), this, SLOT(check()));
}

HashChecker::~HashChecker()
{
    delete ui;
}

void HashChecker::dragEnterEvent(QDragEnterEvent *ev)
{
    if(DragNDropEnabled){
        ev->accept();
        int h = height;
        int w = width;
        QPixmap pix(":Images/DropArrowImage.png");
        ui->imageLabel->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void HashChecker::dragLeaveEvent(QDragLeaveEvent *ev)
{
    if(DragNDropEnabled){
        ev->accept();
        int h = height/SmallRatio;
        int w = width/SmallRatio;
        QPixmap pix(":Images/DropArrowImage.png");
        ui->imageLabel->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void HashChecker::dropEvent(QDropEvent *ev)
{
    if(DragNDropEnabled){
        ev->accept();
        QList<QUrl> tmpL;
        tmpL = ev->mimeData()->urls();
        if(!tmpL.isEmpty() && !tmpL.at(0).toString().endsWith("/")){
            FileUrl = tmpL.at(0);
            FilePath = FileUrl.toString();
            FilePath = FilePath.remove(0,7);
            int h = height/SmallRatio;
            int w = width/SmallRatio;
            QPixmap pix(":Images/DropArrowImage.png");
            ui->imageLabel->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            ui->InstructionLabel->setText("Calculating...");
            this->repaint();
            QApplication::processEvents();
            emit startCheck();
        }
        else {
            int h = height/SmallRatio;
            int w = width/SmallRatio;
            QPixmap pix(":Images/DropArrowImage.png");
            ui->imageLabel->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }
}


void HashChecker::on_hashInputLine_textChanged(const QString &arg1)
{
    inputHash = arg1;
    if(arg1.isEmpty()){
        ui->InstructionLabel->setText("Write the hash to check and pick the algorythm.");
        ui->imageLabel->clear();
        DragNDropEnabled = false;
    }
    else{
        ui->InstructionLabel->setText("Drag and Drop the file to check.");
        int h = height/SmallRatio;
        int w = width/SmallRatio;
        QPixmap pix(":Images/DropArrowImage.png");
        ui->imageLabel->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        DragNDropEnabled = true;
    }
}

void HashChecker::check(){
    QFile file(FilePath);
    QFileInfo info(FilePath);
    file.open(QFile::ReadOnly);
    QCryptographicHash hasher(Algorythm);
    hasher.addData(&file);
    QByteArray result = hasher.result().toHex();
    file.close();
    QByteArray input;
    input.append(inputHash);
    if( result == input ){
        QPixmap pix(":Images/OkImage.png");
        ui->imageLabel->setPixmap(pix.scaled(width,height, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->InstructionLabel->setText(( info.fileName() + " is OK!"));
    }
    else{
        QPixmap pix(":Images/WrongImage.png");
        ui->imageLabel->setPixmap(pix.scaled(width,height, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->InstructionLabel->setText((info.fileName() + " is not OK!"));
    }
}

void HashChecker::on_algorythmBox_currentIndexChanged(int index)
{
    if(index == 0){
        Algorythm = QCryptographicHash::Sha1;
    }
    else{
        Algorythm = QCryptographicHash::Md5;
    }
}
