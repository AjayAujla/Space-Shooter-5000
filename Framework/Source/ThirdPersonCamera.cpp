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
using namespace std;

ThirdPersonCamera::ThirdPersonCamera(glm::vec3 position, Model* m, float radius) : Camera(), mPosition(position), mTargetModel(m), mLookAt(0.0f, 0.0f, -1.0f), mHorizontalAngle(90.0f), mVerticalAngle(0.0f), mSpeed(5.0f), mAngularSpeed(2.5f), toggleCinematic(false), mCinematicRadius(3), mCurrentTime(100.0f), mRadius(radius), numRotationsTillNewCurve(2), aRange(1.0f), bRange(1.0f), cRange(1.0f), firstEllipse(true)
{
}

ThirdPersonCamera::ThirdPersonCamera(glm::vec3 position, Model* m) : Camera(), mPosition(position), mTargetModel(m), mLookAt(0.0f, 0.0f, -1.0f), mHorizontalAngle(90.0f), mVerticalAngle(0.0f), mSpeed(5.0f), mAngularSpeed(2.5f), toggleCinematic(false), mCinematicRadius(3), mCurrentTime(100.0f), numRotationsTillNewCurve(2), aRange(1.0f), bRange(1.0f), cRange(1.0f), firstEllipse(true)
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
	//note that this currently ignore the velocity of the parent model, so no collisions with the main character

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
	if (mCurrentTime > numRotationsTillNewCurve * 3.14159265358979323846){//loop at t=2*pi*rotations 
		mCurrentTime = 0; 
		cout << "generating new ellipse" << endl;
		//should generate new ellipse here
		bool curveIsGood = false;
		//ellipse variables
		vec3 ptm;//point to match
		if(!firstEllipse) vec3 ptm = center + vec3(
			a*mCinematicRadius*cos(phase),
			-c,
			b*mCinematicRadius*sin(phase)
			);
		while (!curveIsGood){
			//generate curve
			center.x = EventManager::GetRandomFloat(0.0f, mCinematicRadius) - 0.5f*mCinematicRadius;
			center.y = 0.0f;
			center.z = EventManager::GetRandomFloat(0.0f,mCinematicRadius) - 0.5f*mCinematicRadius;
			ptm -= center;
			//if (!firstEllipse){
			//	a = EventManager::GetRandomFloat(1.0f, 1.0f + aRange) + center.x;
			//	phase = acos(ptm.x / a / mCinematicRadius);
			//	b = ptm.z / mCinematicRadius / sin(phase);
			//}
			//else{
				a = EventManager::GetRandomFloat(1.0f, 1.0f + aRange);
				phase = 0.0f;
				b = EventManager::GetRandomFloat(1.0f, 1.0f + bRange);
			//}
			c = EventManager::GetRandomFloat(1.0f, 1.0f + cRange);
			baseR = mCinematicRadius;

			//check intersection with planets
			//if (solarSystem == nullptr) break;//no planets, every curve is good
			//tmp
			sunPosition = vec3(0.0f, 0.0f, 0.0f);
			float sunRadius = 5.0f;
			//if planets, check for collisions over the next few loops
			curveIsGood = true;
			//custom for loop. check at numChecks intervals for intersection
			float tTmp = 0.0f;
			int numChecks = 300;
			float interval = 2 * 3.14159265358979323846*numRotationsTillNewCurve / 300.0f;
			int attempts = 0;
			while (tTmp < 2 * 3.14159265358979323846*numRotationsTillNewCurve){
				vec3 ellipsePos = center + vec3(
					a*mCinematicRadius*cos(tTmp + phase),
					-c*cos(tTmp),
					b*mCinematicRadius*sin(tTmp + phase)
					);
				//for (vector<Planet*>::iterator it = solarSystem->GetPlanets().begin(); it < solarSystem->GetPlanets().end(); ++it){
					//todo do nothing for now
				//}
				//check sun seperately
				//SphereModel* sun = solarSystem->GetSun();
				vec3 v = mTargetModel->GetPosition() + ellipsePos - sunPosition;
				float d2 = v.x*v.x + v.y*v.y + v.z*v.z;
				if (d2 <= sunRadius*sunRadius) {
					cout << "intersection, try again" << endl;
					curveIsGood = false;
					break;
				}
				

				tTmp += interval;
			}
			attempts++;
			if (attempts > 4){
				//adjust radius to larger because object in the way
				aRange *= 2;
				bRange *= 2;
				cRange *= 2;
			}
			//if not good, would be set in above for loop
			//if good, will exit while loop
		}
		firstEllipse = false;
	}

	


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
		vec3 ellipsePosition = center + vec3(
			a*mCinematicRadius*cos(mCurrentTime + phase),
			-cos(mCurrentTime),
			b*mCinematicRadius*sin(mCurrentTime + phase)
			);
		//vec3 ellipsePosition = vec3(1.6f * mCinematicRadius * cos(mCurrentTime), 1.5 + 1.5*sin(mCurrentTime - (3.14159265358979323846 / 2.0)), mCinematicRadius * sin(mCurrentTime));
		mPosition = mTargetModel->GetPosition() + ellipsePosition;
		mLookAt = normalize(mTargetModel->GetPosition() - mPosition);
	}
	glfwSetScrollCallback(EventManager::GetWindow(), scrollCallBack);
}

glm::mat4 ThirdPersonCamera::GetViewMatrix() const
{
	return glm::lookAt(	mPosition, mPosition + mLookAt, vec3(0.0f, 1.0f, 0.0f) );
}