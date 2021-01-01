#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&myPainter,&MyPainter::update,this,[=]{
        update();
    });

    myPainter.begin(QPointF(100,100));
    myPainter.lineTo(QPointF(300,300));
    myPainter.lineTo(QPointF(400,50));
    myPainter.lineTo(QPointF(100,100));
    myPainter.end();

    //延时启动绘制
    QTimer::singleShot(1500,[=]{
        myPainter.start();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);

    myPainter.draw(this);
}

