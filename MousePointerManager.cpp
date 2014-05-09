//----------------------------------------------------------------------
// VMouse - OpenCV Virtual Mouse (HCI)
// Copyright (C) 2014  Kunal Dawn <kunal.dawn@gmail.com>
// Copyright (C) 2014  Medha Devaraj <medha.devaraj@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------
#include "MousePointerManager.h"
#include <iostream>
#include <string>

using namespace std ;
MousePointerManager::MousePointerManager()
{
    socketMove.connectToHost("127.0.0.1",8888);
    socketClick.connectToHost("127.0.0.1",8889);
}

void MousePointerManager::mouseEvent(string event,int button)
{
    QString string;
    string.append(QString::fromStdString(event));
    string.append(",");
    string.append(QString::number(button));
    socketClick.write(string.toStdString().c_str());
}

void MousePointerManager::mouseMove(int x, int y)
{
    QString string;
    string.append(QString::number(x));
    string.append(",");
    string.append(QString::number(y));
    socketMove.write(string.toStdString().c_str());
}
