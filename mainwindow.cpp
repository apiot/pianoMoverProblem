#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set Window Title
    setWindowTitle("PianoMoverProblem");
    windowFile = new QFileDialog(this);
    windowFile->setVisible(false);

    /* ************************************************* initialize variables */

    // arrangement
    problem = new arrangement();
    expansion = new arrangement();
    criticalCurves = new arrangement();
    connexes = new arrangement();

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

    QAction *fileNew = new QAction("&New", this);
    menuFile->addAction(fileNew);
    QAction *fileOpen = new QAction("&Open", this);
    menuFile->addAction(fileOpen);
    QAction *fileSaveData = new QAction("&Save Data", this);
    menuFile->addAction(fileSaveData);
    QAction *fileSaveAll = new QAction("&Save All", this);
    menuFile->addAction(fileSaveAll);

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
    tabLeft->addTab(viewExpansion, tr("Minkowski"));
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

    // file menu
    QObject::connect(fileNew, SIGNAL(triggered()), this, SLOT(newFile()));
    QObject::connect(fileOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    QObject::connect(fileSaveData, SIGNAL(triggered()), this, SLOT(saveFileData()));
    QObject::connect(fileSaveAll, SIGNAL(triggered()), this, SLOT(saveFileAll()));

    // for the problem
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

/*=============================== METHODS ==================================*/

/*================================ SLOTs ===================================*/

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
        QPointF c = sceneProblem->mb->rect().center();
        sceneProblem->mb->setRect(c.x()-(radius/2),c.y()-(radius/2),radius,radius);
        c = sceneProblem->me->rect().center();
        sceneProblem->me->setRect(c.x()-(radius/2),c.y()-(radius/2),radius,radius);
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
        QPointF c = sceneProblem->ob->rect().center();
        sceneProblem->ob->setRect(c.x()-(radius/2),c.y()-(radius/2),radius,radius);
        c = sceneProblem->oe->rect().center();
        sceneProblem->oe->setRect(c.x()-(radius/2),c.y()-(radius/2),radius,radius);
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
        QGraphicsLineItem *l = new QGraphicsLineItem(p1x,p1y,p2x,p2y);
        sceneProblem->pLines.push_back(l);
        sceneProblem->addItem(l);
        env_close = true;
        sceneProblem->tLine->setVisible(false);
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
        QGraphicsLineItem *l = new QGraphicsLineItem(p1x,p1y,p2x,p2y);
        sceneProblem->oLines.push_back(l);
        sceneProblem->addItem(l);
        std::vector<QPoint> foo;
        sceneProblem->pObs.push_back(foo);
        sceneProblem->oLine->setVisible(false);
    }
}


void
MainWindow::cancel()
{
    if (activeFrontier)
    {
        if (env_close)
        {
            env_close = false;
            sceneProblem->tLine->setVisible(true);
            sceneProblem->removeItem(sceneProblem->pLines.back());
            sceneProblem->pLines.pop_back();
        }
        else if (sceneProblem->pEnv.size() >= 2)
        {
            sceneProblem->removeItem(sceneProblem->pEllipses.back());
            sceneProblem->pEllipses.pop_back();
            sceneProblem->pEnv.pop_back();
            sceneProblem->removeItem(sceneProblem->pLines.back());
            sceneProblem->pLines.pop_back();
        }
        else if (sceneProblem->pEnv.size() == 1)
        {
            sceneProblem->removeItem(sceneProblem->pEllipses.back());
            sceneProblem->pEllipses.pop_back();
            sceneProblem->pEnv.pop_back();
            sceneProblem->tLine->setVisible(false);
        }
    }
    else if (activeObstacles)
    {
        int firstDim = sceneProblem->pObs.size();
        int sndDim = sceneProblem->pObs[firstDim-1].size();

        if (sndDim == 0 && firstDim == 1)
        {
            // do nothing
        }
        else if (sndDim == 1) // remove point only
        {
            sceneProblem->removeItem(sceneProblem->oEllipses.back());
            sceneProblem->oEllipses.pop_back();
            sceneProblem->pObs[firstDim-1].pop_back();
            sceneProblem->oLine->setVisible(false);
        }
        else if (sndDim == 0 && firstDim > 1) // del dim and remove line
        {
            sceneProblem->removeItem(sceneProblem->oLines.back());
            sceneProblem->oLines.pop_back();

            sceneProblem->pObs.pop_back();
            sceneProblem->oLine->setVisible(true);
        }
        else if (sndDim > 1) // remove point and line
        {
            sceneProblem->removeItem(sceneProblem->oEllipses.back());
            sceneProblem->oEllipses.pop_back();
            sceneProblem->pObs[firstDim-1].pop_back();
            sceneProblem->removeItem(sceneProblem->oLines.back());
            sceneProblem->oLines.pop_back();
        }
    }
    else if (activeManipulator)
    {
        manipb_close = false;
    }
    else if (activeEndManipulator)
    {
        manipe_close = false;
    }
    else if (activeTarget)
    {
        targetb_close = false;
    }
    else if (activeEndTarget)
    {
        targete_close = false;
    }
}

