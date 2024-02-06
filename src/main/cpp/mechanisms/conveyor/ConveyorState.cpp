#include <string>

#include <mechanisms/conveyor/ConveyorState.h>
#include <mechanisms/MechanismFactory.h>
#include <mechanisms/controllers/ControlData.h>

using namespace std;

ConveyorState::ConveyorState(
    string stateName,
    int stateID,
    ControlData* control0,
    double target0) : Mech1MotorState(MechanismFactory::GetMechanismFactory()->GetConveyor(), stateName, stateID, control0, target0),
            m_conveyor(MechanismFactory::GetMechanismFactory()->GetConveyor())
{

}

bool ConveyorState::AtTarget() const {
    return true;
}
