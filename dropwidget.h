#ifndef DROPWIDGET_H
#define DROPWIDGET_H

#include <QFrame>
#include <QUrl>

class DropWidget : public QFrame
{
    Q_OBJECT
public:
    explicit DropWidget(QWidget *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

signals:
    void dropped(QList<QUrl>);
};

#endif // DROPWIDGET_H
