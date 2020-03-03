#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "gamemap.h"
#include "gameobjects.h"
#include "player.h"
#include "enemies.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Player* mainPlayer = new Player();
    GameMap* mainMap = new GameMap(5, 5);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
