def clock_needle():
    time=input('What time is it?:')
    hour=int(time[0:2])
    minute =int(time[3:5])
    hour_angle=hour*360/12
    minute_angle=minute*360/60
    return(hour_angle-minute_angle)
