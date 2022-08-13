import os
import datetime
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # we want to display stocks, number of shares, current price, total value of each holding, current cash, and total value of portfolio
    user_id = session.get("user_id")

    stock_list = db.execute("SELECT distinct(symbol) from purchases WHERE user_id =?", user_id)
    index = {}
    big_index = {}
    total_value = 0

    for i in range(len(stock_list)):
        index["shares"] =  db.execute("SELECT SUM(shares) from purchases WHERE user_id = ? and symbol = ?", user_id, stock_list[i]["symbol"])[0]['SUM(shares)']

        # default if no shares owned
        if index == None:
            index["shares"] = 0
            index["price"] = "N/A"
            index["symbol"] = "None"
            index["value"] = usd(0)
            big_index[0] = index
            break

        #removes sold stock from display
        if index["shares"] == 0:
            continue

        index["price"] = lookup(stock_list[i]['symbol'])['price']
        index["symbol"] = lookup(stock_list[i]['symbol'])['symbol']
        index["value"] = index['price'] * index['shares']
        index["price"] = usd(index["price"])

        big_index[i] = index
        total_value += index["value"]
        index["value"] = usd(index["value"])
        index = {}

    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']
    total_value += cash
    usd_cash = usd(cash)
    usd_tv = usd(total_value)
    return render_template("index.html", cash=usd_cash, total_value=usd_tv, big_index=big_index)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        user_id = session.get("user_id")

        #check if symbol entered
        ticker = request.form.get("symbol")
        if not ticker:
            return apology("enter a symbol")
        #check if symbol exists
        symbol = lookup(ticker)
        if symbol == None:
            return apology("symbol does not exist")

        shares = request.form.get("shares")
        # error checking
        #make sure user entered a share
        if not shares:
            return apology("enter a number of shares")
        #ensure shares is an number
        if not shares.isnumeric():
            return apology("input is not an integer")
        shares = int(shares)
        #ensure shares is positive
        if shares <= 0:
            return apology("input is not a positive integer")

        time = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        purchase_price = symbol["price"]
        cash = db.execute("SELECT cash from users where id = ?", user_id)[0]['cash']

        if purchase_price * shares > cash:
            return apology("you can't afford that much")

        #count = db.execute("SELECT count(table_id) from purchases")[0]['count'] +1
        db.execute("INSERT INTO purchases (symbol, shares, user_id, purchase_price, time) VALUES( ?, ?, ?, ?, ?)", symbol['symbol'], shares,
        user_id, purchase_price, time)
        new_cash= cash - purchase_price * shares
        db.execute("UPDATE users SET cash = ? WHERE id=?", new_cash, user_id)
        #flash("successfully bought")
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    #if request.method == "POST":
    user_id = session.get("user_id")

    history = db.execute("SELECT * from purchases WHERE user_id =?", user_id)
    #share = db.execute("SELECT SUM(shares) from purchases WHERE user_id = ? and symbol = ?", user_id, stock_list[0]["symbol"])[0]['SUM(shares)']

    hist_index = {}
    hist_big_index = {}

    for i in range(len(history)):
        hist_index["shares"] = abs(history[i]["shares"])
        hist_index["price"] = history[i]["purchase_price"]
        hist_index["symbol"] = history[i]["symbol"]
        hist_index["time"] = history[i]["time"]
        if history[i]["shares"] <0:
            hist_index["transaction"] = "sold"
        else:
            hist_index["transaction"] = "bought"

        hist_big_index[i] = hist_index
        hist_index = {}

    return render_template("history.html", hist_big_index=hist_big_index)



@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method=="POST":
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if not quote:
            return apology("enter a symbol")
        if quote == None:
            return apology("invalid symbol")
        quote["price"] = usd(quote["price"])
        return render_template("quoted.html", quote = quote)

    else:
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # allow user to register an account via a form
    # 1 require input a username (text field name:username), apology if username is taken
    if request.method =="POST":

        # validating username input
        if not request.form.get("username"):
            return apology("username required")

        username = request.form.get("username")
        # checking if username is already taken
        placeholder = db.execute("SELECT username FROM users where username = ?", username)
        if placeholder:
            return apology("username Taken")

        # 2 require input a password, require input again, and confirm, apology if passwords don't match
        password = request.form.get("password")
            # validating password input
        if not request.form.get("password"):
            return apology("password required")
        num = set('0123456789')
        if not len(password) > 14 or not any((c in num) for c in password):
            return apology("Password must be >13 characters and have at least one number")
        confirmation = request.form.get("confirmation")

            # validating confirmation input
        if not request.form.get("confirmation"):
            return apology("confirmation required")
        # check if password matches confirmation
        if password != confirmation:
            return apology("Passwords do not match")

        # 3 INSERT new user into users, storing a hash of the password
        password_hash = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, password_hash)

        flash("You are registered!")
        return redirect("/")


    else:
        # route if user clicked on button/redirect
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    big_index = {}
    user_id = session.get("user_id")
    stock_list = db.execute("SELECT distinct(symbol) from purchases WHERE user_id =?", user_id)
    index = {}
    # generate dictionary of owned stocks
    for i in range(len(stock_list)):
        index["shares"] =  db.execute("SELECT SUM(shares) from purchases WHERE user_id = ? and symbol = ?", user_id, stock_list[i]["symbol"])[0]['SUM(shares)']
        index["symbol"] = lookup(stock_list[i]['symbol'])['symbol']
        big_index[i] = index
        index = {}

    if request.method == "POST":
        stock = request.form.get("symbol")
        # ensure proper input
        if not stock:
            return apology("Select a stock")

        qty = int(request.form.get("shares"))
        if not qty:
            return apology("Input a number of shares")

        # check that user has X shares
        owned = db.execute("SELECT SUM(shares) from purchases WHERE user_id = ? and symbol = ?", user_id, stock)[0]['SUM(shares)']
        if not owned or (qty > owned):
            return apology("shares not owned")

        # remove sold stock from database
        price = lookup(stock)["price"]
        new_cash = price * qty
        time = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        db.execute("INSERT INTO purchases (symbol, shares, user_id, purchase_price, time) VALUES( ?, ?, ?, ?, ?)", stock, -qty,
            user_id, price, time)
        # add cash
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", new_cash, user_id)
        return redirect("/")
    else:
        return render_template("sell.html", big_index=big_index)