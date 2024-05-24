// Fill out your copyright notice in the Description page of Project Settings.


#include "PooledObject.h"

// Sets default values
APooledObject::APooledObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void APooledObject::Deactivate()
{
	SetActive(false);
	GetWorldTimerManager().ClearAllTimersForObject(this);
	//OnPooledObjectDespawn.Broadcast(this);
}

void APooledObject::SetActive(bool isActive)
{
	active = isActive;
	SetActorHiddenInGame(!isActive);
	GetWorldTimerManager().SetTimer(lifeSpanTimer, this, &APooledObject::Deactivate, lifeSpan, false);
}

void APooledObject::SetLifeSpan(float lifeTime)
{
	lifeSpan = lifeTime;
}

void APooledObject::SetPoolIndex(int index)
{
	poolIndex = index;
}

bool APooledObject::IsActive()
{
	return active;
}

int APooledObject::GetPoolIndex()
{
	return poolIndex;
}



