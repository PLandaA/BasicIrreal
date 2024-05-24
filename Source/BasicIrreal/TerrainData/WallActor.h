#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WallActor.generated.h"

UCLASS(Blueprintable, BlueprintType)
class BASICIRREAL_API AWallActor : public AActor
{
	GENERATED_BODY()
public:
	AWallActor();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Elements Pointers")
		USceneComponent* root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Elements Pointers")
		UStaticMeshComponent* wallMesh;
};