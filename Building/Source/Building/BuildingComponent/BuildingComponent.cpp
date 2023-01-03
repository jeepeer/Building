#include "BuildingComponent.h"
#include "Building.h"
#include "Building/BuildingCharacter.h"
#include "Camera/CameraComponent.h"

UBuildingComponent::UBuildingComponent()
{
	auto owner = GetOwner();
	spawnPosition = FVector(0.f, 0.f, 0.f);
	spawnRotation = FRotator(0.f, 0.f, 0.f);
	maxSpawnPositionRange = FVector(0.f, 0.f, 0.f);
	minSpawnPositionRange = FVector(0.f, 0.f, 0.f);
}

void UBuildingComponent::PlaceBuilding()
{
	// check that there's no building currently
	// if no place building
	// else ignore

	if (building->BuildingPlaced() == 1) // bool ? array ?
	{
		// building IS placed
		return;
	}

	// if building IS BEING PLACED
	// and the buildings ground check is ok
	// place the building
	// else return
	
	// if the building HAS NOT been placed
	// spawn building
	FActorSpawnParameters spawnInfo;
	GetWorld()->SpawnActor<ABuilding>(GetSpawnPosition(), spawnRotation, spawnInfo);
}

FVector UBuildingComponent::GetSpawnPosition()
{
	// line trace to see where player is aiming
	// if it's too far set spawnPosition to max
	// too close set it to min
	// else return hit pos 

	FVector playerLocation = GetOwner()->GetActorLocation();
	float range = FVector::Distance(playerLocation, GetLineTraceImpactPoint());
	if (maxRange >= range) // switch statement ? 
	{
		spawnPosition = maxSpawnPositionRange;
	}
	else if (minRange <= range)
	{
		spawnPosition = minSpawnPositionRange;
	}
	else
	{
		spawnPosition = GetLineTraceImpactPoint();
	}

	return spawnPosition;
}


FVector UBuildingComponent::GetLineTraceImpactPoint()
{
	// line trace and get impact point
	FHitResult hit;
	ABuildingCharacter* playerCharacter = Cast<ABuildingCharacter>(GetOwner());
	auto camera = playerCharacter->GetFollowCamera();
	FVector start = camera->GetForwardVector();

	float magnitude = 10.f;
	FVector end = start * magnitude;
	FCollisionQueryParams QueryParams;
	if (GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_WorldStatic, QueryParams))
	{
		return hit.ImpactPoint;
	}
}