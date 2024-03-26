def have_requests(count, day):
    requests_per_day = 200 if day == 'Saturday' or day == 'Sunday' else 100
    #requests_per_day = 4 if day == 'Saturday' or day == 'Sunday' else 3
    
    if int(requests_per_day) - int(count) > 0:
        return True
    return False

#---------------------------------------------------------------------------------------------------
