#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UtilitiesInstance.h"
#include "CellActor.h"
#include "WallActor.h"
#include "GridManager.generated.h"

UCLASS(Blueprintable, BlueprintType)
class BASICIRREAL_API AGridManager : public AGameModeBase
{
	GENERATED_BODY()
public:
	AGridManager();
	UPROPERTY(EditAnywhere, Category = "Damage Edit")
		FLinearColor damageA;
	UPROPERTY(EditAnywhere, Category = "Damage Edit")
		FLinearColor damageB;
	UPROPERTY(EditAnywhere, Category = "Damage Edit")
		FLinearColor damageC;
	UPROPERTY(EditAnywhere, Category = "Grid Size")
		FVector2D offsets = FVector2D();
	UPROPERTY(EditAnywhere, Category = "Grid Size")
		int width = 0;
	UPROPERTY(EditAnywhere, Category = "Grid Size")
		int height = 0;
protected:
		virtual void BeginPlay()override;
		virtual void PostInitializeComponents()override;
protected:
	UPROPERTY(EditAnywhere, Category = "Damage Color")
		float changeInterlude = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Damage Color")
		UUtilitiesInstance* utilities;
private:
	UFUNCTION(BlueprintCallable, Category = "Grid Actions")
		ACellActor* instantiateCell(FVector position)const;
	UFUNCTION(BlueprintCallable, Category = "Grid Actions")
		const TArray<int>generateSegment(int maxWalls, int limit)const;
	UFUNCTION(BlueprintCallable, Category = "Grid Actions")
		const int lineAmount(int index, int limit)const;
	UFUNCTION(BlueprintCallable, Category = "Grid Actions")
		void fillSpace(ACellActor* first, ACellActor* second);
	UFUNCTION(BlueprintCallable, Category = "Grid Actions")
		void setCellType(ACellActor* cell);
	UFUNCTION(BlueprintCallable, Category = "Grid Actions")
		void spawnActor(AssetType asset, int xIndex, int yIndex);
	UFUNCTION(BlueprintCallable, Category = "Grid Actions")
		void fillUnlinked(int column);
	UFUNCTION(BlueprintCallable, Category = "Grid Actions")
		void setGrid();
	UFUNCTION(BlueprintCallable, Category = "Grid Actions")
		void scanGrid();
	UFUNCTION(BlueprintCallable, Category = "Grid Actions")
		void setWalls();
};