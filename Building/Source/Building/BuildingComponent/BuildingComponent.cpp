#include "BuildingComponent.h"
#include "BuildingBox.h"
#include "Building/BuildingCharacter.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"

UBuildingComponent::UBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CUBE"));
	
	// Load Cube Mesh
	cubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object;
	
	// Load Materials
	redMaterial = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Engine/EditorMaterials/WidgetMaterial_X'")).Object;
	greenMaterial = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Engine/EditorMaterials/WidgetMaterial_Y'")).Object;
	
	// Set Mesh
	cube->SetStaticMesh(cubeMesh);

	// Initializing variables
	owner = GetOwner();
	state = dead;
	bCanBuild = false;
	spawnPosition = FVector(0.f, 0.f, 0.f);
	spawnRotation = FRotator(0.f, 0.f, 0.f);
	defaultPosition = FVector::UpVector * -1000.f;

	// Set cube location under the map
	cube->SetWorldLocation(defaultPosition);
}

void UBuildingComponent::HandleBuildingAction()
{
	// Gets called on right click
	switch (state)
	{
	// Checks to see if you're able to construct a building
	case constructing:
	{
		ConstructingBuilding();
		break;
	}
	// WIP
	case dead:
	{
		DestroyBuilding();
		break;
	}
	// WIP
	case alive: 
	{
		BuiltBuilding();
		break;
	}
	}
}

void UBuildingComponent::ConstructingBuilding()
{
	if (bCanBuild == false) { return; }

	ConstructBuilding();
	state = alive;
}

void UBuildingComponent::ConstructBuilding()
{
	FActorSpawnParameters spawnInfo;
	// Spawn the building where the cube was placed
	ABuildingBox* test = GetWorld()->SpawnActor<ABuildingBox>(CubePosition(), spawnRotation, spawnInfo);

	// Reset the cube's position
	cube->SetWorldLocation(defaultPosition);
}

void UBuildingComponent::DestroyBuilding()
{
	// Set state to constructing
	// Next HandleBuildingAction will go to constructing
	state = constructing;
}

void UBuildingComponent::BuiltBuilding()
{
	// WIP
	return;
}

void UBuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (state == constructing && cube != nullptr)
	{
		SetCubeMaterial();
		SetCubeRotation();
		cube->SetWorldLocation(CubePosition());
	}
}

void UBuildingComponent::SetCubeMaterial()
{
	GetCubeMaterialState();

	switch (materialState)
	{
	case green:
	{
		cube->SetMaterial(0, greenMaterial);
		materialState = ignore;
		break;
	}
	case red:
	{
		cube->SetMaterial(0, redMaterial);
		materialState = ignore;
		break;
	}
	}
}

void UBuildingComponent::GetCubeMaterialState()
{
	// LineTrace setup
	FVector start = cube->GetComponentLocation();
	float length = -200.f;
	FVector end = start + FVector::UpVector * length;

	FVector startLeft = cube->GetComponentLocation() + (cube->GetRightVector() * -50.f)
		+ (cube->GetForwardVector() * -70.f);
	FVector endLeft = startLeft + cube->GetForwardVector() * 140.f;

	FVector startRight = cube->GetComponentLocation() + (cube->GetRightVector() * 50.f)
		+ (cube->GetForwardVector() * -70.f);
	FVector endRight = startRight + cube->GetForwardVector() * 140.f;

	// LineTrace checks if there is anything under the cube,
	// infront or behind the cube on the left and right side
	bool bCanBePlaced = LineTraceHitResult(startLeft, endLeft) == false
		&& LineTraceHitResult(startRight, endRight) == false
		&& LineTraceHitResult(start, end);

	if (bCanBePlaced)
	{
		materialState = green;
		bCanBuild = true;
	}
	else
	{
		materialState = red;
		bCanBuild = false;
	}
}

void UBuildingComponent::SetCubeRotation()
{
	cube->SetRelativeRotation(owner->GetActorRotation());
}

bool UBuildingComponent::LineTraceHitResult(FVector start, FVector end)
{
	FHitResult hit;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(owner);
	QueryParams.AddIgnoredComponent(cube);
	if (GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_WorldStatic, QueryParams))
	{
		return true;
	}

	return false;
}

FVector UBuildingComponent::CubePosition() 
{
	FVector playerForwardVector = owner->GetActorLocation() + owner->GetActorForwardVector() * 200.f;
	playerForwardVector.Z = GetNewZPosition();

	return playerForwardVector;
}

float UBuildingComponent::GetNewZPosition() 
{
	FHitResult hit;
	FVector start = owner->GetActorLocation() + owner->GetActorForwardVector() * 200.f;
	
	float length = -200.f;
	FVector end = start + FVector::UpVector * length;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(owner);

	if (GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_WorldStatic, QueryParams))
	{
		float newZ = hit.ImpactPoint.Z + 50.f;
		tempZ = newZ;
		return newZ;
	}

	return tempZ;
}