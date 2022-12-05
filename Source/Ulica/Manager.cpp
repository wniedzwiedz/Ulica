// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>


// Sets default values
AManager::AManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	NextSpawn = 0.0f;
	StreetLength = 10000;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane"));

	if (PlaneVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(PlaneVisualAsset.Object);
		VisualMesh->SetWorldScale3D(FVector(StreetLength/100, 5, 0.1));
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

	// material
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

		//remove first car if it's at the end

		if (Cars[0]->GetTargetLocation().X > StreetLength/2) {
			Cars[0]->Destroy();
			Cars.RemoveAt(0);
		}
		else {
			Cars[0]->SpeedUp(DeltaTime);
		}
		
		if (Cars.Num() > 0) {
			float Distance;
			//check distances
			for (int32 Index = 0; Index != Cars.Num() - 1; ++Index)
			{
				Distance = Cars[Index]->GetTargetLocation().X - Cars[Index + 1]->GetTargetLocation().X;

				if (Distance < 2 * Cars[Index + 1]->GetSpeed()) {
					if (Cars[Index + 1]->GetSpeed() > Cars[Index]->GetSpeed()) {
						Cars[Index + 1]->SlowDown(DeltaTime);
					}

				}

				else if (Distance < 600) {
					if (Cars[Index + 1]->GetSpeed() > Cars[Index]->GetSpeed()) {
						Cars[Index + 1]->SlowDown(DeltaTime);
					}
				}
				else {
					Cars[Index + 1]->SpeedUp(DeltaTime);
				}
			}

		}
	}

	float RunningTime = GetGameTimeSinceCreation();
	if (RunningTime >= NextSpawn) {
		SpawnCar();
	}


}

void AManager::SpawnCar()
{

	NextSpawn += FMath::RandRange(4,10);

	FVector Location = GetTargetLocation();
	Location.X -= StreetLength / 2;
	FRotator Rotation(0.0f, 0.0f, 0.0f);

	ACar* Spawned = GetWorld()->SpawnActor<ACar>(Location, Rotation);

	Cars.Add(Spawned);

}

