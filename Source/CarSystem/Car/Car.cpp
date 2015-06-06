// Fill out your copyright notice in the Description page of Project Settings.

#include "CarSystem.h"
#include "Car.h"


// Sets default values
ACar::ACar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FrontSensor = CreateDefaultSubobject<UStaticMeshComponent>("Front Sensor");
	FrontSensor->AttachTo(RootComponent);
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

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	auto Ignored = TArray<UPrimitiveComponent*>();
	Ignored.Add(FrontSensor);
	CollisionParams.AddIgnoredComponents(Ignored);
	FVector FrontSensorLocation = FrontSensor->GetComponentLocation();
	
	DrawDebugLine(GetWorld(), FrontSensorLocation, FrontSensorLocation + FVector(MAX_DIST, 0.f, 0.f) * GetActorForwardVector(), FColor::Green, false, .2f);

	if (GetWorld()->LineTraceSingle(HitResult, FrontSensorLocation, FrontSensorLocation + FVector(MAX_DIST, 0.f, 0.f) * GetActorForwardVector(), ECC_Visibility, CollisionParams))
	{
		float DistanceDiff = FMath::Abs(HitResult.Location.X - FrontSensorLocation.X);
		float Ratio = (DistanceDiff - MIN_DIST) / (MAX_DIST - MIN_DIST - TOLERANCE);
		if (Ratio < 0.05f) Ratio = 0.05f;
		if (DistanceDiff <= MIN_DIST) return;

		AddMovementInput(GetActorForwardVector(), Ratio * MAX_SPEED * DeltaTime);
		return;
	}
	
	AddMovementInput(GetActorForwardVector(), MAX_SPEED * DeltaTime);

}


// Called to bind functionality to input
void ACar::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

