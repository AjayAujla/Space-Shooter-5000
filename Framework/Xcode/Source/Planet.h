//
//  Planet.cpp
//  COMP371_Framework
//
//  Created by Mark Massoud on 2015-08-13.
//  Copyright (c) 2015 Concordia. All rights reserved.
//

#include "SphereModel.h"

class Planet : public SphereModel {
    
public:
    Planet();
    Planet(float offset, vec3 axis, int textureID);
    virtual ~Planet();
    
    virtual void Update(float deltaTime);
    virtual void Draw();
    
private:
    
    vec3 axis;  // center of universe (sun)
    float offset; // distance from the sun
                 // the sun being in the center of universe
    
};