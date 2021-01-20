#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "Engine/DataTable.h"
#include "PlayerInfo.generated.h"

USTRUCT(BlueprintType)
struct FPlayerInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Analytics")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Analytics")
	FString Value;
};