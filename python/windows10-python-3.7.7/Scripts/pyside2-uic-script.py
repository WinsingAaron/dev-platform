#!C:\DEV_PROJECT\GIT\wsrd-python-platform\python-3.7.7-windows10\python.exe
# EASY-INSTALL-ENTRY-SCRIPT: 'PySide2==5.12.6','console_scripts','pyside2-uic'
__requires__ = 'PySide2==5.12.6'
import re
import sys
from pkg_resources import load_entry_point

if __name__ == '__main__':
    sys.argv[0] = re.sub(r'(-script\.pyw?|\.exe)?$', '', sys.argv[0])
    sys.exit(
        load_entry_point('PySide2==5.12.6', 'console_scripts', 'pyside2-uic')()
    )
