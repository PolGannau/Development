#ifndef __j1COLLISIONMANAGER_H__
#define __j1COLLISIONMANAGER_H__

#define MAX_COLLIDERS 300

#include "j1Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "SDL/include/SDL_rect.h"
#include "j1Render.h"

enum COLLIDER_TYPE {
	COLLIDER_NONE = -1,
	COLLIDER_PLATFORM,		// platform colliders
	COLLIDER_PLAYER,		// player collider
	COLLIDER_DEATH,			// death collider
	COLLIDER_SOLID,			// walls and floor collider
	COLLIDER_FINISH,		// finish level trigger
	COLLIDER_MAX,
};

struct Collider {
	SDL_Rect		rect;
	bool			to_delete = false;
	COLLIDER_TYPE	type;
	j1Module*		callback;
	bool			enable = true;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, j1Module* callback = nullptr) :rect(rectangle), type(type), callback(callback) {}

	void SetPos(int x, int y) {
		rect.x = x;
		rect.y = y;
	}

	void SetShape(int w, int h) {
		rect.w = w;
		rect.h = h;
	}

	void SetType(COLLIDER_TYPE type) {
		this->type = type;
	}

	bool CheckCollision(const SDL_Rect& r)const;
};

class j1Collision : public j1Module {
private:
	Collider*		colliders[MAX_COLLIDERS];
	bool			matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool			debug = false;
	bool			godmode = false;

public:
	j1Collision();

	bool PreUpdate();
	bool Update();
	bool CleanUp();

	~j1Collision();

	COLLIDER_TYPE DefineColliderByNum(int num);
	Collider* AddCollider(SDL_Rect, COLLIDER_TYPE, j1Module* callback = nullptr);
	void GodMode();
	void DebugDraw();
	void SetColliderSize(Collider* collider, uint width, uint height);
	bool GetGodModeState();

	p2List<Collider*> colls;
};

#endif // !__j1COLLISIONMANAGER_H__