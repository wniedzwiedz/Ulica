// Fill out your copyright notice in the Description page of Project Settings.


#include "Car.h"

// Sets default values
ACar::ACar()
{

	Speed = 0;
	PreferredSpeed = 100 * FMath::RandRange(3, 12);
	Acceleration = 200;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//mesh creation

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if (CubeVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		VisualMesh->SetWorldScale3D(FVector(4, 2, 1));
	}

	// add material to mesh
	FString MaterialName = "/Game/StarterContent/Materials/M_Metal_Copper.M_Metal_Copper";
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> ghostMaterialAsset(*MaterialName);
	CarMaterial = ghostMaterialAsset.Object;
	VisualMesh->SetMaterial(0, CarMaterial);

}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Location = GetActorLocation();

	if (Speed > 0) {
		Location += GetActorForwardVector() * Speed * DeltaTime;
	}

	SetActorLocation(Location);

}

void ACar::SpeedUp(float DeltaTime) {
	if (Speed < PreferredSpeed - Acceleration) {
		Speed += Acceleration * DeltaTime;
	}
	else {
		Speed = PreferredSpeed;
	}

}

void ACar::SlowDown(float DeltaTime) {
	Speed -= Acceleration * DeltaTime;
	if (Speed < 0) {
		Speed = 0;
	}
}

int ACar::GetSpeed() {
	return Speed;
}