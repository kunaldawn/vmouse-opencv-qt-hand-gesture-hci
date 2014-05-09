OpenCV Virtual Mouse (HCI) v1.0
===============================================================
* A prototype virtual mouse interface using opencv.
* Control mouse pointer via hand movement.
* QT Gui is used for Configuartion and Real time feedback.
* 4 types of operation is supported {Left Click, Right Click, Click and Hold, Double Click}
* Finger Magnet algorithm is implemented to reduce frame flicker errors.
* 2 level of motion filtering is used for mouse pointer; Kalman Filter, Avg Filter
* Small portion of screen region can be selected manually to act as a touch pad, this allows users to move mouse pointer to the edge of the screen without actually moving hand too much.
* Current version is Stable Release. Gives more than 30 fps processing performence.
* Persistence Configuarion file is supported. See demo "settings.conf" file.

### TODO : 
2. How to wiki will be created soon. (will include build and configuration instructions)
2. Interface API will be added soon.
3. User Documentation will be provided soon.

### LICENSE : GPLv3, 29 June 2007 
VMouse - OpenCV Virtual Mouse (HCI)  
Copyright (C) 2014  Kunal Dawn <kunal.dawn@gmail.com>  
Copyright (C) 2014  Medha Devaraj <medha.devaraj@gmail.com>  

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
