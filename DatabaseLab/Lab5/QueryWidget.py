from PyQt5 import QtWidgets, QtGui
from pyodbc import connect

class QueryWidget(QtWidgets.QWidget):
    def __init__(self, parent = None):
        super(QueryWidget,self).__init__(parent)
        self.resize(600,400)
        self.setWindowTitle('Query')
        self.sidLabel=QtWidgets.QLabel(self)
        self.sidLabel.setText('studentID')
        self.sidLabel.move(140,120)
        self.sidInput=QtWidgets.QLineEdit(self)
        self.sidInput.move(250,120)

        self.courseNOLabel=QtWidgets.QLabel(self)
        self.courseNOLabel.setText('CourseNum')
        self.courseNOLabel.move(140,180)
        self.courseNOInput=QtWidgets.QLineEdit(self)
        self.courseNOInput.move(250,180)

        self.dnameLabel=QtWidgets.QLabel(self)
        self.dnameLabel.setText('deptName')
        self.dnameLabel.move(140,240)
        self.dnameInput=QtWidgets.QLineEdit(self)
        self.dnameInput.move(250,240)

        self.infoBtn=QtWidgets.QPushButton(self)
        self.infoBtn.setText('StuInfo')
        self.infoBtn.move(200,330)
        self.scoreBtn=QtWidgets.QPushButton(self)
        self.scoreBtn.setText('Score')
        self.scoreBtn.move(350,330)