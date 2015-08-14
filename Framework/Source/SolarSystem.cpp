//
//  SolarSystem.cpp
//  COMP371_Framework
//
//  Created by Mark Massoud on 2015-08-13.
//  Copyright (c) 2015 Concordia. All rights reserved.
//

#include "SolarSystem.h"
#include "TextureLoader.h"

SolarSystem::SolarSystem()
{
    
#if defined(PLATFORM_OSX)
    int mercuryTextureID = TextureLoader::LoadTexture("Textures/planets/mercury.jpg");
    int venusTextureID = TextureLoader::LoadTexture("Textures/planets/venus.jpg");
    int earthTextureID = TextureLoader::LoadTexture("Textures/planets/earth.jpg");
    int marsTextureID = TextureLoader::LoadTexture("Textures/planets/mars.jpg");
    int jupiterTextureID = TextureLoader::LoadTexture("Textures/planets/jupiter.jpg");
    int saturnTextureID = TextureLoader::LoadTexture("Textures/planets/saturn.jpg");
    int uranusTextureID = TextureLoader::LoadTexture("Textures/planets/uranus.jpg");
    int neptuneTextureID = TextureLoader::LoadTexture("Textures/planets/neptune.jpg");
    int plutoTextureID = TextureLoader::LoadTexture("Textures/planets/pluto.jpg");
#else
    int mercuryTextureID = TextureLoader::LoadTexture("../Assets/planets/Textures/planets/mercury.jpg");
    int venusTextureID = TextureLoader::LoadTexture("../Assets/planets/Textures/planets/venus.jpg");
    int earthTextureID = TextureLoader::LoadTexture("../Assets/planets/Textures/planets/earth.jpg");
    int marsTextureID = TextureLoader::LoadTexture("../Assets/planets/Textures/planets/mars.jpg");
    int jupiterTextureID = TextureLoader::LoadTexture("../Assets/planets/Textures/planets/jupiter.jpg");
    int saturnTextureID = TextureLoader::LoadTexture("../Assets/planets/Textures/planets/saturn.jpg");
    int uranusTextureID = TextureLoader::LoadTexture("../Assets/planets/Textures/planets/uranus.jpg");
    int neptuneTextureID = TextureLoader::LoadTexture("../Assets/planets/Textures/planets/neptune.jpg");
    int plutoTextureID = TextureLoader::LoadTexture("../Assets/planets/Textures/planets/pluto.jpg");
#endif
    
    Planet* mercury = new Planet(5, mercuryTextureID);
    Planet* venus = new Planet(10, venusTextureID);
    Planet* earth = new Planet(15, earthTextureID);
    Planet* mars = new Planet(20, marsTextureID);
    Planet* jupiter = new Planet(25, jupiterTextureID);
    Planet* saturn = new Planet(30, saturnTextureID);
    Planet* uranus = new Planet(35, uranusTextureID);
    Planet* neptune = new Planet(40, neptuneTextureID);
    Planet* pluto = new Planet(45, plutoTextureID);
    
    mPlanets.push_back(mercury);
    mPlanets.push_back(venus);
    mPlanets.push_back(earth);
    mPlanets.push_back(mars);
    mPlanets.push_back(jupiter);
    mPlanets.push_back(saturn);
    mPlanets.push_back(uranus);
    mPlanets.push_back(neptune);
    mPlanets.push_back(pluto);
    
}

SolarSystem::~SolarSystem() {
    for (std::vector<Planet*>::iterator it = mPlanets.begin(); it != mPlanets.end(); ++it)
    {
        delete *it;
    }
    mPlanets.resize(0);
}

void SolarSystem::Update(float dt) {
    
    for(Planet* p : mPlanets) {
        p->Update(dt);
    }
    
}

void SolarSystem::Draw() {
    for(Planet* p : mPlanets) {
        p->Draw();
    }
}
