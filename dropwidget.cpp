#include "dropwidget.h"

#include <QDebug>
#include <QStyleOption>
#include <QPainter>
#include <QDragMoveEvent>
#include <QMimeData>

DropWidget::DropWidget(QWidget *parent) : QFrame(parent)
{
}

void DropWidget::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void DropWidget::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void DropWidget::dropEvent(QDropEvent *event)
{
    const QMimeData* mime = event->mimeData();

    if(mime->hasUrls())
    {
        emit dropped(mime->urls());
    }
}
