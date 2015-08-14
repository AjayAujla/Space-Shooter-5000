//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "ThirdPersonCamera.h"
#include "EventManager.h"
#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>
#include <algorithm>
#include <math.h>


using namespace glm;

ThirdPersonCamera::ThirdPersonCamera(glm::vec3 position, Model* m, float radius) : Camera(), mPosition(position), mTargetModel(m), mLookAt(0.0f, 0.0f, -1.0f), mHorizontalAngle(90.0f), mVerticalAngle(0.0f), mSpeed(5.0f), mAngularSpeed(2.5f), toggleCinematic(false), mCinematicRadius(3), mCurrentTime(0.0f), mRadius(radius)
{
}

ThirdPersonCamera::ThirdPersonCamera(glm::vec3 position, Model* m) :  Camera(), mPosition(position), mTargetModel(m), mLookAt(0.0f, 0.0f, -1.0f), mHorizontalAngle(90.0f), mVerticalAngle(0.0f), mSpeed(5.0f), mAngularSpeed(2.5f), toggleCinematic(false), mCinematicRadius(3), mCurrentTime(0.0f)
{
}

ThirdPersonCamera::~ThirdPersonCamera()
{
}

void ThirdPersonCamera::SetTargetModel(Model* m){
	mTargetModel = m;
}

void ThirdPersonCamera::SetRadius(float r){
	mRadius = r;
}

void ThirdPersonCamera::Update(float dt)
{
	// Prevent from having the camera move only when the cursor is within the windows
	EventManager::DisableMouseCursor();


	// The Camera moves based on the User inputs
	// - You can access the mouse motion with EventManager::GetMouseMotionXY()
	// - For mapping A S D W, you can look in World.cpp for an example of accessing key states
	// - Don't forget to use dt to control the speed of the camera motion

	// Mouse motion to get the variation in angle
	mHorizontalAngle -= EventManager::GetMouseMotionX() * mAngularSpeed * dt;
	mVerticalAngle   -= EventManager::GetMouseMotionY() * mAngularSpeed * dt;

	// Clamp vertical angle to [-85, 85] degrees
	mVerticalAngle = std::max(-85.0f, std::min(85.0f, mVerticalAngle));
	if (mHorizontalAngle > 360)
	{
		mHorizontalAngle -= 360;
	}
	else if (mHorizontalAngle < -360)
	{
		mHorizontalAngle += 360;
	}

	float theta = radians(mHorizontalAngle);
	float phi = radians(mVerticalAngle);

	mLookAt = vec3(cosf(phi)*cosf(theta), sinf(phi), -cosf(phi)*sinf(theta));
	
	vec3 sideVector = glm::cross(mLookAt, vec3(0.0f, 1.0f, 0.0f));
	glm::normalize(sideVector);

	mCurrentTime += dt;
	if (mCurrentTime > 10 * 3.14159265358979323846) mCurrentTime = 0;//loop at 10pi

	


	if (!toggleCinematic){
		// A S D W for motion along the camera basis vectors
		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			//mPosition +=  glm::vec3(0.0,1.0,0.0) * dt * mSpeed;
			mTargetModel->SetPosition(mTargetModel->GetPosition() + vec3(0.0, 1.0, 0.0)*dt*mSpeed);
		}

		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			//mPosition -= glm::vec3(0.0, 1.0, 0.0) * dt * mSpeed;
			mTargetModel->SetPosition(mTargetModel->GetPosition() - vec3(0.0, 1.0, 0.0)*dt*mSpeed);
		}

		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
		{
			//mPosition += mLookAt * dt * mSpeed;
			mTargetModel->SetPosition(mTargetModel->GetPosition() + mLookAt*dt*mSpeed);
		}

		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
		{
			//mPosition -= mLookAt * dt * mSpeed;
			mTargetModel->SetPosition(mTargetModel->GetPosition() - mLookAt*dt*mSpeed);
		}

		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
		{
			//mPosition += sideVector * dt * mSpeed;
			mTargetModel->SetPosition(mTargetModel->GetPosition() + sideVector*dt*mSpeed);
		}

		if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
		{
			//mPosition -= sideVector * dt * mSpeed;
			mTargetModel->SetPosition(mTargetModel->GetPosition() - sideVector*dt*mSpeed);
		}

		//Simon addition
		//model positioning in front of our third person camera
		mPosition = mTargetModel->GetPosition() - mLookAt*mRadius + vec3(0.0f, 2.0f, 0.0f);
	}
	else{
		//if cinematic, then reposition camera according to function and update lookAt
		vec3 ellipsePosition = vec3(1.6f * mCinematicRadius * cos(mCurrentTime), 1.5 + 1.5*sin(mCurrentTime - (3.14159265358979323846 / 2.0)), mCinematicRadius * sin(mCurrentTime));
		mPosition = mTargetModel->GetPosition() + ellipsePosition;
		mLookAt = normalize(mTargetModel->GetPosition() - mPosition);
	}
	glfwSetScrollCallback(EventManager::GetWindow(), scrollCallBack);
}

glm::mat4 ThirdPersonCamera::GetViewMatrix() const
{
	return glm::lookAt(	mPosition, mPosition + mLookAt, vec3(0.0f, 1.0f, 0.0f) );
}