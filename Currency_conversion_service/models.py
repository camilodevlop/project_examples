from app import db, login_manager
from sqlalchemy.dialects.postgresql import JSON
from werkzeug.security import generate_password_hash, check_password_hash
from flask_login import UserMixin

class Person(UserMixin,db.Model): 
    __tablename__ = 'person'
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(250)) 
    password = db.Column(db.String(250))
    service_counter = db.Column(JSON)
    services = db.Column(JSON)
    
    def set_password(self, password):
        self.password = generate_password_hash(password)

    def check_password(self, password):
        return check_password_hash(self.password, password)

@login_manager.user_loader
def load_user(user_id):
    return Person.query.get(int(user_id))

#---------------------------------------------------------------------------------------------------
