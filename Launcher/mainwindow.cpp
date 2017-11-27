#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MemLib.h"
#include <QPixmap>
#include <QPalette>
#include <QResource>
#include <QMessageBox>
#include "simplecrypt.h"
extern MemLib* pMemLib;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    new MemLib();
    ui->setupUi(this);
    pMemLib->EnableDebugPrivileges();
    QPixmap background(":background.png");
    background = background.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    setPalette(palette);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onClickLogIn()));
}

MainWindow::~MainWindow()
{
    delete pMemLib;
    delete ui;
}

void MainWindow::onClickLogIn()
{
     ui->pushButton->setEnabled(false);
     QFile* file = new QFile("G3MP-config.xml");
     if( file->open(QIODevice::WriteOnly) == true )
     {
         file->write(QString("<Sative_g3mp>\n<ip>"+ui->lineEdit->text()+"</ip>\n<nick>"+ui->lineEdit_3->text()+"</nick>\n<port>8888</port>\n</Sative_g3mp>").toStdString().c_str());
         file->close();
         delete file;
         size_t procID = pMemLib->StartExecutable("Gothic3.exe");
         if( procID != 0 )
         {
             if( pMemLib->InjectDLL(procID, "G3MP.dll") == false )
             {
                QMessageBox messageBox;
                messageBox.setWindowTitle("Error!");
                messageBox.setText("Cannot load G3MP.dll");
                messageBox.show();
             }
         }
         else
         {
             QMessageBox messageBox;
             messageBox.setWindowTitle("Error!");
             messageBox.setText("Cannot start Gothic3.exe (on steam, you must rename G3 main file to Gothic3.exe)");
             messageBox.show();
         }
     }
     Sleep(2000);
     ui->pushButton->setEnabled(true);
}
