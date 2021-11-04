#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->ViewButton,&QPushButton::clicked,this,&MainWindow::view);
    connect(ui->TransferButton,&QPushButton::clicked,this,&MainWindow::grayTrans);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::view()
{
    QLabel *viewedLabel=new QLabel(nullptr);
    Image viewedImage(ui->PathEdit->text());
    viewedLabel->setPixmap(viewedImage.getPixmap());
    QScrollArea* viewArea=new QScrollArea(nullptr);
    viewArea->setBackgroundRole(QPalette::Dark);
    viewArea->setWidget(viewedLabel);
    viewArea->resize(1200,800);
    viewArea->show();
}
void MainWindow::grayTrans()
{
    Image originalImage(ui->PathEdit->text());
    int center=ui->CenterEdit->text().toInt();
    int width=ui->WidthEdit->text().toInt();
    GrayTrans grayTran;
    Image transformedImage=grayTran.trans(center,width,originalImage);
    QLabel *viewedLabel=new QLabel(nullptr);
    viewedLabel->setPixmap(transformedImage.getPixmap());
    QScrollArea* viewArea=new QScrollArea(nullptr);
    viewArea->setBackgroundRole(QPalette::Dark);
    viewArea->setWidget(viewedLabel);
    viewArea->resize(1200,800);
    viewArea->show();
}
