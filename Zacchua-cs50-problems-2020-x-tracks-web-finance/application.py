import os

import datetime
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
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


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    i = session["user_id"]
    total1 = 0
    own = db.execute("SELECT * FROM stocks WHERE user_id = :uid", uid=i)
    for row in own:
        value = lookup(row["sym"])
        total = value["price"] * row["count"]
        symb = row["sym"]
        row["total"] = total
        row["name"] = value["name"]
        row["price"] = value["price"]
        total1 += total
    user1 = db.execute("SELECT cash FROM users WHERE id = :k", k=i)
    cash = user1[0]["cash"]
    total1 += cash
    return render_template("index.html", stocks=own, cash=cash, total1=total1)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":

        """error checking"""
        numb = request.form.get("stock")
        numb = int(numb)
        if numb < 1:
            return apology("must enter positive number", 403)
        row1 = {}
        row1 = lookup(request.form.get("symbol"))
        if not row1:
            return apology("invalid stock symbol", 403)

        """gets the price of stocks and amount of money and makes sure enough"""
        price = row1["price"]*numb
        n = session["user_id"]
        money = db.execute("SELECT * FROM users WHERE id = :x", x=n)
        money1 = int(money[0]["cash"])
        if price > money1:
            return apology("Insufficient Funds", 403)
        else:
            rem = money1 - price
            db.execute("UPDATE users SET cash = :m WHERE id = :i", m=rem, i=n)
            row2 = db.execute("SELECT * FROM stocks WHERE sym = :u AND user_id = :k", u=row1["symbol"], k=n)
            if not row2:
                db.execute("INSERT INTO stocks VALUES (:a, :b, :c)", a=n, b=row1["symbol"], c=numb)
            else:
                counter = int(row2[0]["count"])
                counter += numb
                db.execute("UPDATE stocks SET count = :num WHERE user_id = :d AND sym = :stsym", num=counter, d=n, stsym=row1["symbol"])
        now = datetime.datetime.now()
        db.execute("INSERT INTO history VALUES (:d , :y, :t, :p, :s)", d=n, y=numb, t=now, p=row1["price"], s=row1["symbol"])
        return redirect("/")
    if request.method == "GET":
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    hist = db.execute("SELECT * FROM history WHERE user_id=:d", d=session["user_id"])
    return render_template("history.html", hist=hist)


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

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
    if request.method == "POST":
        """error checking"""
        row ={}
        row = lookup(request.form.get("symb"))
        if not row:
            return apology("Invalid stock symbol", 403)
        return render_template("quoted.html", name=row["name"], value=row["price"], symbol=row["symbol"])

    if request.method == "GET":
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Error checking"""
    if request.method == "POST":
        User = request.form.get("user")
        Pass = request.form.get("pass")
        Pass1 = request.form.get("pass1")
        if not User or not Pass or not Pass1:
            return apology("Invalid Username or Password", 403)
        if Pass != Pass1:
            return apology("Passwords do not match", 403)

        """Checks if username exists"""
        check = {}
        check = db.execute("SELECT username FROM users WHERE username = :username", username = User)
        if not check:
            """hash the password"""
            Pass2 = generate_password_hash(Pass)

            """Inserting into the database"""
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", User, Pass2)
            return redirect("/login")
        else:
            return apology("Username taken", 403)

    if request.method == "GET":
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        uid = session["user_id"]
        counter = request.form.get("count")
        symb = request.form.get("symbol")
        if not symb:
            return apology("Invalid stock symbol", 403)
        if int(counter) < 1:
            return apology("Invalid number", 403)
        value = lookup(symb)
        stock = db.execute("SELECT * FROM stocks WHERE sym=:s AND user_id=:l", s=value["symbol"], l=uid)
        if stock[0]["count"] < int(counter):
            return apology("Insufficient Stocks", 403)
        if not stock:
            return apology("No shares to sell", 403)
        newCount = stock[0]["count"] - int(counter)
        user = db.execute("SELECT * FROM users WHERE id = :k", k=uid)
        newCash = user[0]["cash"] + (int(counter) * value["price"])
        if not newCount:
            db.execute("DELETE FROM stocks WHERE user_id=:k AND sym=:s", k=uid, s=symb)
        else:
            db.execute("UPDATE stocks SET count = :c WHERE user_id=:k AND sym=:s",c=newCount, k=uid, s=symb)
        db.execute("UPDATE users SET cash=:o WHERE id=:k", o=newCash, k=uid)
        share = int(counter)*(-1)
        now = datetime.datetime.now()
        db.execute("INSERT INTO history VALUES (:k, :y, :t, :p, :s)", k=uid, y=share, t=now, p=value["price"], s=value["symbol"])
        return redirect("/")
    if request.method == "GET":
        return render_template("sell.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
