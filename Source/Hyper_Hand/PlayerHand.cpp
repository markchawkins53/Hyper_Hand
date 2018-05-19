// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHand.h"


// Sets default values
APlayerHand::APlayerHand()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MoveInput = FVector(0, 0, 0);
	PreviousLocation = GetActorLocation();

	IsMoving = false;
}

// Called when the game starts or when spawned
void APlayerHand::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerHand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckIfMoving();
}

// Called to bind functionality to input
void APlayerHand::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/*Checks if Player is currently moving*/
void APlayerHand::CheckIfMoving()
{
	if (PreviousLocation == GetActorLocation())
		IsMoving = IsDodging = false;
}

void APlayerHand::PlayerMoveInput(float MoveUpDownInput, float MoveLeftRightInput)
{
	MoveInput.X = MoveUpDownInput;
	MoveInput.Y = MoveLeftRightInput;
}

/*Moves the Player in the given directions*/
void APlayerHand::PlayerMove(float PlayerSpeed)
{
	FVector OrigLocation = PreviousLocation = GetActorLocation();

	if (IsDodging)
		return;

	if (!IsMoving)
		IsMoving = true;

	OrigLocation += (FVector(1, 0, 0) * MoveInput.X * PlayerSpeed * FApp::GetDeltaTime());
	OrigLocation += (FVector(0, 1, 0) * MoveInput.Y * PlayerSpeed * FApp::GetDeltaTime());

	SetActorLocation(OrigLocation);
}

void APlayerHand::PlayerDodge(float DodgeDistance, float PlayerSpeed)
{
	if (!IsDodging)
		IsDodging = true;
	else if (IsDodging || (MoveInput.X == 0 && MoveInput.Y == 0))
		return;

	FVector NewLocation = GetActorLocation() + (MoveInput * DodgeDistance);

	while (true)
	{
		SetActorLocation ( FMath::Lerp(GetActorLocation(), NewLocation, .5f) * FApp::GetDeltaTime() );

		if (FMath::Abs( NewLocation.X- GetActorLocation().X ) <= 100 &&
			FMath::Abs( NewLocation.Y - GetActorLocation().Y ) <= 100)
		{
			IsDodging = false;
			break;
		}
	}
}

/*Rotates the Player to the desired direction*/
void APlayerHand::PlayerAim(float LookUpDownInput, float LookLeftRightInput)
{
	FRotator Rotation = GetActorRotation();
	
	if (LookUpDownInput != 0 && LookLeftRightInput != 0)
	{
		Rotation.Yaw = FMath::RadiansToDegrees(FMath::Atan2(LookLeftRightInput, -LookUpDownInput));
		SetActorRotation(Rotation);
	}

}
