# TLC-Calculation  applications

We provide three applications to calculate instantaneous TLC_left and TLC_right using equation 15 of the paper:

* Two console applications with exactly the same functionality but one of them is object-oriented.
* A windows application.

As an example, the values of the variables needed to calculate TLC_left and TLC_right are set initially but users can modify them.

Data is divided into four groups to ease working with them:

* Static vehicle data
* Dynamic vehicle data
* Road data
* Time data

The units of measurements used are:

* Length &nbsp;&nbsp;&nbsp; meter(m)
* Time &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; second (s)
* Speed	 &nbsp;&nbsp;&nbsp;&nbsp; meter per second (m/s)
* Rotation &nbsp; radian (rad)

The code of the three application has comments and it is also documented using doxygen (see folders “html” and “latex” in each application folder).
  
## Console application/Console application OOP
 
It firstly shows some relevant information and then shows a menu.

This menu allows showing TLC, showing data and modifying groups of data.

When modifying a group of data, the program shows before the current data. Note that you do not need to type the unit of measurement. After modifying a group of data, TLC is updated.

## Windows application

It firstly shows some relevant information and then shows a window with all the data.

In this window, data is organised into the groups. TLC_left and TLC_right are displayed on the right side.

TLC_left and TLC_right update after:

* Pressing the button labelled “Calculate”.
* Left clicking to move to another item of the window.
* Pressing the Tab key.
* Pressing the buttons "Copy ->" or "Copy all ->".

Pressing one of the three buttons labelled "Copy ->" copies the value on the left to the right.

These are useful if we want to update a previous value to the current value.

Pressing the button labelled "Copy all ->" makes the three copies at a time.
