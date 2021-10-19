#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void translation();
    void rotate();
    void Geometry();
private:
    //提示用户输入文件名
    QLabel* filepath;
    //文件输入框
    QLineEdit* fileEdit;
    //按钮及参数的输入
    QPushButton* translationButton;//平移
    QLineEdit* translationX;
    QLineEdit* translationY;
    QPushButton* rotateButton;//旋转
    QLineEdit* angle;
    QPushButton* zoomButton;//缩放
    QLineEdit* zoom;
};

#endif // WIDGET_H
