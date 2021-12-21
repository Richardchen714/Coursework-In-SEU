from PyQt5.QtWidgets import QMessageBox
import pyodbc
import random


class DAO:
    def __init__(self, path):
        self.conn = pyodbc.connect(
            'Driver={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=' + path)
        self.cursor = self.conn.cursor()

    def queryUsr(self, name, pswd) -> int:
        sql = "SELECT user.passwd FROM user WHERE user.uname='"+name+"'"
        self.cursor.execute(sql)
        truePswd = self.cursor.fetchall()
        if truePswd == []:
            return 1

        truePswd = truePswd[0][0]
        if pswd != truePswd:
            return 2

        return 0
    
    def queryStudentInfo(self,sid):
        sql="SELECT S.sid, S.sname, S.sex, S.age, S.year, S.gpa, M.dname\
            FROM student S, major M\
            WHERE S.sid=M.sid AND S.sid="+str(sid)+";"
        self.cursor.execute(sql)
        info = self.cursor.fetchall()
        if info==[]:
            return None
        else:
            return info[0]

    def queryScore(self,sid,cno,dname):
        sql="SELECT E.dname, E.cno, E.sectno, E.grade\
            FROM enroll E, student S, course C\
            WHERE S.sid="+str(sid)+" AND S.sid=E.sid AND C.cno=E.cno AND C.dname=E.dname\
            AND C.cno="+str(cno)+" AND E.dname='"+dname+"'"
        self.cursor.execute(sql)
        info = self.cursor.fetchall()
        if info==[]:
            return None
        else:
            return info[0]
