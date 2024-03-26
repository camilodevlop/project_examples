from flask import render_template
from flask_login import current_user

def handle_get_request():
    return render_template('login.html', name=current_user.name)

#---------------------------------------------------------------------------------------------------
