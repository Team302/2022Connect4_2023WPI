#pragma once

#include <string>
#include <memory>

//Team 302 Includes
#include <mechanisms/base/Mech1IndMotor.h>

class Delivery : public Mech1IndMotor
{
    public:
        Delivery(
            std::shared_ptr<IDragonMotorController> motorController,
            std::string controlFileName,
            std::string networkTableName
            );
        Delivery() = delete;
        ~Delivery() = default;


};