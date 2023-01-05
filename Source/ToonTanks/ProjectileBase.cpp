// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComp->MaxSpeed = 1301.f;
	ProjectileMovementComp->InitialSpeed = 1300.f;
	ParticleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComponent"));
	ParticleSystemComp->SetupAttachment(ProjectileMesh);

}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation(), 0.7, 0.8);
	}
	
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr) 
	{
		Destroy();
		return;
	}
	
	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
	UClass* DamageTypeClass = UDamageType::StaticClass();
	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, DamageValue, MyOwnerInstigator, this, DamageTypeClass);
		if (HitParticles && HitSound)
		{
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation());
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation(), 1.3);
		}
		if (HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}

	}
	Destroy();
}

