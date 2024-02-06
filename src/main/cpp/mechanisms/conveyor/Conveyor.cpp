#include <mechanisms/Conveyor/Conveyor.h>

using namespace std;

Conveyor::Conveyor(
std::string ControlFileConveyor,
std::string NetworkFileConveyor,
std::shared_ptr<IDragonMotorController> motorController) : Mech1IndMotor(MechanismTypes::MECHANISM_TYPE::CONVEYOR_MECHANISM, ControlFileConveyor, NetworkFileConveyor, motorController)
{}
