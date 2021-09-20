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
	virtual ~Scene();	// CScene�� ��ӹ��� Ÿ��Ʋ���� �Ҹ��ڵ� ~CScene();�� �ȴ�. �׷� Ÿ��Ʋ���� �Ҹ��� �� �� �Ҹ��ڵ� �޾ƿ´�.
						// �̹� �Ҹ��ڰ� �ִµ� Ÿ��Ʋ���� ���������� �Ű�Ἥ ���� �ʿ䰡 ����. ����, virtual�� �ٿ� ��ӹ޾� �Ҹ��Ų��.
						// virtual Ÿ�� ���� Ŭ������ ������ �ö� ����, ���� �Ҹ��ڸ� ���� ȣ���ؼ� ��ӹ��� Ŭ������ �ѹ��� �Ҹ��Ű�� ���̴�.

	virtual void OnCreate() = 0;		// ���鶧 ����� �Լ�

	virtual void BuildObjects() = 0;
	virtual void Update(float fTimeElapsed) = 0;
	virtual void Render() = 0;
	//protected:
	SceneTag m_Tag;
	Framework* pFramework;	// ���ڷ� �޾ƿ��°� �ƴ϶� �����Ҵ��� �ؿ´�.
};

