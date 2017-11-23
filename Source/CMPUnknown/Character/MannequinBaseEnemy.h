// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MannequinBaseEnemy.generated.h"

UCLASS()
class CMPUNKNOWN_API AMannequinBaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMannequinBaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//Custom Functions
	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
		void SetHealth(float HealthInput);


private: 
	float Health = 0;
	
	
};
