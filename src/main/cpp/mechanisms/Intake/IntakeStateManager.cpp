//====================================================================================================================================================
/// Copyright 2022 Lake Orion Robotics FIRST Team 302 
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
/// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
/// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
/// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================
#include <map>

// FRC includes

// Team 302 includes
#include <auton/PrimitiveParams.h>
#include <mechanisms/base/StateMgr.h>
#include <mechanisms/MechanismFactory.h>
#include <mechanisms/StateStruc.h>
#include <mechanisms\Intake\IntakeStateManager.h>
#include <TeleopControl.h>
#include <utils/Logger.h>

// Third Party Includes

using namespace std;


IntakeStateMgr* IntakeStateMgr::m_instance = nullptr;
IntakeStateMgr* IntakeStateMgr::GetInstance()
{
	if ( IntakeStateMgr::m_instance == nullptr )
	{
	    auto mechFactory = MechanismFactory::GetMechanismFactory();
	    auto intake = mechFactory->GetIntake();
	    if (intake != nullptr)
        {
		    IntakeStateMgr::m_instance = new IntakeStateMgr();
        }
	}
	return IntakeStateMgr::m_instance;
    
}


/// @brief    initialize the state manager, parse the configuration file and create the states.
IntakeStateMgr::IntakeStateMgr() : StateMgr(),
                                   m_intake(MechanismFactory::GetMechanismFactory()->GetIntake())
{
    map<string, StateStruc> stateMap;
    stateMap[m_intakeOffXmlString] = m_offState;
    stateMap[m_intakeIntakeXmlString] = m_onState;
    stateMap[m_intakeExpelXmlString] = m_expelState;  

    Init(m_intake, stateMap);
    if (m_intake != nullptr)
    {
        m_intake->AddStateMgr(this);
    }
}   

/// @brief Check if driver inputs or sensors trigger a state transition
void IntakeStateMgr::CheckForStateTransition()
{

    if ( m_intake != nullptr )
    {    
        auto currentState = static_cast<INTAKE_STATE>(GetCurrentState());
        auto targetState = currentState;

        auto controller = TeleopControl::GetInstance();
        auto isOnSelected   = controller != nullptr ? controller->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::INTAKE_ON) || controller->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::ARM_GOING_UP) : false;
        auto isExpelSelected   = controller != nullptr ? controller->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::INTAKE_EXPEL) : false;

        Logger::GetLogger()->LogData(LOGGER_LEVEL::PRINT, m_intake->GetNetworkTableName(), string( "Is On Selected" ), isOnSelected);
        Logger::GetLogger()->LogData(LOGGER_LEVEL::PRINT, m_intake->GetNetworkTableName(), string( "Is Expel Selected" ), isExpelSelected);
        
        if (isOnSelected)
        {
            targetState = INTAKE_STATE::INTAKE_ON;
        }
        else if (isExpelSelected)
        {
            targetState = INTAKE_STATE::INTAKE_EXPEL;
        }
        else
        {
            targetState = INTAKE_STATE::INTAKE_OFF;
        }

        if (targetState != currentState)
        {
            SetCurrentState(targetState, true);
        }
        
    }
}

/// @brief  Get the current Parameter parm value for the state of this mechanism
/// @param PrimitiveParams* currentParams current set of primitive parameters
/// @returns int state id - -1 indicates that there is not a state to set
int IntakeStateMgr::GetCurrentStateParam
(
    PrimitiveParams*    currentParams
) 
{
    return currentParams != nullptr ? currentParams->GetIntakeState() : StateMgr::GetCurrentStateParam(currentParams);
}