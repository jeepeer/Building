#pragma once
#include "Components/ActorComponent.h"
#include "BuildingComponent.generated.h"

class ABuildingBox;

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

	void TickComponent
	(
		float DeltaTime,
		enum ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction
	);

	bool GetLineTraceImpactPoint(); // Look for collision?

	FVector GetSpawnPosition();
	FVector spawnPosition;
	FVector maxSpawnPositionRange;
	FVector minSpawnPositionRange;

	FVector CubePosition();
	
	float maxRange;
	float minRange;

	UPROPERTY()
	ABuildingBox* building;
	FRotator spawnRotation;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* cube;

	int state;
	AActor* owner;

	enum BuildingState
	{
		constructing,
		dead,
		alive
	};

public:

	void PlaceBuilding(); // handle building action

};