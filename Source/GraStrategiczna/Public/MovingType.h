#pragma once

#include "MovingType.generated.h"

UENUM(BlueprintType)
enum class MovingType : uint8
{
	Idle = 0    UMETA(DisplayName = "Idle"),
	Walk = 1    UMETA(DisplayName = "Walk"),
	Running = 2   UMETA(DisplayName = "Running"),
	Fight = 3   UMETA(DisplayName = "Fight")
};
