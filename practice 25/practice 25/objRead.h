#pragma once
#include "stdafx.h"

extern std::vector< glm::vec3 > outvertex, outnormal;

int loadObj(const char* filename);
int loadObj_normalize_center(const char* filename);
