from flask import render_template, request, redirect, url_for, flash
from flask_login import login_user, logout_user, current_user, login_required
from app import app, db
from models import Person
import json
from datetime import datetime
from request_currency_conversion import request_currency_conversion
from convert_current import convert_current
from update_user_services import update_user_services
from handle_post_request import handle_post_request
from handle_get_request import handle_get_request
from get_supported_currencies_and_crypto import get_supported_currencies_and_crypto

#---------------------------------------------------------------------------------------------------

@app.route('/')
@app.route('/index')
@app.route('/index.html')
def start():
    persons = Person.query.all()
    num_persons = Person.query.count()
    return render_template('index.html', persons=persons, num_persons=num_persons)

#---------------------------------------------------------------------------------------------------

@app.route('/signup', methods=['GET', 'POST'])
def signup():
    if request.method == 'POST':
        name = request.form.get('username')
        password = request.form.get('password')

        # Initialize the user
        user = Person(name=name)
        user.set_password(password)
        now = datetime.now()
        user.service_counter = json.dumps({'counter': 0, 'date': now.strftime("%d-%m-%Y"), 'time': now.strftime("%H:%M:%S")})
        user.services = json.dumps({now.strftime("%d-%m-%Y--")+now.strftime("%H:%M:%S"): {'date': now.strftime("%d-%m-%Y"), 'time': now.strftime("%H:%M:%S"), 'day': now.strftime("%A"), 'input': {'from': '', 'to': '', 'amount': 0}, 'output': {'result': 0}}})

        db.session.add(user)
        db.session.commit()
        flash('User registered successfully.')
        return redirect(url_for('login'))
    return render_template('signup.html')

#---------------------------------------------------------------------------------------------------

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = Person.query.filter_by(name=username).first()
        if user and user.check_password(password):
            login_user(user)
            return render_template('login.html', name=user.name, result=0)
        else:
            return render_template('invalid_user_pass.html')
    return render_template('index.html')

#---------------------------------------------------------------------------------------------------

@app.route('/logout')
def logout():
    logout_user()
    return redirect(url_for('login'))

#---------------------------------------------------------------------------------------------------

@app.route('/convert', methods=['GET', 'POST'])
def convert():
    if not current_user.is_authenticated:
        return redirect(url_for('login'))

    if request.method == 'POST':
        return handle_post_request()
    else:
        return handle_get_request()

#---------------------------------------------------------------------------------------------------

@app.route('/currency_list')
def currency_list():
    if not current_user.is_authenticated:
        return redirect(url_for('login'))

    currencies_and_cryptos_dict = get_supported_currencies_and_crypto()
    return render_template('currency_list.html', currencies_and_cryptos = currencies_and_cryptos_dict)

#---------------------------------------------------------------------------------------------------
