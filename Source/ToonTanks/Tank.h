// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const { return TankPlayerController; };

	bool bAlive = true;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* PlayerCamera;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;
	
	void Move(float Value);

	void Turn(float Value);

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Movement")
	float MovementSpeed = 400.f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Movement")
	float RotationSpeed = 100.f;
	
	APlayerController* TankPlayerController;
	
};
