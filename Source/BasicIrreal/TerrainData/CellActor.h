#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UtilitiesInstance.h"
#include "CellActor.generated.h"

UCLASS(Blueprintable, BlueprintType)
class BASICIRREAL_API ACellActor : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Change Condition")
		float lapseTime = 0.0f;
public:
	ACellActor();
		UFUNCTION(BlueprintCallable, Category = "Terrain Info")
	const DamageColor damageType()const;
		UFUNCTION(BlueprintCallable, Category = "Terrain Info")
	const FLinearColor getColor()const;
		UFUNCTION(BlueprintCallable, Category = "Terrain Info")
	void changeColor(DamageColor damageColor);
protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;
	virtual void Tick(float DeltaTime) override;
protected:
	UFUNCTION(BlueprintCallable, Category = "Terrain Scan")
		const TArray<DamageColor>adjacents()const;
	UFUNCTION(BlueprintCallable, Category = "Terrain Scan")
		const TArray<DamageColor>getOtherColors()const;
	UFUNCTION(BlueprintCallable, Category = "Terrain Scan")
		const DamageColor scanResult(int sameColors, int colorsA, int colorsB)const;
	UFUNCTION(BlueprintCallable, Category = "Terrain Scan")
		const int selectQuantity(DamageColor color, int redAmount, int greenAmount, int blueAmount)const;
	UFUNCTION(BlueprintCallable, Category = "Terrain Scan")
		void updateColor();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Elements Pointers")
		UUtilitiesInstance* utilities;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Elements Pointers")
		USceneComponent* root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Elements Pointers")
		UStaticMeshComponent* cellMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Elements Pointers")
		UMaterialInstanceDynamic* dynamicMaterial;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Change Condition")
		FTimerHandle timer;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Change Condition")
		bool scan = false;
};