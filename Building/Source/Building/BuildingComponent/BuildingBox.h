#pragma once
#include "GameFramework/Actor.h"
#include "BuildingBox.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class ABuildingBox : public AActor
{
	GENERATED_BODY()

public:

	int BuildingPlaced() { return 1; } // states?

	enum State
	{
		dead,
		alive,
		constructing
	};

private:
	
	ABuildingBox();

	// get spawnbox color for the spawning

	// building interaction
	// opens UI
	// building can be upgraded with scrap
	// upgrade state? multiple upgrades? different sizes?

	UPROPERTY(EditAnywhere)
	UBoxComponent* buildingBody;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* buildingMesh;
};