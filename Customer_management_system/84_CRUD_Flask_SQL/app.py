from flask import Flask, render_template, request, url_for
from database import db
from flask_migrate import Migrate
from models import Person
from forms import PersonForm
from werkzeug.utils import redirect


app = Flask(__name__)


#-------------------------------------------------------------------

# Database setup.

USER_DB = 'postgres'
PASS_DB = 'admin'
URL_DB = 'localhost'
NAME_DB = 'sap_flask_db'
FULL_URL_DB = f'postgresql://{USER_DB}:{PASS_DB}@{URL_DB}/{NAME_DB}'

app.config['SQLALCHEMY_DATABASE_URI'] = FULL_URL_DB
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False

# DB object initialization of sqlalchemy.
# db = SQLAlchemy(app)
db.init_app(app)

# flask-migrate: maps model classes to database tables.
migrate = Migrate()
migrate.init_app(app, db)

# flask-wtf.
app.config['SECRET_KEY'] = 'secret_key'

#-------------------------------------------------------------------

@app.route('/')
@app.route('/index')
@app.route('/index.html')
def start():
    # List of persons.
    #persons = Person.query.all()
    persons = Person.query.order_by('id')
    total_persons = Person.query.count()
    app.logger.debug(f'List of persons: {persons}')
    app.logger.debug(f'Total persons: {total_persons}')
    return render_template('index.html', persons = persons, total_persons = total_persons)

#-------------------------------------------------------------------

# View details of each person.

@app.route('/view/<int:id>')
def view_details(id):
    # person = Person.query.get()
    person = Person.query.get_or_404(id)
    app.logger.debug(f'View person: {person}')
    return render_template('detail.html', person = person)

#-------------------------------------------------------------------

# Add persons to the database.

@app.route('/add_person', methods = ['GET', 'POST'])
def add_person():
    person = Person()
    personForm = PersonForm(obj = person)

    if request.method == 'POST':
        if personForm.validate_on_submit():
            personForm.populate_obj(person)
            app.logger.debug(f'Person to be inserted: {person}')
            # Inserting the new person.
            db.session.add(person)
            db.session.commit()
            return redirect(url_for('start'))

    return render_template('add.html', form = personForm)

#-------------------------------------------------------------------

# Edit persons of the database.

@app.route('/edit/<int:id>', methods = ['GET', 'POST'])
def edit_person(id):
    person = Person.query.get_or_404(id)
    personForm = PersonForm(obj = person)

    if request.method == 'POST':
        if personForm.validate_on_submit():
            personForm.populate_obj(person)
            app.logger.debug(f'Person to be updated: {person}')
            # Updating the information.
            db.session.commit()
            return redirect(url_for('start'))

    return render_template('edit.html', form = personForm)

#-------------------------------------------------------------------

# Remove persons.

@app.route('/remove/<int:id>')
def remove(id):
    person = Person.query.get_or_404(id)
    app.logger.debug(f'Person to be removed: {person}')
    db.session.delete(person)
    db.session.commit()
    return redirect(url_for('start'))

#-------------------------------------------------------------------
