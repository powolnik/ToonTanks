// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Tank.h"
#include "kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    //Find the distance to the tank
    if (InFireRange())
    {
        RotateTurret(Tank->GetActorLocation());
    }
}

void ATurret::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}

void ATurret::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATurret::CheckFireCondition, FireRate, true);
}

void ATurret::CheckFireCondition()
{
    if (Tank == nullptr) 
    {
        return;
    }
    if (InFireRange() && Tank->bAlive)
    {
        Fire();
    }
}

bool ATurret::InFireRange()
{
    if (Tank && FVector::Distance(GetActorLocation(), Tank->GetActorLocation()) <= FireRange)
    {
        return true;
    }
    else
    {
        return false;
    }
}