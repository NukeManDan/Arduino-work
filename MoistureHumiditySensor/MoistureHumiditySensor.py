import serial # import Serial Library
import numpy  # Import numpy
import matplotlib.pyplot as plt #import matplotlib library
import datetime

from drawnow import *

hum=[]
temp= []
heatin= []
moist= []

arduinoData = serial.Serial('/dev/ttyACM0', 115200) #Creating our serial object named arduinoData
plt.ion() #Tell matplotlib you want interactive mode to plot live data
cnt=0

def makeFig(): #Create a function that makes our desired plot
#    plt.ylim(80,90)                                 #Set y min and max values
    plt.title('My Live Streaming Sensor Data')      #Plot the title
    plt.grid(True)                                  #Turn the grid on
    plt.ylabel('Temp C')                            #Set ylabels
    plt.plot(temp, 'ro-', label='Degrees C')       #plot the temperature
    plt.legend(loc='upper left')                    #plot the legend
    plt2=plt.twinx()                                #Create a second y axis
#    plt.ylim(93450,93525)                           #Set limits of second y axis- adjust to readings you are getting
    plt2.plot(hum, 'b^-', label='Relative Humidity (%)') #plot pressure data
    plt2.set_ylabel('Relative Humidity (%)')                    #label second y axis
#    plt2.ticklabel_format(useOffset=False)           #Force matplotlib to NOT autoscale y axis
    plt2.legend(loc='upper right')                  #plot the legend
    

infile = open('data.csv', 'a')

try:
    while True: # While loop that loops forever
        while (arduinoData.inWaiting()==0): #Wait here until there is data
            pass #do nothing
        arduinoString = arduinoData.readline() #read the line of text from the serial port
        dataArray = arduinoString.split(',')   #Split it into an array called dataArray
        h   = float( dataArray[0])           
        t   = float( dataArray[1])  
        hic = float( dataArray[2])  
        m   = float( dataArray[3])

        hum.append(h)
        temp.append(t)
        heatin.append(hic)
        moist.append(m)

        row = datetime.datetime.now().strftime("%m-%d-%y,%H:%M:%S") + ',' + str(h) + ',' + str(t) + ',' + str(hic) + ',' + str(m) +'\n'
        infile.write(row)
        infile.flush()

        drawnow(makeFig)
        plt.pause(.001)                     #Pause Briefly. Important to keep drawnow from crashing
        cnt=cnt+1
        if(cnt>50):                            #If you have 50 or more points, delete the first one from the array
            hum.pop(0)                         #This allows us to just see the last 50 data points
            temp.pop(0)
            heatin.pop(0)
            moist.pop(0)

except KeyboardInterrupt:
    infile.close()
