#pragma once
#include <mechanisms/base/StateMgr.h>
#include <mechanisms/Intake/Intake.h>
#include <mechanisms/StateStruc.h>



class IntakeStateMgr : public StateMgr
{
    public:
    static IntakeStateMgr* GetInstance();
    void CheckForStateTransition() override;

    enum INTAKE_STATE
    {
    INTAKE_INTAKING,
    INTAKE_EXPEL,
    INTAKE_OFF
    }; 



    const std::map<const std::string, INTAKE_STATE> m_intakeXmlStringToStateEnumMap{
        {"INTAKE_OFF", INTAKE_STATE::INTAKE_OFF},
        {"INTAKE_INTAKING", INTAKE_STATE::INTAKE_INTAKING},
        {"INTAKE_EXPELLING", INTAKE_STATE::INTAKE_EXPEL}

    };

   private:
        IntakeStateMgr();
        ~IntakeStateMgr() = default;

        Intake* m_intake;

        static IntakeStateMgr* m_instance;
        const StateStruc m_offState          = {INTAKE_STATE::INTAKE_OFF, "INTAKE_OFF", StateType::INTAKE_STATE, true};
        const StateStruc m_onState           = {INTAKE_STATE::INTAKE_INTAKING, "INTAKE_INTAKING", StateType::INTAKE_STATE, false};
        const StateStruc m_expelState        = {INTAKE_STATE::INTAKE_EXPEL, "INTAKE_EXPEL", StateType::INTAKE_STATE, false};

        INTAKE_STATE m_currentState;
        INTAKE_STATE m_targetState;





};
