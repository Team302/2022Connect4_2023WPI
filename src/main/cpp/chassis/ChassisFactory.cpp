//====================================================================================================================================================
// Copyright 2022 Lake Orion Robotics FIRST Team 302
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================


//====================================================================================================================================================
// Copyright 2022 Lake Orion Robotics FIRST Team 302
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================

#include <memory>

#include <units/acceleration.h>
#include <units/angular_acceleration.h>
#include <units/angular_velocity.h>
#include <units/length.h>
#include <units/velocity.h>

#include <chassis/ChassisFactory.h>
//#include <chassis/differential/DifferentialChassis.h>
#include <chassis/mecanum/MecanumChassis.h>
#include <chassis/IChassis.h>
#include <hw/DragonCanCoder.h>
#include <hw/interfaces/IDragonMotorController.h>
#include <hw/usages/IDragonMotorControllerMap.h>
#include <utils/Logger.h>

using namespace std;

ChassisFactory* ChassisFactory::m_chassisFactory = nullptr;
ChassisFactory* ChassisFactory::GetChassisFactory()
{
    if ( ChassisFactory::m_chassisFactory == nullptr )
    {
        ChassisFactory::m_chassisFactory = new ChassisFactory();
    }
    return ChassisFactory::m_chassisFactory;
}

//=======================================================================================
// Method:  		CreateChassis
// Description:		Create a chassis from the inputs
// Returns:         Void
//=======================================================================================
IChassis* ChassisFactory::CreateChassis
(
    ChassisFactory::CHASSIS_TYPE   	                            type,				// <I> - Chassis Type
    string												        networkTableName,
    string												        controlFileName,
    units::length::inch_t										wheelDiameter,		
    units::length::inch_t		        						wheelBase,			// <I> - Front-Back distance between wheel centers
    units::length::inch_t		        						track,				// <I> - Left-Right distance between wheels (same axle)
    units::velocity::meters_per_second_t 						maxVelocity,
    units::radians_per_second_t 								maxAngularSpeed,
    units::acceleration::meters_per_second_squared_t 			maxAcceleration,
    units::angular_acceleration::radians_per_second_squared_t 	maxAngularAcceleration,
 	const IDragonMotorControllerMap&                            motors
)
{
    switch ( type )
    {
        case ChassisFactory::CHASSIS_TYPE::TANK_CHASSIS:
        {
            // todo plug in swerve drive
        }
        break;

        case ChassisFactory::CHASSIS_TYPE::MECANUM_CHASSIS:
        {
            auto leftFrontMotor = GetMotorController(motors, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::MECANUM_LEFT_FRONT);
            auto leftBackMotor = GetMotorController(motors, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::MECANUM_LEFT_BACK);
            auto rightFrontMotor = GetMotorController(motors, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::MECANUM_RIGHT_FRONT);
            auto rightBackMotor = GetMotorController(motors, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::MECANUM_RIGHT_BACK);
            auto chassis = new MecanumChassis(leftFrontMotor,
                                              leftBackMotor,
                                              rightFrontMotor,
                                              rightBackMotor,
                                              wheelBase,
                                              track,
                                              maxVelocity,
                                              maxAngularSpeed,
                                              wheelDiameter,
                                              networkTableName);
            m_chassis = chassis;
            m_holonomicChassis = chassis;
        }
        break;

        case ChassisFactory::CHASSIS_TYPE::SWERVE_CHASSIS:
        {
            // todo plug in swerve drive
        }
        break;

        default:
        break;

    }

    return m_chassis;
}
shared_ptr<IDragonMotorController> ChassisFactory::GetMotorController
(
	const IDragonMotorControllerMap&				motorControllers,
	MotorControllerUsage::MOTOR_CONTROLLER_USAGE	usage
)
{
	shared_ptr<IDragonMotorController> motor;
	auto it = motorControllers.find( usage );
	if ( it != motorControllers.end() )  // found it
	{
		motor = it->second;
	}
	else
	{
		string msg = "motor not found; usage = ";
		msg += to_string( usage );
		Logger::GetLogger()->LogData(LOGGER_LEVEL::ERROR, string( "ChassisFactory" ), string( "GetMotorController" ), msg );
	}
	
	if ( motor.get() == nullptr )
	{
		string msg = "motor is nullptr; usage = ";
		msg += to_string( usage );
		Logger::GetLogger()->LogData(LOGGER_LEVEL::ERROR, string( "ChassisFactory" ), string( ":GetMotorController" ), msg );
	}
	return motor;
}


