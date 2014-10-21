#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(640, 480);
    memset(map, 0, sizeof(map));
    playerNow = PLAYER_H;
    player_h_color = COLOR_BLACK;
    player_c_color = COLOR_WHITE;

}
MainWindow::~MainWindow()
{

}
void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    for(int i = 0; i < MAX_SIZE; ++i)
    {
        p.drawLine(30, 30 + i * 30, 450, 30 + i * 30);
        p.drawLine(30 + i * 30, 30, 30 + i * 30, 450);
    }
    QBrush b;
    b.setStyle(Qt::SolidPattern);
    for(int i = 0 ; i < MAX_SIZE; ++i)
    {
        for(int j = 0; j < MAX_SIZE; ++j)
        {
            int color = map[i][j];
            if(color == COLOR_NONE){
                continue;
            }else if(color == COLOR_BLACK){
                b.setColor(Qt::black);
            }else if(color == COLOR_WHITE){
                b.setColor(Qt::white);
            }
            p.setBrush(b);
            p.drawEllipse(point2pos(i,j),14,14);
        }
    }

}
QPoint MainWindow::pos2point(QPoint pos) const
{
    return QPoint((pos.x() - 15) / 30, (pos.y() - 15) / 30);
}
QPoint MainWindow::point2pos(QPoint point) const
{
    return QPoint(30 + point.x() * 30, 30 + point.y() * 30);
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint p = pos2point(event -> pos());
    addPoint(p);
    update();
}
QPoint MainWindow::point2pos(int x, int y) const
{
    return QPoint(30 + x * 30, 30 + y * 30);
}
QPoint MainWindow::pos2point(int x, int y) const
{
    return QPoint((x - 15) / 30, (y - 15) / 30);
}
void MainWindow::addPoint(QPoint pos)
{
    if(is_in(pos) && map[pos.x()][pos.y()] == COLOR_NONE)
    {
        map[pos.x()][pos.y()] = getPlayerColor(playerNow);
        changePlayer();
    }

}
int MainWindow::getPlayerColor(int player) const
{
    int color;
    if(player == PLAYER_C){
        color = player_c_color;
    }else if(player == PLAYER_H){
        color = player_h_color;
    }
    return color;
}
void MainWindow::changePlayer()
{
    if(playerNow == PLAYER_C){
        playerNow = PLAYER_H;
    }else{
        playerNow = PLAYER_C;
    }
}
bool MainWindow::check(QPoint p) const
{
    return false;
}
bool MainWindow::is_in(QPoint p) const
{
    return is_in(p.x(), p.y());
}
bool MainWindow::is_in(int x, int y) const
{
    if(x < 0 || y < 0 || x >= MAX_SIZE || y >= MAX_SIZE) return false;
    return true;
}
