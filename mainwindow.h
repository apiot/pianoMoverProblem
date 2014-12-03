#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "sceneproblem.h"
#include "sceneresults.h"
#include "arrangement.h"

#include <string>

#include <QMainWindow>

#include <QAction>
#include <QDesktopWidget>
#include <QEvent>
#include <QFrame>
#include <QFile>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QMouseEvent>
#include <QObject>
#include <QPointF>
#include <QPoint>
#include <QPushButton>
#include <QRadioButton>
#include <QRectF>
#include <QString>
#include <QSlider>
#include <QStringList>
#include <QTabWidget>
#include <QTextStream>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>


namespace Ui {
    class MainWindow;
}

class SceneProblem;
class arrangement;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /********************************************************** Constructors ***********/
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /**************************************************************** Methods ***********/





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
    void newFile();
    void openFile();
    void saveFileData();
    void saveFileAll();

    /***************************************************** Members Variables ***********/
public:
    Ui::MainWindow *ui;

    QFileDialog *windowFile;

    // status bar variable
    QLabel *statusBarLeft;
    QLabel *statusBarRight;

    // graphics
    SceneProblem *sceneProblem;
    sceneResults *admissibleR;
    sceneResults *admissibleO;
    sceneResults *criticalCurves;
    sceneResults *movie;

    // arrangement
    arrangement *problem;

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
