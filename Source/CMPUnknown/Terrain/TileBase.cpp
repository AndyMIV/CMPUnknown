// Fill out your copyright notice in the Description page of Project Settings.

#include "CMPUnknown.h"
#include "DrawDebugHelpers.h"
#include "TileBase.h"


// Sets default values
ATileBase::ATileBase()
{
 	
	MinBoxSize = FVector(-2048.0, 0, 64.0);
	MaxBoxSize = FVector(2048.0, -4096.0, 64.0);

	PrimaryActorTick.bCanEverTick = true;

}

void ATileBase::PlaceActors(TSubclassOf<AActor> ToSpawn, FInputVariables InputVariables) {

	RandomlyPlaceActors(ToSpawn, InputVariables);

}

template<class T>
void ATileBase::RandomlyPlaceActors(TSubclassOf<T> ToSpawn, FInputVariables InputVariables) {

	int NumberToSpawn = FMath::RandRange(InputVariables.MinSpawn, InputVariables.MaxSpawn);

	for (int loop = 0; loop < NumberToSpawn; loop++)
	{
		FSpawnPosition SpawnPosition;
		SpawnPosition.Scale = FMath::RandRange(InputVariables.MinScale, InputVariables.MaxScale);
		float NewRadius = SpawnPosition.Scale * InputVariables.Radius;

		if (FindEmptyLocation(SpawnPosition.Location, NewRadius))
		{
			SpawnPosition.Rotation = FMath::RandRange(-180.0f, 180.0f);
			PlaceTheActor(ToSpawn, SpawnPosition);

		}

	}


}

bool ATileBase::FindEmptyLocation(FVector& SpawnPoint, float Radius) {
	// Min and max of fvector (magic numbers)
	auto Bounds = FBox(MinBoxSize, MaxBoxSize);

	int MAX_ATTEMPTS = 100;
	for (size_t i = 0; i < MAX_ATTEMPTS; i++) {
		FVector CandidatePoint = FMath::RandPointInBox(Bounds);
		if (!CastSphere(CandidatePoint, Radius)) {
			SpawnPoint = CandidatePoint;
			return true;
		}
	}


	return false;
}



void ATileBase::PlaceTheActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition PositionActor) {
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn);
	if (SpawnedActor) {
		SpawnedActor->SetActorRelativeLocation(PositionActor.Location);
		SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		SpawnedActor->SetActorRotation(FRotator(0, PositionActor.Rotation, 0));
		SpawnedActor->SetActorScale3D(FVector(PositionActor.Scale));

		ItemsArray.Push(SpawnedActor);
	}

}

bool ATileBase::CastSphere(FVector Location, float Radius) {

	FHitResult HitResult;

	// 
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);

	// we use channel so we can configuew what it hits later
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		GlobalLocation, // was just Location, replaced to make positions global
		GlobalLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1, // find & configure in system folder: config/DefaultEngine.ini
		FCollisionShape::MakeSphere(Radius));

	return HasHit;
}



// Called when the game starts or when spawned
void ATileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void  ATileBase::EndPlay(const EEndPlayReason::Type EndPlayReason) {

	for (int i = 0; i < ItemsArray.Num(); i++) {
		ItemsArray[i]->Destroy();
	}
}

// Called every frame
void ATileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

