// Fill out your copyright notice in the Description page of Project Settings.

#include "CMPUnknown.h"
#include "Kismet/KismetMathLibrary.h"
#include "GrassComponent.h"

UGrassComponent::UGrassComponent()
{
	SetCollisionProfileName(TEXT("NoCollision"));
}

void UGrassComponent::SpawnGrass(int SpawnCount) {
	auto Bounds = FBox(FVector(-2048.0, 0.0, 64.0), FVector(2048.0, -4096, 64.0));
	for (int i = 0; i < SpawnCount; i++) {
		FVector Randomized = FMath::RandPointInBox(Bounds);
		FTransform URandomized = UKismetMathLibrary::Conv_VectorToTransform(Randomized);
		AddInstance(URandomized);
	}
}
