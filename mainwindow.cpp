#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rand_functions.h"

#include "gamemap.h"
#include "qdebug.h"
#include <unitTest.cpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap healthIcon(":/pngs/health.png");
    ui->healthIcon->setPixmap(healthIcon);
    QPixmap damageIcon(":/pngs/damage.png");
    ui->damageIcon->setPixmap(damageIcon);
    QPixmap shieldIcon(":/pngs/shield.png");
    ui->shieldIcon->setPixmap(shieldIcon);

    //QString textOutput = print();
   // ui->playableArea->setText(textOutput);

    //Call this if you want to run unit test, otherwise remove this line
    unitTest();
}

MainWindow::~MainWindow()
{
    delete ui;
}


