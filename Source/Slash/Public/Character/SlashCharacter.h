#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterTypes.h"
#include "InputActionValue.h"
#include "SlashCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class AItem;
class UAnimMontage;

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

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage *AttackMontage;

	void Move(const FInputActionValue &Value);
	void Look(const FInputActionValue &Value);

	void EKeyPressed();
	virtual void Attack();
	void Dodge();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

private:
	UPROPERTY(VisibleInstanceOnly)
	AItem *OverlappingItem;

	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	FORCEINLINE void SetOverlappingItem(AItem *Item) { OverlappingItem = Item; }
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
};
