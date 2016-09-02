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

#ifndef HASHCHECKER_H
#define HASHCHECKER_H

#include <QMainWindow>
#include <QDropEvent>
#include <QUrl>
#include <QFile>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QSettings>
#include <QCryptographicHash>
#include <QFileInfo>
#include <QDebug>

#define SmallRatio 1.2

namespace Ui {
class HashChecker;
}

class HashChecker : public QMainWindow
{
    Q_OBJECT

public:
    explicit HashChecker(QWidget *parent = 0);
    ~HashChecker();

signals:
    void startCheck();

private slots:
    void on_hashInputLine_textChanged(const QString &arg1);
    void check();

    void on_algorythmBox_currentIndexChanged(int index);

private:
    Ui::HashChecker *ui;
    void dropEvent(QDropEvent *ev);
    void dragEnterEvent(QDragEnterEvent *ev);
    void dragLeaveEvent(QDragLeaveEvent *ev);
    QUrl FileUrl;
    QString FilePath;
    bool DragNDropEnabled;
    int height;
    int width;
    QString inputHash;
    QCryptographicHash::Algorithm Algorythm;
};

#endif // HASHCHECKER_H
