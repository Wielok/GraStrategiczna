#pragma once

#include "UnitType.generated.h"

UENUM(BlueprintType)
enum class UnitType : uint8
{
	BasicUnit = 0    UMETA(DisplayName = "BasicUnit"),
	MeleeUnit = 1    UMETA(DisplayName = "MeleeUnit"),
	RangeUnit = 2   UMETA(DisplayName = "RangeUnit")
};
