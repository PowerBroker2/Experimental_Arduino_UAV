/////////////////////////////////////////////////////////////////////////////////////////
/*
   Command Array Anatomy:

   --------------------------------------------------------------------------------------
   Index Number - Command Type                    - Command Format
   --------------------------------------------------------------------------------------
		0       - pitch                           - unsigned 16-Bit Analog
		1       - roll                            - unsigned 16-Bit Analog
		2       - yaw                             - unsigned 16-Bit Analog
		3       - throttle                        - unsigned 16-Bit Analog
		4       - Autopilot Toggle                - unsigned 16-Bit  Boolean (0x0 or 0x1)
		5		- Pitch/Roll Limiter Toggle       - unsigned 16-Bit  Boolean (0x0 or 0x1)
		6       - Landing Gear Toggle             - unsigned 16-Bit  Boolean (0x0 or 0x1)
		7		- Flaps Toggle                    - unsigned 16-Bit  Boolean (0x0 or 0x1)
		8       - Unused                          - Unused
		9       - Unused                          - Unused
		10      - Unused                          - Unused
		11      - Unused                          - Unused
		12      - Unused                          - Unused
		13      - Unused                          - Unused
		14      - Unused                          - Unused
		15      - Unused                          - Unused
		16      - Unused                          - Unused
		17      - Unused                          - Unused
		18      - Unused                          - Unused
		19      - Unused                          - Unused
*/
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
/*
   Telemetry Array Anatomy:

   --------------------------------------------------------------------------------------
   Index Number - Telemetry Type                  - Telemetry Format
   --------------------------------------------------------------------------------------
		0       - Pitot Velocity (m/s) *100       - unsigned 16-bit  Analog
		1       - Converted Altitude (m) * 100    - unsigned 16-bit  Analog
		2       - Pitch Angle (degrees) * 100     - signed 16-bit  Analog
		3       - Roll Angle (degrees) * 100      - signed 16-bit  Analog
		4       - Latitude (dd) * 100             - signed 16-bit  Analog
		5       - Longitude (dd) * 100            - signed 16-bit  Analog
		6       - Unused                          - Unused
		7       - Unused                          - Unused
		8       - Unused                          - Unused
		9       - Unused                          - Unused
		10      - Unused                          - Unused
		11      - Unused                          - Unused
		12      - Unused                          - Unused
		13      - Unused                          - Unused
		14      - Unused                          - Unused
		15      - Unused                          - Unused
		16      - Unused                          - Unused
		17      - Unused                          - Unused
		18      - Unused                          - Unused
		19      - Unused                          - Unused
*/
/////////////////////////////////////////////////////////////////////////////////////////

#include "Arduino.h"




#ifndef AirComms_cpp
#define AirComms_cpp




#define AIR_DATA_LEN			20						//number of 16bit numbers to transfer
#define BUFF_LEN				(AIR_DATA_LEN * 2) + 3	//number of total bytes per transmission (including BUFF_LEN, checksum, and END_BYTE)
#define START_BYTE				0x7E					//dataframe start byte
#define END_BYTE				0xEF					//dataframe end byte

//incoming serial data/parsing errors
#define AIR_NO_DATA				0
#define AIR_NEW_DATA			1
#define AIR_CHECKSUM_ERROR		-1
#define AIR_PAYLOAD_ERROR		-2

//packet index identifiers
///////////////////////////////////////////////////////////////////////////////////////// COMMAND
#define AIR_PITCH_INDEX			0
#define AIR_ROLL_INDEX			1
#define AIR_YAW_INDEX			2
#define AIR_THROTTLE_INDEX		3
#define AIR_AUTOPILOT_INDEX		4
#define AIR_LIMITER_INDEX		5
#define AIR_LANDING_GEAR_INDEX	6
#define AIR_FLAPS_INDEX			7

///////////////////////////////////////////////////////////////////////////////////////// TELEMETRY
#define AIR_PITOT_INDEX			0
#define AIR_ALTITUDE_INDEX		1
#define AIR_PITCH_ANGLE_INDEX	2
#define AIR_ROLL_ANGLE_INDEX	3
#define AIR_LATITUDE_INDEX		4
#define AIR_LONGITUDE_INDEX		5




class airComms
{
public:// <<---------------------------------------------------------------------------//public

	String inputString_Radio = "";      // a String to hold incoming data
	bool stringComplete_Radio = false;  // whether the string is complete

	//data received
	uint16_t incomingArray[AIR_DATA_LEN] = { 0 };

	//data to send
	uint16_t outgoingArray[AIR_DATA_LEN] = { 0 };




	//initialize the class
	void begin();

	//send data from outgoingArray
	void sendData();

	//update incomingArray with new data if available
	byte grabData_Radio();

private:// <<---------------------------------------------------------------------------//private

	//data processing buffers
	byte outBuff[BUFF_LEN] = { 0 };

	//find 8-bit checksum of message
	byte findChecksum(byte buff[]);

	//find 8-bit checksum of message
	byte findChecksum(String buff);




	//send the packet one byte at a time
	void writePacket(byte packet[]);

	//unpack and save received data packet
	int extractData_Radio(byte startingIndex);
};

//create GPS class
extern airComms myRadio;

#endif