#include "Stepper.h"
#include "Config.h"

// Arduino library class style global object
Stepper_ Stepper;

Stepper_::Stepper_() :
    _stepper(AccelStepper::HALF4WIRE, STEPPER_PIN_1, STEPPER_PIN_3, STEPPER_PIN_2, STEPPER_PIN_4)
{
}

void Stepper_::begin()
{
    _stepper.setMaxSpeed(STEPPER_MAX_SPEED);
    _stepper.setSpeed(STEPPER_STEPS_PER_SEC);
    
}

bool Stepper_::step()
{
    return _stepper.runSpeed();
}

