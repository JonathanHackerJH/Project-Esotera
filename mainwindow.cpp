#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rand_functions.h"

#include "gamemap.h"
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Sets a random seed for randomization to have different outputs.
    randomize();

    // Declaring mainMap and mainPlayer.
    GameMap mainMap = GameMap(5, 5);
    GameObject* mainPlayer = mainMap.create<Player>(0, 0, true);
    //mainMap.create<Goblin>(1, 1);
    //mainMap.create<Spike>(1, 0);
    mainMap.create<Tombstone>(1,0);
    mainMap.create<Wall>(1, 1);
    qDebug().noquote() << mainMap.print();

    mainPlayer->move(1, 0);
    qDebug().noquote() << mainMap.print();

    mainPlayer->move(0, 1);
    qDebug().noquote() << mainMap.print();

    mainPlayer->move(0, 1);
    qDebug().noquote() << mainMap.print();

    mainPlayer->move(0, 1);
    qDebug().noquote() << mainMap.print();
}

MainWindow::~MainWindow()
{
    delete ui;
}

