#ifndef EXAMPLE_QSTRING_H
#define EXAMPLE_QSTRING_H

#include <iostream>
#include <QString>

class ExampleQString
{
private:
    QString *m_str;
public:
    ExampleQString();
    void sayHello();
};

#endif // EXAMPLE_QSTRING_H
