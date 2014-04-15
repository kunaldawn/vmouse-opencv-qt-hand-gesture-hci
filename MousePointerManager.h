//----------------------------------------------------------------------
// VMouse - OpenCV Virtual Mouse (HCI)
// Copyright (C) 2014  Kunal Dawn <kunal.dawn@gmail.com>
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
#ifndef MOUSEPOINTERMANAGER_H
#define MOUSEPOINTERMANAGER_H
#include <QtNetwork/QTcpSocket>
#include <QObject>
#include <iostream>
using namespace std;
class MousePointerManager : public QObject
{
    Q_OBJECT
private:
    QTcpSocket socketMove;
    QTcpSocket socketClick;

public:
    MousePointerManager();
    void mouseEvent(string, int);
    void mouseMove(int, int);
};

#endif // MOUSEPOINTERMANAGER_H
