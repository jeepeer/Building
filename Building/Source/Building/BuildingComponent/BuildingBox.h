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

	enum State
	{
		dead,
		alive,
		constructing
	};

private:
	
	ABuildingBox();

	UPROPERTY(EditAnywhere)
	UBoxComponent* buildingBody;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* buildingMesh;
};