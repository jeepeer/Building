#include "BuildingBox.h"
#include "Components/BoxComponent.h"

class UBoxComponent;

ABuildingBox::ABuildingBox()
{
	buildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	// Load Cube Mesh
	UStaticMesh* cubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object;
	buildingMesh->SetStaticMesh(cubeMesh);
	
}