void
MainWindow::compute()
{
    /* in a first time we print all data we got */
    if (sceneProblem->pEnv.size() > 0)
    {
        std::cout << "Environment" << std::endl;
        for (int i = 0; i < (int)sceneProblem->pEnv.size(); ++i)
            std::cout << sceneProblem->pEnv[i].x() << " " << sceneProblem->pEnv[i].y() << std::endl;
    }
    // write obstacles points
    for (int i = 0; i < (int)sceneProblem->pObs.size() && (int)sceneProblem->pObs[i].size() > 0; ++i)
    {
        std::cout << "Obstacle" << std::endl;
        for (int j = 0; j < (int)sceneProblem->pObs[i].size(); ++j)
            std::cout << sceneProblem->pObs[i][j].x() << " " << sceneProblem->pObs[i][j].y() << std::endl;
    }
    // write manipulator info
    std::cout << "Manipulator" << std::endl;
    std::cout << sceneProblem->manip_begin.x() << " " << sceneProblem->manip_begin.y() << " ";
    std::cout << sceneProblem->manip_end.x() << " " << sceneProblem->manip_end.y() << " ";
    std::cout << sceneProblem->manip_radius << std::endl;
    // write target info
    std::cout << "Object" << std::endl;
    std::cout << sceneProblem->obj_begin.x() << " " << sceneProblem->obj_begin.y() << " ";
    std::cout << sceneProblem->obj_end.x() << " " << sceneProblem->obj_end.y() << " ";
    std::cout << sceneProblem->obj_radius << std::endl;

    /* then we compute the problem */
    problem->retrieveData(sceneProblem->pEnv,sceneProblem->pObs,sceneProblem->manip_begin,
                          sceneProblem->manip_end,sceneProblem->manip_radius,
                          sceneProblem->obj_begin,sceneProblem->obj_end,
                          sceneProblem->obj_radius);


}

void
MainWindow::newFile()
{
    env_close = false;
    manipb_close = false;
    manipe_close = false;
    targetb_close = false;
    targete_close = false;
    sceneProblem->newProblem();
}

