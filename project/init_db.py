import sqlite3
from werkzeug.security import generate_password_hash

def init_db(testing=False):
    # Choose the database file based on whether it's for testing or not
    db_name = 'taskmanager_test.db' if testing else 'taskmanager.db'
    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()

    # Create the 'users' table
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS users (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        username TEXT UNIQUE NOT NULL,
        hash TEXT NOT NULL
    )
    ''')

    # Create the 'tasks' table
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS tasks (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        title TEXT NOT NULL,
        description TEXT,
        completed BOOLEAN NOT NULL DEFAULT 0,
        user_id INTEGER,
        priority TEXT DEFAULT 'Low',
        FOREIGN KEY (user_id) REFERENCES users(id)
    )
    ''')

    # Optional: Insert a test user for testing
    if testing:
        # Clear existing data
        cursor.execute('DELETE FROM users')
        cursor.execute('DELETE FROM tasks')

        test_username = 'existing_user'
        test_password = generate_password_hash('existing_password')
        cursor.execute('INSERT OR IGNORE INTO users (username, hash) VALUES (?, ?)', (test_username, test_password))

    conn.commit()
    conn.close()

if __name__ == "__main__":
    init_db()
