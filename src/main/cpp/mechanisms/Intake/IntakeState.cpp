#include <string>

#include <mechanisms/base/Mech1MotorState.h>
#include <mechanisms/controllers/ControlData.h>
#include <mechanisms/Intake/IntakeState.h>
#include <mechanisms/MechanismFactory.h>


using namespace std;

IntakeState::IntakeState(
    string stateName,
    int stateID,
    ControlData *control0,
    double target0) : Mech1MotorState(MechanismFactory::GetMechanismFactory()->GetIntake(), stateName, stateID, control0, target0), 
             m_Intake(MechanismFactory::GetMechanismFactory()->GetIntake())

{}

bool IntakeState::AtTarget() const
{
    return true;
}