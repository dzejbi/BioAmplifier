#ifndef SIGNAL_SCALE_ENUM
#define SIGNAL_SCALE_ENUM

#include "StateMachineEnum.h"

enum SignalScaleEnum {
	INCREASE_AMPLITUDE = 1,
	DECREASE_AMPLITUDE = 2,
	INCREASE_FREQUENCY = 3,
	DECREASE_FREQUENCY = 4,
	INCREASE_OFFSET = 5,
	DECREASE_OFFSET = 6,
	NOT_DEFINED = 999,
};

struct MenuAction {
	SignalScaleEnum signalScaleEnum;
	StateMachineEnum stateMachineEnum;
};

#endif // !STATE_MACHINE_ENUM

