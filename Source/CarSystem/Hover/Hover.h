// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Hover.generated.h"


UCLASS()
class CARSYSTEM_API AHover : public APawn
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = HoverProperties)
	float Altitude;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = HoverProperties)
	float CorrectionPower;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = HoverProperties)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = HoverProperties)
	UStaticMeshComponent* HoverMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = HoverProperties)
	USphereComponent* FrontPower;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = HoverProperties)
	USphereComponent* BackLeftPower;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = HoverProperties)
	USphereComponent* BackRightPower;

	// Sets default values for this character's properties
	AHover();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	
	
};
