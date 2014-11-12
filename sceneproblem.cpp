#include "sceneproblem.h"



SceneProblem::SceneProblem(QLabel *st):
    _statusBar(st)
{

}

void
SceneProblem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPoint qp = event->scenePos().toPoint();
    int x = qp.x();
    int y = qp.y();
    QString qs = QString::fromStdString("  x : "+std::to_string(x)+"  y : "+std::to_string(y)+ "  ");
    _statusBar->setText(qs);
}

void
SceneProblem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QPoint qp = event->scenePos().toPoint();

}
