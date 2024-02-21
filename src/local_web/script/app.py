from flask import Flask, render_template
from flask_login import LoginManager

app = Flask(__name__)
# login_manager = LoginManager()
# login_manager.init_app(app)
@app.route('/')
def hello():
    return 'Welcome to My Watchlist!'

@app.route('/home')
def home():
    return render_template('机器人主页.html')

@app.route('/login')
def login():
    return render_template('登陆页.html')