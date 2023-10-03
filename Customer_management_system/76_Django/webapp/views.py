from django.shortcuts import render
from django.http import HttpResponse
from persons.models import Person, Residence

# Create your views here.

def welcome(request):
    # return HttpResponse('Hello World from Django')
    # messages = {'msg1' : 'Message Value 1',
    #            'msg2' : 'Message Value 2'}
    # return render(request, 'welcome.html', messages)
    no_persons = Person.objects.count()
    #persons = Person.objects.all()
    persons = Person.objects.order_by('id')
    return render(request, 'welcome.html', {'no_persons' : no_persons, 'persons' : persons})

def residences(request):
    residences = Residence.objects.all()
    return render(request, 'residences.html', {'residences' : residences})

'''
def farewell(request):
    return HttpResponse('Bye bye from Django')

def contact(request):
    return HttpResponse('Contact: Camilo A. Castillo B.\nemail: cacastilloben@unal.edu.co')
'''

#-------------------------------------------------------------------
