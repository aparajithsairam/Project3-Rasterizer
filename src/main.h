// CIS565 CUDA Rasterizer: A simple rasterization pipeline for Patrick Cozzi's CIS565: GPU Computing at the University of Pennsylvania
// Written by Yining Karl Li, Copyright (c) 2012 University of Pennsylvania

#ifndef MAIN_H
#define MAIN_H

#ifdef __APPLE__
	#include <GL/glfw.h>
#else
	#include <GL/glew.h>
	#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <cuda_runtime.h>
#include <cutil_inline.h>
#include <cutil_gl_inline.h>
#include <cuda_gl_interop.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>
#include "glslUtility.h"
#include "glm/glm.hpp"
#include "rasterizeKernels.h"
#include "utilities.h"
#include "ObjCore/objloader.h"
#include "Light.h"

//ADDED
#include "glm/gtc/matrix_transform.hpp"
#include "Camera.h"

#include "EasyBMP.h"
#include "EasyBMP_BMP.h"
#include "EasyBMP_DataStructures.h"
#include "EasyBMP_VariousBMPutilities.h"
//ADDED

using namespace std;

//-------------------------------
//------------GL STUFF-----------
//-------------------------------
int frame;
int fpstracker;
double seconds;
int fps = 0;
GLuint positionLocation = 0;
GLuint texcoordsLocation = 1;
const char *attributeLocations[] = { "Position", "Tex" };
GLuint pbo = (GLuint)NULL;
GLuint displayImage;
uchar4 *dptr;

obj* mesh;
//ADDED
unsigned int numberOfMeshes = 0;
glm::vec3 currentForward;
glm::vec3 currentUp;
glm::vec3 currentEye;
float  fovy, aspectRatio;
float currentNear;
float currentFar;
float currentLeft;
float currentRight;
float currentBottom;
float currentTop;
Light *lights;
unsigned int numberOfLights = 2;
float *nbo;
int nbosize;
float *vto;
int vtosize;
unsigned char *textureImage;
int textureImageWidth, textureImageHeight;
//ADDED
float* vbo;
int vbosize;
float* cbo;
int cbosize;
int* ibo;
int ibosize;

//Mouse Interaction
Camera theCamera;
int theButtonState = 0;
int theModifierState = 0;
int mouseStartX, mouseEndX;
int mouseStartY, mouseEndY;
int lastX = 0, lastY = 0;
//Mouse Interaction

//-------------------------------
//----------CUDA STUFF-----------
//-------------------------------

int width=800; int height=800;

//-------------------------------
//-------------MAIN--------------
//-------------------------------

int main(int argc, char** argv);

//-------------------------------
//---------RUNTIME STUFF---------
//-------------------------------

void runCuda();

#ifdef __APPLE__
	void display();
#else
	void display();
	void keyboard(unsigned char key, int x, int y);
	void onMouseCb(int button, int state, int x, int y);
	void onMouseMotionCb(int x, int y);
	void initCamera();
#endif

//-------------------------------
//----------SETUP STUFF----------
//-------------------------------

#ifdef __APPLE__
	void init();
#else
	void init(int argc, char* argv[]);
#endif

void initPBO(GLuint* pbo);
void initCuda();
void initTextures();
void initVAO();
GLuint initShader(const char *vertexShaderPath, const char *fragmentShaderPath);

//-------------------------------
//---------CLEANUP STUFF---------
//-------------------------------

void cleanupCuda();
void deletePBO(GLuint* pbo);
void deleteTexture(GLuint* tex);
void shut_down(int return_code);

void initializeTextureData(std::string s);

#endif