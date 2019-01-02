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
/**
 * Setup Done
 */
static const uint8_t SETUP_DONE_KEY =		777; // Setup flag
static const uint8_t SETUP_CLEAR_KEY =		0; // Setup flag
static const uint8_t SETUP_DATA_ADDRESS =	sizeof(int); // Struct flag
/**	Device Name	*/
static const char DEVICE_NAME_KEY[] = "DeviceName";
/**	Wifi keys	*/
static const char SSID_KEY[] = "SSID";
static const char PSK_KEY[] = "PSK";
static const char TEST_WIFI_KEY[] = "TestWifi";

static const char NO_VALUE_FOR_KEY = 0;

class RemoteSetup {
    public:
        RemoteSetup(uint8_t interface);
        boolean isSetupDone();
        boolean runRemoteSetup();
        String getAttribute(String key);
        boolean sendAttribute(char key[], char value[]);
        boolean saveSetup();
        void clearSetup();
        String getDeviceName();
        String getWifiSSID();
        String getWifiPSK();
        boolean testWifi();
        void sendWifiResult(boolean result);
    private:
    	CommandUtil _commandHandler;
    	uint8_t _interface;
    	boolean _isSetupDone;
    	struct _SetupDataStruct;
};
#endif
