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

/**
 * Implement library RemoteSetup.h
 */

/**
 * Constructor, get prefix for file, chip selected for out and file format
 */
RemoteSetup::RemoteSetup(uint8_t interface) : _commandHandler(10, 11) {
	_interface = interface;
	_isSetupDone = false;
	_commandHandler.setDelay(250);
	_commandHandler.begin(9600);
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
	return _commandHandler.readPort();
}

/**
 * Get attribute from key
 */
String RemoteSetup::getAttribute(String key) {
    return "";
}

/**
 * Send a attribute
 */
void RemoteSetup::sendAttribute(String key, String value) {
    return "";
}

/**
 * Save Setup
 */
boolean RemoteSetup::saveSetup() {
	return false;
}
