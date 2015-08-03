//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 15/7/15.
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#pragma once


// Simple Texture Loader Class
class TextureLoader
{
public:
    static int LoadTexture(const char * imagepath);
	static void toggleWireframe();

private:
    static bool toggle;
};