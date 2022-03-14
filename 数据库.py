
import pymysql

# 远程登陆数据库

con = pymysql.Connect(
    host='cd-cdb-8i96b46e.sql.tencentcdb.com',           # 外网地址  (数据库管理中查看)
    port=61812,             # 外网端口  (数据库管理中查看)
    user='root',            # 账号      (初始化的账号)
    passwd='shangyi1234567',         # 密码      (初始化的密码)
    db='test1'              # 数据库名称
)
# 获取本次的游标
cur = con.cursor()
try:
    sql = 'create table t1(id int,name char(4),class char(10))'
    sql1 = 'insert into t1 values(1,"尚艺","大二")'
    cur.execute(sql)
    cur.execute(sql1)
    con.commit()
    print('成功')
except pymysql.Error as e:
    print("Error %d: %s" % (e.args[0], e.args[1]))
