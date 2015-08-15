//
//  Planet.cpp
//  COMP371_Framework
//
//  Created by Mark Massoud on 2015-08-13.
//  Copyright (c) 2015 Concordia. All rights reserved.
//

#include "Planet.h"
#include "EventManager.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

Planet::Planet(vec3 position, int textureID, float mass) : SphereModel(textureID) {

    this->mPosition = position;
    this->mass = mass;
    
}

Planet::~Planet() {
}

void Planet::Update(float dt) {
    
    float angle =dt/this->mass*10;
    
    this->mPosition.x = this->mPosition.x*cos(angle) - this->mPosition.z*sin(angle);
    this->mPosition.y = 0;
    this->mPosition.z = this->mPosition.x*sin(angle) + this->mPosition.z*cos(angle);
    
}

void Planet::Draw(){
    SphereModel::Draw();
}
