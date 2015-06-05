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
	
	DrawDebugLine(GetWorld(), FrontSensor->GetComponentLocation() + FVector::ForwardVector * 210.f, FrontSensor->GetComponentLocation() + FVector::ForwardVector * (MAX_DIST + 210.f), FColor::Green, false, .2f);
	
	if (GetWorld()->LineTraceSingle(HitResult, FrontSensor->GetComponentLocation() + FVector::ForwardVector * 210.f, FrontSensor->GetComponentLocation() + FVector::ForwardVector * (MAX_DIST + 210.f), ECC_Visibility, CollisionParams))
	{
		float Ratio = (HitResult.Location.X - FrontSensor->GetComponentLocation().X + 210.f) / (MAX_DIST - MIN_DIST);
		if (GEngine) GEngine->AddOnScreenDebugMessage(0, .2f, FColor::Green, FString::SanitizeFloat(Ratio));

		AddMovementInput(FVector::ForwardVector, Ratio * MAX_SPEED * DeltaTime);
		return;
	}
	
	AddMovementInput(FVector(1.f, 0.f, 0.f), MAX_SPEED * DeltaTime);

}

// Called to bind functionality to input
void ACar::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

