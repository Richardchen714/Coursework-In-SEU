# FileName: CreateRandom.py
# Author: Richard H. CHEN
import pyodbc  # 连接MS Access需要使用的模块
import random

DBfile = r'C:\Users\richardchen0714\Documents\3rd Year Database\university.accdb'  # 数据库文件路径
conn = pyodbc.connect(
    r'Driver={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=' + DBfile)
# 创建游标
cursor = conn.cursor()
table_name = "student"  # 数据库中的表

# 一些英文名，第一位为性别
engName = ["fAaliyah", "mAaron", "fAarushi", "fAbagail", "fAbbey", "fAbbi", "fAbbie", "fAbby", "mAbdul", "mAbdullah", "mAbe", "mAbel", "fAbi", "fAbia", "fAbigail", "mAbraham", "mAbram", "fAbrianna", "mAbriel", "fAbrielle", "fAby", "fAcacia", "mAce", "fAda", "fAdalia", "fAdalyn", "mAdam", "mAdan", "fAddie", "mAddison",
           "fAddison", "mAde", "fAdelaide", "fAdele", "fAdelene", "fAdelia", "fAdelina", "fAdeline", "mAden", "mAdnan", "mAdonis", "fAdreanna", "mAdrian", "fAdriana", "fAdrianna", "fAdrianne", "mAdriel", "fAdrienne", "fAerona", "fAgatha", "fAggie", "fAgnes", "mAhmad", "mAhmed", "fAida", "mAidan", "mAiden", "fAileen", "fAilsa", "fAimee"]
# 获取数据库中表的全部数据
cursor.execute('SELECT count(1) AS count FROM %s' % table_name)
num = cursor.fetchall()[0][0]  # 表的行数

# 加入5000个数据
for i in range(5000):
    no = num+i+1
    nameIndex = random.randint(0, len(engName)-1)
    sex = engName[nameIndex][0]  # 性别
    name = engName[nameIndex][1:]  # 名
    age = random.randint(18, 30)  # 随机生成年龄
    year = random.randint(1, 5)
    gpa1 = random.uniform(0, 4)
    gpa = round(gpa1, 2)
    sql = "INSERT INTO "+table_name+" (sid, sname, sex, age, year, gpa) VALUES ("+str(
        no)+", '"+name+"', '"+sex+"', "+str(age)+", "+str(year)+", "+str(gpa)+");"
    # print(sql)
    cursor.execute(sql)
    cursor.commit()

cursor.close()
conn.close()  # 关闭游标&连接
