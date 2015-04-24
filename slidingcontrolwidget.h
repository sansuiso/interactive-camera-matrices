#ifndef SLIDINGCONTROLWIDGET_H
#define SLIDINGCONTROLWIDGET_H

#include <functional>

#include <QString>
#include <QWidget>

QT_FORWARD_DECLARE_CLASS(QSlider)
QT_FORWARD_DECLARE_CLASS(QLabel)

class SlidingControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SlidingControlWidget(QString const& title,
                                  int minSliderValue, int maxSliderValue, int initialValue,
                                  std::function<float(int)> mapping,  QWidget *parent = 0);
    ~SlidingControlWidget();

    void setValue(float value);

    float value() const {
        return _value;
    }

signals:
    void valueChanged(float);

public slots:

private:
    QLabel* _valueLabel;
    QSlider* _slider;
    std::function<float(int)> _mapping;

    float _value;
};

#endif // SLIDINGCONTROLWIDGET_H
