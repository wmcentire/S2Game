#include "ContactListener.h"
#include "Framework/Actor.h"
#include "Components/CollisionComponent.h"
#include <iostream>

namespace pb {
	void ContactListener::BeginContact(b2Contact* contact)
	{
		b2Fixture* fixA = contact->GetFixtureA();
		b2Fixture* fixB = contact->GetFixtureB();

		if (fixA->GetUserData().pointer && fixB->GetUserData().pointer) {
			Actor* actorA = (Actor*)(fixA->GetUserData().pointer);
			Actor* actorB = (Actor*)(fixB->GetUserData().pointer);

			std::cout << actorA->GetName() << std::endl;
			std::cout << actorB->GetName() << std::endl;

			if (actorA->GetComponent<CollisionComponent>()) {
				actorA->GetComponent<CollisionComponent>()->OnCollisionEnter(actorB);
			}
			if (actorB->GetComponent<CollisionComponent>()) {
				actorB->GetComponent<CollisionComponent>()->OnCollisionEnter(actorA);
			}
		}
	}

	void ContactListener::EndContact(b2Contact* contact)
	{
		
	}
}
