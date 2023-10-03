from django.forms import ModelForm, EmailInput, TextInput
from persons.models import Person, Residence

class PersonForm(ModelForm):
    class Meta:
        model = Person
        fields = '__all__' # Using all fields of the Person class.
        widgets = {
            'email' : EmailInput(attrs = { 'type' : 'email'})
        }

class ResidenceForm(ModelForm):
    class Meta:
        model = Residence
        fields = '__all__'
        widgets = {
            'no_street' : TextInput(attrs = {'type' : 'number'})
        }

#-------------------------------------------------------------------
