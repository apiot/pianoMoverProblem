#include "mainwindow.h"
#include "sceneproblem.h"
#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    QLabel *statusBar = new QLabel();
    statusBar->setText("Waiting");
    SceneProblem *sceneProblem = new SceneProblem(statusBar);

    MainWindow w = MainWindow(statusBar, sceneProblem);
    w.show();
    return app.exec();
}
