//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#include "World.h"
#include "Renderer.h"
#include "ParsingHelper.h"

#include "StaticCamera.h"
#include "FirstPersonCamera.h"
#include "ThirdPersonCamera.h"

#include "CubeModel.h"
#include "SphereModel.h"
#include "AsteroidModel.h"
#include "Animation.h"
#include "Billboard.h"
#include <GLFW/glfw3.h>
#include "EventManager.h"
#include "TextureLoader.h"

#include "ParticleDescriptor.h"
#include "ParticleEmitter.h"
#include "ParticleSystem.h"

using namespace std;
using namespace glm;

World* World::instance;

World::World()
{
    instance = this;


	this->spaceship = new Spaceship();
	this->spaceship->SetScaling(vec3(1.0f, 1.0f, 1.0f));
	mModel.push_back(this->spaceship);

	//setup sphere model 1
	this->sphere1 = new SphereModel(TextureLoader::LoadTexture("..\\Assets\\Textures\\asteroidTexture.jpg"));
	this->sphere1->SetPosition(vec3(5.0f, 5.0f, -20.0f));
	this->sphere1->SetVelocity(vec3(1.0f, 0.0f, 0.0f));

	this->emitter = new ParticleEmitter(vec3(0.0f, 0.0f, 0.0f), this->sphere1);
	this->desc = new ParticleDescriptor();

	desc->SetFireDescriptor();

	this->particleSystem = new ParticleSystem(emitter, desc);
	AddParticleSystem(this->particleSystem);

	mModel.push_back(this->sphere1);

	//setup sphere model 2
	this->sphere2 = new SphereModel(TextureLoader::LoadTexture("..\\Assets\\Textures\\asteroidTexture.jpg"));
	this->sphere2->SetPosition(vec3(5.0f, 5.0f, -20.0f));
	this->sphere2->SetVelocity(vec3(0.0f, 0.0f, 1.0f));

	this->emitter = new ParticleEmitter(vec3(0.0f, 0.0f, 0.0f), this->sphere2);
	this->desc = new ParticleDescriptor();

	desc->SetFireDescriptor();

	this->particleSystem = new ParticleSystem(emitter, desc);
	AddParticleSystem(this->particleSystem);

	mModel.push_back(this->sphere2);


	
#if defined(PLATFORM_OSX)
	std::string texturePathPrefix = "Textures\\";
#else
    std::string texturePathPrefix = "..\\Assets\\Textures\\";
#endif
	this->skybox = new Skybox(vec3(100.0f, 100.0f, 100.0f), texturePathPrefix + "skyboxPositiveX.png", texturePathPrefix + "skyboxNegativeX.png", texturePathPrefix + "skyboxPositiveY.png", texturePathPrefix + "skyboxNegativeY.png", texturePathPrefix + "skyboxPositiveZ.png", texturePathPrefix + "skyboxNegativeZ.png");

	// Setup Camera
	mCamera.push_back(new ThirdPersonCamera(vec3(3.0f, 1.0f, 5.0f), this->spaceship, 5.0f));
	
	ThirdPersonCamera* newCam = new ThirdPersonCamera(vec3(3.0f, 1.0f, 5.0f), spaceship);
	newCam->SetCinematic(true);
	newCam->SetCinematicRadius(6.0f);
	mCamera.push_back(newCam);

	mCamera.push_back(new FirstPersonCamera(vec3(3.0f, 1.0f, 5.0f)));
	mCamera.push_back(new StaticCamera(vec3(3.0f, 30.0f, 5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)));
	mCamera.push_back(new StaticCamera(vec3(0.5f,  0.5f, 5.0f), vec3(0.0f, 0.5f, 0.0f), vec3(0.0f, 1.0f, 0.0f)));
	mCurrentCamera = 0;

#if defined(PLATFORM_OSX)
    int billboardTextureID = TextureLoader::LoadTexture("Textures/Particle.png");
#else
    int billboardTextureID = TextureLoader::LoadTexture("../Assets/Textures/Particle.png");
#endif
    assert(billboardTextureID != 0);

    mpBillboardList = new BillboardList(2048, billboardTextureID);
    
    ParticleDescriptor* asteroidDescriptor = new ParticleDescriptor();
    asteroidDescriptor->SetAsteroidDescriptor();
    
    ParticleEmitter* emitter = new ParticleEmitter(vec3(0.0f, 0.0f, 0.0f));
    
    mAsteroidSystem = new AsteroidSystem(emitter, asteroidDescriptor);
}