void
MainWindow::openFile()
{
    QStringList fileNames;
    windowFile->setFileMode(QFileDialog::ExistingFile);
    windowFile->setNameFilter(tr("Files (*.pmb)"));
    windowFile->setVisible(true);
    if (windowFile->exec())
    {
        fileNames = windowFile->selectedFiles();
        std::cout << "Selected File : " << fileNames[0].toStdString() << std::endl;
        QFile file(fileNames[0]);
        int choix = 0;
        int obs = -1;
        if(file.open(QIODevice::ReadOnly))
        {
            // call newFile() function
            newFile();
            // and then import data
            QTextStream in(&file);
            while(!in.atEnd()) {
                QString line = in.readLine();
                if (line.compare("Environment") == 0)
                    choix = 0;
                else if (line.compare("Obstacle") == 0)
                {
                    choix = 1;
                    ++obs;
                    if (obs > 0)
                        sceneProblem->pObs.push_back(std::vector<QPoint>());
                }
                else if (line.compare("Manipulator") == 0)
                    choix = 2;
                else if (line.compare("Object") == 0)
                    choix = 3;
                else
                {
                    QStringList l = line.split(" ");
                    std::vector<int> p;
                    for (int i=0; i< l.size(); ++i)
                        p.push_back(l[i].toInt());
                    switch (choix)
                    {
                        case 0:
                            sceneProblem->pEnv.push_back(QPoint(p[0],p[1]));
                            break;
                        case 1:
                            sceneProblem->pObs[obs].push_back(QPoint(p[0],p[1]));
                            break;
                        case 2:
                            sceneProblem->manip_begin = QPoint(p[0],p[1]);
                            sceneProblem->manip_end = QPoint(p[2],p[3]);
                            sceneProblem->manip_radius = p[4];
                            break;
                        case 3:
                            sceneProblem->obj_begin = QPoint(p[0],p[1]);
                            sceneProblem->obj_end = QPoint(p[2],p[3]);
                            sceneProblem->obj_radius = p[4];
                            break;
                    }
                }
            }
            if (sceneProblem->pObs.back().size() > 2)
                sceneProblem->pObs.push_back(std::vector<QPoint>());
            if (sceneProblem->pEnv.size() > 2)
                env_close = true;
            manipb_close = true;
            manipe_close = true;
            targetb_close = true;
            targete_close = true;
            file.close();

            /* and draw problem */
            // print environment
            if (sceneProblem->pEnv.size() > 0)
            {
                QPoint qp0 = sceneProblem->pEnv[0];
                QGraphicsEllipseItem *e0 = new QGraphicsEllipseItem(qp0.x()-1,qp0.y()-1,2,2);
                e0->setBrush(Qt::black);
                sceneProblem->pEllipses.push_back(e0);
                sceneProblem->addItem(e0);
                for (int i=1; i < (int)sceneProblem->pEnv.size(); ++i)
                {
                    QPoint qp = sceneProblem->pEnv[0];
                    QGraphicsEllipseItem *e = new QGraphicsEllipseItem(qp.x()-1,qp.y()-1,2,2);
                    e->setBrush(Qt::black);
                    sceneProblem->pEllipses.push_back(e);
                    sceneProblem->addItem(e);

                    QPoint p1 = sceneProblem->pEnv[i-1];
                    QPoint p2 = sceneProblem->pEnv[i];
                    QGraphicsLineItem *l = new QGraphicsLineItem(p1.x(),p1.y(),p2.x(),p2.y());
                    sceneProblem->pLines.push_back(l);
                    sceneProblem->addItem(l);
                }
                if (sceneProblem->pEnv.size() > 3)
                {
                    QPoint p1 = sceneProblem->pEnv[0];
                    QPoint p2 = sceneProblem->pEnv.back();
                    QGraphicsLineItem *l = new QGraphicsLineItem(p1.x(),p1.y(),p2.x(),p2.y());
                    sceneProblem->pLines.push_back(l);
                    sceneProblem->addItem(l);
                }
            }
            // print obstacles
            int first = sceneProblem->pObs.size();
            for (int k = 0; k < first; ++k)
            {
                int snd = sceneProblem->pObs[k].size();
                if (snd > 1)
                {
                    QPoint qp0 = sceneProblem->pObs[k][0];
                    QGraphicsEllipseItem *e0 = new QGraphicsEllipseItem(qp0.x()-1,qp0.y()-1,2,2);
                    e0->setBrush(Qt::black);
                    sceneProblem->oEllipses.push_back(e0);
                    sceneProblem->addItem(e0);
                    for (int i=1; i < (int)sceneProblem->pObs[k].size(); ++i)
                    {
                        QPoint qp = sceneProblem->pObs[k][0];
                        QGraphicsEllipseItem *e = new QGraphicsEllipseItem(qp.x()-1,qp.y()-1,2,2);
                        e->setBrush(Qt::black);
                        sceneProblem->oEllipses.push_back(e);
                        sceneProblem->addItem(e);

                        QPoint p1 = sceneProblem->pObs[k][i-1];
                        QPoint p2 = sceneProblem->pObs[k][i];
                        QGraphicsLineItem *l = new QGraphicsLineItem(p1.x(),p1.y(),p2.x(),p2.y());
                        sceneProblem->oLines.push_back(l);
                        sceneProblem->addItem(l);
                    }
                    if (sceneProblem->pObs[k].size() > 3)
                    {
                        QPoint p1 = sceneProblem->pObs[k][0];
                        QPoint p2 = sceneProblem->pObs[k].back();
                        QGraphicsLineItem *l = new QGraphicsLineItem(p1.x(),p1.y(),p2.x(),p2.y());
                        sceneProblem->oLines.push_back(l);
                        sceneProblem->addItem(l);
                    }
                }
            }
            // print manipulator and target
            int x = sceneProblem->manip_begin.x();
            int y = sceneProblem->manip_begin.y();
            int r = sceneProblem->manip_radius;
            sceneProblem->mb->setRect(x-(r/2),y-(r/2),r,r);
            x = sceneProblem->manip_end.x();
            y = sceneProblem->manip_end.y();
            sceneProblem->me->setRect(x-(r/2),y-(r/2),r,r);
            x = sceneProblem->obj_begin.x();
            y = sceneProblem->obj_begin.y();
            r = sceneProblem->obj_radius;
            sceneProblem->ob->setRect(x-(r/2),y-(r/2),r,r);
            x = sceneProblem->obj_end.x();
            y = sceneProblem->obj_end.y();
            sceneProblem->oe->setRect(x-(r/2),y-(r/2),r,r);
        }
    }
}

