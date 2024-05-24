// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PooledObject.h"
#include "ObjectPooler.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASICIRREAL_API UObjectPooler : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UObjectPooler();

	UFUNCTION(BlueprintCallable, Category = "Object Pool")
		APooledObject* SpawnPooledObject();

	UPROPERTY(EditAnywhere, Category = "Object Pool")
		TSubclassOf<class APooledObject> PooledObjectSubClass;

	UPROPERTY(EditAnywhere, Category = "Object Pool")
		int PoolSize = 30;

	UPROPERTY(EditAnywhere, Category = "Object Pool")
		float PooledObjectLifeSpan = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Object Pool")
		bool reuse = false;

	UFUNCTION()
		void OnPooledObjectDespawn(APooledObject* PoolActor);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TArray<APooledObject*> objectPool;
	TArray<int> spawnedPoolIndexes;
		
};
