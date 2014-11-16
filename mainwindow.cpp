#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set Window Title
    setWindowTitle("PianoMoverProblem");

    /* ************************************************* initialize variables */

    // arrangement
    arrangement *frontier = new arrangement();
    std::list<arrangement> *obstacles = new std::list<arrangement>();
    arrangement *manipulator = new arrangement();
    arrangement *target = new arrangement();

    // boolean variables for control panel
    activeFrontier = true;
    activeObstacles = false;
    activeManipulator = false;
    activeEndManipulator = false;
    activeTarget = false;
    activeEndTarget = false;

    env_close = false;
    manipb_close = false;
    manipe_close = false;
    targetb_close = false;
    targete_close = false;

    // set default size of manipulator and target (they are circle)
    manipulatorRadius = 50;
    targetRadius = 60;

    /* ************************************************************** set Menu */
    QMenu *menuFile = menuBar()->addMenu("&File");
    QMenu *menuTools = menuBar()->addMenu("&Tools");
    QMenu *menuOption = menuBar()->addMenu("&Option");

    QAction *fileNew = new QAction("&New", this);
    menuFile->addAction(fileNew);
    QAction *fileOpen = new QAction("&Open", this);
    menuFile->addAction(fileOpen);
    QAction *fileSave = new QAction("&Save", this);
    menuFile->addAction(fileSave);
    QAction *fileQuit = new QAction("&Quit", this);
    menuFile->addAction(fileQuit);

    /* ******************************************************** set Status Bar */
    statusBarLeft = new QLabel("Waiting");
    statusBar()->addWidget(statusBarLeft);
    statusBarRight = new QLabel();
    statusBar()->addWidget(statusBarRight);

    /* **************************************************** left of the screen */

    QFrame *central = new QFrame();

    // set Horizontal Layout
    QHBoxLayout *hBoxLayout = new QHBoxLayout();
    central->setLayout(hBoxLayout);

    // create scene for the problem
    sceneProblem = new SceneProblem(this);
    QGraphicsView *viewProblem = new QGraphicsView(sceneProblem);
    viewProblem->setSceneRect(0,0,800,600);
    viewProblem->setMouseTracking(true);
    //viewProblem->setBackgroundBrush(Qt::white);

    // create scene for the expansion
    QGraphicsScene *expansion = new QGraphicsScene();
    QGraphicsView *viewExpansion = new QGraphicsView(expansion);
    //viewExpansion->setBackgroundBrush(Qt::red);

    // create scene for the limits
    QGraphicsScene *criticalCurves = new QGraphicsScene();
    QGraphicsView *viewCriticalCurves = new QGraphicsView(criticalCurves);
    //viewCriticalCurves->setBackgroundBrush(Qt::white);

    // create tab
    QTabWidget *tabLeft = new QTabWidget();
    tabLeft->addTab(viewProblem, tr("Problem"));
    tabLeft->addTab(viewExpansion, tr("Expansion"));
    tabLeft->addTab(viewCriticalCurves, tr("Critical Curves"));

    // left of the screen
    hBoxLayout->addWidget(tabLeft);

    /* *************************************************** right of the screen */

    // right of the screen
    QGroupBox *rightBox = new QGroupBox("CONTROL PANEL");
    rightBox->setStyleSheet("QGroupBox{border:1px solid black;background-color:#F8F8F8;}QGroupBox::title{subcontrol-position:top center;padding-top:0px}");
    addEnv = new QRadioButton("Environment");
    addEnv->setChecked(true);
    QPushButton *terminateEnv = new QPushButton("Close Polygon");
    addObstacles = new QRadioButton("Obstacles");
    QPushButton *terminateObs = new QPushButton("Close Polygon");
    addManipulator = new QRadioButton("Manipulator");
    endManipulator = new QRadioButton("End");
    QSlider *manipulatorSize = new QSlider(Qt::Horizontal);
    manipulatorSize->setRange(10,200);
    manipulatorSize->setSliderPosition(manipulatorRadius);
    manipulatorSize->setMaximumWidth(180);
    addTarget = new QRadioButton("Object");
    endTarget = new QRadioButton("End");
    QSlider *targetSize = new QSlider(Qt::Horizontal);
    targetSize->setRange(10,200);
    targetSize->setSliderPosition(targetRadius);
    targetSize->setMaximumWidth(180);
    QVBoxLayout *vBox = new QVBoxLayout;
    vBox->addWidget(addEnv);
    vBox->addWidget(terminateEnv);
    vBox->addWidget(addObstacles);
    vBox->addWidget(terminateObs);
    vBox->addWidget(addManipulator);
    vBox->addWidget(endManipulator);
    vBox->addWidget(manipulatorSize);
    vBox->addWidget(addTarget);
    vBox->addWidget(endTarget);
    vBox->addWidget(targetSize);
    rightBox->setLayout(vBox);

    QPushButton *cancel = new QPushButton("Cancel");

    QPushButton *compute = new QPushButton("Compute");
    compute->setMinimumHeight(60);

    QVBoxLayout *rightScreen = new QVBoxLayout();
    rightScreen->addWidget(rightBox);
    rightScreen->addWidget(cancel);
    rightScreen->addWidget(compute);

    QFrame *right = new QFrame();
    right->setMaximumWidth(200);
    right->setLayout(rightScreen);


    // right of the screen
    hBoxLayout->addWidget(right);
    // set last parameters
    setCentralWidget(central);



    /* *********************************************** set signals and slots */

    QObject::connect(manipulatorSize, SIGNAL(valueChanged(int)),this,SLOT(updateManipulatorSize(int)));
    QObject::connect(targetSize, SIGNAL(valueChanged(int)),this,SLOT(updateTargetSize(int)));
    QObject::connect(addEnv, SIGNAL(toggled(bool)), this, SLOT(updateEnv(bool)));
    QObject::connect(addObstacles, SIGNAL(toggled(bool)), this, SLOT(updateObstacles(bool)));
    QObject::connect(addManipulator, SIGNAL(toggled(bool)), this, SLOT(updateManipulator(bool)));
    QObject::connect(endManipulator, SIGNAL(toggled(bool)), this, SLOT(updateEndManipulator(bool)));
    QObject::connect(addTarget, SIGNAL(toggled(bool)), this, SLOT(updateTarget(bool)));
    QObject::connect(endTarget, SIGNAL(toggled(bool)), this, SLOT(updateEndTarget(bool)));
    QObject::connect(terminateEnv, SIGNAL(released()), this, SLOT(closeEnv()));
    QObject::connect(terminateObs, SIGNAL(released()), this, SLOT(closeObs()));
    QObject::connect(cancel, SIGNAL(released()), this, SLOT(cancel()));
    QObject::connect(compute, SIGNAL(released()), this, SLOT(compute()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// SLOTS
void
MainWindow::updateManipulatorSize(int radius)
{
    if (manipb_close || manipe_close)
    {
        QString qs = QString::fromStdString("Manipulator Radius : Cannot be changed");
        statusBarRight->setText(qs);
    }
    else {
        QString qs = QString::fromStdString("Manipulator Radius : "+std::to_string(radius));
        statusBarRight->setText(qs);
        manipulatorRadius = radius;
    }
}

void
MainWindow::updateTargetSize(int radius)
{
    if (targetb_close || targete_close)
    {
        QString qs = QString::fromStdString("Object Radius : Cannot be changed");
        statusBarRight->setText(qs);
    }
    else
    {
        QString qs = QString::fromStdString("Object Radius : "+std::to_string(radius));
        statusBarRight->setText(qs);
        targetRadius = radius;
    }
}

void
MainWindow::updateEnv(bool b)
{
    addEnv->setChecked(b);
    activeFrontier = b;
    QString qs = QString::fromStdString("Set Mode on : Environment");
    statusBarRight->setText(qs);
}

void
MainWindow::updateObstacles(bool b)
{
    addObstacles->setChecked(b);
    activeObstacles = b;
    QString qs = QString::fromStdString("Set Mode on : Obsctacle");
    statusBarRight->setText(qs);
}

void
MainWindow::updateManipulator(bool b)
{
    addManipulator->setChecked(b);
    activeManipulator = b;
    QString qs = QString::fromStdString("Set Mode on : Manipulator");
    statusBarRight->setText(qs);
}

void
MainWindow::updateEndManipulator(bool b)
{
    endManipulator->setChecked(b);
    activeEndManipulator = b;
    QString qs = QString::fromStdString("Set Mode on : Manipulator End");
    statusBarRight->setText(qs);
}

void
MainWindow::updateTarget(bool b)
{
    addTarget->setChecked(b);
    activeTarget = b;
    QString qs = QString::fromStdString("Set Mode on : Object");
    statusBarRight->setText(qs);
}

void
MainWindow::updateEndTarget(bool b)
{
    endTarget->setChecked(b);
    activeEndTarget = b;
    QString qs = QString::fromStdString("Set Mode on : Object End");
    statusBarRight->setText(qs);
}

void
MainWindow::closeEnv()
{
    if (!env_close && sceneProblem->pEnv.size() >= 3)
    {
        int p1x = sceneProblem->pEnv[sceneProblem->pEnv.size()-1].x();
        int p1y = sceneProblem->pEnv[sceneProblem->pEnv.size()-1].y();
        int p2x = sceneProblem->pEnv[0].x();
        int p2y = sceneProblem->pEnv[0].y();;
        sceneProblem->addLine(p1x,p1y,p2x,p2y);
        env_close = true;
    }
}

void
MainWindow::closeObs()
{
    if (sceneProblem->pObs.size() >= 1 && sceneProblem->pObs[sceneProblem->pObs.size()-1].size() >= 3)
    {
        int p1x = sceneProblem->pObs[sceneProblem->pObs.size()-1][sceneProblem->pObs[sceneProblem->pObs.size()-1].size()-1].x();
        int p1y = sceneProblem->pObs[sceneProblem->pObs.size()-1][sceneProblem->pObs[sceneProblem->pObs.size()-1].size()-1].y();
        int p2x = sceneProblem->pObs[sceneProblem->pObs.size()-1][0].x();
        int p2y = sceneProblem->pObs[sceneProblem->pObs.size()-1][0].y();;
        sceneProblem->addLine(p1x,p1y,p2x,p2y);
        std::vector<QPoint> foo;
        sceneProblem->pObs.push_back(foo);
    }
}


void
MainWindow::cancel()
{

}


void
MainWindow::compute()
{

}

