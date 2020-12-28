from datetime import datetime

import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


db.execute("CREATE TABLE IF NOT EXISTS 'users'(id INTEGER, username TEXT NOT NULL, hash TEXT NOT NULL, cash NUMERIC NOT NULL DEFAULT 10000.00, PRIMARY KEY(id))")
db.execute("CREATE UNIQUE INDEX IF NOT EXISTS username ON users(username)")
db.execute("CREATE TABLE IF NOT EXISTS 'stock'(stock_id INTEGER, symbol TEXT NOT NULL, shares INTEGER, user_id INTEGER, PRIMARY KEY(stock_id), FOREIGN KEY(user_id) REFERENCES users(id))")
db.execute("CREATE TABLE IF NOT EXISTS 'history'(hist_id INTEGER, user_id INTEGER, symbol TEXT NOT NULL, shares INTEGER, price REAL , transacted TEXT, PRIMARY KEY(hist_id))")

now = datetime.now()
dt_string = now.strftime("%d/%m/%Y %H:%M:%S")

ITEMS = [
    "Symbol",
    "Name",
    "Shares",
    "Price",
    "TOTAL"
]


def pass_check(passwd):
    check = True
    if len(passwd) < 8:
        check = False
    if not any(char.isdigit() for char in passwd):
        check = False
    if not any(char.isupper() for char in passwd):
        check = False
    if not any(char.islower() for char in passwd):
        check = False
    return check


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    hardcash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    inspect = db.execute("SELECT * FROM stock WHERE user_id = ?", session["user_id"])
    if not inspect:
        return render_template("index.html", items=ITEMS, info=" ", totalown=hardcash[0]['cash'], cashown=hardcash[0]['cash'])
    else:
        t_own = hardcash[0]['cash']
        for i in inspect:
            dof = lookup(i['symbol'])
            i['name'] = dof['name']
            i['price'] = dof['price']

            t_own += i['price'] * i['shares']

        return render_template("index.html", items=ITEMS, info=inspect, totalown=t_own, cashown=hardcash[0]['cash'])


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        num = request.form.get("shares")
        stock = lookup(request.form.get("symbol"))

        if not stock:
            return apology("no such symbol", 400)

        if not num.isnumeric():
            return apology("Invalid shates", 400)

        num = int(num)

        stock_cost = stock["price"]
        if num < 1 or not stock:
            return apology("Cant process that. Check if the shares and symbol is valid")

        availmon = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        availmon = availmon[0]['cash']

        if availmon < num * stock_cost:
            return apology("Cant afford that much currently")
        preshare = db.execute("SELECT shares FROM stock WHERE symbol=? AND user_id=?", stock["symbol"], session["user_id"])
        if not preshare:
            db.execute("INSERT INTO stock(symbol,shares,user_id) VALUES(?, ?, ?)", stock["symbol"], num, session["user_id"])
        else:
            db.execute("UPDATE stock SET shares=? WHERE symbol=? AND user_id=?",
                       num+preshare[0]['shares'], stock["symbol"], session["user_id"])

        availmon -= num * stock_cost
        db.execute("UPDATE users SET cash = ? WHERE id = ?", availmon, session["user_id"])

        db.execute("INSERT INTO history(user_id, symbol, shares, price, transacted) VALUES(?, ?, ?, ?, ?)",
                   session['user_id'], stock['symbol'], num, stock_cost, dt_string)
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    histfil = db.execute("SELECT * FROM history WHERE user_id=?", session['user_id'])
    return render_template("history.html", hist=histfil)


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
    if request.method == "POST":
        info = lookup(request.form.get("symbol"))
        if not info:
            return apology("no such symbol", 400)

        return render_template("quoted.html", info=info)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        # Query database for existing username
        rows = db.execute("SELECT username FROM users")

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)
        elif not request.form.get("confirmation"):
            return apology("must confirm password", 400)

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords didnt match", 400)

        elif not pass_check(request.form.get("password")):
            return apology("password should contain atleat 8 characters, 1 uppercase letter, 1 lowercase letter, 1 number", 400)

        # Ensure username not in use
        for row in rows:
            if request.form.get("username") == row['username']:
                return apology("username already in use", 400)

        # Get password hash
        hashval = generate_password_hash(request.form.get("password"))
        db.execute("INSERT INTO users(username, hash) VALUES(?, ?)", request.form.get("username"), hashval)

        return redirect("/login", 200)

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        num = int(request.form.get("shares"))
        stock = lookup(request.form.get("symbol"))
        stock_cost = int(stock["price"])
        if num < 1 or not stock:
            return apology("Cant process that. Check if the shares and symbol is valid")

        availmon = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        availmon = availmon[0]['cash']

        preshare = db.execute("SELECT shares FROM stock WHERE symbol=? AND user_id=?", stock["symbol"], session["user_id"])
        if not preshare:
            return apology("Sorry you dont own that stock", 400)
        elif num > preshare[0]['shares']:
            return apology('Sorry you dont own that many stock', 400)
        elif num == preshare[0]['shares']:
            db.execute("DELETE FROM stock WHERE symbol=? AND user_id=?", stock["symbol"], session["user_id"])
        elif num < preshare[0]['shares']:
            db.execute("UPDATE stock SET shares=? WHERE symbol=? AND user_id=?",
                       preshare[0]['shares']-num, stock["symbol"], session["user_id"])

        availmon += num * stock_cost
        db.execute("UPDATE users SET cash = ? WHERE id = ?", availmon, session["user_id"])

        db.execute("INSERT INTO history(user_id, symbol, shares, price, transacted) VALUES(?, ?, ?, ?, ?)",
                   session['user_id'], stock['symbol'], 0-num, stock_cost, dt_string)
        return redirect("/")
    else:
        own = db.execute("SELECT symbol FROM stock WHERE user_id=?", session['user_id'])
        return render_template("sell.html", stocks=own)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
