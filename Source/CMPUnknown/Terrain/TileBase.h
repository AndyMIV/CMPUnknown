// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TileBase.generated.h"



USTRUCT()
struct FSpawnPosition {
	GENERATED_USTRUCT_BODY()


	FVector Location;
	float Rotation;
	float Scale;
};

// BlueprintType not necesarilly needed. just split the pin in BP
USTRUCT(BlueprintType)
struct FItemVariables {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Setup")
		int MinSpawn = 1;

	UPROPERTY(BlueprintReadWrite, Category = "Setup")
		int MaxSpawn = 1;

	UPROPERTY(BlueprintReadWrite, Category = "Setup")
		float Radius = 500;

	UPROPERTY(BlueprintReadWrite, Category = "Setup")
		float MaxScale = 1;

	UPROPERTY(BlueprintReadWrite, Category = "Setup")
		float MinScale = 1;

	UPROPERTY(BlueprintReadWrite, Category = "Setup")
		bool IsLive = false;


};

USTRUCT(BlueprintType)
struct FaiVariables {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Setup")
		int Health = 100;

	UPROPERTY(BlueprintReadWrite, Category = "Setup")
		float MaxScale = 1;

	UPROPERTY(BlueprintReadWrite, Category = "Setup")
		float MinScale = 1;

	UPROPERTY(BlueprintReadWrite, Category = "Setup")
		int PercentUtilized = 100;

	UPROPERTY(BlueprintReadWrite, Category = "Setup")
		bool isConstant = 0;


};

class UActorPool;

UCLASS()
class CMPUNKNOWN_API ATileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ATileBase();


	// Blueprint Function
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void PlaceActors(TSubclassOf<AActor> ToSpawn, FItemVariables ItemVariables);

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void PlaceAI(TSubclassOf<APawn> ToSpawn, FaiVariables aiVariables);

	UFUNCTION(BlueprintCallable, Category = "Pool")
		void SetPool(UActorPool* Pool);

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		FVector MinBoxSize;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		FVector MaxBoxSize;

	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
		FVector NavigationBoundsOffset;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		int YTileSize;

	
private:
	bool CastSphere(FVector Location, float Radius);
	bool FindEmptyLocation(FVector& OutLocation, float Radius);

	void RandomlyPlaceActors(TSubclassOf<AActor> ToSpawn, FItemVariables ItemVariables);
	void PlaceTheActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition PositionActor, bool IsLive);
	void PlaceTheActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition PositionActor);

	int ConstantContainer = 0;
	void ChangeConstant();

	TArray<AActor*> ItemsArray;
	TArray<APawn*> AIArray;
	TArray<AActor*> AICrateArray;

	void PositionNavMeshBoundsVolume();
	AActor* NavMeshBoundsVolume = nullptr;
	UActorPool* Pool;

};
