#ifndef UNIVERSAL_HPP
#define UNIVERSAL_HPP
#include <QObject>
#include <QDateTime>
#include <QTime>
#include <QTimer>
#include <QVector>
#include <QAbstractButton>
#include <QList>
#include <QCoreApplication>
#include <QRandomGenerator>
#include <QStringList>


namespace UNIVERSAL
{

#define CURR_DATE_TIME QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz")

const QString m_none_SheetStyle = "min-width: %3px; \
                                   min-height: %3px; \
                                   max-width: %3px; \
                                   max-height: %3px;\
                                   border-radius: %2px; \
                                   border:1px solid black; \
                                   background:%1";
const QString m_red_SheetStyle = m_none_SheetStyle.arg("red").arg(8).arg(16);
const QString m_green_SheetStyle = m_none_SheetStyle.arg("#06b025").arg(8).arg(16);

enum BIG_LITTLE
{
    BIG         ,   //大端
    LITTLE      ,   //小端
    BIG_SWAP    ,   //大端-交换
    LITTLE_SWAP ,   //小端-交换
};

inline const QString redSheetStyle(uint a, uint b) {
    return m_none_SheetStyle.arg("red").arg(a).arg(b);
}

inline const QString greenSheetstyle(uint a, uint b) {
    return m_none_SheetStyle.arg("06b025").arg(a).arg(b);
}

inline const QString whiteSheetstyle(uint a, uint b) {
    return m_none_SheetStyle.arg("white").arg(a).arg(b);
}

inline void MSleep(int msec) {
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


//小端 DCBA 4321
inline float getFloat(quint16 l16, quint16 h16, uint pos1, uint pos2, uint pos3, uint pos4) {
    // chTemp 0  1  2  3
    //    0x  12 34 56 78
    //        A  B  C  D
    float a = 0.f;
    unsigned char * r = (unsigned char *)&a;
    unsigned char chTemp[4]; // 4*8=32bit

    //L：0   H:3
    chTemp[0] = l16 & 0xFF;
    chTemp[1] = (l16 >> 8) & 0xFF;
    chTemp[2] = h16 & 0xFF;
    chTemp[3] = (h16 >> 8) & 0xFF;

    *r++ = chTemp[pos1];
    *r++ = chTemp[pos2];
    *r++ = chTemp[pos3];
    *r++ = chTemp[pos4];

    return a;
}

inline float getLittleFloat(quint16 h16, quint16 l16) {
    return getFloat(h16, l16, 3,2,1,0);
}
inline float getLittleFloat(quint32 u32) {
    quint16 h16 = u32 & 0xFFFF;
    quint16 l16 = u32 >> 0x10;
    return getLittleFloat(h16, l16);
}

inline float getLittleSwapFloat(quint16 h16, quint16 l16) {
    return getFloat(h16, l16, 2,3,0,1);
}
inline float getLittleSwapFloat(quint32 u32) {
    quint16 h16 = u32 >> 0x10;
    quint16 l16 = u32 & 0xFFFF;
    return getLittleSwapFloat(h16, l16);
}

//大端 ABCD
inline float getBigFloat(quint16 h16, quint16 l16) {
    return getFloat(h16, l16, 0,1,2,3);
}
inline float getBigFloat(quint32 u32) {
    quint16 h16 = u32 >> 0x10;
    quint16 l16 = u32 & 0xFFFF;
    return getBigFloat(h16, l16);
}

inline float getBigSwapFloat(quint16 h16, quint16 l16) {
    return getFloat(h16, l16, 1,0,3,2);
}
inline float getBigSwapFloat(quint32 u32) {
    quint16 h16 = u32 & 0xFFFF;
    quint16 l16 = u32 >> 0x10;
    return getBigSwapFloat(h16, l16);
}


//转32位浮点数  Big Big-Swap Littel  Littel-S
//             0     1        2       3
inline const QList<float> toFloatDatas(QVector<quint16> datas, BIG_LITTLE model) {
    QList<float> fList;

    if(0 != datas.size() % 2) return fList;
    for(int i = 0; i < datas.size(); i+=2)
    {
        float f;
        if(BIG_LITTLE::BIG == model)            f = UNIVERSAL::getBigFloat(datas.at(i), datas.at(i+1));
        else if(BIG_LITTLE::BIG_SWAP == model)  f = UNIVERSAL::getBigSwapFloat(datas.at(i), datas.at(i+1));
        else if(BIG_LITTLE::LITTLE == model)    f = UNIVERSAL::getLittleFloat(datas.at(i), datas.at(i+1));
        else                                    f = UNIVERSAL::getLittleSwapFloat(datas.at(i), datas.at(i+1));

        fList << f;
    }
    return fList;
}

inline  bool isLittelEndian() {
    return ((uchar)0x1234 == 0x34);
}


bool oneButton(QAbstractButton *btn, const int msec, const QString& tipText=nullptr, bool recover=true)
{
    if(nullptr == btn) return false;
    if(msec <= 0) return false;

    btn->setEnabled(false);
    auto oldStr = btn->text();
    if(!tipText.isNull()) btn->setText(tipText);
    QTimer::singleShot(msec, [=](){ btn->setEnabled(true);  if(recover) btn->setText(oldStr);});
    return true;
}

inline const QString generateRandomString(const uint length)
{
    QString str;
    auto randomGenerator = QRandomGenerator::system();

    for (uint i = 0; i < length; i++)
    {
        int value = randomGenerator->bounded(62);
        char nextChar;

        if(value < 10) nextChar = '0' + value;
        else if(value < 36) nextChar = 'A' + value  - 10;
        else nextChar = 'a' + value  - 36;
        str.append(nextChar);
    }
    return str;
}


}


#endif // UNIVERSAL_H
