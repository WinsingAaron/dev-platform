import os
import sys
from PySide2 import QtWidgets, QtCore, QtGui


def main():
    app = QtWidgets.QApplication(sys.argv)
    widget_ = QtWidgets.QWidget()
    widget_.show()
    app.exec_()


if __name__ == '__main__':
    main()
