#pragma once

#include <mechanisms/base/StateMgr.h>
#include <mechanisms/conveyor/Conveyor.h>
#include <mechanisms/StateStruc.h>

class ConveyorStateMgr : public StateMgr {
    public:
    enum CONVEYORSTATE {
        OFF,
        LIFTING,
        DELIFTING
    };
    const std::map<const std::string, CONVEYORSTATE> m_conveyorXmlStringToStateEnumMap{
{"CONVEYOR_OFF", CONVEYORSTATE::OFF},
{"CONVEYOR_LIFT", CONVEYORSTATE::LIFTING},
{"CONVEYOR_DELIFT", CONVEYORSTATE::DELIFTING}
    };
    static ConveyorStateMgr* GetInstance();
    void CheckForStateTransition() override;

    private:
    ConveyorStateMgr();
    ~ConveyorStateMgr() = default;

    Conveyor*           m_conveyor;
    static ConveyorStateMgr* m_instance;
    const StateStruc m_offState ={CONVEYORSTATE::OFF, "CONVEYOR_OFF", StateType::CONVEYOR_STATE, true};
    const StateStruc m_liftingState ={CONVEYORSTATE::LIFTING, "CONVEYOR_LIFT", StateType::CONVEYOR_STATE, false};
    const StateStruc m_deliftingState ={CONVEYORSTATE::DELIFTING, "CONVEYOR_DELIFT", StateType::CONVEYOR_STATE, false};
CONVEYORSTATE m_currentstate;
CONVEYORSTATE m_targetstate;
};
