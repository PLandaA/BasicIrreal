#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GridMatrix.h"
#include "Walls.h"
#include "UtilitiesInstance.generated.h"
class ACellActor;

UENUM(BlueprintType)
enum class DamageColor : UINT8 { NONE, RED, GREEN, BLUE };

UENUM(BlueprintType)
enum class AssetType : UINT8 { EMPY, FLOOR, WALL, PLAYER, ENEMY1, ENEMY2, ENEMY3 };

UCLASS(BlueprintType)
class BASICIRREAL_API UUtilitiesInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UUtilitiesInstance();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Damage Color")
		FLinearColor firstDamage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Damage Color")
		FLinearColor secondDamage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Damage Color")
		FLinearColor thirdDamage;
	UFUNCTION(BlueprintCallable, Category = "Utilities")
		const FString assetPath(AssetType asset)const;
	UFUNCTION(BlueprintCallable, Category = "Utilities")
		const FName damageColorName()const;
	UFUNCTION(BlueprintCallable, Category = "Utilities")
		FVector validCoord(FVector position)const;
	UFUNCTION(BlueprintCallable, Category = "Utilities")
		FLinearColor damageColorByType(DamageColor colorType)const;
	UFUNCTION(BlueprintCallable, Category = "Utilities")
		DamageColor damageTypeByColor(FLinearColor color)const;
	UFUNCTION(BlueprintCallable, Category = "Utilities")
		DamageColor damageTypeByTransform(FTransform transform)const;
	UFUNCTION(BlueprintCallable, Category = "Utilities")
		DamageColor damageTypeByCoord(FVector position)const;
	UFUNCTION(BlueprintCallable, Category = "Utilities")
		FVector minLimits()const;
	UFUNCTION(BlueprintCallable, Category = "Utilities")
		FVector maxLimits()const;
	UFUNCTION(BlueprintCallable, Category = "Utilities")
		const bool obstacleByCoord(FVector position)const;
	UFUNCTION(BlueprintCallable, Category = "Utilities")
		const bool obstacleByIndices(int xIndex, int yIndex)const;
	UFUNCTION(BlueprintCallable, Category = "Utilities")
		void setGridMatrix(FVector2D offsets, int width, int height);
public:
	FGridMatrix& getGridMatrix();
private:
	FGridMatrix* gridMatrix;
	FWalls* wallsMap;
};