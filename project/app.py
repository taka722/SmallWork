import sqlite3
from flask import Flask, g, render_template, request, redirect, url_for, session, flash
from flask_session import Session
from werkzeug.security import generate_password_hash, check_password_hash
from flask import g
import random


# Create a new Flask instance　initializing
app = Flask(__name__)



# Additional configuration for session
# Configure Flask-Session to use Redis for session storage

# app.config["SESSION_PERMANENT"] = False
# app.config["SESSION_TYPE"] = "filesystem"

# Configure the secret key for the session
app.config['SECRET_KEY'] = 'your_secret_key'  # Replace with a real secret key

# Choose one session type
app.config['SESSION_TYPE'] = 'filesystem'  # Or 'redis' if using Redis

# Configure the path to your database
app.config['DATABASE'] = 'taskmanager.db'

Session(app)



def get_db():
    """
    Opens a new database connection if there is none yet for the
    current application context.
    """
    if 'db' not in g:
        g.db = sqlite3.connect(app.config['DATABASE'])
        g.db.row_factory = sqlite3.Row
    return g.db

@app.teardown_appcontext
def close_db(error):
    """
    Closes the database again at the end of the request.
    """
    if 'db' in g:
        g.db.close()

# Route for the main index page
@app.route('/')
def index():
    compliment = request.args.get('compliment')
    if 'user_id' in session:
        db = get_db()
        tasks = db.execute('SELECT * FROM tasks WHERE user_id = ?', (session['user_id'],)).fetchall()
        # print(tasks) # for debugging
        return render_template('index.html', tasks=tasks, logged_in=True, compliment=compliment)
    return render_template('index.html', logged_in=False, compliment=None)


# Route for user registration
@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        hash = generate_password_hash(password)

        db = get_db()
        try:
            db.execute('INSERT INTO users (username, hash) VALUES (?, ?)', (username, hash))
            db.commit()
            flash('Registered successfully')
            # print(f"Registered user: {username}")  # for Debugging
        except sqlite3.IntegrityError:
            # print("Username already taken")  # for Debugging
            return "Username already taken!"

        return redirect(url_for('login'))

    return render_template('register.html')


# Route for user login
@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        # print("Attempting login for:", username)  # Debugging

        db = get_db()
        user = db.execute('SELECT * FROM users WHERE username = ?', (username,)).fetchone()

        if user:
            # print("User found in database")  # Debugging
            password_check = check_password_hash(user['hash'], password)
            # print("Password check:", password_check)  # Debugging

            if password_check:
                session['user_id'] = user['id']
                flash('Logged in successfully')
                return redirect(url_for('index'))
            else:
                flash('Invalid username or password!', 'error')
                # print("Invalid password")  # Debugging
        else:
            # print("User not found")  # Debugging
            flash('Invalid username or password!', 'error')
        return "Invalid username or password!"

    return render_template('login.html')



# Route for user logout
@app.route('/logout')
def logout():
    session.pop('user_id', None)
    return redirect(url_for('index'))



# Route to add a new task
@app.route('/add_task', methods=['POST'])
def add_task():
    if 'user_id' in session:
        title = request.form['title']
        description = request.form['description']
        # task priority level would be low as default
        priority = request.form.get('priority', 'Low')
        db = get_db()
        db.execute('INSERT INTO tasks (title, description, user_id, priority) VALUES (?, ?, ?, ?)', (title, description, session['user_id'], priority))
        db.commit()
        flash('Task added successfully')
        return redirect(url_for('index'))
    return redirect(url_for('login'))



# Route to delete a task
@app.route('/delete_task/<int:task_id>', methods=['POST'])
def delete_task(task_id):
    if 'user_id' in session:
        db = get_db()
        db.execute('DELETE FROM tasks WHERE id = ? AND user_id = ?', (task_id, session['user_id']))
        db.commit()
        return redirect(url_for('index'))
    return redirect(url_for('login'))



# Route to mark a task as complete
@app.route('/complete_task/<int:task_id>', methods=['POST'])
def complete_task(task_id):
    if 'user_id' in session:
        db = get_db()
        db.execute('UPDATE tasks SET completed = TRUE WHERE id = ? AND user_id = ?', (task_id, session['user_id']))
        db.commit()
        # compliments sentence
        compliments = ["Great job!", "Well done!", "Keep up the good work!"]
        compliment = random.choice(compliments)
        return redirect(url_for('index', compliment=compliment))
    return redirect(url_for('login'))



if __name__ == '__main__':
    app.run(debug=True)
