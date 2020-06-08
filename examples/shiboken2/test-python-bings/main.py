import os
import sys
from PySide2 import QtWidgets, QtCore, QtGui
try:
    import Universe
except Exception as e:
    print("Import ERROR: {}".format(e))
    os.putenv("PATH", r"C:\DEV_PROJECT\LIBRARY\libclang\bin;C:\DEV_PROJECT\LIBRARY\Qt\5.12.6\msvc2017_64\bin;%path%")
    os.putenv("PATH", r";%path%")
    import Universe


class RunScript(QtCore.QObject):
    def __init__(self, mainWindow):
        QtCore.QObject.__init__(self)
        self.mainWindow = mainWindow

    def runScript(self, script):
        print ("runScript")
        mainWindow = self.mainWindow
        exec (str(script))

    def SlotTest(self):
        print (w.editor.toPlainText())
        self.runScript(w.editor.toPlainText())
        # QObject.connect(SIGNAL('runPythonCodegg(Qstring)'),self.runScript)

    @QtCore.Slot(int)
    def SlotTestInt(num):
        print ("SlotTestInt")
        speak_words = QtCore.Signal(str)
        signaltest = QtCore.Signal()

    @QtCore.Slot(str)
    def say_some_words(words):
        print(words)


def main():
    a = QtWidgets.QApplication(sys.argv)

    print ("Start")
    w = Universe.MainWindow()
    print ("END")
    r = RunScript(w)

    w.setWindowTitle('PyHybrid')
    w.resize(1000, 800)
    w.show()

    w.connect(w, QtCore.SIGNAL('runPythonCode(Qstring)'), r.runScript)

    a.exec_()


if __name__ == '__main__':
    main()
