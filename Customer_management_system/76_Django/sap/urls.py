"""
URL configuration for sap project.

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/4.2/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path
from webapp.views import welcome, residences
from persons.views import newPerson, personDetail, editPerson, delPerson, newResidence, residenceDetail, editResidence, delResidence

urlpatterns = [
    path('admin/', admin.site.urls),
    path('', welcome, name = 'index'),
    path('residences', residences, name = 'index_residences'),

    # Persons
    path('person_details/<int:id>', personDetail),
    path('new_person', newPerson),
    path('edit_person/<int:id>', editPerson),
    path('delete_person/<int:id>', delPerson),

    # Residences
    path('residence_details/<int:id>', residenceDetail),
    path('new_residence', newResidence),
    path('edit_residence/<int:id>', editResidence),
    path('delete_residence/<int:id>', delResidence)
]

#-------------------------------------------------------------------
