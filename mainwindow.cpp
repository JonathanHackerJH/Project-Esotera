#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set some test values in the map.
    mainMap->set(new Goblin, 2, 3);
    mainMap->set(mainPlayer, 4, 4);
    mainMap->print(); //Display the map.
}

MainWindow::~MainWindow()
{
    delete ui;
}

