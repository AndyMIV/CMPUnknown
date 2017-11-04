// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CMPUnknownGameMode.h"
#include "CMPUnknownGameMode_Expanded.generated.h"

/**
 * 
 */
UCLASS()
class CMPUNKNOWN_API ACMPUnknownGameMode_Expanded : public ACMPUnknownGameMode
{
	GENERATED_BODY()
	
public:
	ACMPUnknownGameMode_Expanded();

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void PopulateBoundsVolumePool();

private:
	void AddToPool(class ANavMeshBoundsVolume *VolumeToAdd);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pool")
		class UActorPool* NavMeshBoundsVolumePool;
	
	
};
