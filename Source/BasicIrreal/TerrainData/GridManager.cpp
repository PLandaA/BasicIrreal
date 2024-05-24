#include "GridManager.h"

AGridManager::AGridManager()
{
	
}
void AGridManager::BeginPlay()
{
	Super::BeginPlay();
}
void AGridManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	utilities = Cast<UUtilitiesInstance>(GetGameInstance());
	if (utilities)
	{
		utilities->firstDamage = damageA;
		utilities->secondDamage = damageB;
		utilities->thirdDamage = damageC;
	}
	setGrid();
}
ACellActor* AGridManager::instantiateCell(FVector position)const
{
	ACellActor* cell = GetWorld()->SpawnActor<ACellActor>(ACellActor::StaticClass(), FTransform(position));
	return cell;
}
const TArray<int> AGridManager::generateSegment(int maxCells, int limit)const
{
	TArray<int>segment = TArray<int>();
	for (int i = 0; i < maxCells; i++)
	{
		int current = FMath::RandRange(0, limit);
		if (segment.Contains(current))
		{
			for (int w : segment)
			{
				int positive = w + 1;
				int negative = w - 1;
				if (positive < limit && !segment.Contains(positive))
				{
					current = positive;
					break;
				}
				else if (negative >= 0 && !segment.Contains(negative))
				{
					current = negative;
					break;
				}
			}
		}
		segment.Add(current);
	}
	return segment;
}
const int AGridManager::lineAmount(int index, int limit)const
{
	int probability = 0;
	if (index < limit / 4)
	{
		probability = limit * 0.7f;
	}
	else if (index < limit / 2)
	{
		probability = limit * 0.9f;
	}
	else
	{
		probability = limit * 0.8f;
	}
	return probability;
}
void AGridManager::fillSpace(ACellActor* first, ACellActor* second)
{
	if (first && second)
	{
		FGridMatrix& grid = utilities->getGridMatrix();
		FVector2D firstIndices = grid.indices(first->GetActorLocation());
		FVector2D secondIndices = grid.indices(second->GetActorLocation());
		int startX = FMath::RoundToInt(firstIndices.X);
		int column = FMath::RoundToInt(firstIndices.Y);
		int destinyX = FMath::RoundToInt(secondIndices.X);
		if (column == 0 || column == height - 1 || !grid.linked(startX, column) ||
			!grid.linked(destinyX, FMath::RoundToInt(secondIndices.Y)))
		{
			for (int i = startX; i < width && i >= 0; i += startX < destinyX ? 1 : -1)
			{
				if (!grid[i][column])
				{
					spawnActor(AssetType::FLOOR, i, column);
				}
			}
		}
	}
}
void AGridManager::setCellType(ACellActor* cell)
{
	if (cell)
	{
		int randomDamage = FMath::RandRange(1, 3);
		DamageColor damageColor = DamageColor::NONE;
		if (utilities)
		{
			switch (randomDamage)
			{
			case 1:
				damageColor = DamageColor::RED;
				break;
			case 2:
				damageColor = DamageColor::GREEN;
				break;
			case 3:
				damageColor = DamageColor::BLUE;
				break;
			}
		}
		cell->changeColor(damageColor);
	}
}
void AGridManager::spawnActor(AssetType asset, int xIndex, int yIndex)
{
	switch (asset)
	{
	case AssetType::FLOOR:
		if (utilities)
		{
			FGridMatrix& grid = utilities->getGridMatrix();
			if (&grid && grid.inside(xIndex, yIndex))
			{
				FVector cellPosition = FVector(FVector2D(xIndex, yIndex) * offsets, 0.0f);
				ACellActor* cell = instantiateCell(cellPosition);
				cell->lapseTime = changeInterlude;
				setCellType(cell);
				grid[xIndex][yIndex] = cell;
			}
		}
		break;
	case AssetType::WALL:
		FVector wallPosition = FVector(FVector2D(xIndex, yIndex) * offsets, 0.0f);
		AWallActor* wall = GetWorld()->SpawnActor<AWallActor>(AWallActor::StaticClass(), FTransform(wallPosition));
		break;
	}
}
void AGridManager::fillUnlinked(int column)
{
	FGridMatrix& grid = utilities->getGridMatrix();
	if (grid.inside(0, column - 1))
	{
		ACellActor* closer = nullptr;
		ACellActor* cellUnlinked = nullptr;
		for (int firstX = 0; firstX < width; firstX++)
		{
			for (int secondX = 0; secondX < width; secondX++)
			{
				ACellActor* cellPrev = grid[firstX][column - 1];
				ACellActor* cellNext = grid[secondX][column];
				if (cellNext)
				{
					cellUnlinked = cellNext;
				}
				if ((!closer && cellPrev) || (cellUnlinked && cellPrev &&
					FVector::Dist(closer->GetActorLocation(), cellUnlinked->GetActorLocation()) >
					FVector::Dist(cellPrev->GetActorLocation(), cellUnlinked->GetActorLocation())))
				{
					closer = cellPrev;
				}
				fillSpace(cellUnlinked, closer);
			}
		}
	}
}
void AGridManager::setGrid()
{
	if (utilities)
	{
		utilities->setGridMatrix(offsets, width, height);
		FGridMatrix& grid = utilities->getGridMatrix();
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				int horizontalAmount = lineAmount(y, height);
				TArray<int>places = generateSegment(horizontalAmount, width);
				if (places.Contains(x))
				{
					spawnActor(AssetType::FLOOR, x, y);
				}
			}
		}
		scanGrid();
		setWalls();
	}
}
void AGridManager::scanGrid()
{
	if (utilities)
	{
		FGridMatrix& grid = utilities->getGridMatrix();
		if (&grid)
		{
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					fillUnlinked(y);
				}
			}
		}
	}
}
void AGridManager::setWalls()
{
	if (utilities)
	{
		FGridMatrix& grid = utilities->getGridMatrix();
		if (&grid)
		{
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					if (!grid[x][y])
					{
						spawnActor(AssetType::WALL, x, y);
					}
				}
			}
			for (int y = -1; y <= height; y++)
			{
				spawnActor(AssetType::WALL, width, y);
				spawnActor(AssetType::WALL, -1, y);
			}
			for (int x = -1; x <= width; x++)
			{
				spawnActor(AssetType::WALL, x, height);
				spawnActor(AssetType::WALL, x, -1);
			}
		}
	}
}