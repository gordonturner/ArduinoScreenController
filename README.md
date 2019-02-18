Arduino Screen Controller
=========================

- Listener that evaluates state:

```
#!/bin/bash

echo `date` "Called with $1" >> ~/screen-control.log

STATE=`/opt/vc/bin/tvservice -s`

if [ ! -z "$1" ] && [ $1 = "toggle" ]; then

  echo `date` "Toggling screen."
  echo `date` "Toggling screen." >> ~/screen-control.log
  
  if [[ $STATE == *"TV is off"* ]]; then

    echo `date` "Screen is off, turning on."
    echo `date` "Screen is off, turning on." >> ~/screen-control.log
    /opt/vc/bin/tvservice -p && fbset -depth 16 && fbset -depth 32 && xrefresh -display :0.0
  else

    echo `date` "Screen is on, turning off."
    echo `date` "Screen is on, turning off." >> ~/screen-control.log  
    /opt/vc/bin/tvservice -o
  fi
    
  # BUG: Not sure why, but if screen is on, and a toggle is triggered, context menu appears.
  # The Escape key is the windows left key and will hide the context menu.
  export DISPLAY=:0.0
  xdotool key Escape

elif [ ! -z "$1" ] && [ $1 = "on" ]; then

  if [[ $STATE == *"TV is off"* ]]; then

    echo `date` "Screen is off, turning on."
    echo `date` "Screen is off, turning on." >> ~/screen-control.log
    /opt/vc/bin/tvservice -p && fbset -depth 16 && fbset -depth 32 && xrefresh -display :0.0
  else

    echo `date` "Screen is on, doing nothing."
    echo `date` "Screen is on, doing nothing." >> ~/screen-control.log
  fi
    
  # BUG: Not sure why, but if screen is on, and a toggle is triggered, context menu appears.
  # The Escape key is the windows left key and will hide the context menu.
  export DISPLAY=:0.0
  xdotool key Escape

elif [ ! -z "$1" ] && [ $1 = "off" ]; then

  if [[ $STATE == *"TV is off"* ]]; then

    echo `date` "Screen is off, doing nothing."
    echo `date` "Screen is off, doing nothing." >> ~/screen-control.log
  else

    echo `date` "Screen is on, turning off."
    echo `date` "Screen is on, turning off." >> ~/screen-control.log  
    /opt/vc/bin/tvservice -o
  fi
    
  # BUG: Not sure why, but if screen is on, and a toggle is triggered, context menu appears.
  # The Escape key is the windows left key and will hide the context menu.
  export DISPLAY=:0.0
  xdotool key Escape

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


Hot Keybindings
---------------

- Toggle, on and off keybindings:

```
  <!-- BEGIN Adding keybindings -->

  <keybind key="W-0">
    <action name="Execute">
      <command>~/screen-control.sh off</command>
    </action>
  </keybind>

  <keybind key="W-1">
    <action name="Execute">
      <command>~/screen-control.sh on</command>
    </action>
  </keybind>

  <keybind key="W-3">
    <action name="Execute">
      <command>~/screen-control.sh toggle</command>
    </action>
  </keybind>

  <!-- END Adding keybindings -->
```

- Original, single keybindings for toggle:

```
  <!-- BEGIN Adding keybindings -->

  <keybind key="W-0">
    <action name="Execute">
      <command>~/screen-control.sh toggle</command>
    </action>
  </keybind>

  <!-- END Adding keybindings -->
```