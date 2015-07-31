//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#include "Animation.h"
#include "Renderer.h"
#include "World.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>


// Include GLEW - OpenGL Extension Wrangler
#include <GL/glew.h>

using namespace glm;
using namespace std;

AnimationKey::AnimationKey() : Model()
{
}

AnimationKey::~AnimationKey()
{
}

void AnimationKey::Update(float dt)
{
	Model::Update(dt);
}

void AnimationKey::Draw()
{
	Model::Draw();
}

bool AnimationKey::ParseLine(const std::vector<ci_string> &token)
{
	if (token.empty())
	{
		return true;
	}
	else
	{
		return Model::ParseLine(token);
	}
}

Animation::Animation() 
	: mName(""), mCurrentTime(0.0f), mDuration(0.0f), mVertexBufferID(0), mVertexArrayID(0)
{
}

Animation::~Animation()
{
}

void Animation::CreateVertexBuffer()
{
    // This is just to display lines between the animation keys
    for (int i=0; i<mKey.size(); ++i)
    {
//        cout << "mKey SIZE: " << mKey[i].GetName().c_str() << endl;
        
        Vertex v;
        v.position = mKey[i].mPosition;
        mVertexBuffer.push_back(v);
    }
    
	// Create a vertex array
	glGenVertexArrays(1, &mVertexArrayID);

	// Upload Vertex Buffer to the GPU, keep a reference to it (mVertexBufferID)
	glGenBuffers(1, &mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*mVertexBuffer.size(), &(mVertexBuffer[0]), GL_STATIC_DRAW);
}

void Animation::Update(float dt)
{
	mCurrentTime += dt;

    while(mCurrentTime > mDuration)
    {
        mCurrentTime -= mDuration;
    }
}

void Animation::Draw()
{
	// Draw lines between waypoints
	//
	// Steps:
	// - Draw the Vertex Buffer
	// - The Shader used to draw the Animation is AnimationLines, only requires to send the positions of the waypoints
	// - You need to bind the vertex buffer created in CreateVertexBuffer() as the input of the vertex shader
	// - Also set the WorldTransform uniform variable in the vertex shader
	// - You Should use GL_LINE_LOOP as a primitive to draw lines (not triangles)
	// - You can look at CubeModel::Draw() for a good example!

	// The Model View Projection transforms are computed in the Vertex Shader
	glBindVertexArray(mVertexArrayID);
	GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform");
    glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &mat4(1.0f)[0][0]);

	// 1st attribute buffer : vertex Positions
    glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(0,
		3,				// size
		GL_FLOAT,		// type
		GL_FALSE,		// normalized?
		sizeof(Vertex), // stride
		(void*)0        // array buffer offset
		);
    
	// Draw the triangles !
	glDrawArrays(GL_LINE_LOOP, 0, mVertexBuffer.size());

	glDisableVertexAttribArray(0);
}


void Animation::Load(ci_istringstream& iss)
{
	ci_string line;

	// Parse model line by line
	while(std::getline(iss, line))
	{
		// Splitting line into tokens
		ci_istringstream strstr(line);
		istream_iterator<ci_string, char, ci_char_traits> it(strstr);
		istream_iterator<ci_string, char, ci_char_traits> end;
		vector<ci_string> token(it, end);

		if (ParseLine(token) == false)
		{
			fprintf(stderr, "Error loading scene file... token:  %s!", token[0].c_str());
			getchar();
			exit(-1);
		}
	}
}


bool Animation::ParseLine(const std::vector<ci_string> &token)
{
    if (token.empty())
    {
        return true;
    }
	else if (token[0] == "name")
	{
		assert(token.size() > 2);
		assert(token[1] == "=");

		mName = token[2];
		return true;
	}
	else if (token[0] == "key")
	{
		assert(token.size() > 5);
        assert(token[1] == "=");
        assert(token[3] == "time");
        assert(token[4] == "=");

		ci_string name = token[2];
		AnimationKey *key = World::GetInstance()->FindAnimationKey(name);
        
		assert(key != nullptr);
		AddKey(key, atof(token[5].c_str()));
		return true;
	}
	return false;
}

void Animation::AddKey(AnimationKey* key, float time)
{
    assert(time >= mDuration);
	mKey.push_back(*key);
    mKeyTime.push_back(time);
    mDuration = time;
}

ci_string Animation::GetName() const
{
	return mName;
}

/**
 *	return: World Matrix
 */
glm::mat4 Animation::GetAnimationWorldMatrix() const
{
    // @TODO 3 - Find the 2 keys to interpolate the transformation
    //           Interpolate the position, scaling and rotation separately
    //           Finally concatenate the interpolated transforms into a single
    //           world transform and return it.
    
	int key1 = 0;
	int key2 = 0;
	float normalizedTime = 0.0f;

	for(int i = 0; i < this->mKey.size(); ++i) {
		if(this->mCurrentTime < this->mKeyTime[i]){
			key1 = i - 1;
			key2 = i;
			normalizedTime = (this->mCurrentTime - this->mKeyTime[key1])/(this->mKeyTime[key2] - this->mKeyTime[key1]);
			break;
		}
	}

	//Interpolate Between 2 Keys
	vec3 position = mix(this->mKey[key1].mPosition, this->mKey[key2].mPosition, normalizedTime);
	vec3 scaling = mix(this->mKey[key1].mScaling, this->mKey[key2].mScaling, normalizedTime);

	//2 Rotation States
	quat rotation1(angleAxis(this->mKey[key1].mRotationAngleInDegrees, this->mKey[key1].mRotationAxis));
	quat rotation2(angleAxis(this->mKey[key2].mRotationAngleInDegrees, this->mKey[key2].mRotationAxis));

	//Slerp
	quat rotation = slerp(rotation1, rotation2, normalizedTime);

	//Concatenate Interpolated Components to a Single World Transform
	mat4 worldMatrix(1.0f);
	mat4 translationMatrix = translate(worldMatrix, position);
	mat4 rotationMatrix = mat4_cast(rotation);
	mat4 scaleMatrix = scale(worldMatrix, scaling);
	return translationMatrix * rotationMatrix * scaleMatrix;
}
