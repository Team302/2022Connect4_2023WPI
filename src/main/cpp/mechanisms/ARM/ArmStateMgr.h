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

// FRC includes


// Team 302 includes
#include <mechanisms\base\StateMgr.h>
#include <mechanisms\StateStruc.h>
#include <mechanisms\ARM\arm.h>

// Third Party Includes

class PrimitiveParams;

class ArmStateMgr : public StateMgr
{
    public:
        /// @enum the various states of the Intake
        enum ARM_STATE
        {
           OFF,
           UP,
           DOWN,
           MOVING_UP,
           MOVING_DOWN
        };
        const std::string m_armOffXmlString = "ARM_OFF";
        const std::string m_armUpXmlString = "ARM_UP";
        const std::string m_armDownXmlString = "ARM_DOWN";
        const std::string  m_armMovingUpXmlString = "ARM_MOVING_UP";
        const std::string m_armMovingDownXmlString = "ARM_MOVING_DOWN";
        
        const std::map<const std::string, ARM_STATE> m_armXmlStringToStateEnumMap
        {   {m_armOffXmlString, ARM_STATE::OFF},
            {m_armUpXmlString, ARM_STATE::UP},
            {m_armDownXmlString, ARM_STATE::DOWN},
            {m_armMovingUpXmlString, ARM_STATE::MOVING_UP},
            {m_armMovingDownXmlString, ARM_STATE::MOVING_DOWN}
        };

        
		/// @brief  Find or create the state manmanager
		/// @return IntakeStateMgr* pointer to the state manager
		static ArmStateMgr* GetInstance();

        /// @brief  Get the current Parameter parm value for the state of this mechanism
        /// @param PrimitiveParams* currentParams current set of primitive parameters
        /// @returns int state id - -1 indicates that there is not a state to set
        int GetCurrentStateParam
        (
            PrimitiveParams*    currentParams
        ) override;

        void CheckForStateTransition() override;
        private:

       ArmStateMgr();
        ~ArmStateMgr() = default;
        
        arm*                                m_arm;
        std::string                             m_nt;


        const double m_CHANGE_STATE_TARGET = 120.0; 
		static ArmStateMgr*	m_instance;
        const StateStruc m_offState = {ARM_STATE::OFF, m_armOffXmlString, StateType::ARM_STATE, true};
        const StateStruc m_upState = {ARM_STATE::UP, m_armUpXmlString, StateType::ARM_STATE, false};
        const StateStruc m_downState = {ARM_STATE::DOWN, m_armDownXmlString, StateType::ARM_STATE, false};
        const StateStruc m_movingDownState = {ARM_STATE::MOVING_DOWN, m_armMovingDownXmlString, StateType::ARM_STATE, false};
        const StateStruc m_movingUpState = {ARM_STATE::MOVING_UP, m_armMovingUpXmlString, StateType::ARM_STATE, false};
};