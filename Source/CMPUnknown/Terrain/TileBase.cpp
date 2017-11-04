// Fill out your copyright notice in the Description page of Project Settings.

#include "CMPUnknown.h"
#include "DrawDebugHelpers.h"
#include "ActorPool.h"
#include "TileBase.h"


// Sets default values
ATileBase::ATileBase()
{
 	
	MinBoxSize = FVector(-2048.0, 0, 64.0);
	MaxBoxSize = FVector(2048.0, -4096.0, 64.0);

	NavigationBoundsOffset = FVector(2048, 0, 0);

	PrimaryActorTick.bCanEverTick = true;

}

void ATileBase::PlaceActors(TSubclassOf<AActor> ToSpawn, FItemVariables ItemVariables) {

	RandomlyPlaceActors(ToSpawn, ItemVariables);

}

void ATileBase::RandomlyPlaceActors(TSubclassOf<AActor> ToSpawn, FItemVariables ItemVariables) {

	int NumberToSpawn = FMath::RandRange(ItemVariables.MinSpawn, ItemVariables.MaxSpawn);

	for (int loop = 0; loop < NumberToSpawn; loop++)
	{
		FSpawnPosition SpawnPosition;
		SpawnPosition.Scale = FMath::RandRange(ItemVariables.MinScale, ItemVariables.MaxScale);
		float NewRadius = SpawnPosition.Scale * ItemVariables.Radius;

		if (FindEmptyLocation(SpawnPosition.Location, NewRadius))
		{
			SpawnPosition.Rotation = FMath::RandRange(-180.0f, 180.0f);
			bool LiveActor = ItemVariables.IsLive;
			PlaceTheActor(ToSpawn, SpawnPosition, LiveActor);

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



void ATileBase::PlaceTheActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition PositionActor, bool IsLive) {
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn);
	if (SpawnedActor) {
		SpawnedActor->SetActorRelativeLocation(PositionActor.Location);
		SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		SpawnedActor->SetActorRotation(FRotator(0, PositionActor.Rotation, 0));
		SpawnedActor->SetActorScale3D(FVector(PositionActor.Scale));

		ItemsArray.Push(SpawnedActor);

		if (IsLive) {
			AICrateArray.Push(SpawnedActor);
		}
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

/// Placing AI

void ATileBase::PlaceAI(TSubclassOf<APawn> ToSpawn, FaiVariables aiVariables) {

	int CrateRange = AICrateArray.Num() * aiVariables.PercentUtilized / 100;
	int NumberToSpawn = FMath::RandRange(aiVariables.MinSpawn, aiVariables.MaxSpawn);

	for (int loop = 0, i = 0; loop < NumberToSpawn; loop++, i++)
	{
		if (i > CrateRange) {
			i = 0;
		}
		FSpawnPosition SpawnPosition;

		SpawnPosition.Location = AICrateArray[i]->GetActorLocation();
		SpawnPosition.Rotation = AICrateArray[i]->GetActorRotation().Yaw;

		SpawnPosition.Scale = FMath::RandRange(aiVariables.MinScale, aiVariables.MaxScale);

		PlaceTheActor(ToSpawn, SpawnPosition);

		// TODO: delay
	}

}

void ATileBase::PlaceTheActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition PositionActor) {

	APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(ToSpawn);
	if (SpawnedPawn) {
		SpawnedPawn->SetActorRelativeLocation(PositionActor.Location + FVector(0, 0, 200));
		SpawnedPawn->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		SpawnedPawn->SetActorRotation(FRotator(0, PositionActor.Rotation, 0));
		SpawnedPawn->SpawnDefaultController();
		SpawnedPawn->Tags.Add(FName("Enemy"));

		// TODO: setup health on AI

		AIArray.Add(SpawnedPawn);
	}

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

	for (int i = 0; i < AIArray.Num(); i++) {
		AIArray[i]->Destroy();
	}

	UE_LOG(LogTemp, Warning, TEXT("%s End play"), *GetName());
	if (Pool != nullptr && NavMeshBoundsVolume != nullptr) {
		Pool->Return(NavMeshBoundsVolume);
	}
}

// Called every frame
void ATileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


/// Navigation Code

void ATileBase::SetPool(UActorPool* InPool) {
	Pool = InPool;
	UE_LOG(LogTemp, Warning, TEXT("Setting pool %s"), *(InPool->GetName()));

	PositionNavMeshBoundsVolume();
}

void ATileBase::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = Pool->Checkout();
	if (NavMeshBoundsVolume == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Not enough actors in pool!!!"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Checked out: %s"), *NavMeshBoundsVolume->GetName());
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavigationBoundsOffset);


	// update navigation system
	GetWorld()->GetNavigationSystem()->Build();
}



