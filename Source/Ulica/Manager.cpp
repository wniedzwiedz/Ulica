// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>


// Sets default values
AManager::AManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	nextSpawn = 0.0f;

}

// Called when the game starts or when spawned
void AManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (Cars.Num() > 0) {
		//remove first car if it's at the end

		if (Cars[0]->GetTargetLocation().X > 3000) {
			Cars[0]->Destroy();
			Cars.RemoveAt(0);
		}
		else {
			Cars[0]->SpeedUp();
		}
		
		float Distance;
		//check distances
		for (int32 Index = 0; Index != Cars.Num()-1; ++Index)
		{
			Distance = Cars[Index]->GetTargetLocation().X - Cars[Index + 1]->GetTargetLocation().X;
			if (Distance < 3*Cars[Index + 1]->GetSpeed() || Distance < 500) {
				Cars[Index + 1]->SlowDown();
			 }
			else {
				Cars[Index + 1]->SpeedUp();
			}	
		}
	}

	float RunningTime = GetGameTimeSinceCreation();
	if (RunningTime >= nextSpawn) {
		SpawnCar();
	}


}

void AManager::SpawnCar()
{

	nextSpawn += FMath::RandRange(4, 8);

	FVector Location(0.0f, 0.0f, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);

	ASamochod* Spawned = GetWorld()->SpawnActor<ASamochod>(Location, Rotation);

	Cars.Add(Spawned);

}

