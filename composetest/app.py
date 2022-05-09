import time
import redis
import http.client, urllib.parse
import json
from flask import Flask
from flask import request
import mysql.connector


app = Flask(__name__)
cache = redis.Redis(host='redis', port=6379)

#/api?cidade=12

@app.route('/api')
def testf():
    cidade = request.args.get('cidade', default = 0)
    bairro = request.args.get('bairro', default = 0)

    conn = http.client.HTTPConnection('api.positionstack.com')

    params = urllib.parse.urlencode({
        'access_key': '476d4e4b1abf22991de5fb8000f7f063',
        'query': cidade,
        })

    conn.request('GET', '/v1/forward?{}'.format(params))

    res = conn.getresponse()
    data = res.read()

    dataJson = json.loads(data.decode('utf-8'))

    lat = dataJson["data"][0]["latitude"]
    long = dataJson["data"][0]["longitude"]

    conn = http.client.HTTPConnection('api.openweathermap.org')
    conn.request('GET', '/data/2.5/weather?lat={}&lon={}&appid=76ebe714332866e8aee016451cc2da97'.format(lat,long))

    res = conn.getresponse()
    data = res.read()
    #print(data)
    dataJson = json.loads(data.decode('utf-8'))

    conv = int(dataJson["main"]["temp"]) - 273.15 

    #print(int(conv))

    cnx = mysql.connector.connect(user='root', database='test_db',passwd='root',host='192.168.0.10',port = '3308')

    # db = MySQLdb.connect(host="localhost",    # your host, usually localhost
    #                      user="root",         # your username
    #                      passwd="root",  # your password
    #                      db="test_db")        # name of the data base

    # you must create a Cursor object. It will let
    #  you execute all the queries you need
    cur = cnx.cursor()

    # Use all the SQL you like
    #cur.execute("DROP TABLE CidadeData;")
    #cur.execute("CREATE TABLE CidadeData (Cidade varchar(255),longitude int,latitude int,Temperatura int);")
    
    cur.execute("INSERT INTO CidadeData (Cidade, longitude, latitude, Temperatura) VALUES ('{}', {}, {}, {}); ".format(cidade,long,lat,conv))


    cnx.commit()
    cnx.close()

    return 'temperatura {} graus celsius'.format(int(conv)) 