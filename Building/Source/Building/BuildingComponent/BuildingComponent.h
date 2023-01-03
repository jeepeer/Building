#pragma once
#include "Components/ActorComponent.h"
#include "BuildingComponent.generated.h"

class ABuilding;

UCLASS()
class UBuildingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	
	// shoot 
	// if there is flat ground
	// show green box
	// place box
	// else 
	// show red box

	UBuildingComponent();

	void PlaceBuilding();

	FVector GetLineTraceImpactPoint();
	void PlaceBuilding();

	FVector GetSpawnPosition();
	FVector spawnPosition;
	FVector maxSpawnPositionRange;
	FVector minSpawnPositionRange;

	float maxRange;
	float minRange;

	UPROPERTY()
	ABuilding* building;
	FRotator spawnRotation;


};