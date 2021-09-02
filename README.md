# Electric_Water_Heater
![CaptureSwiftACT](https://user-images.githubusercontent.com/75904835/131776174-82a99d27-7e57-4bbd-ad39-17b7fbbf912a.PNG) **Electric Water Heater:** It was Swift Act embedded software internship program for 2020

### Specification-ON/OFF Behavior

1. If power connected to the heater, the electric water heater is in OFF state
2. If "ON/OFF" button is released and the Electric water heater is in OFF state, the electric water heater goes to ON state
3. If "ON/OFF" button is released and the Electric water heater is in ON state, the electric water heater goes to OFF state
4. In the OFF state, all display should be turned off
________________________________________________________________________________________________________________________________
### Specification- Temperature Setting 

1. The "UP" or "down" buttons are used to change the required water temperature (set temperature)
2. The first "UP" or "Down" button press, enters the temperature setting mode
3. After entering temperature setting mode, a single "UP" button press increase the set temperature by 5 degrees
4. After increasing temperature setting mode, a single "Down" button press decrease the set temperature by 5 degrees
5. The minimum possible set temperature is 35 degree
6. The maximum possible set temperature is 75 degree
7. The "External EEPROM" should save the set temperature once set
8. If the Electric water heater is turned OFF then ON , the stored set temperature should be retrieved from the "External EEPROM"
9. The initial set temperature is 60 degree
__________________________________________________________________________________________________________________________________
### Specification- Heating/Cooling Element
1. The "Heating Element" should be turned ON , if the current water temperature is less than the set temperature by 5 degree 
2. The "Cooling Element" should be turned OFF , if the current water temperature is less than the set temperature by 5 degree 
3. The "Heating Element" should be turned OFF , if the current water temperature is greater than the set temperature by 5 degree 
4. The "Cooling Element" should be turned ON , if the current water temperature is greater than the set temperature by 5 degree 
____________________________________________________________________________________________________________________________________
### Specification- Seven Segments
1. 2 seven segments by default shows the current water temperature or the set temperature
2. By default , the 2 seven segments display are show the current water temperature
3. If the electric water heater is in the temperature setting mode , the 2 seven segments displays should blink every 1 second and show the set temperature 
4. In the temperature setting mode , every change in the set temperature should be reflected on the 2 seven segment displays
5. The 2 seven segments display should exit the temperature setting mode, if "UP" and "Down" buttons are not pressed for 5 seconds
______________________________________________________________________________________________________________________________________ 
### Specification- Heating/Cooling Elements LEDs
1. If the Heating Element is ON, "The Heating Element LED" should be ON
2. If the Cooling Element is ON, "The Cooling Element LED" should be ON
3. If the Heating Element is OFF, "The Heating Element LED" should be OFF
4. If the Cooling Element is OFF, "The Heating Element LED" should be OFF
_______________________________________________________________________________________________________________________________________

![Capture](https://user-images.githubusercontent.com/75904835/131776377-ea25868a-4bd9-4e66-808a-ea045c520960.PNG)

