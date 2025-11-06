#include "Items/Weapons/Weapon.h"

// Attaches the weapon mesh to a specified socket on the given parent component
void AWeapon::Equip(USceneComponent *InParent, FName InSocketN)
{
    // Snap the weapon to the target socket (position, rotation, scale)
    FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
    ItemMesh->AttachToComponent(InParent, TransformRules, InSocketN);
}

// Called when something begins overlapping the weapon’s collision sphere
void AWeapon::OnSphereOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                              UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                              const FHitResult &SweepResult)
{
    // Call base class version to maintain shared item behavior
    Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

// Called when something stops overlapping the weapon’s collision sphere
void AWeapon::OnSphereEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                                 UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
    // Call base class version to maintain shared item behavior
    Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
