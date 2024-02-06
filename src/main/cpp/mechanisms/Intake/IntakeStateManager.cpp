#include <mechanisms/Intake/IntakeStateManager.h>
#include <TeleopControl.h>
#include <utils/Logger.h>
#include <mechanisms/MechanismFactory.h>


using namespace std;

IntakeStateMgr* IntakeStateMgr::m_instance = nullptr;
IntakeStateMgr* IntakeStateMgr::GetInstance()
{
    if (IntakeStateMgr::m_instance == nullptr)
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

IntakeStateMgr::IntakeStateMgr() : StateMgr(),
                            m_intake(MechanismFactory::GetMechanismFactory()->GetIntake()),
                            m_currentState(INTAKE_STATE::INTAKE_OFF),
                            m_targetState(INTAKE_STATE::INTAKE_OFF)


{
    map<string, StateStruc> stateMap;
    stateMap["INTAKE_OFF"]      = m_offState;
    stateMap["INTAKE_INTAKING"] = m_onState;
    stateMap["INTAKE_EXPEL"]    = m_expelState;


    Init(m_intake, stateMap);

    if (m_intake != nullptr)
    {
         m_intake->AddStateMgr(this);


    }
}

void IntakeStateMgr::CheckForStateTransition()
{
    if (m_intake != nullptr)
    {
        m_currentState = static_cast<INTAKE_STATE>(GetCurrentState());
        m_targetState = m_currentState;

        auto controller = TeleopControl::GetInstance();
        if (controller != nullptr)
        {
            if (controller->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::INTAKE_BALLS))
            {
                m_targetState = INTAKE_STATE::INTAKE_INTAKING;
            }
            

            else if (controller->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::EXPEL_BALLS))
            {
                m_targetState = INTAKE_STATE::INTAKE_EXPEL;
            }
            else
            {
                 m_targetState = INTAKE_STATE::INTAKE_OFF;
            }


        }
    }


    



    if (m_targetState != m_currentState)
    {
        SetCurrentState(m_targetState, true);
    }



    

}