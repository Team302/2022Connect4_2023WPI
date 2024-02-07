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

#pragma once

// C++ Includes
#include <string>

// FRC includes


// Team 302 includes
#include <mechanisms/base/StateMgr.h>
#include <mechanisms/StateStruc.h>




// Third Party Includes
class FlagArm;
class PrimitiveParams;

class FlagArmStateManager : public StateMgr
{
    public:
        /// @enum the various states of the Intake
        enum FLAG_ARM_STATE
        {
            GRABBER_OPEN,
            GRABBER_CLOSED
            
        };
        const std::string m_openXmlString = "FLAG_RELEASE";
        const std::string m_closedXmlString = "FLAG_GRAB";
        
        const std::map<const std::string, FlagArmStateManager::FLAG_ARM_STATE> m_FlagXmlStringToStateEnumMap
        {   {m_openXmlString, FlagArmStateManager::FLAG_ARM_STATE::GRABBER_OPEN},
            {m_closedXmlString, FlagArmStateManager::FLAG_ARM_STATE::GRABBER_CLOSED}
        };

        
		/// @brief  Find or create the state manmanager
		/// @return IntakeStateMgr* pointer to the state manager
		static FlagArmStateManager* GetInstance();

        /// @brief  Get the current Parameter parm value for the state of this mechanism
        /// @param PrimitiveParams* currentParams current set of primitive parameters
        /// @returns int state id - -1 indicates that there is not a state to set
        int GetCurrentStateParam
        (
            PrimitiveParams*    currentParams
        ) override;

        /// @brief Check if driver inputs or sensors trigger a state transition
        void CheckForStateTransition() override;
    private:

        FlagArmStateManager();
        ~FlagArmStateManager() = default;

        FlagArm*                    m_flagArm;

        static FlagArmStateManager* m_instance;

        const StateStruc m_openState = {FlagArmStateManager::FLAG_ARM_STATE::GRABBER_OPEN, m_openXmlString,  StateType::FLAGARM_STATE, true};
        const StateStruc m_closedState = {FlagArmStateManager::FLAG_ARM_STATE::GRABBER_CLOSED, m_closedXmlString, StateType::FLAGARM_STATE, false};
};