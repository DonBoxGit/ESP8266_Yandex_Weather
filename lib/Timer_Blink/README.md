##### Timer_Blink library organizes the time delay and switch state by time some action.

###### For use it you need to create the Timer object with parameter to point time as milliseconds. <br> 
###### For example:
```c++
    Timer displayShowTimer(2000);
```
###### Now, to check the status of object, use the ```ready()``` method, which returns true every 2 seconds. <br><br>For example:
```c++
    if (displayShowTimer.ready()) {
      Do somethink ...
    }
```
###### The `resetCounter()` method is resseting the milliseconds counter. The ```setPeriod(period)``` method is sestting the period manually. <br><br>For example:
```c++
    displayShowTimer.resetCounter();
    displayShowTimer.setPeriod(550);
```
###### The Blink class is creating object which to switch the state from true to false and back. And to check the status object, use ```getStatus()``` method, which returns boolean value. <br><br>For example:
```c++
    Blink blinkDots(500);
    ...
    if (blinkDots.getStatus()) {
      Do somethink ...
    }
```
###### Method `resetStatus()` to setting `false` in to flag variable. Method `toggle()` to toggling status manually accordingly. <br><br>For example:
```c++
    blinkDots.resetStatus();
    blinkDots.toggle();
```
###### and etc.
