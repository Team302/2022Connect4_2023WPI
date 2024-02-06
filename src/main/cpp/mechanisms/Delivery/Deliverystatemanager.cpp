#include <auton/PrimitiveParams.h>
#include <mechanisms/base/StateMgr.h>
#include <mechanisms/MechanismFactory.h>
#include <mechanisms/Delivery/Deliverystatemanager.h>
#include <TeleopControl.h>
// #include <
using namespace std;

DeliveryStateMgr* DeliveryStateMgr::m_instance = nullptr;
DeliveryStateMgr* DeliveryStateMgr::GetInstance()
{
    if ( DeliveryStateMgr::m_instance == nullptr)
    {
        auto mechFactory = MechanismFactory::GetMechanismFactory();
        auto delivery = mechFactory->GetDelivery();
        if (delivery != nullptr)
        {
            DeliveryStateMgr::m_instance = new DeliveryStateMgr;
        }
    }

    return DeliveryStateMgr::m_instance;
}

DeliveryStateMgr::DeliveryStateMgr() : StateMgr(),
                                     m_currentState(DELIVERY_STATE::OFF),
                                     m_targetState(DELIVERY_STATE::OFF),
                                     m_delivery(MechanismFactory::GetMechanismFactory()->GetDelivery())


{
map<string, StateStruc> stateMap;
stateMap["DELIVERY_OFF"] = m_offState;
stateMap["DELIVERY_DELIVER"] = m_deliveringState;

Init(m_delivery, stateMap);
if (m_delivery != nullptr)
{
    m_delivery->AddStateMgr(this);
}

}

void DeliveryStateMgr::CheckForStateTransition()
{
    if (m_delivery != nullptr)
    {
        m_currentState = static_cast<DELIVERY_STATE>(GetCurrentState());
        m_targetState = m_currentState;

        auto controller = TeleopControl::GetInstance();
        if (controller != nullptr)
        {
            if (controller->IsButtonPressed(TeleopControl::DELIVER_BALLS))
            {
                m_targetState = DELIVERY_STATE::DELIVERING;
            }
            else
            {
                m_targetState = DELIVERY_STATE::OFF;
            }
        }

        if (m_targetState != m_currentState)
        {
            SetCurrentState(m_targetState, true);
        }
    }
}




