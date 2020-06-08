import os
try:
    import Shiboken2QtExample
except Exception as e:
    print("import ERROR: {}".format(e))
    pyside2_path = os.path.join(os.path.abspath(os.path.dirname(__file__)), "..", "..", "..", "python", "windows10-python-2.7.15", "Lib", "site-packages", "PySide2")
    os.putenv("PATH", r"C:\DEV_PROJECT\LIBRARY\libclang\bin;C:\DEV_PROJECT\LIBRARY\Qt\5.12.6\msvc2017_64\bin;%path%")
    os.putenv("PATH", r"{};%PATH%".format(pyside2_path))
    # check dll dependencies
    # VS x64 : dumpbin /dependents xxx.dll or xxx.pyd
    import Shiboken2QtExample


def slotRecive(*args, **kwargs):
    print("Signal emitted: {}, {}".format(args, kwargs))


def main():

    a = Shiboken2QtExample.QObjectWithEnum()
    a.someSignal.connect(slotRecive)
    a.aSlot()
    print("int(QObjectWithEnum.MyEnum.Values) =", int(Shiboken2QtExample.QObjectWithEnum.MyEnum.Values))
    a.nonSlotFunction(Shiboken2QtExample.QObjectWithEnum.MyEnum.Some)


if __name__ == '__main__':
    main()
