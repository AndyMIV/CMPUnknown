// Andy Montoya 2017

#include "CMPUnknown.h"
#include "OpenDoor.h"
#include "Engine/TriggerVolume.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();

	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"), *GetOwner()->GetName());
	}

	Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);



	// poll the trigger volume every frame. 
	if (CheckIsPlayer()) {  // TODO make into a parameter
		OnOpenRequest.Broadcast();
	}
	else {
		OnCloseRequest.Broadcast();
	}
	// if the actor that opens is in the volume, then we open the door.

	// check if its time to close the door:

}

bool UOpenDoor::CheckIsPlayer() {

	UE_LOG(LogTemp, Warning, TEXT("Checking Player..."));
	if (!PressurePlate) { return false; }

	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OverlappingActors);
	// iterate through them adding their masses
	// actor does not change
	for (const auto* element : OverlappingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("Iterating"));
		if (element == Player) {
			UE_LOG(LogTemp, Warning, TEXT("I am the player!!!"));
			return true;
		}
		else
			return false;

	}
	return false;

}
