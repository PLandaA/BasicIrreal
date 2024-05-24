// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Delegates/Delegate.h"
#include "PooledObject.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnPooledObjectDespawn, APooledObject*, PoolActor);


UCLASS()
class BASICIRREAL_API APooledObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APooledObject();

	FOnPooledObjectDespawn OnPooledObjectDespawn;

	UFUNCTION(BlueprintCallable, Category = "Pooled Object")
		void Deactivate();

	void SetActive(bool isActive);
	void SetLifeSpan(float lifeTime);
	void SetPoolIndex(int index);

	bool IsActive();
	int GetPoolIndex();

protected:

	bool active;
	float lifeSpan = 0.0f;
	int poolIndex;

	FTimerHandle lifeSpanTimer;
};