World::~World()
{
	// Models
	for (vector<Model*>::iterator it = mModel.begin(); it < mModel.end(); ++it)
	{
		delete *it;
	}

	mModel.clear();

	for (vector<Animation*>::iterator it = mAnimation.begin(); it < mAnimation.end(); ++it)
	{
		delete *it;
	}

	mAnimation.clear();

	for (vector<AnimationKey*>::iterator it = mAnimationKey.begin(); it < mAnimationKey.end(); ++it)
	{
		delete *it;
	}

	mAnimationKey.clear();

	// Camera
	for (vector<Camera*>::iterator it = mCamera.begin(); it < mCamera.end(); ++it)
	{
		delete *it;
	}
	mCamera.clear();

	delete mpBillboardList;
}

World* World::GetInstance()
{
    return instance;
}

void World::Update(float dt)
{
	// User Inputs
	// 1 2 3 4 to change the Camera
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_1 ) == GLFW_PRESS)
	{
		mCurrentCamera = 0;
	}
	else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_2 ) == GLFW_PRESS)
	{
		if (mCamera.size() > 1)
		{
			mCurrentCamera = 1;
		}
	}
	else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_3 ) == GLFW_PRESS)
	{
		if (mCamera.size() > 2)
		{
			mCurrentCamera = 2;
		}
	} else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_4 ) == GLFW_PRESS)
	{
		if (mCamera.size() > 3)
		{
			mCurrentCamera = 3;
		}
	}

	// R to reset camera field of view
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_R ) == GLFW_PRESS)
	{
		mCamera[mCurrentCamera]->fieldOfView = 45.0f;
	}
	
	// 0 9 to change the shader
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_0 ) == GLFW_PRESS)
	{
		Renderer::SetShader(SHADER_SOLID_COLOR);
	}
	else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_9 ) == GLFW_PRESS)
	{
		Renderer::SetShader(SHADER_BLUE);
	}

    // Update animation and keys
    for (vector<Animation*>::iterator it = mAnimation.begin(); it < mAnimation.end(); ++it)
    {
        (*it)->Update(dt);
    }
    
    for (vector<AnimationKey*>::iterator it = mAnimationKey.begin(); it < mAnimationKey.end(); ++it)
    {
        (*it)->Update(dt);
    }


	// Update current Camera
	mCamera[mCurrentCamera]->Update(dt);

	// Update models
	for (vector<Model*>::iterator it = mModel.begin(); it < mModel.end(); ++it)
	{
		(*it)->Update(dt);
	}
    
    // Update billboards
    
    for (vector<ParticleSystem*>::iterator it = mParticleSystemList.begin(); it != mParticleSystemList.end(); ++it)
    {
        (*it)->Update(dt);
    }
    
    mAsteroidSystem->Update(dt);

    mpBillboardList->Update(dt);

	// M to toggle wireframe textures
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_M ) == GLFW_PRESS)
	{
		Renderer::toggleWireframe();
	}

	// Left mouse button projectiles in camera lookAt vector direction
	if(glfwGetMouseButton(EventManager::GetWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		mat4 viewMatrix = mCamera[mCurrentCamera]->GetViewMatrix();
		vec3 cameraLookAtVector = -normalize(vec3(viewMatrix[0][2], viewMatrix[1][2], viewMatrix[2][2]));
		
		this->spaceship->shoot(cameraLookAtVector);
	}

	//Collision Detection
	vector<Projectile*> projectileContainer = this->spaceship->getProjectileContainer();
	vector<Asteroid*> asteroidContainer = mAsteroidSystem->getAsteroidList();
	
	for (int i = 0; i < projectileContainer.size(); ++i) {
		if (projectileContainer[i]->outOfRange) continue;
		
		//for (int j = i+1; j < projectileContainer.size(); ++j) {
			//collide(projectileContainer[i],projectileContainer[j]);
		//}

		for (int j = 1; j < this->mModel.size(); ++j) {
			collide(projectileContainer[i],mModel[j]);
		}
		for (int j = 1; j < asteroidContainer.size(); ++j) {
			collide(projectileContainer[i],asteroidContainer[j]);
		}
	}
	for (int i = 0; i<mModel.size();++i){
		for (int j=i+1; j<mModel.size();++j){
			collide(mModel[i],mModel[j]);
		}
		for (int j = 1; j < asteroidContainer.size(); ++j) {
			collide(mModel[i],asteroidContainer[j]);
		}
	}
	//end collision detection

	this->skybox->Update(dt);
}

