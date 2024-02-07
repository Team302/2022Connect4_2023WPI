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
#include <mechanisms/controllers/MechanismTargetData.h>
#include <mechanisms/flagarm/FlagArmStateManager.h>
#include <mechanisms/MechanismFactory.h>
#include <mechanisms/StateStruc.h>
#include <TeleopControl.h>

// Third Party Includes

using namespace std;


FlagArmStateManager* FlagArmStateManager::m_instance = nullptr;
FlagArmStateManager* FlagArmStateManager::GetInstance()
{
	if ( FlagArmStateManager::m_instance == nullptr )
	{
	    auto mechFactory = MechanismFactory::GetMechanismFactory();
	    auto flagarm = mechFactory->GetFlag();
	    if (flagarm != nullptr)
        {
		    FlagArmStateManager::m_instance = new FlagArmStateManager();
        }
	}
	return FlagArmStateManager::m_instance;
    
}


/// @brief    initialize the state manager, parse the configuration file and create the states.
FlagArmStateManager::FlagArmStateManager() : StateMgr(),
                                             m_flagArm(MechanismFactory::GetMechanismFactory()->GetFlag())
{
    map<string, StateStruc> stateMap;
    stateMap[m_closedXmlString] = m_closedState;
    stateMap[m_openXmlString] = m_openState; 

    Init(m_flagArm, stateMap);
    if (m_flagArm != nullptr)
    {
        m_flagArm->AddStateMgr(this);
    }
}   

/// @brief Check if driver inputs or sensors trigger a state transition
void FlagArmStateManager::CheckForStateTransition()
{

    if ( m_flagArm != nullptr )
    {    
        auto currentState = static_cast<FLAG_ARM_STATE>(GetCurrentState());
        auto targetState = currentState;

        auto controller = TeleopControl::GetInstance();
        auto isForwardSelected   = controller != nullptr ? controller->IsButtonPressed(TeleopControl::FLAG_RELEASE) : true;

        if (isForwardSelected)
        {
            targetState = FLAG_ARM_STATE::GRABBER_OPEN;
        }
        else
        {
            targetState = FLAG_ARM_STATE::GRABBER_CLOSED;
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
int FlagArmStateManager::GetCurrentStateParam
(
    PrimitiveParams*    currentParams
) 
{
    return currentParams != nullptr ? currentParams->GetLFlagArmState() : StateMgr::GetCurrentStateParam(currentParams);
}