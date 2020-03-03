#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "gamemap.h"
#include "gameobjects.h"
#include "player.h"
#include "enemies.h"

// Initialize the GameMap
GameMap mainMap(5, 5);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set some test values in the map.
    mainMap.set(new Goblin, 2, 3);
    mainMap.set(new Player, 4, 4);
    mainMap.print(); //Display the map.
}

MainWindow::~MainWindow()
{
    delete ui;
}

