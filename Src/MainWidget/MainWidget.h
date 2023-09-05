#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QFile>
#include <QFrame>

class QLineEdit;
class QPushButton;

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *p=nullptr);
    ~MainWidget();

    void InitUi();
    
    void InitObject();

    void InitConnect();

    void InitProperty();

public slots:


signals:

private slots:


private:
    QWidget * m_pFunWidget;

    QLineEdit * m_pRandomLineEdit;

    QPushButton * m_pCreateRandomBtn;
    QPushButton * m_pClipBtn;



};








#endif//MAINWIDGET.H