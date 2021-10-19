#include "widget.h"
#include "image.h"
#include "translation.h"
#include "rotate.h"
#include "zoom.h"
#include <QFileInfo>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(600,400);
    //定义标签
    filepath=new QLabel("Input filepath",this);
    filepath->move(100,40);
    //定义文件输入框
    fileEdit=new QLineEdit(this);
    fileEdit->setText("C:/Users/richardchen0714/Documents/Image/barbara.bmp");//默认为barbara.bmp
    fileEdit->move(300,40);
    //定义按钮并移动按钮到适当位置
    translationButton=new QPushButton("Translation",this);
    translationButton->move(350,100);
    rotateButton=new QPushButton("Rotate",this);
    rotateButton->move(350,200);
    zoomButton=new QPushButton("Zoom",this);
    zoomButton->move(350,300);
    //移动输入框到适当位置
    translationX=new QLineEdit(this);
    translationX->setText("TranslationX");
    translationX->move(150,80);
    translationY=new QLineEdit(this);
    translationY->setText("TranslationY");
    translationY->move(150,120);
    angle=new QLineEdit(this);
    angle->setText("Angle");
    angle->move(150,200);
    zoom=new QLineEdit(this);
    zoom->setText("zoom");
    zoom->move(150,300);
    connect(translationButton,&QPushButton::clicked,this,&Widget::translation);
    connect(rotateButton,&QPushButton::clicked,this,&Widget::rotate);
    connect(zoomButton,&QPushButton::clicked,this,&Widget::Geometry);
}

Widget::~Widget(){}
void Widget::translation()
{
    //从文本框中获取移动距离
    double moveX=translationX->text().toDouble();
    double moveY=translationY->text().toDouble();
    QString path=fileEdit->text();//绝对路径
    QFileInfo fi(path);
    if(!fi.exists())
        QMessageBox::information(NULL, "Warning", "File doesn't exist");
    Image original(path);
    Translation trans;
    Image transformed=trans.imageTranslation(original,moveX,moveY);

    QLabel* originalP=new QLabel(nullptr);
    QLabel* transformedP=new QLabel(nullptr);
    originalP->resize(original.getX(),original.getY());
    transformedP->resize(transformed.getX(),transformed.getY());
    originalP->setPixmap(original.getPixmap());
    transformedP->setPixmap(transformed.getPixmap());
    originalP->show();
    transformedP->show();
}
void Widget::rotate()
{
    //从文本框中获取移动距离
    int deg=angle->text().toInt();
    QString path=fileEdit->text();//绝对路径
    QFileInfo fi(path);
    if(!fi.exists())
        QMessageBox::information(NULL, "Warning", "File doesn't exist");
    Image original(path);
    Rotate rot;
    Image transformed=rot.rotateImage(original,deg);

    QLabel* originalP=new QLabel(nullptr);
    QLabel* transformedP=new QLabel(nullptr);
    originalP->resize(original.getX(),original.getY());
    transformedP->resize(transformed.getX(),transformed.getY());
    originalP->setPixmap(original.getPixmap());
    transformedP->setPixmap(transformed.getPixmap());
    originalP->show();
    transformedP->show();
}
void Widget::Geometry(){
    //从文本框中获取移动距离
    double times=zoom->text().toDouble();
    QString path=fileEdit->text();//绝对路径
    QFileInfo fi(path);
    if(!fi.exists())
        QMessageBox::information(NULL, "Warning", "File doesn't exist");
    Image original(path);
    Zoom zom;
    Image transformed=zom.ZoomImage(original,times);

    QLabel* originalP=new QLabel(nullptr);
    QLabel* transformedP=new QLabel(nullptr);
    originalP->resize(original.getX(),original.getY());
    transformedP->resize(transformed.getX(),transformed.getY());
    originalP->setPixmap(original.getPixmap());
    transformedP->setPixmap(transformed.getPixmap());
    originalP->show();
    transformedP->show();
}
