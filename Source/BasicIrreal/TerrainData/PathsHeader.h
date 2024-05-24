#pragma once
#include "CoreMinimal.h"
#include "UtilitiesInstance.h"
#include "PathsHeader.generated.h"

USTRUCT(BlueprintType)
struct BASICIRREAL_API FPathsHeader
{
	GENERATED_USTRUCT_BODY()
	static const TCHAR* assetPathChar(AssetType asset);
	static const TCHAR* colorTypeChar();
	static const FString assetPathString(AssetType asset);
	static const FName colorTypeName();
};