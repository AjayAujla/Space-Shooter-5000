//
//  SolarSystem.h
//  COMP371_Framework
//
//  Created by Mark Massoud on 2015-08-13.
//  Copyright (c) 2015 Concordia. All rights reserved.
//

#include "Planet.h"

class SolarSystem
{

public:
    
    SolarSystem();
    ~SolarSystem();
    
    void Update(float dt);
    void Draw();

	std::vector<Planet*> GetPlanets(){return mPlanets;}
	SphereModel* GetSun(){ return sun; }
    
private:
    
    std::vector<Planet*> mPlanets;
    SphereModel* sun;
    
};