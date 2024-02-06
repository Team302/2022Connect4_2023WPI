#include <mechanisms/Delivery/Delivery.h>
Delivery::Delivery(
    std::shared_ptr<IDragonMotorController> motorController,
    std::string controlFileName,
    std::string networkTableName
):Mech1IndMotor(MechanismTypes::MECHANISM_TYPE::DELIVERY, controlFileName, networkTableName, motorController)
{}

