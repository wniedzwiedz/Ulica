// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>


// Sets default values
AManager::AManager()
{
	NextSpawnTime = 0.0f;
	StreetLength = 10000;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create street mesh
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(VisualMesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane"));

	if (PlaneVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(PlaneVisualAsset.Object);
		VisualMesh->SetWorldScale3D(FVector(StreetLength / 100, 5, 0.1));
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

	// add material  to mesh
	FString MaterialName = "/Game/StarterContent/Materials/M_Basic_Floor.M_Basic_Floor";
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> ghostMaterialAsset(*MaterialName);
	StreetMaterial = ghostMaterialAsset.Object;
	VisualMesh->SetMaterial(0, StreetMaterial);

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

		//remove first car if it's at the end of the street
		if (Cars[0]->GetTargetLocation().X > StreetLength / 2) {
			Cars[0]->Destroy();
			Cars.RemoveAt(0);
		}
		//otherwise speed it up
		else {
			Cars[0]->SpeedUp(DeltaTime);
		}

		if (Cars.Num() > 0) {

			float Distance;

			//check distances between cars
			for (int32 Index = 0; Index != Cars.Num() - 1; ++Index)
			{
				Distance = Cars[Index]->GetTargetLocation().X - Cars[Index + 1]->GetTargetLocation().X;

				//if they are too close at a too high speed or very close at any speed, then slow down
				if (Distance < 2 * Cars[Index + 1]->GetSpeed() || Distance < 600) {
					if (Cars[Index + 1]->GetSpeed() > Cars[Index]->GetSpeed()) {
						Cars[Index + 1]->SlowDown(DeltaTime);
					}
				}

				//speed up if nothing is in the way
				else {
					Cars[Index + 1]->SpeedUp(DeltaTime);
				}

			}
		}

		//spawn a new car if enough time passed
		float RunningTime = GetGameTimeSinceCreation();
		if (RunningTime >= NextSpawnTime) {
			SpawnCar();
		}


	}

}

void AManager::SpawnCar()
{
	//random time until new car spawns
	NextSpawnTime += FMath::RandRange(4, 8);

	//place the spawned car at the beginning of the street
	FVector Location = GetTargetLocation();
	Location.X -= StreetLength / 2;
	FRotator Rotation(0.0f, 0.0f, 0.0f);

	//spawn the car
	ACar* Spawned = GetWorld()->SpawnActor<ACar>(Location, Rotation);

	//add to the list of cars
	Cars.Add(Spawned);

}

