#pragma once
#include "Components/ActorComponent.h"
#include "BuildingComponent.generated.h"

class ABuildingBox;

UCLASS()
class UBuildingComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	UBuildingComponent();

	void TickComponent
	(
		float DeltaTime,
		enum ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction
	);
	float GetNewZPosition();
	FVector CubePosition();
	void ConstructingBuilding();
	void ConstructBuilding();
	void DestroyBuilding();
	void BuiltBuilding();
	void SetCubeMaterial();
	void GetCubeMaterialState();
	void SetCubeRotation();
	bool LineTraceHitResult(FVector start, FVector end);

	FVector spawnPosition;
	FVector defaultPosition;
	FRotator spawnRotation;

	bool bCanBuild;
	
	int state;
	int materialState;
	float tempZ;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* cube;
	UPROPERTY()
	ABuildingBox* building;

	AActor* owner;
	UStaticMesh* cubeMesh;
	UMaterial* redMaterial;
	UMaterial* greenMaterial;

	enum BuildingState
	{
		constructing,
		dead,
		alive
	};

	enum MaterialState
	{
		green,
		red,
		ignore
	};

public:

	void HandleBuildingAction(); // handle building action
};