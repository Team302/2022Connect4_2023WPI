/*
* DragonSparkMax.h
*
* Date Created: Jan 15, 2019
* Author: Jonah Shader
*/

#pragma once

#include <memory>

#include "hw/interfaces/IDragonMotorController.h"
#include "hw/usages/MotorControllerUsage.h"

#include "rev/CANSparkMax.h"
#include <ctre/phoenix/motorcontrol/RemoteSensorSource.h>

// namespaces
using namespace rev;

class DragonSparkMax : public IDragonMotorController
{
public:
    //note: two PIDs: 0 is position, 1 is velocity
    // Constructors
    DragonSparkMax() = delete;
    DragonSparkMax( int id, 
                    MotorControllerUsage::MOTOR_CONTROLLER_USAGE deviceType, 
                    CANSparkMax::MotorType motorType, 
                    double gearRatio);

    virtual ~DragonSparkMax() = default;

    // Getters
    double GetRotations() const override;
    double GetRPS() const override;
    MotorControllerUsage::MOTOR_CONTROLLER_USAGE GetType() const override;
    int GetID() const override;

    // Setters
    void SetControlConstants(int slot, ControlData* controlInfo) override;

    void Set(double value) override;
    void SetRotationOffset(double rotations) override;
    void SetVoltageRamping(double ramping, double rampingClosedLoop = -1) override; // seconds 0 to full, set to 0 to disable
    void EnableCurrentLimiting(bool enabled) override;
    void EnableBrakeMode(bool enabled) override;
    void Invert(bool inverted) override;

    void InvertEncoder(bool inverted);
    void SetSmartCurrentLimiting(int limit);
    void SetSecondaryCurrentLimiting(int limit, int duration);
    //CANError Follow(DragonSparkMax* leader, bool invert = false);

    // dummy methods below
    std::shared_ptr<frc::MotorController> GetSpeedController() const override;
    double GetCurrent() const override;
    IDragonMotorController::MOTOR_TYPE GetMotorType() const override;
    void SetSensorInverted(bool inverted) override;
    void SetDiameter( double diameter ) override;
    void SetVoltage(units::volt_t output) override;
    double GetCounts() const override;
    void SetRemoteSensor(int canID, ctre::phoenix::motorcontrol::RemoteSensorSource deviceType) override;
    void SetFramePeriodPriority(MOTOR_PRIORITY priority) override;
    bool IsForwardLimitSwitchClosed() const override;
    bool IsReverseLimitSwitchClosed() const override;
    void EnableVoltageCompensation( double fullvoltage) override;
    void SetSelectedSensorPosition(double  initialPosition) override;
    double GetCountsPerInch() const override;
    double GetCountsPerDegree() const override;
    void EnableDisableLimitSwitches(bool enable) override;
    double GetCountsPerRev() const override {return 1.0;}
    double GetGearRatio() const override { return 1.0;}

private:
    double GetRotationsWithGearNoOffset() const;
    int m_id;
    CANSparkMax* m_spark;
    //DRAGON_CONTROL_MODE m_controlMode;
    double m_outputRotationOffset;
    double m_gearRatio;
    MotorControllerUsage::MOTOR_CONTROLLER_USAGE m_deviceType;

    CANSparkMax* GetSparkMax();
    
};