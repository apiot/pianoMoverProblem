#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QLabel *st, SceneProblem *sp, QWidget *parent) :
    QMainWindow(parent),
    _statusBar(st),
    _sceneProblem(sp),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set window size
    //QDesktopWidget dw;
    //setFixedSize(dw.width()*0.8,dw.height()*0.8);

    // set Window Title
    setWindowTitle("PianoMoverProblem");



    // set Menu
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

    // set Status Bar
    statusBar()->addWidget(_statusBar);


    QFrame *central = new QFrame();

    // set Horizontal Layout
    QHBoxLayout *hBoxLayout = new QHBoxLayout();
    central->setLayout(hBoxLayout);

    // create scene for the problem
    QGraphicsView *viewProblem = new QGraphicsView(_sceneProblem);
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

    hBoxLayout->addWidget(tabLeft);
    hBoxLayout->addWidget(new QLabel("toto"));

    // set last parameters
    setCentralWidget(central);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void
MainWindow::setStatusBar(QLabel *st)
{
    _statusBar = st;
}

void
MainWindow::setSceneProblem(SceneProblem *sp)
{
    _sceneProblem = sp;
}
