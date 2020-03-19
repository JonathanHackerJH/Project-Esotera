#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rand_functions.h"

#include "gamemap.h"
#include "gameobject.h"
#include "qdebug.h"
#include "terrainmap.h"
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

    //Call this if you want to run unit test, otherwise remove this line
 //   unitTest();
    GameMap mainMap = makeLevel(15, 15);
    getGraphic(mainMap);
    setStats();
}


void MainWindow::getGraphic(GameMap map)
{

    QString text = map.print();

    ui->playableArea->setText(text);

}

void MainWindow::setStats()
{
    ui->healthLabel->setNum(10.0);
    ui->shieldLabel->setNum(1.0);
    ui->damageLabel->setNum(1.0);


}

MainWindow::~MainWindow()
{
    delete ui;
}


