#pragma once

#include <string>

//Team 302 Includes
#include <mechanisms/base/Mech1MotorState.h>

class ControlData;
class Conveyor;
class ConveyorState : public Mech1MotorState{
    public:
    ConveyorState() = delete;
    ConveyorState(
        std::string stateName,
        int stateID,
        ControlData* control0,
        double target0
    );
    ~ConveyorState()=default;
    bool AtTarget() const override;
    Conveyor *GetConveyor() const {return m_conveyor;}
private:
    Conveyor *m_conveyor;
};
