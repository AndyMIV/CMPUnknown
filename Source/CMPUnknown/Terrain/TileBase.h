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
struct FInputVariables {
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


};

UCLASS()
class CMPUNKNOWN_API ATileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ATileBase();


	// Blueprint Function
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void PlaceActors(TSubclassOf<AActor> ToSpawn, FInputVariables InputVariables);

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		FVector MinBoxSize;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		FVector MaxBoxSize;

	
private:
	bool CastSphere(FVector Location, float Radius);
	bool FindEmptyLocation(FVector& OutLocation, float Radius);

	TArray<AActor*> ItemsArray;

	template<class T>
	void RandomlyPlaceActors(TSubclassOf<T> ToSpawn, FInputVariables InputVariables);
	void PlaceTheActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition PositionActor);

};
