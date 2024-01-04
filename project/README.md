# Task Manager Application

#### Video Demo: [https://youtu.be/akEnWrm1yuQ]
#### Description:
The ToDoList Manager is a web application developed using Flask, designed to help users manage and organize their tasks efficiently. With features like task addition, deletion, and completion tracking, it offers a user-friendly interface for personal task management.

### Features:
- **User Authentication**: Users can register, log in, and log out securely. Passwords are hashed for security.
- **Task Management**: Users can add new tasks with a title, description, and priority level. They can also delete tasks and mark them as completed.
- **Dynamic UI**: The application uses Bootstrap for a responsive and modern interface. It includes a dark mode toggle for user preference.
- **Compliment words**: When tasks are marked as complete, users receive random compliments, enhancing the user's motivation.

### Files:
- `app.py`: This is the file, for our Flask application. It contains route definitions and configurations for the app.
- `init_db.py`: This script helps initialize the database by creating tables and setting up a test environment.
- `test_app.py`: We use this file to run unit tests for our application using Pythons unittest framework.
- `templates/`: Folder containing HTML templates for different pages (index, register, login, etc.).
- `static/`: Contains static files like CSS stylesheets and JavaScript files.
- `config.py`: Configuration settings for different environments, including the test setup.
- `README.md`: This file, providing an overview of the project.

### Design Choices:
- **SQLite Database**: Chosen for its simplicity and ease of integration with Flask. It stores user and task information.
- **Flask-Session for Session Management**: Ensures user sessions are managed securely.
- **Bootstrap and Custom CSS**: For a responsive design that works on both desktop and mobile devices.
- **JavaScript for Interactive Features**: Like the dark mode toggle and fade-out effects for compliments.

### Setup and Running:
1. Install dependencies: `pip install -r requirements.txt`
2. Initialize the database: `python init_db.py`
3. Run the Flask app: `flask run`
4. Run the basic test (if you would like) : `python test_app.py`

The ToDoList Manager is the culmination of skills I've developed in web programming, offering a practical solution to everyday task management.

---

This project was developed as part of the final project submission for CS50x. It represents my understanding and application of web development concepts using Flask, HTML, CSS, and JavaScript.