//returns true if there was a collision, false otherwise
bool World::collide(Model* m1, Model* m2){
	vec3 p1 = m1->GetPosition();
	vec3 p2 = m2->GetPosition();
	vec3 dp = p2-p1;
	float norm2 = dp.x*dp.x+dp.y*dp.y+dp.z*dp.z;
	if(norm2 <= m1->GetRadius() + m2->GetRadius()){
		//there was a collision, update velocities

		//cout << "there was a collision" << endl;
		//TODO
		m2->SetVelocity(m2->GetVelocity() + 0.5f * m1->GetVelocity());
		m1->SetVelocity(-1.0f * m1->GetVelocity());

		return true;
	}
	//no collision
	return false;
	
}

void World::Draw()
{
	Renderer::BeginFrame();
	
	// Set shader to use
	glUseProgram(Renderer::GetShaderProgramID());

	// Material Coefficients
	const float ka = 0.2f;
	const float kd = 0.8f;
	const float ks = 0.2f;
	const float n = 90.0f;

	// Light Coefficients
	const vec3 lightColor(1.0f, 1.0f, 1.0f);
	const float lightKc = 0.0f;
	const float lightKl = 0.0f;
	const float lightKq = 1.0f;
	const vec4 lightPosition[3] = { vec4(5.0f, 5.0f, -20.0f, 1.0f),
									vec4(-20.0f, 5.0f, 5.0f, 1.0f),
									vec4(5.0f, 5.0f, 20.0f, 1.0f), };

	// This looks for the MVP Uniform variable in the Vertex Program
	GLuint VPMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "ViewProjectionTransform");
	
	// Get a handle for our Transformation Matrices uniform
	GLuint WorldMatrixID = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform");
	GLuint ViewMatrixID = glGetUniformLocation(Renderer::GetShaderProgramID(), "ViewTransform");
	GLuint ProjMatrixID = glGetUniformLocation(Renderer::GetShaderProgramID(), "ProjectionTransform");

	// Get a handle for Light Attributes uniform
	GLuint LightPosition1ID = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldLightPosition[0]");
	GLuint LightPosition2ID = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldLightPosition[1]");
	GLuint LightPosition3ID = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldLightPosition[2]");
	GLuint LightColorID = glGetUniformLocation(Renderer::GetShaderProgramID(), "lightColor");
	GLuint LightAttenuationID = glGetUniformLocation(Renderer::GetShaderProgramID(), "lightAttenuation");

	// Get a handle for Material Attributes uniform
	GLuint MaterialAmbientID = glGetUniformLocation(Renderer::GetShaderProgramID(), "materialAmbient");
	GLuint MaterialDiffuseID = glGetUniformLocation(Renderer::GetShaderProgramID(), "materialDiffuse");
	GLuint MaterialSpecularID = glGetUniformLocation(Renderer::GetShaderProgramID(), "materialSpecular");
	GLuint MaterialExponentID = glGetUniformLocation(Renderer::GetShaderProgramID(), "materialExponent");

	// Send the view projection constants to the shader
	mat4 VP = mCamera[mCurrentCamera]->GetViewProjectionMatrix();
	glUniformMatrix4fv(VPMatrixLocation, 1, GL_FALSE, &VP[0][0]);

	mat4 V = mCamera[mCurrentCamera]->GetViewMatrix();
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &V[0][0]);
	mat4 P = mCamera[mCurrentCamera]->GetProjectionMatrix();
	glUniformMatrix4fv(ProjMatrixID, 1, GL_FALSE, &P[0][0]);

	// Draw the Vertex Buffer

	// Set shader constants
	glUniform1f(MaterialAmbientID, ka);
	glUniform1f(MaterialDiffuseID, kd);
	glUniform1f(MaterialSpecularID, ks);
	glUniform1f(MaterialExponentID, n);

	glUniform4f(LightPosition1ID, lightPosition[0].x, lightPosition[0].y, lightPosition[0].z, lightPosition[0].w);
	glUniform4f(LightPosition2ID, lightPosition[1].x, lightPosition[1].y, lightPosition[1].z, lightPosition[1].w);
	glUniform4f(LightPosition3ID, lightPosition[2].x, lightPosition[2].y, lightPosition[2].z, lightPosition[2].w);
	glUniform3f(LightColorID, lightColor.r, lightColor.g, lightColor.b);
	glUniform3f(LightAttenuationID, lightKc, lightKl, lightKq);

	// Draw models
	for (vector<Model*>::iterator it = mModel.begin(); it < mModel.end(); ++it)
	{
		(*it)->Draw();
	}

	mAsteroidSystem->Draw();

	// Draw Path Lines
	
	// Set Shader for path lines
	unsigned int prevShader = Renderer::GetCurrentShader();
	//Renderer::SetShader(SHADER_PATH_LINES);
	glUseProgram(Renderer::GetShaderProgramID());

	// Send the view projection constants to the shader
	VPMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "ViewProjectionTransform");
	glUniformMatrix4fv(VPMatrixLocation, 1, GL_FALSE, &VP[0][0]);

	for (vector<Animation*>::iterator it = mAnimation.begin(); it < mAnimation.end(); ++it)
	{
		mat4 VP = mCamera[mCurrentCamera]->GetViewProjectionMatrix();
		glUniformMatrix4fv(VPMatrixLocation, 1, GL_FALSE, &VP[0][0]);

		(*it)->Draw();
	}

	for (vector<AnimationKey*>::iterator it = mAnimationKey.begin(); it < mAnimationKey.end(); ++it)
	{
		mat4 VP = mCamera[mCurrentCamera]->GetViewProjectionMatrix();
		glUniformMatrix4fv(VPMatrixLocation, 1, GL_FALSE, &VP[0][0]);

		(*it)->Draw();
	}

    Renderer::CheckForErrors();
    
    // Draw Billboards
    mpBillboardList->Draw();

	this->skybox->Draw();

	// Restore previous shader
	Renderer::SetShader((ShaderType) prevShader);

	Renderer::EndFrame();
}

