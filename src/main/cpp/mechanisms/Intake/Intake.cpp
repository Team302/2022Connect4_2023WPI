#include <mechanisms/Intake/Intake.h>


using namespace std;

Intake::Intake(
    
    std::string controlFileName, 
    std::string networkTableName,
    std::shared_ptr<IDragonMotorController> Intake_Controller) : Mech1IndMotor(MechanismTypes::MechanismTypes::MECHANISM_TYPE::INTAKE, controlFileName, networkTableName, Intake_Controller)
{

}

