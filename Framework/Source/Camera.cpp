//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#pragma once

#include "Camera.h"
#include "FirstPersonCamera.h"
#include <GLM/gtx/transform.hpp>

using namespace glm;

float Camera::fieldOfView = 45.0f;

Camera::Camera()
{
}

Camera::~Camera()
{
}

/**
 *	ViewProjection matrix is derived from matrix multiplication respective of this order of the projection matrix, world matrix, model matrix 
 *	return: ViewProjection Matrix
 */
mat4 Camera::GetViewProjectionMatrix() const
{
	// @TODO 1 - Calculate View Projection Matrix
	//           The projection matrix is hardcoded below
	//           The view matrix is set in the derived camera classes.
   
   	return this->GetProjectionMatrix() * this->GetViewMatrix();
}


glm::mat4 Camera::GetProjectionMatrix() const {
	return perspective(Camera::fieldOfView, 4.0f / 3.0f, 0.1f, 100.0f);
}

/**
  *	Zooming functionality call back function confining field of view within upper and lower boundaries
  * Must remain between [0, 180] degrees, otherwise the image flips
  */
void Camera::scrollCallBack(GLFWwindow* window, double xOffset, double yOffset) {
	
	float multiplier = 5.0f; //arbitrary
	float zoom = (float)yOffset * multiplier;
	float lowerBound = 15.0f;
	float upperBound = 155.0f;

	if(Camera::fieldOfView + zoom <= lowerBound) {
		Camera::fieldOfView = lowerBound;
	} else if(Camera::fieldOfView + zoom >= upperBound) {
		Camera::fieldOfView = upperBound;
	} else {
		Camera::fieldOfView += zoom;
	}
}