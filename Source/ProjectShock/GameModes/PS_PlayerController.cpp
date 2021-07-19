// Fill out your copyright notice in the Description page of Project Settings.


#include <ProjectShock/GameModes/PS_PlayerController.h>
#include "GameFramework/PlayerController.h"
APS_PlayerController::APS_PlayerController()
{
	
}

void APS_PlayerController::MoveForward(float Value)
{
	if ((PlayerCharacter != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation{ PlayerCharacter->GetControlRotation() };
		const FRotator YawRotation{ 0, Rotation.Yaw, 0 };

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X) };
		PlayerCharacter->AddMovementInput(Direction, Value);
		if (Value < 0) {
			PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = PlayerCharacter->PlayerPropertiesData->BackWalkSpeed;
		}
		if(Value >= 0){
			PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = PlayerCharacter->PlayerPropertiesData->WalkSpeed;
		}
		if (PlayerCharacter->bIsSprinting == true && PlayerCharacter->bIsAiming != true) {
			PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = PlayerCharacter->PlayerPropertiesData->SprintSpeed;
		}
	}
}

void APS_PlayerController::MoveSide(float Value)
{
	if ((PlayerCharacter != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation{ PlayerCharacter->GetController()->GetControlRotation() };
		const FRotator YawRotator{ 0, Rotation.Yaw, 0 };

		const FVector Direction{ FRotationMatrix{YawRotator}.GetUnitAxis(EAxis::Y) };
		PlayerCharacter->AddMovementInput(Direction, Value);
	}

}

void APS_PlayerController::TurnMovement(float Rate)
{
	PlayerCharacter->AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APS_PlayerController::LoopUpMovement(float Rate)
{
	PlayerCharacter->AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
