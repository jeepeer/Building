#pragma once
#include "GameFramework/Actor.h"
#include "Building.generated.h"

class UBoxComponent;

UCLASS()
class ABuilding : public AActor
{
	GENERATED_BODY()

public:

	int BuildingPlaced() { return 1; } // states?

private:
	
	ABuilding();

	// get spawnbox color for the spawning

	// building interaction
	// opens UI
	// building can be upgraded with scrap
	// upgrade state? multiple upgrades? different sizes?


	UBoxComponent* spawnBox;
	UBoxComponent* buildingBody;

};