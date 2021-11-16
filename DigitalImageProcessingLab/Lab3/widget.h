#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include "image.h"
#include "process.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void view();
    void grayTrans();
    void sharpenAndTransfer();
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
