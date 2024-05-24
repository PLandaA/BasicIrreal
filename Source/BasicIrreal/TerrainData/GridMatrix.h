#pragma once
#include "CoreMinimal.h"
#include "GridMatrix.generated.h"
class ACellActor;

USTRUCT(BlueprintType)
struct BASICIRREAL_API FGridColumn
{
	GENERATED_USTRUCT_BODY()
	FGridColumn() {}
	FGridColumn(int height);
	UPROPERTY()
		TArray<ACellActor*> column;
};

USTRUCT(BlueprintType)
struct BASICIRREAL_API FGridMatrix
{
	GENERATED_USTRUCT_BODY()
	FGridMatrix();
	FGridMatrix(FVector2D offsets, int width, int height);
	UPROPERTY(VisibleAnywhere, Category = "Grid Matrix")
		TArray<FGridColumn> rows;
	UPROPERTY(VisibleAnywhere, Category = "Grid Matrix")
		FVector2D offsetsVector = FVector2D();
	UPROPERTY(VisibleAnywhere, Category = "Grid Matrix")
		int w = 0;
	UPROPERTY(VisibleAnywhere, Category = "Grid Matrix")
		int h = 0;
	ACellActor* get(FTransform transform)const;
	ACellActor* get(FVector position)const;
	const FVector2D indices(FVector position)const;
	bool const inside(int x, int y)const;
	const bool linked(int x, int y)const;
	TArray<ACellActor*>& operator[](int index);
};