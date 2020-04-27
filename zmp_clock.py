#this function ask the hour to the users, supposing that the user enters the hour in a HH:MM format
def clock_needle():
    time=input('What time is it?:')
    #if the user use a 24hours based notation, the hour is converted to the 12h based notation
    hour=int(time[0:2])%12
    minute =int(time[3:5])
    hour_angle=hour*360/12
    minute_angle=minute*360/60
    #the returned angle is a postive angle and is the smallest one 
    return(max(hour_angle,minute_angle)-min(hour_angle,minute_angle))%180
