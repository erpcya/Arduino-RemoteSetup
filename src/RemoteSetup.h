/*************************************************************************************
 * Copyright (C) 2012-2018 E.R.P. Consultores y Asociados, C.A.                      *
 * Contributor(s): Yamel Senih ysenih@erpya.com                                      *
 * This program is free software: you can redistribute it and/or modify              *
 * it under the terms of the GNU General Public License as published by              *
 * the Free Software Foundation, either version 3 of the License, or                 *
 * (at your option) any later version.                                               *
 * This program is distributed in the hope that it will be useful,                   *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of                    *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                     *
 * GNU General Public License for more details.                                      *
 * You should have received a copy of the GNU General Public License                 *
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.            *
 ************************************************************************************/
#ifndef RemoteSetup_h
#define RemoteSetup_h

#include "Arduino.h"
#include "CommandUtil.h"
/**
 * This class if used for handle all remote setup
 */
static const uint8_t BLUETOOTH_INTERFACE =  1; // Setup from bluetooth
static const uint8_t WIFI_INTERFACE =		2; // Setup from Wifi

class RemoteSetup {
    public:
        RemoteSetup(uint8_t interface);
        boolean isSetupDone();
        boolean runRemoteSetup();
        String getAttribute(String key);
        boolean sendAttribute(String key, String value);
        boolean saveSetup();
    private:
    	CommandUtil _commandHandler;
    	uint8_t _interface;
    	boolean _isSetupDone;
};
#endif
