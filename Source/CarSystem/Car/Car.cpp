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
	
	SidesDistances = TArray<float>();
	for (int i = 0; i < 10; ++i)
		SidesDistances.Add(0.f);
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

	TimePassed += DeltaTime;
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
	// TODO: Save last state. If decreasing distances, center yourself!
	AdjustSidesDistancesValues(SidesDistanceDiff);

//	if (GEngine) GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Cyan, "Median: " + FString::SanitizeFloat(SidesDistanceDiff * 0.1f * DeltaTime));
//	AddControllerYawInput(SidesDistanceDiff * 0.1f * DeltaTime);

	float median = 0.f;
	for (int i = 0; i < 10; ++i)
		median += SidesDistances[i];
	median /= 10;

	float angle = median * 0.02f * DeltaTime;

	if (GEngine) GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Cyan, "Median: " + FString::SanitizeFloat(median) + ", Angle = " + FString::SanitizeFloat(angle));
	AddControllerYawInput(angle);



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


void ACar::AdjustSidesDistancesValues(float SidesDistanceDiff)
{
	for (int i = 0; i < 9; ++i)
		SidesDistances[i] = SidesDistances[i + 1];
	SidesDistances[9] = SidesDistanceDiff;
}


// Called to bind functionality to input
void ACar::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

