#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../TerrainData/UtilitiesInstance.h"
#include "ExampleUtilitiesUse.generated.h"

UCLASS(Blueprintable, BlueprintType)
class BASICIRREAL_API AExampleUtilitiesUse : public AActor
{
	GENERATED_BODY()
public:	
	AExampleUtilitiesUse();
protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;
	virtual void Tick(float DeltaTime) override;
private:
	void setUtilitiesInstance();
	FString getAssetPath(AssetType assetType);
	FName getDamageColorName();
	FLinearColor getDamageColor(DamageColor damageColor);
	DamageColor getDamageColor(FLinearColor color);
	DamageColor getDamageColor(FTransform transform);
	DamageColor getDamageColor(FVector position);
	FVector getMinBorder();
	FVector getMaxBorder();
	void setAllUtilitiesCalls();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utilities Pointer")
		UUtilitiesInstance* utilities;
};
