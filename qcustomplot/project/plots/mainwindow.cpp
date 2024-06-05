#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QScreen>
#include <QMessageBox>
#include <QMenuBar>

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#  include <QDesktopWidget>
#endif



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    screenShotNo(1)
{
    ui->setupUi(this);
    plotGraph(0);
    colorGraph(2);

    QMenu *menuGraph = menuBar()->addMenu("&Построение");
    QAction *menuGraph1Action = menuGraph->addAction("Квадополоид");
    QAction *menuGraph2Action = menuGraph->addAction("Сегмент параболы");
    QAction *menuGraph3Action = menuGraph->addAction("cos/sin");
    connect(menuGraph1Action, &QAction::triggered, this, [this](){plotGraph(1);});
    connect(menuGraph2Action, &QAction::triggered, this, [this](){plotGraph(2);});
    connect(menuGraph3Action, &QAction::triggered, this, [this](){plotGraph(3);});

    QMenu *menuErase = menuBar()->addMenu("&Очистка");
    QAction *menuEraseAction = menuErase->addAction("Очистить график");
    connect(menuEraseAction, &QAction::triggered, this, [this](){plotGraph(0);});

    QMenu *menuColor = menuBar()->addMenu("&Цвет");
    QAction *menuColorRedAction = menuColor->addAction("Красный");
    QAction *menuColorGreenAction = menuColor->addAction("Зелёный");
    QAction *menuColorBlueAction = menuColor->addAction("Синий");
    connect(menuColorRedAction, &QAction::triggered, this, [this](){colorGraph(1);});
    connect(menuColorGreenAction, &QAction::triggered, this, [this](){colorGraph(2);});
    connect(menuColorBlueAction, &QAction::triggered, this, [this](){colorGraph(3);});

    QMenu *menuScreenShot = menuBar()->addMenu("С&криншот");
    QAction *menuScreenShotAction = menuScreenShot->addAction("Сделать скриншот окна");
    connect(menuScreenShotAction, &QAction::triggered, this, &MainWindow::screenShot);

    QMenu *menuAbout = menuBar()->addMenu("&Справка");
    QAction *menuAboutAction = menuAbout->addAction("О программе");
    connect(menuAboutAction, &QAction::triggered, this, &MainWindow::showAbout);
}

void MainWindow::setupSimpleDemo(QCustomPlot *customPlot, int no)
{
    customPlot->addGraph();

    QVector<double> x(251), y(251);
    switch(no)
    {
    case 1:
        for (int i=0; i<251; ++i)
        {
            x[i] = i;
            y[i] = qExp(-i/250.0)*qCos(i/10.0);
        }
        setWindowTitle("График квадрополоида");
        break;

    case 2:
        for (int i=0; i<251; ++i)
        {
            x[i] = i/75.0 - 1;
            y[i] = x[i]*x[i];
        }
        setWindowTitle("График сегмента параболы");
        break;

    case 3:
        for (int i=0; i<251; i++)
        {
            x[i] = i;
            y[i] = qCos(i/5.0)/qSin(i/5.0);
        }
        setWindowTitle("График cos/sin");
        break;

    default:
        for (int i=0; i<251; i++)
        {
            x[i] = x[i] = 0;
        }
        setWindowTitle("Выберите график!");
        break;
    }

    customPlot->xAxis2->setVisible(true);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setVisible(true);
    customPlot->yAxis2->setTickLabels(false);
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
    customPlot->graph(0)->setData(x, y);
    customPlot->graph(0)->rescaleAxes();
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::screenShot()
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    QPixmap pm = QPixmap::grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);
#elif QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
    QPixmap pm = qApp->primaryScreen()->grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);
#elif QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QPixmap pm = qApp->primaryScreen()->grabWindow(qApp->desktop()->winId(), this->x()-7, this->y()-7, this->frameGeometry().width()+14, this->frameGeometry().height()+14);
#else
    QPixmap pm = qApp->primaryScreen()->grabWindow(0, this->x()-7, this->y()-7, this->frameGeometry().width()+14, this->frameGeometry().height()+14);
#endif
    QString fileName = QString("scr_%1.png").arg(screenShotNo);
    pm.save("./screenshots/" + fileName);

    QMessageBox::warning(
        this, QString("scr_%1.png").arg(screenShotNo),
        "Скриншот окна сохранён в папке 'screenshots'."
    );

    screenShotNo++;
}

void MainWindow::plotGraph(int no)
{
    setupSimpleDemo(ui->customPlot, no);
    ui->customPlot->replot();
}

void MainWindow::colorGraph(int no)
{
    if (no == 1) {
        ui->customPlot->graph(0)->setPen(QPen(Qt::darkRed));
        ui->customPlot->graph(0)->setBrush(QBrush(QColor(128, 0, 0, 24)));
    }
    else if (no == 2) {
        ui->customPlot->graph(0)->setPen(QPen(Qt::darkGreen));
        ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 128, 0, 24)));
    }
    else {
        ui->customPlot->graph(0)->setPen(QPen(Qt::darkBlue));
        ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 128, 24)));
    }
    ui->customPlot->replot();
}

void MainWindow::showAbout()
{
    QMessageBox::information(
        this, "CPP + QT = HUCKING FELL",
        "Добро пожаловать! Добро пожаловать в Сити 17. \n\n"
        "Сами вы его выбрали, или его выбрали за вас — это лучший город из оставшихся. "
        "Я такого высокого мнения о Сити 17, что решил разместить свое правительство здесь, "
        "в Цитадели, столь заботливо предоставленной нашими Покровителями. "
        "Я горжусь тем, что называю Сити 17 своим домом. \n\n"
        "Итак, собираетесь ли вы остаться здесь, или же вас ждут неизвестные дали, "
        "добро пожаловать в Сити 17! Здесь... безопасно ;)"
    );
}
