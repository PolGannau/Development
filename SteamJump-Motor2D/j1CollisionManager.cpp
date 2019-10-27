#include "j1App.h"
#include "j1Input.h"
#include "j1CollisionManager.h"
//#include "j1Player.h"
#include "p2Log.h"

j1Collision::j1Collision() {
	name.create("collision");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)colliders[i] = nullptr;

	matrix[COLLIDER_PLATFORM][COLLIDER_PLATFORM] = false;
	matrix[COLLIDER_PLATFORM][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_PLATFORM][COLLIDER_DEATH] = false;
	matrix[COLLIDER_PLATFORM][COLLIDER_SOLID] = false;
	matrix[COLLIDER_PLATFORM][COLLIDER_FINISH] = false;

	matrix[COLLIDER_PLAYER][COLLIDER_PLATFORM] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_DEATH] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_SOLID] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_FINISH] = true;

	matrix[COLLIDER_DEATH][COLLIDER_PLATFORM] = false;
	matrix[COLLIDER_DEATH][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_DEATH][COLLIDER_DEATH] = false;
	matrix[COLLIDER_DEATH][COLLIDER_SOLID] = false;
	matrix[COLLIDER_DEATH][COLLIDER_FINISH] = false;

	matrix[COLLIDER_SOLID][COLLIDER_PLATFORM] = false;
	matrix[COLLIDER_SOLID][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_SOLID][COLLIDER_DEATH] = false;
	matrix[COLLIDER_SOLID][COLLIDER_SOLID] = false;
	matrix[COLLIDER_SOLID][COLLIDER_FINISH] = false;

	matrix[COLLIDER_FINISH][COLLIDER_PLATFORM] = false;
	matrix[COLLIDER_FINISH][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_FINISH][COLLIDER_DEATH] = false;
	matrix[COLLIDER_FINISH][COLLIDER_SOLID] = false;
	matrix[COLLIDER_FINISH][COLLIDER_FINISH] = false;
}

j1Collision::~j1Collision() {}

bool j1Collision::PreUpdate() {
	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		if (colliders[i] != nullptr && colliders[i]->to_delete == true) {
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider*		coll1;
	Collider*		coll2;
	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		if (colliders[i] == nullptr)continue;
		coll1 = colliders[i];

		for (uint j = i + 1; j < MAX_COLLIDERS; ++j) {
			if (colliders[j] == nullptr)continue;
			coll2 = colliders[j];
			if (coll1->CheckCollision(coll2->rect) == true) {
				///if(matrix[coll1->type][coll2->type]&&coll2->callback)// need to add oncollision
				///if(matrix[coll2->type][coll1->type]&&coll2->callback)// need to add oncollision
			}
		}
	}
	return true;
}

bool j1Collision::Update() {
	DebugDraw();
	return true;
}

bool j1Collision::CleanUp() {
	LOG("Freeing all the colliders");
	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		if (colliders[i] != nullptr) {
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
	return true;
}

void j1Collision::DebugDraw() {
	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)debug = !debug;
	if (debug == false)return;

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		switch (colliders[i]->type) {
		case COLLIDER_NONE:		// white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_PLATFORM:	// magenta
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 204, alpha);
			break;
		case COLLIDER_PLAYER:	// green
			if(!godmode)App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			if (godmode)App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_SOLID:	// blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_DEATH:	// red
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
		case COLLIDER_FINISH:	// yellow
			break;
		}
	}
}

void j1Collision::SetColliderSize(Collider * collider, uint width, uint height)
{
	collider->rect.w = width;
	collider->rect.h = height;
}

bool j1Collision::GetGodModeState()
{
	return this->godmode;
}

bool Collider::CheckCollision(const SDL_Rect& r)const
{
	if ((r.x + r.w <= rect.x) || (r.x >= rect.x + rect.w) || (r.y + r.h <= rect.y) || (r.y >= rect.y + rect.h)) return false;
	else return true;
}

Collider* j1Collision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback)
{
	Collider* ret = nullptr;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}
	return ret;
}

COLLIDER_TYPE j1Collision::DefineColliderByNum(int type_asInt)
{
	switch (type_asInt)
	{
	case 0:
		return COLLIDER_PLATFORM;
	case 1:
		return COLLIDER_PLAYER;
	case 2:
		return COLLIDER_DEATH;
	case 3:
		return COLLIDER_SOLID;
	case 4:
		return COLLIDER_FINISH;
	default:
		return COLLIDER_NONE;
	}
}

void j1Collision::GodMode()
{
	godmode = !godmode;
	matrix[COLLIDER_PLAYER][COLLIDER_DEATH] = !matrix[COLLIDER_PLAYER][COLLIDER_DEATH];
	matrix[COLLIDER_DEATH][COLLIDER_PLAYER] = !matrix[COLLIDER_DEATH][COLLIDER_PLAYER];
}