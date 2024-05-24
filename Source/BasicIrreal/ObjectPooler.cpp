// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPooler.h"

// Sets default values for this component's properties
UObjectPooler::UObjectPooler()
{

}

// Called when the game starts
void UObjectPooler::BeginPlay()
{
	Super::BeginPlay();

	if (PooledObjectSubClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			for (int i = 0; i < PoolSize; i++)
			{
				APooledObject* PoolableActor = World->SpawnActor<APooledObject>(PooledObjectSubClass, FVector().ZeroVector, FRotator().ZeroRotator);

				if (PoolableActor != nullptr)
				{
					PoolableActor->SetActive(false);
					PoolableActor->SetPoolIndex(i);
					//PoolableActor->OnPooledObjectDespawn.AddDynamic(this, &UObjectPooler::OnPooledObjectDespawn);
					objectPool.Add(PoolableActor);
				}
			}
		}
	}
}

APooledObject* UObjectPooler::SpawnPooledObject()
{
	for (APooledObject* PoolableActor : objectPool)
	{
		if (PoolableActor != nullptr && !PoolableActor->IsActive())
		{
			PoolableActor->TeleportTo(FVector(0, 0, 0), FRotator(0, 0, 0));
			PoolableActor->SetLifeSpan(PooledObjectLifeSpan);
			PoolableActor->SetActive(true);
			spawnedPoolIndexes.Add(PoolableActor->GetPoolIndex());

			return PoolableActor;
		}
	}
	if (reuse && spawnedPoolIndexes.Num() > 0)
	{
		int PooledObjectIndex = spawnedPoolIndexes[0];
		spawnedPoolIndexes.Remove(PooledObjectIndex);
		APooledObject* PoolableActor = objectPool[PooledObjectIndex];

		if (PoolableActor != nullptr)
		{
			PoolableActor->SetActive(false);

			PoolableActor->TeleportTo(FVector(0, 0, 0), FRotator(0, 0, 0));
			PoolableActor->SetLifeSpan(PooledObjectLifeSpan);
			PoolableActor->SetActive(true);
			spawnedPoolIndexes.Add(PoolableActor->GetPoolIndex());

			return PoolableActor;
		}
	}

	return nullptr;
}


void UObjectPooler::OnPooledObjectDespawn(APooledObject* PoolActor)
{
	spawnedPoolIndexes.Remove(PoolActor->GetPoolIndex());
}




