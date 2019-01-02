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
#include "RemoteSetup.h"
#include "CommandUtil.h"
#include <EEPROM.h>

/**
 * Struct used for save initial setup
 */
struct _SetupDataStruct {
  String deviceName;
  //	Network setup
  String wifiSSID;
  String wifiPSK;
} _dataSaved;

/**
 * Implement library RemoteSetup.h
 */
RemoteSetup::RemoteSetup(uint8_t interface) : _commandHandler(10, 11) {
	_interface = interface;
	_isSetupDone = false;
	_commandHandler.setDelay(250);
	_commandHandler.begin(9600);
	//	Get Struct from EEPROM
	//	Validate if setup is done
	if(EEPROM.read(0) == SETUP_DONE_KEY) {
		_isSetupDone = true;
		EEPROM.get(SETUP_DATA_ADDRESS, _dataSaved);
	} else {
		_dataSaved = {
				"",
				"",
				""
		};
		_isSetupDone = false;
	}
}

/**
 * Is setup done
 */
boolean RemoteSetup::isSetupDone() {
    return _isSetupDone;
}

/**
 * Start Remote setup
 */
boolean RemoteSetup::runRemoteSetup() {
	if(isSetupDone()) {
		return true;
	}
	//	Else
	if(_commandHandler.readPort()) {
		_dataSaved.deviceName = getAttribute(DEVICE_NAME_KEY);
		_dataSaved.wifiSSID = getAttribute(SSID_KEY);
		_dataSaved.wifiPSK = getAttribute(PSK_KEY);
		return true;
	}
	//
	return false;
}

/**
 * Get attribute from key
 */
String RemoteSetup::getAttribute(String key) {
	if(_commandHandler.hasValue()) {
		String token;
		String evaluateCommand = _commandHandler.getValue();
		int startTokenIndex = evaluateCommand.indexOf(STX_CHARACTER);
		while (startTokenIndex != -1) {
			evaluateCommand = evaluateCommand.substring(startTokenIndex + 1, evaluateCommand.length());    // from first STX_CHARACTER
		    //
		    int endTokenIndex = evaluateCommand.indexOf(ETX_CHARACTER);                        // next ETX_CHARACTER
		    //	Get individual command
		    token = evaluateCommand.substring(0, endTokenIndex);
		    //
		    if (token.indexOf(VALUE_SEPARATOR) > 0) {
		    	String findKey = token.substring(0, token.indexOf(VALUE_SEPARATOR));
		    	String value = token.substring(token.indexOf(VALUE_SEPARATOR) + 1, token.length());
		    	//  Add to command
		    	if(findKey == key) {
		    		return value;
		    	}
		    }
		    //
		    evaluateCommand = evaluateCommand.substring(endTokenIndex + 1, evaluateCommand.length());    // from second STX_CHARACTER
		    startTokenIndex = evaluateCommand.indexOf(STX_CHARACTER);
		}
	}
    return NO_VALUE_FOR_KEY;
}



/**
 * Send a attribute
 */
boolean RemoteSetup::sendAttribute(char key[], char value[]) {
	_commandHandler.initCommand(REMOTE_SETUP);
	_commandHandler.sendValue(key, value);
	_commandHandler.endCommand();
    return false;
}

/**
 * Save Setup
 */
boolean RemoteSetup::saveSetup() {
	EEPROM.update(0, SETUP_DONE_KEY);
	EEPROM.put(SETUP_DATA_ADDRESS, _dataSaved);
	return true;
}

/**
 * Test Wifi from remote
 */
boolean RemoteSetup::testWifi() {
	String wifiValue = getAttribute(TEST_WIFI_KEY);
	return wifiValue != NO_VALUE_FOR_KEY;
}

/**
 * Send Wifi result of test
 */
void RemoteSetup::sendWifiResult(boolean result) {
	sendAttribute(TEST_WIFI_KEY, (result? "Y": "N"));
}

/**
 * Clear Setup
 */
void RemoteSetup::clearSetup() {
	for (int index = 0 ; index < EEPROM.length() ; index++) {
		EEPROM.write(index, SETUP_CLEAR_KEY);
	}
}

/**
 * Get Device Name
 */
String RemoteSetup::getDeviceName() {
    return _dataSaved.deviceName;
}

/**
 * Get Wifi SSID
 */
String RemoteSetup::getWifiSSID() {
    return _dataSaved.wifiSSID;
}

/**
 * Get Wifi PSK
 */
String RemoteSetup::getWifiPSK() {
    return _dataSaved.wifiPSK;
}
