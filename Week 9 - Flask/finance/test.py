import os
import datetime
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from helpers import apology, login_required, lookup, usd

db = SQL("sqlite:///finance.db")

#testing sql searches and dictionaries

user_id = 4
print(lookup('teasdf'))

stock_list = db.execute("SELECT distinct(symbol) from purchases WHERE user_id =?", user_id) #order by alphabetical?
share = db.execute("SELECT SUM(shares) from purchases WHERE user_id = ? and symbol = ?", user_id, stock_list[0]["symbol"])[0]['SUM(shares)']
price = lookup(stock_list[0]['symbol'])

index = {}
big_index = {}
total_value = 0

index["shares"] =  db.execute("SELECT SUM(shares) from purchases WHERE user_id = ? and symbol = ?", user_id, stock_list[0]["symbol"])[0]['SUM(shares)']
#print(stock_list)
#for i in range(len(stock_list)):
  #  index["shares"] =  db.execute("SELECT SUM(shares) from purchases WHERE user_id = ? and symbol = ?", user_id, stock_list[i]["symbol"])[0]['SUM(shares)']
    #index["price"] = lookup(stock_list[i]['symbol'])['price']
    #index["symbol"] = lookup(stock_list[i]['symbol'])['symbol']
    #index["value"] = index['price'] * index['shares']
    #total_value += index["value"]
    #big_index[i] = index
    #index = {}
    #print(index)
#print(big_index[0])
#print(big_index[0]['shares'])
cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']
total_value += cash



#print(stock_list[0]['symbol'])
#print(db.execute("SELECT SUM(shares) from purchases WHERE user_id = ? and symbol = ?", user_id, stock_list[i]["symbol"]))
#print(lookup('gme')['symbol'])
#print('cash: ', cash[0]['cash'])
#print('total value: ', total_value)
#print(big_index)
#print(index)
#print('cash: ', cash)
#print('stock list: ', stock_list)
#print("stock_list[0]['symbol']: ", stock_list[0]['symbol'])
#print("stock_list[1]['symbol']: ", stock_list[1]['symbol'])
#print('share: ', share)
#print("share[0]['SUM(shares)']: ", share)
#print('price: ', price)
