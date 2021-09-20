#include "stdafx.h"
#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

Scene::Scene(SceneTag tag, Framework* framework)
{
	m_Tag = tag;
	pFramework = framework;
}
