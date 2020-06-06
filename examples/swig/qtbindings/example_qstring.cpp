#include "example_qstring.h"

using namespace std;

ExampleQString::ExampleQString()
{
    m_str = new QString("Hello Python, we are Example for QString!");
}

void ExampleQString::sayHello(){
    cout << m_str->toLatin1().data() << endl;
}