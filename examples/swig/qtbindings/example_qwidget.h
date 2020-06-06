#ifndef EXAMPLE_QWIDGET_H
#define EXAMPLE_QWIDGET_H

#include <QWidget>
#include <QPushButton>

class ExampleQWidget : public QWidget
{
    Q_OBJECT

public:
    ExampleQWidget(QWidget *parent = nullptr);
    ~ExampleQWidget();
    void showMe();
    /*
     * Get m_value
     */
    int value() const { return m_value; }

public slots:
    void setValue(int value);

signals:
    void valueChanged(int newValue);
private:
    int m_value;
    QPushButton* m_button;
};
#endif // EXAMPLE_QWIDGET_H
