#pragma once

#include "UnitStatusType.generated.h"

UENUM(BlueprintType)
enum class UnitStatusType : uint8
{
	Owner = 0    UMETA(DisplayName = "Owner"),
	Firendly = 1    UMETA(DisplayName = "Firendly"),
	Enemy = 2   UMETA(DisplayName = "Enemy")
};
