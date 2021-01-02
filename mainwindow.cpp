#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&drawPainter,&MyPainter::update,this,[=]{
        update();
    });

    drawPainter.begin(QPointF(100,100));
    drawPainter.beginFill(QColor(0,125,250));
    drawPainter.setPenWidth(2);
    drawPainter.setPenColor(QColor(0,255,170));
    drawPainter.lineTo(QPointF(300,300));
    drawPainter.setPenWidth(5);
    drawPainter.lineTo(QPointF(400,50));
    drawPainter.setPenColor(QColor(255,0,170));
    drawPainter.lineTo(QPointF(100,100));
    drawPainter.endFill();
    drawPainter.moveTo(QPointF(100,200));
    drawPainter.lineTo(QPointF(400,200));
    drawPainter.end();

    //延时启动绘制
    QTimer::singleShot(1500,[=]{
        drawPainter.start();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);

    drawPainter.draw(this);
}

