#include "example_qwidget.h"

ExampleQWidget::ExampleQWidget(QWidget *parent)
    : QWidget(parent)
{
    m_button = new QPushButton(this);
    m_button->setText("Click Me!");
}

ExampleQWidget::~ExampleQWidget()
{
}

void ExampleQWidget::showMe(){
    show();
}

void ExampleQWidget::setValue(int value)
{
    if (value != m_value) {
        m_value = value;
        emit valueChanged(value);
    }
}
