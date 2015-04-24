#ifndef SLIDINGCONTROLWIDGET_H
#define SLIDINGCONTROLWIDGET_H

#include <QString>
#include <QWidget>

QT_FORWARD_DECLARE_CLASS(QSlider)
QT_FORWARD_DECLARE_CLASS(QLabel)

class SlidingControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SlidingControlWidget(QString const& title, int minSliderValue, int maxSliderValue, QWidget *parent = 0);
    ~SlidingControlWidget();

signals:

public slots:

private:
    QLabel* _valueLabel;
    QSlider* _slider;
};

#endif // SLIDINGCONTROLWIDGET_H
