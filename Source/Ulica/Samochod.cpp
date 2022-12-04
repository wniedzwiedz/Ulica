// Fill out your copyright notice in the Description page of Project Settings.


#include "Samochod.h"

// Sets default values
ASamochod::ASamochod()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if (CubeVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		VisualMesh->SetWorldScale3D(FVector(4, 2, 1));
	}

}

// Called when the game starts or when spawned
void ASamochod::BeginPlay()
{
	Super::BeginPlay();

	speed = 0; 
	PreferredSpeed = 10*FMath::RandRange(10, 25);
	
}


// Called every frame
void ASamochod::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//speed+= acceleration * DeltaTime;
	
	FVector Location = GetActorLocation();

	if (speed > 0) {
		Location += GetActorForwardVector() * speed * DeltaTime;
	}

	SetActorLocation(Location);



}

void ASamochod::SpeedUp() {
	if (speed < PreferredSpeed-100) {
		speed += 10;
	}
	else {
		speed = PreferredSpeed;
	}

}

void ASamochod::SlowDown() {
	speed -= 5;
	if (speed < 0) {
		speed = 0;
	}
}

int ASamochod::GetSpeed() {
	return speed;
}