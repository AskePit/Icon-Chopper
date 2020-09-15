#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardPaths>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

static void CallInfoDialog(const QString &message)
{
    QMessageBox msgBox;
    msgBox.setText(message);

    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

using Errors = QStringList;
static const Errors NoErrors = Errors();

static const std::array<int, 6> IconSizes = {
    512, 384, 256, 192, 128, 96
};

static bool Chop(const QImage& img, const QFileInfo file);
static void Chop(const QList<QUrl>& urls)
{
    Errors errors;

    for(const QUrl& url : urls)
    {
        const QString path = url.toLocalFile();
        const QString fileName = url.fileName();

        QImage img(path);

        if(img.isNull())
        {
            const QString error = QString("<b>%1</b> is an invalid image!<br>").arg(fileName);
            errors.push_back(std::move(error));
            continue;
        }

        const QSize size = img.size();

        if(size.width() != size.height())
        {
            const QString error = QString("<b>%1</b> is not square-sized!<br>").arg(fileName);
            errors.push_back(std::move(error));
            continue;
        }

        if(size.width() < IconSizes.back())
        {
            const QString error = QString("<b>%1</b> is to small! Required %2x%2 at least.<br>").arg(fileName).arg(IconSizes.back());
            errors.push_back(std::move(error));
            continue;
        }

        Chop(img, QFileInfo(path));
    }

    if(errors != NoErrors)
    {
        CallInfoDialog(errors.join("\n"));
    }
}

static bool Chop(const QImage& img, const QFileInfo file)
{
    const QSize imgSize = img.size();

    for(int iconSize : IconSizes)
    {
        if(imgSize.width() >= iconSize)
        {
            const QString iconFileDirPath = QString("%1/%2x%2/").arg(file.absolutePath()).arg(iconSize);
            const QDir iconFileDir(iconFileDirPath);
            if (!iconFileDir.exists())
            {
                iconFileDir.mkpath(".");
            }
            const QString iconFileName = QString("%1%2").arg(iconFileDirPath).arg(file.fileName());
            QImage icon = img.scaled(iconSize, iconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            icon.save(iconFileName);
        }
    }


    return true;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->dropWidget, &DropWidget::dropped, [](QList<QUrl> urls){
        Chop(urls);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

