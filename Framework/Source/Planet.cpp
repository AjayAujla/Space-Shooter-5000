//
//  Planet.cpp
//  COMP371_Framework
//
//  Created by Mark Massoud on 2015-08-13.
//  Copyright (c) 2015 Concordia. All rights reserved.
//

#include "Planet.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

Planet::Planet(vec3 position, int textureID) : SphereModel(textureID) {

    this->mPosition = position;

    this->mRotationAxis = vec3(0.0f, 1.0f, 0.0f);
    
    this->currentAngle = 0.0f;
    
    this->velocity = vec3(5.0f, 0.0f, 5.0f);    // no velocity in y axis
    this->acceleration = vec3(5.0f, 0.0f, 5.0f);
}

Planet::~Planet() {
}

void Planet::Update(float dt) {
    // rotate around sun using rotate() function
    if(currentAngle >= 360)
        currentAngle = 0;

    mat4 rotationMatrix = rotate(mat4(1.0f), ++currentAngle, this->mRotationAxis);
    
    this->velocity = vec3(rotationMatrix * vec4(this->velocity, 1.0f));
    
    //position
    this->mPosition += this->velocity * dt + 0.5f*dt*dt; // x_final = x_initial + v * t + 0.5 * a * t^2
    std::cout << this->mPosition.x << ", " << this->mPosition.z << ", " <<this->mPosition.z << std::endl;
    
    // for debugging
//    if(this->mPosition.x > 100)
//        this->mPosition = vec3(0);
    
}

void Planet::Draw(){
    SphereModel::Draw();
}
