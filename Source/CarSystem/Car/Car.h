// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Car.generated.h"

UCLASS()
class CARSYSTEM_API ACar : public ACharacter
{
	GENERATED_BODY()

	const float MAX_SPEED = 80.f;
	const float MAX_DIST = 2500.f;
	const float MIN_DIST = 500.f;
	const float TOLERANCE = 200.f;

public:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = CarProperties)
	UStaticMeshComponent* FrontSensor;

	// Sets default values for this character's properties
	ACar();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	
	
};
