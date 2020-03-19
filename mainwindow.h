#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamemap.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QPixmap KnightSprite = QPixmap(":/pngs/knight.png");
    QPixmap DarkKnightSprite = QPixmap(":/pngs/knight2.png");
    QPixmap WallSprite = QPixmap(":/pngs/brickWall.png");
    QPixmap FireSprite = QPixmap(":/pngs/fire.png");
    QPixmap FloorSprite = QPixmap(":/pngs/floorTile.png");
    QPixmap LanternSprite = QPixmap(":/pngs/lanter.png");
    QPixmap PlayerSprite = QPixmap(":/pngs/playerFront.png");
    QPixmap PotionSprite = QPixmap(":/pngs/potion.png");
    QPixmap SpikeSprite = QPixmap(":/pngs/spike.png");
    QPixmap StairsSprite = QPixmap(":/pngs/stairs.png");

public:
    MainWindow(QWidget *parent = nullptr);
    void getGraphic(GameMap map);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
