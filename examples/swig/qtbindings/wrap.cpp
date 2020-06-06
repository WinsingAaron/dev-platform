#include "wrap.h"
#include "example_qstring.h"
#include "example_qwidget.h"

Wrap::Wrap()
{
    m_example_qstring = new ExampleQString();
}

void Wrap::EQ_sayHello(){
    m_example_qstring->sayHello();
}

void Wrap::EQ_createWidget(){
    ExampleQWidget* w = new ExampleQWidget();
    w->show();
}

ExampleQWidget* Wrap::EQ_getWidget(){
    ExampleQWidget* w = new ExampleQWidget();
    w->setFixedSize(560, 560);
    return w;
}

void Wrap::EQ_widgetShow(ExampleQWidget* w){
    w->showMe();
}