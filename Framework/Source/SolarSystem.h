//
//  SolarSystem.h
//  COMP371_Framework
//
//  Created by Mark Massoud on 2015-08-13.
//  Copyright (c) 2015 Concordia. All rights reserved.
//

#ifndef __COMP371_Framework__SolarSystem__
#define __COMP371_Framework__SolarSystem__

#include <stdio.h>
#include "SphereModel.h"

#endif /* defined(__COMP371_Framework__SolarSystem__) */

class SolarSystem
{

public:
    
    SolarSystem();
    ~SolarSystem();
    
    void Update(float dt);
    void Draw();
    
private:
    
    SphereModel* sun;
    std::vector<SphereModel*> mPlanets;
    
};
