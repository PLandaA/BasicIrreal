#include "CellActor.h"
#include "PathsHeader.h"

ACellActor::ACellActor()
{
	PrimaryActorTick.bCanEverTick = true;
	scan = true;

	root = CreateDefaultSubobject<USceneComponent>("Root Component");
	cellMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	auto mesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(FPathsHeader::assetPathChar(AssetType::FLOOR));
	if (mesh.Object)
	{
		cellMesh->SetStaticMesh(mesh.Object);
	}
	RootComponent = root;
	cellMesh->SetupAttachment(root);
}
void ACellActor::BeginPlay()
{
	Super::BeginPlay();
}
void ACellActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	utilities = Cast<UUtilitiesInstance>(GetGameInstance());
	UMaterialInterface* baseMaterial = cellMesh->GetMaterial(0);
	if (baseMaterial)
	{
		dynamicMaterial = UMaterialInstanceDynamic::Create(baseMaterial, this);
		cellMesh->SetMaterial(0, dynamicMaterial);
	}
}
void ACellActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (scan)
	{
		updateColor();
		GetWorld()->GetTimerManager().SetTimer(timer, [this]() {scan = true; }, lapseTime, false);
		scan = false;
	}
}
const DamageColor ACellActor::damageType()const
{
	DamageColor damage = DamageColor::NONE;
	if (utilities)
	{
		damage = utilities->damageTypeByColor(getColor());
	}
	return damage;
}
const FLinearColor ACellActor::getColor()const
{
	FLinearColor color = FColor::Black;
	if (dynamicMaterial)
	{
		dynamicMaterial->GetVectorParameterValue(FPathsHeader::colorTypeName(), color);
	}
	return color;
}
void ACellActor::changeColor(DamageColor damageColor)
{
	if (dynamicMaterial && utilities)
	{
		FLinearColor color = utilities->damageColorByType(damageColor);
		dynamicMaterial->SetVectorParameterValue(FPathsHeader::colorTypeName(), color);
	}
}
const TArray<DamageColor> ACellActor::adjacents()const
{
	TArray<DamageColor>adjacentColors = TArray<DamageColor>();
	if (utilities)
	{
		FVector position = GetActorLocation();
		FVector2D offsets = utilities->getGridMatrix().offsetsVector;
		for (int x = -1; x < 2; x++)
		{
			for (int y = -1; y < 2; y++)
			{
				if (!(x == 0 && y == 0))
				{
					FVector currentCoord(position.X + (x * offsets.X), position.Y + (y * offsets.Y), 0.0f);
					if (!utilities->obstacleByCoord(currentCoord))
					{
						DamageColor currentColor = utilities->damageTypeByCoord(currentCoord);
						if (currentColor != DamageColor::NONE)
						{
							adjacentColors.Add(currentColor);
						}
					}
				}
			}
		}
	}
	return adjacentColors;
}
const TArray<DamageColor> ACellActor::getOtherColors()const
{
	TArray<DamageColor>others = TArray<DamageColor>();
	switch (damageType())
	{
	case DamageColor::RED:
		others.Add(DamageColor::GREEN);
		others.Add(DamageColor::BLUE);
		break;
	case DamageColor::GREEN:
		others.Add(DamageColor::BLUE);
		others.Add(DamageColor::RED);
		break;
	case DamageColor::BLUE:
		others.Add(DamageColor::RED);
		others.Add(DamageColor::GREEN);
		break;
	default:
		others.Add(DamageColor::NONE);
		others.Add(DamageColor::NONE);
		break;
	}
	return others;
}
const DamageColor ACellActor::scanResult(int sameColors, int colorsA, int colorsB)const
{
	DamageColor result = damageType();
	TArray<DamageColor>others = getOtherColors();
	if (colorsA == 2 || colorsA == 4)
	{
		result = others[0];
	}
	else if (colorsB == 2 || colorsB == 4)
	{
		result = others[1];
	}
	else if (colorsA == colorsB)
	{
		result = others[1];
	}
	else if (sameColors < 3 && colorsA > 3)
	{
		result = others[0];
	}
	else if (sameColors < 3 && colorsB > 3)
	{
		result = others[1];
	}
	else if (sameColors > 1 && colorsA < sameColors && colorsB < sameColors)
	{
		result = others[0];
	}
	return result;
}
const int ACellActor::selectQuantity(DamageColor color, int redAmount, int greenAmount, int blueAmount)const
{
	int selected = 0;
	switch (color)
	{
	case DamageColor::RED:
		selected = redAmount;
		break;
	case DamageColor::GREEN:
		selected = greenAmount;
		break;
	case DamageColor::BLUE:
		selected = blueAmount;
		break;
	}
	return selected;
}
void ACellActor::updateColor()
{
	TArray<DamageColor>closerColors = adjacents();
	int currentCount = 0;
	int redCount = 0;
	int greenCount = 0;
	int blueCount = 0;
	for (DamageColor c : closerColors)
	{
		if (c == damageType())
		{
			currentCount++;
		}
		switch (c)
		{
		case DamageColor::RED:
			redCount++;
			break;
		case DamageColor::GREEN:
			greenCount++;
			break;
		case DamageColor::BLUE:
			blueCount++;
			break;
		}
	}
	TArray<DamageColor>others = getOtherColors();
	int colorCountA = selectQuantity(others[0], redCount, greenCount, blueCount);
	int colorCountB = selectQuantity(others[1], redCount, greenCount, blueCount);
	changeColor(scanResult(currentCount, colorCountA, colorCountB));
}