// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    
    PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    PlayerCamera->SetupAttachment(SpringArm);
}



// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}
// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

    PlayerControllerRef = Cast<APlayerController>(GetController());
    
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    if (PlayerControllerRef)
    {   
        FHitResult HitResult;
        PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Red, false, -1.f);
    }
}

void ATank::Move(float Value)
{
    double DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    FVector DeltaLocation(0.f);
	DeltaLocation.X = Value*MovementSpeed*DeltaTime;
    AddActorLocalOffset(DeltaLocation, true);
    
    //UE_LOG(LogTemp, Display, TEXT("W/S Value %f"), Value);
}
void ATank::Turn(float Value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator;
    DeltaRotation.Yaw = Value*RotationSpeed*UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(DeltaRotation, true);
    
    //UE_LOG(LogTemp, Display, TEXT("A/D Value %f"), Value);
}
