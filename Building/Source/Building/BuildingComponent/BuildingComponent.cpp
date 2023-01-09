#include "BuildingComponent.h"
#include "BuildingBox.h"
#include "Building/BuildingCharacter.h"
#include "Camera/CameraComponent.h"

UBuildingComponent::UBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CUBE"));
	// Load Cube Mesh
	UStaticMesh* cubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object;
	// load more meshes to swap between ?
	cube->SetStaticMesh(cubeMesh); // color change mebe?
	auto pe = FVector::UpVector * - 1000.f;
	cube->SetWorldLocation(pe);

	owner = GetOwner();
	
	spawnPosition = FVector(0.f, 0.f, 0.f);
	spawnRotation = FRotator(0.f, 0.f, 0.f);
	maxSpawnPositionRange = FVector(0.f, 0.f, 0.f);
	minSpawnPositionRange = FVector(0.f, 0.f, 0.f);

	state = dead;
}

void UBuildingComponent::PlaceBuilding()
{
	// if building is under construction
	// and there's no collision issues
	// place

	switch (state)
	{
	case constructing:
	{
		FActorSpawnParameters spawnInfo;
		ABuildingBox* test = GetWorld()->SpawnActor<ABuildingBox>(GetSpawnPosition(), spawnRotation, spawnInfo);
		state = alive;
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, "CONSTRUCTING");
		break;
	}
	case dead:
	{
		// move cube 
		// green if placeable
		// red if not
		//constructing;
		cube->SetWorldLocation(FVector::UpVector * 100.f);
		state = constructing;
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, "DEAD");
		break;
	}
	case alive:
	{
		// if the building is alive then there's nothing to do?
		// or menu ?
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, "ALIVE");
		return;
		break;
	}
	}
}

FVector UBuildingComponent::GetSpawnPosition()
{
	// line trace too see if there is any collision 
	// if there is collision distance is greater than min range
	// then take collision hit location - size of building

	if (GetLineTraceImpactPoint())
	{
		return FVector::ZeroVector;
	}

	FVector newPos;
	newPos = owner->GetActorLocation() + owner->GetActorForwardVector() * 1000.f;
	newPos.Z += 100.f;
	return newPos;
}


void UBuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if state is correct
	// then move the cube according to the camera / actor
	if (state == constructing && cube != nullptr)
	{
		// only movement
		cube->SetWorldLocation(CubePosition());
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Red, "tick");
	}
}

FVector UBuildingComponent::CubePosition()
{
	FVector playerForwardVector = owner->GetActorLocation() + owner->GetActorForwardVector() * 200.f;

	playerForwardVector.Z = 200.f;

	return playerForwardVector;
}

bool UBuildingComponent::GetLineTraceImpactPoint()
{
	// line trace and get impact point
	FHitResult hit;
	FVector start = owner->GetActorLocation() + owner->GetActorForwardVector();

	float magnitude = 200.f;
	FVector end = start * magnitude;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(owner);

	if (GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_WorldStatic, QueryParams))
	{
		float dis = hit.Distance;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "HIT");
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::SanitizeFloat(dis));
		return true;
	}

	// return some default spawn point ?
	return false;
}