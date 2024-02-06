#pragma once
#include <string>
#include <mechanisms/base/Mech1MotorState.h>

class ControlData;
class Delivery;

class DeliveryState : public Mech1MotorState
{
  public:
    DeliveryState() = delete;
    DeliveryState(
        std::string stateName,
        int stateId,
        ControlData *control0,
        double target0
    );
    ~DeliveryState() = default;

    bool AtTarget() const override;
    Delivery *GetDelivery() const { return m_delivery; }

    private:
     Delivery *m_delivery;
};