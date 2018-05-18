// Fill out your copyright notice in the Description page of Project Settings.

#include "Player_Hand.h"


// Sets default values
APlayer_Hand::APlayer_Hand()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayer_Hand::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayer_Hand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayer_Hand::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

