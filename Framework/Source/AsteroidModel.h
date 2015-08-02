//
//  AsteroidModel.h
//  COMP371_Framework
//
//  Created by Mark Massoud on 2015-08-02.
//  Copyright (c) 2015 Concordia. All rights reserved.
//

#ifndef __COMP371_Framework__AsteroidModel__
#define __COMP371_Framework__AsteroidModel__

#include <stdio.h>

#endif /* defined(__COMP371_Framework__AsteroidModel__) */

#pragma once
#include "AsteroidModel.h"
#include "Model.h"

class AsteroidModel : public Model
{
public:
    AsteroidModel(glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
    virtual ~AsteroidModel(void);
    
    virtual void Update(float dt);
    virtual void Draw();
    
protected:
    virtual bool ParseLine(const std::vector<ci_string> &token);
    
private:
    // The vertex format could be different for different types of models
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 color;
    };
    
    unsigned int mVertexArrayID;
    unsigned int mVertexBufferID;
    unsigned int numOfVertices;
    
    
};


