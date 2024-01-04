import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# set the secret key
app.secret_key = 'my_very_secret_key_here'


# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        try:
            # TODO: Add the user's entry into the database
            # Get the user's input from the form
            name = request.form.get("name")
            month = int(request.form.get("month"))
            day = int(request.form.get("day"))

            # Check the month and day
            if not (1 <= month <= 12):
                flash("Invalid month. Please enter a number between 1 and 12.")
                return redirect("/")
            if not (1 <= day <= 31):
                flash("Invalid day. Please enter a number between 1 and 31.")
                return redirect("/")

            # Insert the new birthday into the database
            db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)
            flash("Birthday added!")
        except Exception as e:
            flash("An error occurred while adding the birthday.")
            print(e)  # For debugging

    # TODO: Display the entries in the database on index.html
    birthdays = db.execute("SELECT * FROM birthdays")
    # Print the birthdays for debugging
    print("Birthdays from the database:", birthdays)
    return render_template("index.html", birthdays=birthdays)


# add the feature of deleting the birthday
@app.route("/delete/<int:birthday_id>", methods=["POST"])
def delete(birthday_id):
    #delete the birthday entry from the database
    db.execute("DELETE FROM birthdays WHERE id = ?", birthday_id)
    flash("Birthday deleted!")
    return redirect("/")

