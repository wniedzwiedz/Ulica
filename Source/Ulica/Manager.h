// Author: Weronika Niedüwiedü

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Car.h"
#include "Manager.generated.h"


UCLASS()
class ULICA_API AManager : public AActor
{
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* VisualMesh;

	UPROPERTY(VisibleAnywhere)
		class USceneComponent* RootScene;

	UPROPERTY(VisibleInstanceOnly)
		UMaterialInterface* StreetMaterial = nullptr;


	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// create a new car and add it to the list
	void SpawnCar();


protected:
	//length of the road (cm)
	int StreetLength;
	//time until next car is spawned (seconds)
	int NextSpawnTime;
	//array of all existing cars
	TArray<ACar*> Cars;
};
