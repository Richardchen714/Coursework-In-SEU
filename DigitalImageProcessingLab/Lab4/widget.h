#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QFileInfo>
#include <QMessageBox>
#include "image.h"
#include "seg.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void Display();
    void Save();

private:
    //提示用户输入文件名
    QLabel* filepath;
    QLabel* savepath;
    //文件输入框
    QLineEdit* fileLine;
    QLineEdit* saveLine;//文件保存的位置
    //按钮及参数的输入
    QPushButton* DisplayButton;//展示，不保存图片
    QPushButton* SaveButton;//保存变换后的图像
};
#endif // WIDGET_H
