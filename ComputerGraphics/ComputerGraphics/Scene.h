#pragma once
#include "Object.h"

class Framework;

class Scene
{
public:
	enum SceneTag {
		Title
		, Main
	};

	Scene();
	Scene(SceneTag tag, Framework* framework);
	virtual ~Scene();	// CScene을 상속받은 타이틀씬의 소멸자도 ~CScene();이 된다. 그럼 타이틀씬이 소멸할 때 이 소멸자도 받아온다.
						// 이미 소멸자가 있는데 타이틀씬이 상위계층을 신경써서 지울 필요가 없다. 따라서, virtual을 붙여 상속받아 소멸시킨다.
						// virtual 타고 상위 클래스의 끝까지 올라간 다음, 하위 소멸자를 전부 호출해서 상속받은 클래스를 한번에 소멸시키는 것이다.

	virtual void OnCreate() = 0;		// 만들때 선언용 함수

	virtual void BuildObjects() = 0;
	virtual void Update(float fTimeElapsed) = 0;
	virtual void Render() = 0;
	//protected:
	SceneTag m_Tag;
	Framework* pFramework;	// 인자로 받아오는게 아니라 동적할당을 해온다.
};

