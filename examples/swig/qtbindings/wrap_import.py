import os
import sys
try:
    import wrap
except ImportError as e:
    os.putenv("PATH", r"C:/DEV_PROJECT/LIBRARY/Qt/5.12.6/msvc2017_64/bin;%path%")
    import wrap

from PySide2 import QtWidgets


def SlotPrintMsg(*args, **kwargs):
    print("PrintMsg: {}, {}".format(args, kwargs))


if __name__ == '__main__':
    wp = wrap.Wrap()
    app = QtWidgets.QApplication(sys.argv)
    # wp.EQ_sayHello()
    # wp.EQ_createWidget()
    widget_ = wp.EQ_getWidget()
    print(widget_)
    wp.EQ_widgetShow(widget_)

    app.exec_()
