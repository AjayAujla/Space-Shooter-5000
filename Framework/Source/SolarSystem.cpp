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
    int sunTextureID = TextureLoader::LoadTexture("Textures/planets/sun.jpg");
#else
    int mercuryTextureID = TextureLoader::LoadTexture("../Assets/Textures/planets/mercury.jpg");
    int venusTextureID = TextureLoader::LoadTexture("../Assets/Textures/planets/venus.jpg");
    int earthTextureID = TextureLoader::LoadTexture("../Assets/Textures/planets/earth.jpg");
    int marsTextureID = TextureLoader::LoadTexture("../Assets/Textures/planets/mars.jpg");
    int jupiterTextureID = TextureLoader::LoadTexture("../Assets/Textures/planets/jupiter.jpg");
    int saturnTextureID = TextureLoader::LoadTexture("../Assets/Textures/planets/saturn.jpg");
    int uranusTextureID = TextureLoader::LoadTexture("../Assets/Textures/planets/uranus.jpg");
    int neptuneTextureID = TextureLoader::LoadTexture("../Assets/Textures/planets/neptune.jpg");
    int plutoTextureID = TextureLoader::LoadTexture("../Assets/Textures/planets/pluto.jpg");
    int sunTextureID = TextureLoader::LoadTexture("../Assets/Textures/planets/sun.jpg");
#endif
    
    vec3 offset = vec3(6.0f);
    
    // this is the real order of the planets, DO NOT CHANGE!
    // the mass (3rd argument) is relatively correct, DO NOT CHANGE!
    Planet* mercury = new Planet(vec3(10.0f), mercuryTextureID, 20.0f);
    Planet* venus = new Planet(mercury->GetPosition() + offset, venusTextureID, 40.0f);
    Planet* earth = new Planet(venus->GetPosition() + offset, earthTextureID, 50.0f);
    Planet* mars = new Planet(earth->GetPosition() + offset, marsTextureID, 30.0f);
    Planet* jupiter = new Planet(mars->GetPosition() + offset, jupiterTextureID, 90.0f);
    Planet* saturn = new Planet(jupiter->GetPosition() + offset, saturnTextureID, 80.0f);
    Planet* uranus = new Planet(saturn->GetPosition() + offset, uranusTextureID, 60.0f);
    Planet* neptune = new Planet(uranus->GetPosition() + offset, neptuneTextureID, 70.0f);
    Planet* pluto = new Planet(neptune->GetPosition() + offset, plutoTextureID, 20.0f);
    
    // their size is relatively correct, DO NOT CHANGE!
    pluto->SetScaling(vec3(0.4f));
    mercury->SetScaling(vec3(0.6f));
    mars->SetScaling(vec3(0.8f));
    venus->SetScaling(vec3(1.0f));
    earth->SetScaling(vec3(1.2f));
    neptune->SetScaling(vec3(2.0f));
    uranus->SetScaling(vec3(2.2f));
    saturn->SetScaling(vec3(3.0f));
    jupiter->SetScaling(vec3(3.5f));
    
    sun = new SphereModel(sunTextureID);
    sun->SetScaling(vec3(5));
    
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
    delete sun;
}

void SolarSystem::Update(float dt) {
    
    for(Planet* p : mPlanets) {
        p->Update(dt);
    }
    sun->Update(dt);
    
}

void SolarSystem::Draw() {
    for(Planet* p : mPlanets) {
        p->Draw();
    }
    sun->Draw();
}