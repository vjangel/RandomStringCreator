#include "MainWidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>

#include <Universal>
#include <QGuiApplication>
#include <QClipboard>


MainWidget::MainWidget(QWidget *p)
    :QWidget{p}
{
    InitUi();
    InitObject();
    InitConnect();
    InitProperty();
}

MainWidget::~MainWidget()
{
    //do something...
}

void MainWidget::InitUi()
{
    setObjectName("MainWidget");
    setWindowTitle(tr("RandomStringCreator"));
    setMinimumSize(300,120);

    auto rootLayout = new QHBoxLayout(this);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(0);

    auto backWidget = new QWidget(this);
    backWidget->setObjectName("MainWidgetBackgroundWidget");
    
    auto backLayout = new QHBoxLayout(backWidget);
    backLayout->setContentsMargins(0, 0, 0, 0);
    backLayout->setSpacing(0);

    auto shadeWidget = new QWidget(backWidget);
    shadeWidget->setObjectName("MainWidgetShadeWidget");
    
    auto shadeLayout = new QHBoxLayout(shadeWidget);
    shadeLayout->setContentsMargins(0, 0, 0, 0);
    shadeLayout->setSpacing(0);


    //Layout 
    rootLayout->addWidget(backWidget);
    backLayout->addWidget(shadeWidget);

    m_pFunWidget = new QWidget(this);
    m_pFunWidget->setObjectName("MainWidgetFunWidget");
    shadeLayout->addWidget(m_pFunWidget);


    auto funLayout = new QVBoxLayout(m_pFunWidget);
    funLayout->setContentsMargins(10, 10, 10, 10);
    funLayout->setSpacing(10);


    m_pRandomLineEdit = new QLineEdit(this);
    m_pRandomLineEdit->setObjectName("MainWidgetRandomLineEdit");
    m_pRandomLineEdit->setReadOnly(true);
    m_pRandomLineEdit->setMinimumHeight(30);


    m_pCreateRandomBtn = new QPushButton(tr("Create"), m_pFunWidget);
    m_pCreateRandomBtn->setObjectName("MainWidgetRandomBtn");
    m_pCreateRandomBtn->setToolTip(tr("Create a random string"));
    m_pCreateRandomBtn->setToolTipDuration(5000);
    m_pCreateRandomBtn->setMinimumHeight(30);

    m_pClipBtn = new QPushButton(tr("Copy"), m_pFunWidget);
    m_pClipBtn->setObjectName("MainWidgetResetBtn");
    m_pClipBtn->setToolTip(tr("Copy to clipboard"));
    m_pClipBtn->setMinimumHeight(30);

    auto btnLayout = new QHBoxLayout;
    btnLayout->addWidget(m_pCreateRandomBtn);
    btnLayout->addWidget(m_pClipBtn);

    funLayout->addWidget(m_pRandomLineEdit, 1);
    funLayout->addLayout(btnLayout, 1);




}

void MainWidget::InitObject()
{

}

void MainWidget::InitConnect()
{

    connect(m_pCreateRandomBtn, &QPushButton::clicked, this, [=]()
    {
        this->m_pRandomLineEdit->clear();
        auto randomStr = UNIVERSAL::generateRandomString(30);
        this->m_pRandomLineEdit->setText(randomStr);

        if(randomStr.size() > 20) 
        {
            QString longRandomStr;
            for(int i = 0; i < randomStr.size(); ++i)
            {
                if(i != 0 && i % 20 == 0) longRandomStr.append('\n');
                longRandomStr.append(randomStr.at(i));
            }
            this->m_pRandomLineEdit->setToolTip(longRandomStr);
        }
        else this->m_pRandomLineEdit->setToolTip(randomStr);
    });

    connect(m_pClipBtn, &QPushButton::clicked, this, [=]()
    {
        auto str = this->m_pRandomLineEdit->text();
        if(!str.isEmpty())
        {
            auto clipboard = QGuiApplication::clipboard();
            clipboard->clear();
            clipboard->setText(str);
            UNIVERSAL::oneButton(this->m_pClipBtn, 1000, "Success");
        }
    });
}

void MainWidget::InitProperty()
{
    QFile qss(":/style/MainWidget.css");
    if(qss.open(QFile::ReadOnly))
    {
        setStyleSheet(qss.readAll());
        qss.close();
    }
    else qWarning() << "[ERROR] style load failed!";
}