void World::LoadScene(const char * scene_path)
{
	// Using case-insensitive strings and streams for easier parsing
	ci_ifstream input;
	input.open(scene_path, ios::in);

	// Invalid file
	if(input.fail() )
	{	 
		fprintf(stderr, "Error loading file: %s\n", scene_path);
		getchar();
		exit(-1);
	}

	ci_string item;
	while( std::getline( input, item, '[' ) )   
	{
        ci_istringstream iss( item );

		ci_string result;
		if( std::getline( iss, result, ']') )
		{
			if( result == "cube" )
			{
				CubeModel* cube = new CubeModel();
				cube->Load(iss);
				mModel.push_back(cube);
            }
            else if( result == "sphere" )
            {
				#if defined(PLATFORM_OSX)
					int sphereTextureID = TextureLoader::LoadTexture("Textures/moonTexture.jpg");
				#else
					int sphereTextureID = TextureLoader::LoadTexture("../Assets/Textures/moonTexture.jpg");
				#endif
                
				SphereModel* moon = new SphereModel(sphereTextureID, vec3(10.0f, 10.0f, 10.0f));
                moon->Load(iss);
                mModel.push_back(moon);
            }
			else if ( result == "animationkey" )
			{
				AnimationKey* key = new AnimationKey();
				key->Load(iss);
				mAnimationKey.push_back(key);
			}
			else if (result == "animation")
			{
				Animation* anim = new Animation();
				anim->Load(iss);
				mAnimation.push_back(anim);
			}
			else if ( result.empty() == false && result[0] == '#')
			{
				// this is a comment line
			}
			else
			{
				fprintf(stderr, "Error loading scene file... !");
				getchar();
				exit(-1);
			}
	    }
	}
	input.close();

	// Set Animation vertex buffers
	for (vector<Animation*>::iterator it = mAnimation.begin(); it < mAnimation.end(); ++it)
	{
		// Draw model
		(*it)->CreateVertexBuffer();
	}
}

Animation* World::FindAnimation(ci_string animName)
{
    for(std::vector<Animation*>::iterator it = mAnimation.begin(); it < mAnimation.end(); ++it)
    {
        if((*it)->GetName() == animName)
        {
            return *it;
        }
    }
    return nullptr;
}

AnimationKey* World::FindAnimationKey(ci_string keyName)
{
    for(std::vector<AnimationKey*>::iterator it = mAnimationKey.begin(); it < mAnimationKey.end(); ++it)
    {
        if((*it)->GetName() == keyName)
        {
            return *it;
        }
    }
    return nullptr;
}

const Camera* World::GetCurrentCamera() const
{
     return mCamera[mCurrentCamera];
}

void World::AddBillboard(Billboard* b)
{
    mpBillboardList->AddBillboard(b);
}

void World::RemoveBillboard(Billboard* b)
{
    mpBillboardList->RemoveBillboard(b);
}

void World::AddParticleSystem(ParticleSystem* particleSystem)
{
    mParticleSystemList.push_back(particleSystem);
}

void World::RemoveParticleSystem(ParticleSystem* particleSystem)
{
    vector<ParticleSystem*>::iterator it = std::find(mParticleSystemList.begin(), mParticleSystemList.end(), particleSystem);
    mParticleSystemList.erase(it);
}