#include "mainwindow.h"
#define IS_AI
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(640, 480);
    init();
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
#ifdef IS_AI
    if(stateNow == STATE_PLAY || stateNow == STATE_WAIT)
#else
    if(stateNow == STATE_PLAY)
#endif
    {
        QPoint p = pos2point(event -> pos());
        addPoint(p);
        update();
        int i = checkAll();
        if(i != PLAYER_NONE){
            stateNow = STATE_HOLD;
            QMessageBox::information(0,"","end");
        }
    }else if(stateNow == STATE_HOLD){
        init();
        update();
    }
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
        recStep.push(std::pair<QPoint,int>(QPoint(pos.x(),pos.y()),playerNow));
        changePlayer();
        changeState();
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
bool MainWindow::checkPoint(int x, int y) const
{
    int color = map[x][y];
    if(color == COLOR_NONE) return false;
    int num = 0;
    for(int i = 1; i < 5; ++i)
    {
        if(is_in(x,y) && map[x + i][y] == color){
            ++num;
        }else{
            break;
        }
    }
    for(int i = 1; i < 5; ++i)
    {
        if(is_in(x,y) && map[x - i][y] == color){
            ++num;
        }else{
            break;
        }
    }
    if(num >= 4) return true;
    num = 0;
    for(int i = 1; i < 5; ++i)
    {
        if(is_in(x,y) && map[x][y + i] == color){
            ++num;
        }else{
            break;
        }
    }
    for(int i = 1; i < 5; ++i)
    {
        if(is_in(x,y) && map[x][y - i] == color){
            ++num;
        }else{
            break;
        }
    }
    if(num >= 4) return true;
    num = 0;
    for(int i = 1; i < 5; ++i)
    {
        if(is_in(x,y) && map[x + i][y + i] == color){
            ++num;
        }else{
            break;
        }
    }
    for(int i = 1; i < 5; ++i)
    {
        if(is_in(x,y) && map[x - i][y - i] == color){
            ++num;
        }else{
            break;
        }
    }
    if(num >= 4) return true;
    num = 0;
    for(int i = 1; i < 5; ++i)
    {
        if(is_in(x,y) && map[x + i][y - i] == color){
            ++num;
        }else{
            break;
        }
    }
    for(int i = 1; i < 5; ++i)
    {
        if(is_in(x,y) && map[x - i][y + i] == color){
            ++num;
        }else{
            break;
        }
    }
    if(num >= 4) return true;
    return false;
}
bool MainWindow::checkPoint(QPoint p) const
{
    return checkPoint(p.x(), p.y());
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
int MainWindow::checkAll() const
{
    for(int i = 0; i < MAX_SIZE; ++i)
    {
        for(int j = 0; j < MAX_SIZE; ++j)
        {
            if(checkPoint(i, j) == true){
                return getPlayerByColor(map[i][j]);
            }
        }
    }
    return COLOR_NONE;
}
int MainWindow::getPlayerByColor(int color) const
{
    if(color == player_c_color){
        return PLAYER_C;
    }else if(color == player_h_color){
        return PLAYER_H;
    }
    return PLAYER_NONE;
}
void MainWindow::init()
{
    memset(map, 0, sizeof(map));
    playerNow = PLAYER_H;
    player_h_color = COLOR_BLACK;
    player_c_color = COLOR_WHITE;
    stateNow = STATE_PLAY;
    while(!recStep.empty())
    {
        recStep.pop();
    }
}
void MainWindow::changeState()
{
    if(stateNow == STATE_PLAY){
        stateNow = STATE_WAIT;
    }else if(stateNow == STATE_WAIT){
        stateNow = STATE_PLAY;
    }
}
void MainWindow::AI_Behavior()
{

}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event -> modifiers() == Qt::ControlModifier && event -> key() == Qt::Key_Z)
    {
        if(!recStep.empty())
        {
            std::pair<QPoint,int> p = recStep.top();
            QPoint pt = p.first;
            recStep.pop();
            map[pt.x()][pt.y()] = COLOR_NONE;
            changePlayer();
            changeState();
        }
    }
    update();
}
