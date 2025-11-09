// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/SlashCharacter.h"

#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Items/Item.h"
#include "Items/Weapons/Weapon.h"

// Sets default values
ASlashCharacter::ASlashCharacter()
{
	// Enable Tick() — can be disabled later for performance if not needed
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASlashCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add the input mapping context for this character
	if (APlayerController *PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(SlashContext, 0);
		}
	}
}

// Called every frame
void ASlashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Handles movement input from the player
void ASlashCharacter::Move(const FInputActionValue &Value)
{
	// Get 2D movement vector from input
	const FVector2D MovementVector = Value.Get<FVector2D>();

	// Get controller's rotation, only use the yaw (horizontal rotation)
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	// Move forward/backward
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);

	// Move right/left
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

// Handles camera look input
void ASlashCharacter::Look(const FInputActionValue &Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();

	if (GetController())
	{
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(LookAxisValue.Y);
	}
}

// Called when 'E' key is pressed (for interacting / picking up weapons)
void ASlashCharacter::EKeyPressed()
{
	AWeapon *OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if (OverlappingWeapon)
	{
		// Attach weapon to right hand socket
		OverlappingWeapon->Equip(GetMesh(), FName("hand_rSocket"));
		CharacterState = ECharacterState::ECS_EquippedWeapon;
	}
}

// Placeholder for attack input
void ASlashCharacter::Attack()
{
	return;
}

// Placeholder for dodge input
void ASlashCharacter::Dodge()
{
	return;
}

// Override jump behavior if needed
void ASlashCharacter::Jump()
{
	Super::Jump();
}

// Bind input actions to functions
void ASlashCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent *EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Bind movement and look
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Look);

		// Bind jump and interact (E key)
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(EKeyAction, ETriggerEvent::Triggered, this, &ASlashCharacter::EKeyPressed);

		// Bind attack and dodge actions
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Attack);
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Dodge);
	}
}
