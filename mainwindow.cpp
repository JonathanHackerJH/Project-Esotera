#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"

double globalTest = 0.0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set some test values in the map.
    mainMap->replace(new Goblin, 2, 3);
    mainMap->replace(mainPlayer, 4, 4);

    // Debug display the map.
    qDebug().noquote() << mainMap->print();

    mainPlayer->move(0, -1);
    qDebug().noquote() << mainMap->print();
}

MainWindow::~MainWindow()
{
    delete ui;
}

