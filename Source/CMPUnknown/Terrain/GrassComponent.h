// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "GrassComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CMPUNKNOWN_API UGrassComponent : public UHierarchicalInstancedStaticMeshComponent
{
	GENERATED_BODY()
	
	UGrassComponent();

public:

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SpawnGrass(int SpawnCount = 10);
	
	
};
