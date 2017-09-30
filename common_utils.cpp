/*
Basic MODBUS communication tool
Copyright (C) 2017 Martin Zúber

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
*/

#include "common_utils.h"

quint8 lowQb(quint8 byte)
{
    quint8 cipher = byte & 0x0F;
    return (quint8) cipher < 0xA ? cipher + '0' : cipher + 'A' - 0xA;
}

quint8 highQb(quint8 byte)
{
    quint8 cipher = (byte & 0xF0) >> 4;
    return (quint8) cipher < 0xA ? cipher + '0' : cipher + 'A' - 0xA;
}
