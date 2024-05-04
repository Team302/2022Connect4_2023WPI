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
#include <string>
#include <mechanisms/base/StateMgr.h>
#include <mechanisms/StateStruc.h>

 
class Intake;
class PrimitiveParams;

class IntakeStateMgr : public StateMgr
{
    public:
        /// @enum the various states of the Intake
        enum INTAKE_STATE
        {
            INTAKE_OFF,
            INTAKE_ON,
            INTAKE_EXPEL
        };

        const std::string m_intakeOffXmlString = "INTAKE_OFF";
        const std::string m_intakeIntakeXmlString = "INTAKE_ON";
        const std::string m_intakeExpelXmlString = "INTAKE_EXPEL";
        
        
        const std::map<const std::string, INTAKE_STATE> m_intakeXmlStringToStateEnumMap
        {   {m_intakeOffXmlString, INTAKE_STATE::INTAKE_OFF},
            {m_intakeIntakeXmlString, INTAKE_STATE::INTAKE_ON},
            {m_intakeExpelXmlString, INTAKE_STATE::INTAKE_EXPEL}
        };
        static IntakeStateMgr* GetInstance();
        void CheckForStateTransition() override;

        /// @brief  Get the current Parameter parm value for the state of this mechanism
        /// @param PrimitiveParams* currentParams current set of primitive parameters
        /// @returns int state id - -1 indicates that there is not a state to set
        int GetCurrentStateParam
        (
            PrimitiveParams*    currentParams
        ) override;

    private:
        IntakeStateMgr();
        ~IntakeStateMgr() = default;

        Intake*                                m_intake;

        static IntakeStateMgr*	m_instance;
        const StateStruc m_offState = {INTAKE_STATE::INTAKE_OFF, m_intakeOffXmlString, StateType::INTAKE_STATE, true};
        const StateStruc m_onState = {INTAKE_STATE::INTAKE_ON, m_intakeIntakeXmlString, StateType::INTAKE_STATE, false};
        const StateStruc m_expelState = {INTAKE_STATE::INTAKE_EXPEL, m_intakeExpelXmlString, StateType::INTAKE_STATE, false};
};
