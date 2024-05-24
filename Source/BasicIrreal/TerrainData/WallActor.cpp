#include "WallActor.h"
#include "PathsHeader.h"

AWallActor::AWallActor()
{
	PrimaryActorTick.bCanEverTick = false;

	root = CreateDefaultSubobject<USceneComponent>("Root Component");
	wallMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	auto mesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(FPathsHeader::assetPathChar(AssetType::WALL));
	if (mesh.Object)
	{
		wallMesh->SetStaticMesh(mesh.Object);
	}
	RootComponent = root;
	wallMesh->SetupAttachment(root);
}
void AWallActor::BeginPlay()
{
	Super::BeginPlay();
}
void AWallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}