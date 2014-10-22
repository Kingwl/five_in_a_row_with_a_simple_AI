#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMessageBox>
#include <QMouseEvent>
#include <QKeyEvent>
#include <stack>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    static const int MAX_SIZE = 15;
    static const int COLOR_NONE = 0;
    static const int COLOR_WHITE = 1;
    static const int COLOR_BLACK = 2;
    static const int PLAYER_NONE = 0;
    static const int PLAYER_H = 1;
    static const int PLAYER_C = 2;
    static const int STATE_HOLD = 0;
    static const int STATE_WAIT = 1;
    static const int STATE_PLAY = 2;
    int player_c_color;
    int player_h_color;
    int playerNow;
    int stateNow;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent*);
    QPoint pos2point(QPoint pos) const;
    QPoint pos2point(int x, int y) const;
    QPoint point2pos(QPoint point) const;
    QPoint point2pos(int x, int y) const;
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void addPoint(QPoint pos);
    int getPlayerColor(int player) const;
    void changePlayer();
    bool checkPoint(int x, int y) const;
    bool checkPoint(QPoint p) const;
    int checkAll() const;
    bool is_in(QPoint p) const;
    bool is_in(int x, int y) const;
    int getPlayerByColor(int color) const;
    void init();
    void changeState();
    void AI_Behavior();
private:
    int map[MAX_SIZE][MAX_SIZE];
    std::stack<std::pair<QPoint,int>>recStep;

};

#endif // MAINWINDOW_H
