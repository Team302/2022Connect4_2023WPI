// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.


#include <Robot.h>

#include <string>

#include <cameraserver/CameraServer.h>

#include <auton/CyclePrimitives.h>
#include <chassis/ChassisFactory.h>
#include <chassis/holonomic/HolonomicDrive.h>
#include <chassis/IHolonomicChassis.h>
#include <chassis/mecanum/MecanumChassis.h>
#include <mechanisms/StateMgrHelper.h>
#include <RobotXmlParser.h>
#include <TeleopControl.h>
#include <utils/Logger.h>
#include <utils/LoggerData.h>
#include <utils/LoggerEnums.h>
#include <LoggableItemMgr.h>

using namespace std;

void Robot::RobotInit() 
{
    m_startLogging = false;
    Logger::GetLogger()->PutLoggingSelectionsOnDashboard();
    Logger::GetLogger()->LogData(LOGGER_LEVEL::PRINT, string("ArrivedAt"), string("RobotInit"), string("arrived"));   
    
    m_controller = TeleopControl::GetInstance();

    // Read the XML file to build the robot 
    auto XmlParser = new RobotXmlParser();
    XmlParser->ParseXML();

    auto factory = ChassisFactory::GetChassisFactory();
    m_chassis = factory->GetMecanumChassis();
    m_holonomic = nullptr;
    if (m_chassis != nullptr)
    {
         m_holonomic = m_chassis->GetType() != IChassis::CHASSIS_TYPE::DIFFERENTIAL ? new HolonomicDrive() : nullptr;
    }        
    
    StateMgrHelper::InitStateMgrs();

    m_cyclePrims = new CyclePrimitives();
    Logger::GetLogger()->LogData(LOGGER_LEVEL::PRINT, string("ArrivedAt"), string("RobotInit"), string("end"));

    m_startLogging = true;
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() 
{
   if (m_chassis != nullptr)
   {
       m_chassis->UpdateOdometry();
  }

    if (m_startLogging)
    {
        LoggableItemMgr::GetInstance()->LogData();
        Logger::GetLogger()->PeriodicLog();
    }
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() 
{
    Logger::GetLogger()->LogData(LOGGER_LEVEL::PRINT, string("ArrivedAt"), string("AutonomousInit"), string("arrived"));   
    if (m_cyclePrims != nullptr)
    {
        m_cyclePrims->Init();
    }
    Logger::GetLogger()->LogData(LOGGER_LEVEL::PRINT, string("ArrivedAt"), string("AutonomousInit"), string("end"));
}

void Robot::AutonomousPeriodic() 
{
    if (m_cyclePrims != nullptr)
    {
        m_cyclePrims->Run();
    }
}

void Robot::TeleopInit() 
{
    Logger::GetLogger()->LogData(LOGGER_LEVEL::PRINT, string("ArrivedAt"), string("TeleopInit"), string("arrived"));   
    if (m_chassis != nullptr && m_controller != nullptr && m_holonomic != nullptr)
    {
        m_holonomic->Init();
    }
    StateMgrHelper::RunCurrentMechanismStates();

    Logger::GetLogger()->LogData(LOGGER_LEVEL::PRINT, string("ArrivedAt"), string("TeleopInit"), string("end"));
}


void Robot::TeleopPeriodic() 
{
    Logger::GetLogger()->LogData(LOGGER_LEVEL::PRINT, string("ArrivedAt"), string("TeleopPeriodic"), string("arrived"));   
    if (m_chassis != nullptr && m_controller != nullptr && m_holonomic != nullptr)
    {
        m_holonomic->Run();
    }
    StateMgrHelper::RunCurrentMechanismStates();

    Logger::GetLogger()->LogData(LOGGER_LEVEL::PRINT, string("ArrivedAt"), string("TeleopPeriodic"), string("end"));

}

void Robot::DisabledInit() 
{
    Logger::GetLogger()->LogData(LOGGER_LEVEL::PRINT, string("ArrivedAt"), string("DisabledInit"), string("arrived"));   
    Logger::GetLogger()->LogData(LOGGER_LEVEL::PRINT, string("ArrivedAt"), string("DisabledInit"), string("end"));   
}

void Robot::DisabledPeriodic() 
{

}

void Robot::TestInit() 
{
    Logger::GetLogger()->LogData(LOGGER_LEVEL::PRINT, string("ArrivedAt"), string("TestInit"), string("arrived"));   
}

void Robot::TestPeriodic() 
{

}


#ifndef RUNNING_FRC_TESTS
int main() 
{
    return frc::StartRobot<Robot>();
}
#endif
