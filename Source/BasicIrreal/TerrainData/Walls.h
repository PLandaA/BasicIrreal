#pragma once
#include "CoreMinimal.h"
#include "Walls.generated.h"

USTRUCT(BlueprintType)
struct BASICIRREAL_API FWalls
{
	GENERATED_USTRUCT_BODY()
	FWalls();
	TMap<FVector2D, FTransform*>walls;
	FVector2D offsets;
	~FWalls();
};