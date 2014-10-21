#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMessageBox>
#include <QMouseEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    static const int MAX_SIZE = 15;
    static const int COLOR_NONE = 0;
    static const int COLOR_WHITE = 1;
    static const int COLOR_BLACK = 2;
    int PLAYER_H;
    int PLAYER_C;
    int player_c_color;
    int player_h_color;
    int playerNow;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent*);
    QPoint pos2point(QPoint pos) const;
    QPoint pos2point(int x, int y) const;
    QPoint point2pos(QPoint point) const;
    QPoint point2pos(int x, int y) const;
    void mousePressEvent(QMouseEvent *event);
    void addPoint(QPoint pos);
    int getPlayerColor(int player) const;
    void changePlayer();
    bool check(QPoint p) const;
    bool is_in(QPoint p) const;
    bool is_in(int x, int y) const;
private:
    int map[MAX_SIZE][MAX_SIZE];

};

#endif // MAINWINDOW_H
