ArduinoScreenControllerListener
===============================

- Listener that evaluates state:
```
#!/bin/bash

if [ ! -z "$1" ] && [ $1 = "toggle" ]; then

  echo `date` "Toggling screen."
  echo `date` "Toggling screen." >> ~/screen-control.log
  
  STATE=`/opt/vc/bin/tvservice -s`
  
  if [[ $STATE == *"TV is off"* ]]; then

    echo `date` "Screen is off, turning on."
    echo `date` "Screen is off, turning on." >> ~/screen-control.log
    /opt/vc/bin/tvservice -p && fbset -depth 16 && fbset -depth 32 && xrefresh -display :0.0
  else

    echo `date` "Screen is on, turning off."
    echo `date` "Screen is on, turning off." >> ~/screen-control.log  
    /opt/vc/bin/tvservice -o
  fi

elif [ ! -z "$1" ] && [ $1 = "on" ]; then

  echo `date` "Turning screen on."
  echo `date` "Turning screen on." >> ~/screen-control.log
  /opt/vc/bin/tvservice -p && fbset -depth 16 && fbset -depth 32 && xrefresh -display :0.0

elif [ ! -z "$1" ] && [ $1 = "off" ]; then

  echo `date` "Turning screen off."
  echo `date` "Turning screen off." >> ~/screen-control.log
  /opt/vc/bin/tvservice -o

else

  echo
  /opt/vc/bin/tvservice -s
  echo
  echo usage:
  echo $0 on
  echo $0 off
  echo $0 toggle

fi
```


- Listener with no state:
```
#!/bin/bash


if [ ! -z "$1" ] && [ $1 = "on" ]; then

  echo `date` "Turning screen on."
  echo `date` "Turning screen on." >> ~/screen-control.log
  /opt/vc/bin/tvservice -p && fbset -depth 16 && fbset -depth 32 && xrefresh -display :0.0

elif [ ! -z "$1" ] && [ $1 = "off" ]; then

  echo `date` "Turning screen off."
  echo `date` "Turning screen off." >> ~/screen-control.log
  /opt/vc/bin/tvservice -o


elif [ ! -z "$1" ] && [ $1 = "status" ]; then

  /opt/vc/bin/tvservice -s

else

  echo usage:
  echo $0 on
  echo $0 off
  echo $0 status
  exit

fi
```