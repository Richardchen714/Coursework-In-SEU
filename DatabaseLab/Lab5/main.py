import sys
from PyQt5.QtWidgets import QApplication, QMainWindow
from Widget import Widget

if __name__ == '__main__':
    app = QApplication(sys.argv) # Must construct a QApplication before a QWidget
    widget=Widget(None)
    widget.show()
    sys.exit(app.exec_())
    