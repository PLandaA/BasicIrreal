#include "PathsHeader.h"

const TCHAR* FPathsHeader::assetPathChar(AssetType asset)
{
	const TCHAR* path = TEXT("");
	switch (asset)
	{
	case AssetType::FLOOR:
		path = TEXT("/Script/Engine.StaticMesh'/Game/Models3D/FloorModel/Floor.Floor'");
		break;
	case AssetType::WALL:
		path = TEXT("/Script/Engine.StaticMesh'/Game/Models3D/WallModel/Wall_Joined.Wall_Joined'");
		break;
	case AssetType::PLAYER:
		path = TEXT("");
		break;
	case AssetType::ENEMY1:
		path = TEXT("");
		break;
	case AssetType::ENEMY2:
		path = TEXT("");
		break;
	case AssetType::ENEMY3:
		path = TEXT("");
		break;
	default:
		path = TEXT("");
		break;
	}
	return path;
}
const TCHAR* FPathsHeader::colorTypeChar()
{
	const TCHAR* name = TEXT("Damage Color");
	return name;
}
const FString FPathsHeader::assetPathString(AssetType asset)
{
	return assetPathChar(asset);
}

const FName FPathsHeader::colorTypeName()
{
	return colorTypeChar();
}