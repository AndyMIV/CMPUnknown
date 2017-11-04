// Fill out your copyright notice in the Description page of Project Settings.

#include "CMPUnknown.h"
#include "ActorPool.h"


// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


AActor* UActorPool::Checkout() {
	if (Pool.Num() == 0) {
		return nullptr; // nothing in the pool to take
	}
	UE_LOG(LogTemp, Warning, TEXT("Checking out"));
	return  Pool.Pop();
}


void UActorPool::Return(AActor* ActorToReturn) {
	if (ActorToReturn == nullptr) {
		return;
	}
	Pool.Push(ActorToReturn);
}


void UActorPool::Add(AActor* ActorToAdd) {
	if (ActorToAdd == nullptr) {
		return;
	}
	Pool.Push(ActorToAdd);


	for (int i = 0; i < Pool.Num(); i++) {
		AActor* temp = Pool[i];
		UE_LOG(LogTemp, Warning, TEXT("The Pool has: %s"), *(temp->GetName()));
	}

}