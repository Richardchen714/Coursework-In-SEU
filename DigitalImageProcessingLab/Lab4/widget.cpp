#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(600,400);
    //定义标签
    filepath=new QLabel("Input filepath",this);
    filepath->move(100,40);
    savepath=new QLabel("Input savepath",this);
    savepath->move(100,120);
    //定义文件输入框
    fileLine=new QLineEdit(this);
    fileLine->setText("C:/Users/richardchen0714/Documents/Seg/seed.bmp");//默认为seed.bmp
    fileLine->move(300,40);
    saveLine=new QLineEdit(this);
    saveLine->setText("C:/Users/richardchen0714/Documents/Seg/seedSeg.bmp");
    saveLine->move(300,120);
    DisplayButton=new QPushButton("Display",this);
    DisplayButton->move(250,200);
    SaveButton=new QPushButton("Save",this);
    SaveButton->move(250,300);
    connect(DisplayButton,&QPushButton::clicked,this,&Widget::Display);
    connect(SaveButton,&QPushButton::clicked,this,&Widget::Save);
}

Widget::~Widget()
{
}

void Widget::Display()
{
    QString filePath=fileLine->text();//绝对路径
    QFileInfo fi(filePath);
    if(!fi.exists())
        QMessageBox::information(NULL, "Warning", "File doesn't exist");
    Image image(filePath);
    Seg* seg=new Seg();
    Image segImage=seg->Otsu(image);
    image.display("Image");
    segImage.display("segImage");
}
void Widget::Save()
{
    QString filePath=fileLine->text();
    QString savePath=saveLine->text();
    QFileInfo fi(filePath);
    if(!fi.exists())
        QMessageBox::information(NULL, "Warning", "File doesn't exist");
    Image image(filePath);
    Seg* seg=new Seg();
    Image segImage=seg->Otsu(image);
    QPixmap segPix=segImage.getPixmap();
    segPix.save(savePath);
    QFileInfo fii(savePath);//是否保存成功
    if(!fii.exists())
        QMessageBox::information(NULL, "Warning", "Failed to save");
    else QMessageBox::information(NULL,"Info","Saved Successfully");
}
