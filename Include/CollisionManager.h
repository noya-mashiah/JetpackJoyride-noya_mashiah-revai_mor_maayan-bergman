/**
 *  CollisionManager.h
 *  Handles collision processing between game objects.
 *
 * Provides the processCollision function, which dispatches collision logic
 * based on the types of the colliding objects.
 */
#pragma once
class GameObject;

void processCollision(GameObject& obj1, GameObject& obj2);
