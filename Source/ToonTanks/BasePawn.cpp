// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectileBase.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	RootComponent = CapsuleComp;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(CapsuleComp);
	
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMesh);
	
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction()
{
	if(DeathParticles && DeathSound)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
		UGameplayStatics::SpawnSoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());
	}
	if (DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), LookAtRotation, UGameplayStatics::GetWorldDeltaSeconds(this), 20.f));
}

void ABasePawn::Fire()
{
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();
	//DrawDebugSphere(GetWorld(), Location, 10, 10, FColor::Red, false, 1.f);
	AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileBaseClass, Location, Rotation);
	Projectile->SetOwner(this);
}







