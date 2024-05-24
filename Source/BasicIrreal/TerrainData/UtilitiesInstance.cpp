#include "UtilitiesInstance.h"
#include "PathsHeader.h"
#include "CellActor.h"

UUtilitiesInstance::UUtilitiesInstance()
{
	firstDamage = FColor::Red;
	secondDamage = FColor::Green;
	thirdDamage = FColor::Blue;
}

const FString UUtilitiesInstance::assetPath(AssetType asset)const
{
	FString path = FPathsHeader::assetPathString(asset);
	return path;
}
const FName UUtilitiesInstance::damageColorName()const
{
	return FPathsHeader::colorTypeName();
}
FVector UUtilitiesInstance::validCoord(FVector position) const
{
	FVector validCoord = position;
	if (gridMatrix)
	{
		FVector2D positiveIndices = gridMatrix->indices(position);
		FVector2D negativeIndices = positiveIndices;
		ACellActor* cell = gridMatrix->get(position);
		while (!cell)
		{
			if (!obstacleByIndices(positiveIndices.X + 1, positiveIndices.Y))
			{
				cell = (*gridMatrix)[positiveIndices.X + 1][positiveIndices.Y];
			}
			else if (!obstacleByIndices(positiveIndices.X, positiveIndices.Y + 1))
			{
				cell = (*gridMatrix)[positiveIndices.X][positiveIndices.Y + 1];
			}
			else if (!obstacleByIndices(positiveIndices.X + 1, positiveIndices.Y + 1))
			{
				cell = (*gridMatrix)[positiveIndices.X + 1][positiveIndices.Y + 1];
			}
			else if (!obstacleByIndices(negativeIndices.X - 1, negativeIndices.Y))
			{
				cell = (*gridMatrix)[negativeIndices.X - 1][negativeIndices.Y];
			}
			else if (!obstacleByIndices(negativeIndices.X, negativeIndices.Y - 1))
			{
				cell = (*gridMatrix)[negativeIndices.X][negativeIndices.Y - 1];
			}
			else if (!obstacleByIndices(negativeIndices.X - 1, negativeIndices.Y - 1))
			{
				cell = (*gridMatrix)[negativeIndices.X - 1][negativeIndices.Y - 1];
			}
			positiveIndices += FVector2D::One();
			negativeIndices -= FVector2D::One();
		}
		validCoord = cell->GetActorLocation();
		validCoord.Z = 300.0f;
	}
	return validCoord;
}
FLinearColor UUtilitiesInstance::damageColorByType(DamageColor colorType)const
{
	FLinearColor damageColor = FColor::Black;
	switch (colorType)
	{
	case DamageColor::RED:
		damageColor = firstDamage;
		break;
	case DamageColor::GREEN:
		damageColor = secondDamage;
		break;
	case DamageColor::BLUE:
		damageColor = thirdDamage;
		break;
	}
	return damageColor;
}

DamageColor UUtilitiesInstance::damageTypeByColor(FLinearColor color)const
{
	DamageColor damageColor = DamageColor::NONE;
	if (color == firstDamage)
	{
		damageColor = DamageColor::RED;
	}
	else if (color == secondDamage)
	{
		damageColor = DamageColor::GREEN;
	}
	else if (color == thirdDamage)
	{
		damageColor = DamageColor::BLUE;
	}
	return damageColor;
}

DamageColor UUtilitiesInstance::damageTypeByTransform(FTransform transform)const
{
	DamageColor color = DamageColor::NONE;
	if (gridMatrix)
	{
		color = damageTypeByCoord(transform.GetLocation());
	}
	return color;
}
DamageColor UUtilitiesInstance::damageTypeByCoord(FVector position)const
{
	DamageColor color = DamageColor::NONE;
	if (gridMatrix)
	{
		FVector2D offsets = gridMatrix->offsetsVector;
		FVector2D indices = gridMatrix->indices(position);
		FVector currentCoord(offsets * indices, 0.0f);
		int negativeX = indices.X;
		int negativeY = indices.Y;
		if (obstacleByCoord(currentCoord))
		{
			for (int y = indices.Y; y < gridMatrix->h || negativeY >= 0; y++)
			{
				for (int x = indices.X; x < gridMatrix->w || negativeX >= 0; x++)
				{
					FVector positiveCoord = FVector(offsets.X * x, offsets.Y * y, 0.0f);
					FVector negativeCoord = FVector(offsets.X * negativeX, offsets.Y * negativeY, 0.0f);
					if (!obstacleByCoord(positiveCoord))
					{
						return gridMatrix->get(positiveCoord)->damageType();
					}
					else if (!obstacleByCoord(negativeCoord))
					{
						return gridMatrix->get(negativeCoord)->damageType();
					}
					negativeX--;
				}
				negativeY--;
				negativeX = 0;
			}
		}
		color = damageTypeByColor(gridMatrix->get(currentCoord)->getColor());
	}
	return color;
}
FVector UUtilitiesInstance::minLimits() const
{
	FVector min;
	if (gridMatrix)
	{
		min = FVector(gridMatrix->offsetsVector * FVector2D(0.0f, 0.0f), 0.0f);
	}
	return min;
}
FVector UUtilitiesInstance::maxLimits() const
{
	FVector max;
	if (gridMatrix)
	{
		max = FVector(gridMatrix->offsetsVector * FVector2D(gridMatrix->w - 1, gridMatrix->h - 1), 0.0f);
	}
	return max;
}
const bool UUtilitiesInstance::obstacleByCoord(FVector position)const
{
	bool isObstacle = true;
	if (gridMatrix)
	{
		isObstacle = !gridMatrix->get(position);
	}
	return isObstacle;
}
const bool UUtilitiesInstance::obstacleByIndices(int xIndex, int yIndex)const
{
	bool isObstacle = true;
	if (gridMatrix && gridMatrix->inside(xIndex, yIndex))
	{
		isObstacle = !(*gridMatrix)[xIndex][yIndex];
	}
	return isObstacle;
}
void UUtilitiesInstance::setGridMatrix(FVector2D offsets, int width, int height)
{
	gridMatrix = new FGridMatrix(offsets, width, height);
}
FGridMatrix& UUtilitiesInstance::getGridMatrix()
{
	return *gridMatrix;
}