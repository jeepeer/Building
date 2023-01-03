#include "Building.h"

class UBoxComponent;

ABuilding::ABuilding()
{
	spawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("spawnBox"));
	spawnBox->SetupAttachment(RootComponent);

	buildingBody = CreateDefaultSubobject<UBoxComponent>(TEXT("buildingBody"));
	buildingBody->SetupAttachment(RootComponent);
}