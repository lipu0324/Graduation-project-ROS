from flask import Flask, render_template

app = Flask(__name__)

@app.route('/')
def hello():
    return 'Welcome to My Watchlist!'

@app.route('/home')
def home():
    return render_template('机器人主页.html')