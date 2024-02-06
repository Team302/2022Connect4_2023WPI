#pragma once

#include<string>

//Team 302 Includes

#include <mechanisms/base/Mech1IndMotor.h> 

#include <memory>


class Intake : public Mech1IndMotor
{
public:
  Intake(
  std::string controlFileName, 
  std::string networkTableName,
  std::shared_ptr<IDragonMotorController> Intake_Controller
  );
  Intake() = delete;
  ~Intake() = default;
  

};
