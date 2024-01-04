import unittest
import uuid
from app import app  # Import your Flask app
from init_db import init_db  # Replace with the actual import of your db setup
# test congig file
from config import TestConfig



class BasicTests(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        # Set the app to use the test configuration
        app.config.from_object(TestConfig)
        print("Test database pa:", app.config['DATABASE'])  # Print here after setting config
        # Initialize the test database
        init_db(testing=True)

    def setUp(self):
        # Set up the test client
        self.app = app.test_client()
        self.app.testing = True

    def test_index(self):
        response = self.app.get('/')
        self.assertEqual(response.status_code, 200)
        self.assertIn(b'Task Manager', response.data)

    def test_user_registration(self):
        unique_username = f"user_{uuid.uuid4()}"  # Generate a unique username
        response = self.app.post('/register', data=dict(
            username=unique_username,
            password="testpassword"
        ), follow_redirects=True)
        self.assertIn(b'Registered successfully', response.data)

    def login_user(self):
        valid_username = "existing_user"
        valid_password = "existing_password"
        # change here return
        response = self.app.post('/login', data=dict(
            username=valid_username,
            password=valid_password
        ), follow_redirects=True)
        print(response.data)  # Add this to debug
        return response

    def test_add_task(self):
        login_response = self.login_user()
        if b'Logged in successfully' not in login_response.data:
            self.fail("Login failed, cannot test task addition")

        response = self.app.post('/add_task', data=dict(
            title="Test Task",
            description="Test Description",
            priority="Low"
        ), follow_redirects=True)
        self.assertIn(b'Task added successfully', response.data)

    # Additional test cases, if i have

if __name__ == '__main__':
    unittest.main()
