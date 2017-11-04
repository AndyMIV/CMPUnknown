// Fill out your copyright notice in the Description page of Project Settings.

#include "CMPUnknown.h"
#include "MannequinBaseEnemy.h"


// Sets default values
AMannequinBaseEnemy::AMannequinBaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMannequinBaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMannequinBaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMannequinBaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


int  AMannequinBaseEnemy::GetHealth() {
	return Health;
}


void  AMannequinBaseEnemy::SetHealth(int Health) {
	this->Health = Health;
}

