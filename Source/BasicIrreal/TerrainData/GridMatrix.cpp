#include "GridMatrix.h"

FGridColumn::FGridColumn(int height)
{
	column.SetNum(height);
}
FGridMatrix::FGridMatrix()
{
	
}
FGridMatrix::FGridMatrix(FVector2D offsets, int width, int height)
{
	w = width;
	h = height;
	rows.SetNum(w);
	for (int i = 0; i < w; ++i)
	{
		rows[i] = FGridColumn(h);
	}
	offsetsVector = offsets;
}
ACellActor* FGridMatrix::get(FTransform transform) const
{
	ACellActor* cell = nullptr;
	const FVector2D index2D = indices(transform.GetLocation());
	if (inside(index2D.X, index2D.Y))
	{
		cell = rows[(int)index2D.X].column[(int)index2D.Y];
	}
	return cell;
}
ACellActor* FGridMatrix::get(FVector position)const
{
	ACellActor* cell = nullptr;
	const FVector2D index2D = indices(position);
	if (inside(index2D.X, index2D.Y))
	{
		cell = rows[(int)index2D.X].column[(int)index2D.Y];
	}
	return cell;
}
const FVector2D FGridMatrix::indices(FVector position)const
{
	FVector2D tmpVector = FVector2D(position.X, position.Y) / offsetsVector;
	FVector2D index2D = tmpVector;
	if (inside(tmpVector.X, tmpVector.Y))
	{
		index2D = FVector2D(FMath::RoundToFloat(tmpVector.X), FMath::RoundToFloat(tmpVector.Y));
	}
	else
	{
		if (index2D.X < 0)
		{
			index2D.X = 0.0f;
		}
		else if (index2D.X >= w)
		{
			index2D.X = w - 1;
		}
		if (index2D.Y < 0)
		{
			index2D.Y = 0.0f;
		}
		else if (index2D.Y >= h)
		{
			index2D.Y = h - 1;
		}
		index2D = FVector2D(FMath::RoundToFloat(index2D.X), FMath::RoundToFloat(index2D.Y));
	}
	return index2D;
}
bool const FGridMatrix::inside(int x, int y) const
{
	bool insideRange = x >= 0.0f && x < w && y >= 0 && y < h;
	return insideRange;
}
const bool FGridMatrix::linked(int x, int y) const
{
	bool linkedCell = false;
	if (inside(x, y) && rows[x].column[y])
	{
		if (inside(x, y - 1))
		{
			linkedCell = (bool)rows[x].column[y - 1];
		}
		else if (inside(x, y + 1))
		{
			linkedCell = (bool)rows[x].column[y + 1];
		}
		else if (inside(x - 1, y))
		{
			linkedCell = (bool)rows[x - 1].column[y];
		}
		else if (inside(x + 1, y))
		{
			linkedCell = (bool)rows[x + 1].column[y];
		}
	}
	return linkedCell;
}
TArray<ACellActor*>& FGridMatrix::operator[](int index)
{
	ensure(index >= 0 && index < rows.Num());
	return rows[index].column;
}