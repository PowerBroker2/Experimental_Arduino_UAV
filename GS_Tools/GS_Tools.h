#include "Arduino.h"

#include "GS_Serial.h"
#include "Shared_Tools.h"
#include "AirComms.h"




#ifndef GS_Tools_cpp
#define GS_Tools_cpp




/////////////////////////////////////////////////////////////////////////////////////////
//macros
#define GS

#define YAW_ANALOG_PIN			    0
#define THROTTLE_ANALOG_PIN		    1
#define ROLL_ANALOG_PIN			    2
#define PITCH_ANALOG_PIN		    3

#define PITCH_RATE_PIN			    0
#define ROLL_RATE_PIN			    1
#define YAW_RATE_PIN				2

#define AILERON_OFFSET              0
#define ELEVATOR_OFFSET             0
#define RUDDER_OFFSET               0
#define THROTTLE_OFFSET             0

#define AILERON_MAX_LOWRATES        325
#define ELEVATOR_MAX_LOWRATES       350
#define RUDDER_MAX_LOWRATES         292

#define AILERON_MIN_LOWRATES        289
#define ELEVATOR_MIN_LOWRATES       264
#define RUDDER_MIN_LOWRATES         264

#define THROTTLE_MIN_ADC            35880
#define AILERON_MIN_ADC             35300
#define ELEVATOR_MIN_ADC            36620
#define RUDDER_MIN_ADC              37330

#define THROTTLE_MAX_ADC            61220
#define AILERON_MAX_ADC             60180
#define ELEVATOR_MAX_ADC            62300
#define RUDDER_MAX_ADC              62170
/////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////
//GS Class
class GS_Class
{
public:
	struct telemetry
	{
		float altitude;
		float rollAngle;
		float pitchAngle;
		float velocity;
		float latitude;
		float longitude;
	} telemetry;

	struct controlInputs
	{
		uint16_t pitch_command;
		uint16_t roll_command;
		uint16_t yaw_command;
		uint16_t throttle_command;
		uint16_t autopilot_command;
		uint16_t limiter_command;
		uint16_t landingGear_command;
		uint16_t flaps_command;
	} controlInputs;

	//initialize the IFC class
	void begin();

	//get data from GS
	int grabData_Radio();

	//send telemetry data to GS
	void sendCommands();

	//determine each command value based off GS sensor data
	void computeCommands();

private:
	/////////////////////////////////////////////////////////////////////////////////////////
	//structs to handle control surface commands
	struct controlSurfaces
	{
		byte command_index;
		byte analog_pin;
		byte rate_pin;
		uint16_t _offset;
		uint16_t high_rates_surface_max;
		uint16_t high_rates_surface_min;
		uint16_t low_rates_surface_max;
		uint16_t low_rates_surface_min;
		uint16_t ADC_max;
		uint16_t ADC_min;
	};

	struct controlSurfaces ailerons
	{
		AIR_ROLL_INDEX,         //command_index
		ROLL_ANALOG_PIN,        //analog_pin
		ROLL_RATE_PIN,          //rate_pin
		AILERON_OFFSET,         //_offset
		AILERON_MAX,			//high_rates_surface_max
		AILERON_MIN,			//high_rates_surface_min
		AILERON_MAX_LOWRATES,   //low_rates_surface_max
		AILERON_MIN_LOWRATES,   //low_rates_surface_min
		AILERON_MAX_ADC,        //ADC_max
		AILERON_MIN_ADC         //ADC_min
	};

	struct controlSurfaces elevator
	{
		AIR_PITCH_INDEX,        //command_index
		PITCH_ANALOG_PIN,       //analog_pin
		PITCH_RATE_PIN,         //rate_pin
		ELEVATOR_OFFSET,        //_offset
		ELEVATOR_MAX,			//high_rates_surface_max
		ELEVATOR_MIN,			//high_rates_surface_min
		ELEVATOR_MAX_LOWRATES,  //low_rates_surface_max
		ELEVATOR_MIN_LOWRATES,  //low_rates_surface_min
		ELEVATOR_MAX_ADC,       //ADC_max
		ELEVATOR_MIN_ADC        //ADC_min
	};

	struct controlSurfaces rudder
	{
		AIR_YAW_INDEX,          //command_index
		YAW_ANALOG_PIN,         //analog_pin
		YAW_RATE_PIN,           //rate_pin
		RUDDER_OFFSET,          //_offset
		RUDDER_MAX,				//high_rates_surface_max
		RUDDER_MIN,				//high_rates_surface_min
		RUDDER_MAX_LOWRATES,    //low_rates_surface_max
		RUDDER_MIN_LOWRATES,    //low_rates_surface_min
		RUDDER_MAX_ADC,         //ADC_max
		RUDDER_MIN_ADC          //ADC_max
	};

	struct controlSurfaces throttle
	{
		AIR_THROTTLE_INDEX,     //command_index
		THROTTLE_ANALOG_PIN,    //analog_pin
		0,                      //rate_pin
		THROTTLE_OFFSET,        //_offset
		THROTTLE_MAX,           //high_rates_surface_max
		THROTTLE_MIN,           //high_rates_surface_min
		0,                      //low_rates_surface_max
		0,                      //low_rates_surface_min
		THROTTLE_MAX_ADC,       //ADC_max
		THROTTLE_MIN_ADC        //ADC_max
	};
	/////////////////////////////////////////////////////////////////////////////////////////

	//calculate the 
	int16_t updateServoCommand(controlSurfaces controlSurface);
};

extern GS_Class myGS;
/////////////////////////////////////////////////////////////////////////////////////////

#endif