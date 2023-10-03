from django.db import models

# Create your models here.
class Residence(models.Model):
    street = models.CharField(max_length = 255)
    no_street = models.IntegerField()
    country = models.CharField(max_length = 255)

    def __str__(self) -> str:
        return f'Residence { self.id }: {self.street} {self.no_street} {self.country}'

class Person(models.Model):
    name = models.CharField(max_length = 255)
    surname = models.CharField(max_length = 255)
    email = models.CharField(max_length = 255)
    time_stamps = models.DateField()
    residence = models.ForeignKey(Residence, on_delete = models.SET_NULL, null = True)


    def __str__(self) -> str:
        return f'Person { self.id }: {self.name} {self.surname} {self.email} {self.time_stamps}'

#-------------------------------------------------------------------
