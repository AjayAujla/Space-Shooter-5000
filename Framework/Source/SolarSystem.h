//
//  SolarSystem.h
//  COMP371_Framework
//
//  Created by Mark Massoud on 2015-08-13.
//  Copyright (c) 2015 Concordia. All rights reserved.
//

#include "Planet.h"

class Planet;

class SolarSystem
{

public:
    
    SolarSystem();
    ~SolarSystem();
    
    void Update(float dt);
    void Draw();
    
private:
    
    std::vector<Planet*> mPlanets;
    
};
