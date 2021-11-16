#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->ViewButton,&QPushButton::clicked,this,&Widget::view);
    connect(ui->TransferButton,&QPushButton::clicked,this,&Widget::grayTrans);
    connect(ui->SharpenAndTransferButton,&QPushButton::clicked,this,&Widget::sharpenAndTransfer);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::view()
{
    Image viewedImage(ui->PathEdit->text());
    viewedImage.display("view");
}
void Widget::grayTrans()
{
    Image originalImage(ui->PathEdit->text());
    int center=ui->CenterEdit->text().toInt();
    int width=ui->WidthEdit->text().toInt();
    Process process;
    Image transformedImage=process.grayTrans(center,width,originalImage);
    transformedImage.display("graytrans");
}
void Widget::sharpenAndTransfer()
{
    Image originalImage(ui->PathEdit->text());
    int center=ui->CenterEdit->text().toInt();
    int width=ui->WidthEdit->text().toInt();
    int kernelSize1=ui->KernelSizeEdit1->text().toInt();
    double alpha=ui->AlphaEdit->text().toDouble();
    Process process;
    Image trans=process.denoise(originalImage,kernelSize1);
    Image trans1=process.Laplacian(trans,alpha);
    Image transformedImage=process.grayTrans(center,width,trans1);
    transformedImage.display("sharpen&transfer");
    grayTrans();
    //trans.display();
}
