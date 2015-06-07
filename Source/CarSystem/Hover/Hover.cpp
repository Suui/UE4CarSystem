// Fill out your copyright notice in the Description page of Project Settings.

#include "CarSystem.h"
#include "Hover.h"


// Sets default values
AHover::AHover()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("RootScene");
	RootComponent = Root;

	HoverMesh = CreateDefaultSubobject<UStaticMeshComponent>("Hover Mesh");
	HoverMesh->AttachTo(RootComponent);
	HoverMesh->SetSimulatePhysics(true);

	FrontPower = CreateDefaultSubobject<USphereComponent>("Front Power");
	FrontPower->AttachTo(HoverMesh);

	BackLeftPower = CreateDefaultSubobject<USphereComponent>("Back Left Power");
	BackLeftPower->AttachTo(HoverMesh);

	BackRightPower = CreateDefaultSubobject<USphereComponent>("Back Right Power");
	BackRightPower->AttachTo(HoverMesh);

	Altitude = 200.f;
	CorrectionPower = 100.f;
}


// Called when the game starts or when spawned
void AHover::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AHover::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FVector FrontPowerLocation = FrontPower->GetComponentLocation();
	FVector BackLeftPowerLocation = BackLeftPower->GetComponentLocation();
	FVector BackRightPowerLocation = BackRightPower->GetComponentLocation();
	FVector AltitudeVector = FVector(0.f, 0.f, Altitude);

	FHitResult FrontResult;
	FCollisionQueryParams CollisionParams;
	auto Ignored = TArray<UPrimitiveComponent*>();
	Ignored.Add(FrontPower);
	Ignored.Add(HoverMesh);
	CollisionParams.AddIgnoredComponents(Ignored);

	DrawDebugLine(GetWorld(), FrontPowerLocation, FrontPowerLocation + AltitudeVector, FColor::Red, false);
	DrawDebugLine(GetWorld(), BackLeftPowerLocation, BackLeftPowerLocation + AltitudeVector, FColor::Red, false);
	DrawDebugLine(GetWorld(), BackRightPowerLocation, BackRightPowerLocation + AltitudeVector, FColor::Red, false);

	if (GetWorld()->LineTraceSingle(FrontResult, FrontPowerLocation, FrontPowerLocation + FVector(0.f, 0.f, -500.f), ECC_Visibility, CollisionParams))
	{
		HoverMesh->AddImpulseAtLocation(FVector(0.f, 0.f, 1000.f), FrontPowerLocation);
	}


}


// Called to bind functionality to input
void AHover::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

