#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "sceneproblem.h"


#include <QMainWindow>

#include <QDesktopWidget>
#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QLabel>
#include <QFrame>
#include <QPointF>
#include <QPoint>
#include <QString>
#include <QMouseEvent>
#include <QEvent>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /********************************************************** Constructors ***********/
    explicit MainWindow(QLabel *st, SceneProblem *sp, QWidget *parent = 0);
    ~MainWindow();

    /************************************************** Setters and Modifiers ***********/
    void setStatusBar(QLabel *st);
    void setSceneProblem(SceneProblem *sp);

    /**************************************************************** Methods ***********/



    /*************************************************************** SIGNALS ***********/
signals:


    /***************************************************************** SLOTS ***********/
public slots:


    /***************************************************** Members Variables ***********/
private:
    Ui::MainWindow *ui;

    // status bar variable
    QLabel *_statusBar;
    SceneProblem *_sceneProblem;

};

#endif // MAINWINDOW_H
