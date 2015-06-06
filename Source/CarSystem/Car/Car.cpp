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

	FVector FrontSensorLocation = FrontSensor->GetComponentLocation();

	DrawDebugLine(GetWorld(), FrontSensorLocation, FrontSensorLocation + MAX_DIST_VECTOR * GetActorRightVector(), FColor::Cyan, false);
	DrawDebugLine(GetWorld(), FrontSensorLocation, FrontSensorLocation + MAX_DIST_VECTOR * -GetActorRightVector(), FColor::Cyan, false);
	
	DrawDebugLine(GetWorld(), FrontSensorLocation, FrontSensorLocation + MAX_DIST_VECTOR * GetActorForwardVector(), FColor::Green, false);


	FHitResult RightResult;
	FHitResult LeftResult;

	FCollisionQueryParams CollisionParams;
	auto Ignored = TArray<UPrimitiveComponent*>();
	Ignored.Add(FrontSensor);
	CollisionParams.AddIgnoredComponents(Ignored);


	GetWorld()->LineTraceSingle(RightResult, FrontSensorLocation, FrontSensorLocation + MAX_DIST_VECTOR * GetActorRightVector(), ECC_Visibility, CollisionParams);
	GetWorld()->LineTraceSingle(LeftResult, FrontSensorLocation, FrontSensorLocation + MAX_DIST_VECTOR * -GetActorRightVector(), ECC_Visibility, CollisionParams);

	float SidesDistanceDiff = (RightResult.Location - FrontSensorLocation).Size() - (LeftResult.Location - FrontSensorLocation).Size();
	if (GEngine) GEngine->AddOnScreenDebugMessage(0, .5f, FColor::Blue, FString::SanitizeFloat(SidesDistanceDiff));
	// TODO: Save last state. If decreasing distances, center yourself!

	if (SidesDistanceDiff > 0.f)	// More space on the right side, turn right!
		AddControllerYawInput(SidesDistanceDiff * DeltaTime);
	else if (SidesDistanceDiff < 0.f)
		AddControllerYawInput(SidesDistanceDiff * DeltaTime);

	FHitResult FrontResult;


	if (GetWorld()->LineTraceSingle(FrontResult, FrontSensorLocation, FrontSensorLocation + MAX_DIST_VECTOR * GetActorForwardVector(), ECC_Visibility, CollisionParams))
	{
		float DistanceDiff = (FrontResult.Location - FrontSensorLocation).Size();
		float Ratio = (DistanceDiff - MIN_DIST) / (MAX_DIST - MIN_DIST - TOLERANCE);
		if (Ratio < 0.05f) Ratio = 0.05f;
		if (DistanceDiff< MIN_DIST) return;

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

