#include "Items/Item.h"
#include "../DebugMacros.h"
#include "Components/SphereComponent.h"
#include "Character/SlashCharacter.h"

// Sets default values
AItem::AItem()
{
	// Enable ticking every frame (can be disabled for performance if unnecessary)
	PrimaryActorTick.bCanEverTick = true;

	// Create the item’s mesh and set it as the root component
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = ItemMesh;

	// Create a sphere collision component and attach it to the root
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	// Bind overlap events for interaction detection
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereEndOverlap);
}

// Returns a sine value scaled by amplitude (used for floating animation)
float AItem::TransformedSin()
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

// Returns a cosine value scaled by amplitude
float AItem::TransformedCosin()
{
	return Amplitude * FMath::Cos(RunningTime * TimeConstant);
}

// Triggered when another actor overlaps with the sphere
void AItem::OnSphereOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	// Check if the overlapping actor is the player character
	ASlashCharacter *SlashCharacter = Cast<ASlashCharacter>(OtherActor);
	if (SlashCharacter)
	{
		// Notify the character that it's overlapping with this item
		SlashCharacter->SetOverlappingItem(this);
	}
}

// Triggered when another actor stops overlapping with the sphere
void AItem::OnSphereEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
	// Check if the actor leaving the overlap is the player character
	ASlashCharacter *SlashCharacter = Cast<ASlashCharacter>(OtherActor);
	if (SlashCharacter)
	{
		// Clear the overlapping item reference on the character
		SlashCharacter->SetOverlappingItem(nullptr);
	}
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Keep track of running time for floating animation
	RunningTime += DeltaTime;

	// Example floating motion (currently commented out)
	// float DeltaZ = Amplitude * FMath::Sin(RunningTime * TimeConstant);
	// AddActorWorldOffset(FVector(0.f, 0.f, DeltaZ));
}
