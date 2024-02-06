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


#pragma once

#include <units/acceleration.h>
#include <units/angular_acceleration.h>
#include <units/angular_velocity.h>
#include <units/length.h>
#include <units/velocity.h>


#include <memory>

#include <chassis/IChassis.h>
#include <chassis/IHolonomicChassis.h>
#include <hw/DragonCanCoder.h>
#include <hw/interfaces/IDragonMotorController.h>
#include <hw/usages/IDragonMotorControllerMap.h>
//#include <chassis/differential/DifferentialChassis.h>
#include <chassis/mecanum/MecanumChassis.h>

namespace ctre
{
	namespace phoenix
	{
		namespace sensors
		{
			class CANCoder;
		}
	}
}

class ChassisFactory
{

		public:
			enum CHASSIS_TYPE
			{
				UNKNOWN_CHASSIS = -1,
				TANK_CHASSIS,
				MECANUM_CHASSIS,
				SWERVE_CHASSIS,
				MAX_CHASSIS_TYPES
			};
			static ChassisFactory* GetChassisFactory();

			inline IChassis* GetIChassis(){return m_chassis;}
			inline IHolonomicChassis* GetHolonomicChassis() {return m_holonomicChassis;}

			//inline DifferentialChassis* GetDifferentialChassis() {return static_cast<DifferentialChassis*>(m_chassis); };
			inline MecanumChassis* GetMecanumChassis() {return static_cast<MecanumChassis*>(m_chassis); };


			//=======================================================================================
			// Method:  		CreateChassis
			// Description:		Create a chassis from the inputs
			// Returns:         Void
			//=======================================================================================
			IChassis* CreateChassis
			(
				CHASSIS_TYPE     			        						type,				// <I> - Chassis Type
				std::string													networkTableName,
				std::string													controlFileName,
				units::length::inch_t										wheelDiameter,		// <I> - Diameter of the wheel
			    units::length::inch_t		        						wheelBase,			// <I> - Front-Back distance between wheel centers
				units::length::inch_t		        						track,				// <I> - Left-Right distance between wheels (same axle)
				units::velocity::meters_per_second_t 						maxVelocity,
				units::radians_per_second_t 								maxAngularSpeed,
				units::acceleration::meters_per_second_squared_t 			maxAcceleration,
				units::angular_acceleration::radians_per_second_squared_t 	maxAngularAcceleration,
				const IDragonMotorControllerMap&    						motors 		        // <I> - Motor motorControllers
			);


		private:
			std::shared_ptr<IDragonMotorController> GetMotorController
			(
				const IDragonMotorControllerMap&				motorControllers,
				MotorControllerUsage::MOTOR_CONTROLLER_USAGE	usage
			);
			ChassisFactory() = default;
			~ChassisFactory() = default;

			IChassis*        	m_chassis;
			IHolonomicChassis* 	m_holonomicChassis;

			static ChassisFactory*	m_chassisFactory;

};
