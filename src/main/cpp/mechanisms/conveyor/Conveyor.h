#pragma once

#include <string>

//Team 302 Includes
#include <mechanisms/base/Mech1IndMotor.h>

class Conveyor : public Mech1IndMotor {
  public:
  Conveyor(
std::string ControlFileConveyor,
std::string NetworkFileConveyor,
std::shared_ptr<IDragonMotorController> motorController
  );
Conveyor()= delete;
~Conveyor()=default;

};