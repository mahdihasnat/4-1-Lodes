#ifndef C01156FF_D2B7_456A_A91A_ED5F655770C0
#define C01156FF_D2B7_456A_A91A_ED5F655770C0

#include "common.h"

typedef double Ftype;

template<typename T>
class Object;

template<typename T>
class Vec3;

template<typename T>
class Light;

vector< UniquePtr<Object<Ftype> > > objects;
vector< UniquePtr<Light<Ftype> > > lights;
int recursionLevel;
int imageWidth;
int imageHeight;
int nObjects;

Vec3<Ftype> cameraPos;
Vec3<Ftype> cameraUpDir;
Vec3<Ftype> cameraRightDir;
Vec3<Ftype> cameraLookDir;

int drawgrid;
int drawaxes;
double angle;

// glWindowSize
const int windowHeight = 500;
const int windowWidth = 500;
// glPerspective
const double fieldOfView = 80;
const double aspectRatio = windowWidth / windowHeight;
const double nearPlane = 0.5;
const double farPlane = 1000.0;
#endif /* C01156FF_D2B7_456A_A91A_ED5F655770C0 */
