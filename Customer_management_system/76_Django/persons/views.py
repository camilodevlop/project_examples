from django.shortcuts import render, get_object_or_404, redirect
from django.forms import modelform_factory
from persons.models import Person, Residence
from persons.forms import PersonForm, ResidenceForm

# Create your views here.

#-------------------------------------------------------------------

# Persons.

def personDetail(request, id):
    # person = Person.objects.get(pk = id)
    person = get_object_or_404(Person, pk = id)
    return render(request, 'persons/detail.html', {'person' : person})

# PersonForm = modelform_factory(Person, exclude = [])

def newPerson(request):
    if request.method == 'POST':
        personForm = PersonForm(request.POST)
        if personForm.is_valid():
            personForm.save()
            return redirect('index')

    else:
        personForm = PersonForm()

    return render(request, 'persons/new.html', {'personForm' : personForm})

def editPerson(request, id):
    person = get_object_or_404(Person, pk = id)

    if request.method == 'POST':
        personForm = PersonForm(request.POST, instance = person)
        if personForm.is_valid():
            personForm.save()
            return redirect('index')

    else:
        personForm = PersonForm(instance = person)

    return render(request, 'persons/edit.html', {'personForm' : personForm})

def delPerson(request, id):
    person = get_object_or_404(Person, pk = id)
    
    if person:
        person.delete()

    return redirect('index')

#-------------------------------------------------------------------

# Residences.

def residenceDetail(request, id):
    residence = get_object_or_404(Residence, pk = id)
    return render(request, 'residences/detail_residence.html', {'residence' : residence})

def newResidence(request):
    if request.method == 'POST':
        residenceForm = ResidenceForm(request.POST)
        if residenceForm.is_valid():
            residenceForm.save()
            return redirect('index_residences')

    else:
        residenceForm = ResidenceForm()

    return render(request, 'residences/new_residence.html', {'residenceForm' : residenceForm})

def editResidence(request, id):
    residence = get_object_or_404(Residence, pk = id)

    if request.method == 'POST':
        residenceForm = ResidenceForm(request.POST, instance = residence)
        if residenceForm.is_valid():
            residenceForm.save()
            return redirect('index_residences')

    else:
        residenceForm = ResidenceForm(instance = residence)

    return render(request, 'residences/edit_residence.html', {'residenceForm' : residenceForm})

def delResidence(request, id):
    residence = get_object_or_404(Residence, pk = id)
    
    if residence:
        residence.delete()

    return redirect('index_residences')

#-------------------------------------------------------------------
