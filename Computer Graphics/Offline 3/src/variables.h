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

vector< Object<Ftype> * > objects;
vector< Light<Ftype> * > lights;
int recursionLevel;
int pixelDimension;
int nObjects;

Vec3<Ftype> cameraPos;
Vec3<Ftype> cameraUpDir;
Vec3<Ftype> cameraRightDir;
Vec3<Ftype> cameraLookDir;

int drawgrid;
int drawaxes;
double angle;

#endif /* C01156FF_D2B7_456A_A91A_ED5F655770C0 */
