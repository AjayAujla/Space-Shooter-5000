//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#pragma once

#include "Camera.h"
#include "Model.h"

class ThirdPersonCamera : public Camera
{
public:
	ThirdPersonCamera(glm::vec3 position, Model *m);
	virtual ~ThirdPersonCamera();

	virtual void Update(float dt);

	virtual glm::mat4 GetViewMatrix() const;

	void SetTargetModel(Model* m);
	void SetRadius(float r);

private:
	glm::vec3 mPosition;	
	float mHorizontalAngle; // horizontal angle
	float mVerticalAngle;   // vertical angle

	Model* mTargetModel;
	float mRadius;

	float mSpeed;			// World units per second
	float mAngularSpeed;    // Degrees per pixel

	glm::vec3 mLookAt;
};