void
MainWindow::saveFileData()
{
    QStringList fileNames;
    windowFile->setFileMode(QFileDialog::AnyFile);
    windowFile->setVisible(true);
    if (windowFile->exec())
    {
        fileNames = windowFile->selectedFiles();
        std::string f = fileNames[0].toStdString();
        QString file;
        if (f.size() > 4 && f.substr(f.size()-4,4).compare(".pmb") == 0)
            file = QString::fromStdString(f);
        else
        {
            file = QString::fromStdString(f+".pmb");
        }
        std::cout << "Selected File : " << file.toStdString() << std::endl;
        // write data in file
        QFile qfile(file);
        if ( qfile.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text) )
        {
            QTextStream stream(&qfile);
            // write environment points
            if (sceneProblem->pEnv.size() > 0)
            {
                stream << "Environment" << endl;
                for (int i = 0; i < (int)sceneProblem->pEnv.size(); ++i)
                    stream << sceneProblem->pEnv[i].x() << " " << sceneProblem->pEnv[i].y() << endl;
            }
            // write obstacles points
            for (int i = 0; i < (int)sceneProblem->pObs.size() && (int)sceneProblem->pObs[i].size() > 0; ++i)
            {
                stream << "Obstacle" << endl;
                for (int j = 0; j < (int)sceneProblem->pObs[i].size(); ++j)
                    stream << sceneProblem->pObs[i][j].x() << " " << sceneProblem->pObs[i][j].y() << endl;
            }
            // write manipulator info
            stream << "Manipulator" << endl;
            stream << sceneProblem->manip_begin.x() << " " << sceneProblem->manip_begin.y() << " ";
            stream << sceneProblem->manip_end.x() << " " << sceneProblem->manip_end.y() << " ";
            stream << sceneProblem->manip_radius << endl;
            // write target info
            stream << "Object" << endl;
            stream << sceneProblem->obj_begin.x() << " " << sceneProblem->obj_begin.y() << " ";
            stream << sceneProblem->obj_end.x() << " " << sceneProblem->obj_end.y() << " ";
            stream << sceneProblem->obj_radius << endl;
            // close file
            qfile.close();
        }
    }
}

void
MainWindow::saveFileAll()
{
    QStringList dirNames;
    windowFile->setFileMode(QFileDialog::Directory);
    windowFile->setVisible(true);
    if (windowFile->exec())
    {
        dirNames = windowFile->selectedFiles();
        std::string directory = dirNames[0].toStdString();
    }
    // TODO : Later
    // Save data, and image, and movie if it is done
}
