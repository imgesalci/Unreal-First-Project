#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SlashCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class AItem;
UCLASS()
class SLASH_API ASlashCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASlashCharacter();
	virtual void Jump() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext *SlashContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction *MovementAction;

	UPROPERTY(EditAnywhere, Category = Input);
	UInputAction *LookAction;

	UPROPERTY(EditAnywhere, Category = Input);
	UInputAction *JumpAction;

	UPROPERTY(EditAnywhere, Category = Input);
	UInputAction *EKeyAction;

	UPROPERTY(EditAnywhere, Category = Input);
	UInputAction *AttackAction;

	UPROPERTY(EditAnywhere, Category = Input);
	UInputAction *DodgeAction;

	void Move(const FInputActionValue &Value);
	void Look(const FInputActionValue &Value);

	void EKeyPressed();
	virtual void Attack();
	void Dodge();

private:
	UPROPERTY(VisibleInstanceOnly)
	AItem *OverlappingItem;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	void SetOverlappingItem(AItem *Item) { OverlappingItem = Item; }
};
