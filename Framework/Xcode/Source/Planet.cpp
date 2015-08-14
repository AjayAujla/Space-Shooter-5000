//
//  Planet.cpp
//  COMP371_Framework
//
//  Created by Mark Massoud on 2015-08-13.
//  Copyright (c) 2015 Concordia. All rights reserved.
//

#include "Planet.h"

Planet::Planet() {}

Planet::Planet(float offset, vec3 axis, int textureID) : SphereModel(textureID) {

    this->mPosition = vec3(offset);

    this->axis = vec3(0, 1, 0);
}

Planet::~Planet() {
}

void Planet::Update(float deltaTime) {
    // rotate around sun using rotate() function
    
}

void Planet::Draw(){
    SphereModel::Draw();
}
