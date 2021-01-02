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

    //测试图案 1
    //drawPainter.begin(QPointF(100,100));
    //drawPainter.beginFill(QColor(0,125,250));
    //drawPainter.setPenWidth(2);
    //drawPainter.setPenColor(QColor(0,255,170));
    //drawPainter.lineTo(QPointF(300,300));
    //drawPainter.setPenWidth(5);
    //drawPainter.arc(QPointF(300,200),100,-90,180);
    //drawPainter.moveTo(QPointF(300,100));
    //drawPainter.setPenColor(QColor(255,0,170));
    //drawPainter.lineTo(QPointF(100,100));
    //drawPainter.endFill();
    //drawPainter.moveTo(QPointF(100,200));
    //drawPainter.lineTo(QPointF(400,200));
    //drawPainter.end();

    //测试图案 2
    drawPainter.begin(QPointF(300,200));
    drawPainter.beginFill(QColor(0,100,0));
    drawPainter.setPenWidth(2);
    drawPainter.setPenColor(QColor(0,150,0));
    drawPainter.arc(QPointF(200,200),100,0,180);
    //drawPainter.moveTo(QPointF(100,200));
    //drawPainter.lineTo(QPointF(300,400));
    //drawPainter.lineTo(QPointF(500,200));
    drawPainter.arc(QPointF(400,100),318,-161,53);
    drawPainter.arc(QPointF(200,100),318,-72,53);
    drawPainter.arc(QPointF(400,200),100,0,180);
    drawPainter.endFill();
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

