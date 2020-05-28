// Copyright Scott Kolby 2020


#include "SprungWheel.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	SpringConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring Constraint"));
	SetRootComponent(SpringConstraint);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(SpringConstraint);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);
	Wheel->SetNotifyRigidBodyCollision(true);

	AxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle Constraint"));
	AxleConstraint->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);

	SetupConstraint();
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		FrameTotalForceMagnitude = 0.f;
	}
}

void ASprungWheel::SetupConstraint()
{
	if (!GetAttachParentActor())
		return;

	auto BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot)
		return;

	SpringConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
	AxleConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplyWheelForce();
}

void ASprungWheel::ApplyWheelForce()
{
	Wheel->AddForce(Axle->GetForwardVector() * FrameTotalForceMagnitude);
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	FrameTotalForceMagnitude += ForceMagnitude;
}

