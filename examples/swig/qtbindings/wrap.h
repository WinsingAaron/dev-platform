#ifndef WRAP_H
#define WRAP_H

class ExampleQString;
class ExampleQWidget;

class  Wrap
{
private:
    ExampleQString *m_example_qstring;
public:
    Wrap();
    void EQ_sayHello();
    void EQ_createWidget();
    ExampleQWidget* EQ_getWidget();
    void EQ_widgetShow(ExampleQWidget*);
};

#endif // WRAP_H
