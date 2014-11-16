#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "sceneproblem.h"
#include "arrangement.h"

#include <string>

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
#include <QVBoxLayout>
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
#include <QRadioButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QSlider>
#include <QPainter>
#include <QObject>



namespace Ui {
    class MainWindow;
}

class SceneProblem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /********************************************************** Constructors ***********/
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /************************************************** Setters and Modifiers ***********/


    /**************************************************************** Methods ***********/



    /*************************************************************** SIGNALS ***********/
signals:


    /***************************************************************** SLOTS ***********/
public slots:
    void updateManipulatorSize(int radius);
    void updateTargetSize(int radius);
    void updateEnv(bool b);
    void updateObstacles(bool b);
    void updateManipulator(bool b);
    void updateEndManipulator(bool b);
    void updateTarget(bool b);
    void updateEndTarget(bool b);
    void closeEnv();
    void closeObs();
    void cancel();
    void compute();

    /***************************************************** Members Variables ***********/
public:
    Ui::MainWindow *ui;

    // status bar variable
    QLabel *statusBarLeft;
    QLabel *statusBarRight;

    // graphics
    SceneProblem *sceneProblem;

    // arrangement
    arrangement *frontier;
    std::list<arrangement> *obstacles;
    arrangement *manipulator;
    arrangement *target;

    // control variables
    bool activeFrontier;
    bool activeObstacles;
    bool activeManipulator;
    bool activeEndManipulator;
    bool activeTarget;
    bool activeEndTarget;

    bool env_close;
    bool manipb_close;
    bool manipe_close;
    bool targetb_close;
    bool targete_close;

    // manipulator and target size
    int manipulatorRadius;
    int targetRadius;

    // radio button
    QRadioButton *addEnv;
    QRadioButton *addObstacles;
    QRadioButton *addManipulator;
    QRadioButton *endManipulator;
    QRadioButton *addTarget;
    QRadioButton *endTarget;


};

#endif // MAINWINDOW_H
