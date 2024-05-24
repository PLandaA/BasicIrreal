#include "ExampleUtilitiesUse.h"

AExampleUtilitiesUse::AExampleUtilitiesUse()
{
	PrimaryActorTick.bCanEverTick = true;
}
void AExampleUtilitiesUse::BeginPlay()
{
	Super::BeginPlay();
}
void AExampleUtilitiesUse::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	setUtilitiesInstance();
	setAllUtilitiesCalls();
}
void AExampleUtilitiesUse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AExampleUtilitiesUse::setUtilitiesInstance()
{
	utilities = Cast<UUtilitiesInstance>(GetGameInstance());
	if (utilities)
	{
		//furulo el llamado del casteo Utilities Instance
	}
}
FString AExampleUtilitiesUse::getAssetPath(AssetType assetType)
{
	FString path = "";
	if (utilities)
	{
		path = utilities->assetPath(assetType);
	}
	return path;
}
FName AExampleUtilitiesUse::getDamageColorName()
{
	FName name = "";
	if (utilities)
	{
		name = utilities->damageColorName();
	}
	return name;
}
FLinearColor AExampleUtilitiesUse::getDamageColor(DamageColor damageColor)
{
	FLinearColor color = FLinearColor::Black;
	if (utilities)
	{
		color = utilities->damageColorByType(damageColor);
	}
	return color;
}
DamageColor AExampleUtilitiesUse::getDamageColor(FLinearColor color)
{
	DamageColor damageColor = DamageColor::NONE;
	if (utilities)
	{
		damageColor = utilities->damageTypeByColor(color);
	}
	return damageColor;
}
DamageColor AExampleUtilitiesUse::getDamageColor(FTransform transform)
{
	DamageColor damageColor = DamageColor::NONE;
	if (utilities)
	{
		damageColor = utilities->damageTypeByTransform(transform);
	}
	return damageColor;
}
DamageColor AExampleUtilitiesUse::getDamageColor(FVector position)
{
	DamageColor damageColor = DamageColor::NONE;
	if (utilities)
	{
		damageColor = utilities->damageTypeByCoord(position);
	}
	return damageColor;
}
FVector AExampleUtilitiesUse::getMinBorder()
{
	FVector min;
	if (utilities)
	{
		min = utilities->minLimits();
	}
	return min;
}
FVector AExampleUtilitiesUse::getMaxBorder()
{
	FVector max = utilities->maxLimits();
	if (utilities)
	{
		max = utilities->maxLimits();
	}
	return max;
}
void AExampleUtilitiesUse::setAllUtilitiesCalls()
{
	FString pathA = getAssetPath(AssetType::FLOOR);
	FString pathB = getAssetPath(AssetType::PLAYER);
	FString pathC = getAssetPath(AssetType::ENEMY1);
	FName damageColorName = getDamageColorName();

	DamageColor damageColorB = getDamageColor(GetTransform());
	DamageColor damageColorC = getDamageColor(GetTransform().GetLocation());
	
	FLinearColor colorA = getDamageColor(DamageColor::RED);
	FLinearColor colorB = getDamageColor(DamageColor::BLUE);
	FLinearColor colorC = getDamageColor(DamageColor::GREEN);

	DamageColor damageColorByRGB = getDamageColor(colorB);

	FVector minBorder = getMinBorder();
	FVector maxBorder = getMaxBorder();
}