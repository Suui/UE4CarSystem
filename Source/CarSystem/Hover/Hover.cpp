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

	PhysicsBody = CreateDefaultSubobject<UBoxComponent>("Physics Body");
	PhysicsBody->AttachTo(Root);
	PhysicsBody->SetWorldLocation(FVector(70.0f, 0.f, 70.f));
	PhysicsBody->SetWorldScale3D(FVector(9.2f, 6.5f, 2.0f));
	PhysicsBody->SetSimulatePhysics(true);

	HoverMesh = CreateDefaultSubobject<UStaticMeshComponent>("Hover Mesh");
	HoverMesh->AttachTo(PhysicsBody);

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
	FVector AltitudeVector = FVector(0.f, 0.f, -Altitude);

	FHitResult FrontResult;
	FCollisionQueryParams CollisionParams;
	auto Ignored = TArray<UPrimitiveComponent*>();
	Ignored.Add(FrontPower);
	Ignored.Add(HoverMesh);
	Ignored.Add(PhysicsBody);
	CollisionParams.AddIgnoredComponents(Ignored);

	DrawDebugLine(GetWorld(), FrontPowerLocation, FrontPowerLocation + AltitudeVector, FColor::Red, false);
	DrawDebugLine(GetWorld(), BackLeftPowerLocation, BackLeftPowerLocation + AltitudeVector, FColor::Red, false);
	DrawDebugLine(GetWorld(), BackRightPowerLocation, BackRightPowerLocation + AltitudeVector, FColor::Red, false);

	float CompensationRatio;
	float FullLength = Altitude;
	if (GetWorld()->LineTraceSingle(FrontResult, FrontPowerLocation, FrontPowerLocation + AltitudeVector, ECC_Visibility, CollisionParams))
	{
		float HitLength = (FrontPowerLocation + AltitudeVector - FrontResult.Location).Size();
		CompensationRatio = HitLength / FullLength;
		if (GEngine) GEngine->AddOnScreenDebugMessage(0, 10.f, FColor::Green, FString::SanitizeFloat(FullLength) + ", " + FString::SanitizeFloat(HitLength) + ", " + FString::SanitizeFloat(CompensationRatio));
		PhysicsBody->AddImpulseAtLocation(FVector(0.f, 0.f, 100.f * CompensationRatio), FrontPowerLocation);
	}

	if (GetWorld()->LineTraceSingle(FrontResult, BackLeftPowerLocation, BackLeftPowerLocation + AltitudeVector, ECC_Visibility, CollisionParams))
	{
		float HitLength = (BackLeftPowerLocation + AltitudeVector - FrontResult.Location).Size();
		CompensationRatio = HitLength / FullLength;
		PhysicsBody->AddImpulseAtLocation(FVector(0.f, 0.f, 50.f * CompensationRatio), BackLeftPowerLocation);
	}

	if (GetWorld()->LineTraceSingle(FrontResult, BackRightPowerLocation, BackRightPowerLocation + AltitudeVector, ECC_Visibility, CollisionParams))
	{
		float HitLength = (BackRightPowerLocation + AltitudeVector - FrontResult.Location).Size();
		CompensationRatio = HitLength / FullLength;
		PhysicsBody->AddImpulseAtLocation(FVector(0.f, 0.f, 50.f * CompensationRatio), BackRightPowerLocation);
	}


}


// Called to bind functionality to input
void AHover::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

