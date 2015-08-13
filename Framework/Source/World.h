//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#pragma once


#include "ParsingHelper.h"
#include "Billboard.h"
#include "Spaceship.h"
#include <vector>
#include "Skybox.h"
#include "SphereModel.h"
#include "ParticleDescriptor.h"
#include "ParticleEmitter.h"
#include "ParticleSystem.h"

class Camera;
class Model;
class Animation;
class AnimationKey;
class ParticleSystem;
class AsteroidSystem;

class World
{
public:
	World();
	~World();
	
    static World* GetInstance();

	void Update(float dt);
	void Draw();

	void LoadScene(const char * scene_path);
    Animation* FindAnimation(ci_string animName);
	AnimationKey* FindAnimationKey(ci_string keyName);

    const Camera* GetCurrentCamera() const;
    void AddBillboard(Billboard* b);
    void RemoveBillboard(Billboard* b);
    void AddParticleSystem(ParticleSystem* particleSystem);
    void RemoveParticleSystem(ParticleSystem* particleSystem);

private:
    static World* instance;
    
	std::vector<Model*> mModel;
    std::vector<Animation*> mAnimation;
    std::vector<AnimationKey*> mAnimationKey;
	std::vector<Camera*> mCamera;
    std::vector<ParticleSystem*> mParticleSystemList;
    AsteroidSystem* mAsteroidSystem;
	unsigned int mCurrentCamera;
    BillboardList* mpBillboardList;
	bool collide(Model* m1, Model* m2);
	ParticleSystem* particleSystem;
	ParticleEmitter* emitter;
	ParticleDescriptor* desc;
	SphereModel* sphere1;
	SphereModel* sphere2;
	
	Skybox* skybox;
	Spaceship* spaceship;
};