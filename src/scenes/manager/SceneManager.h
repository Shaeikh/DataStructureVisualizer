#pragma once

#include <iostream>
#include <stack>
#include <memory>

#include <raylib.h>

//enum class SceneList
//{
//	NONE,
//	MAIN_MENU,
//	ARRAY
//};

class Scene
{
public:
	virtual void Render() = 0;
	virtual void Update(float dt) = 0;
	virtual ~Scene() {};
};

class SceneManager
{
private:
	std::stack<std::unique_ptr<Scene>> m_scenes;
	Scene *m_currentScene = nullptr;

public:
	void PushScene(std::unique_ptr<Scene> scene)
	{
		m_currentScene = scene.get();
		m_scenes.push(std::move(scene));
	}

	Scene *GetScene()
	{
		if (!m_scenes.empty())
			return m_scenes.top().get();
	}
	
	void PopScene()
	{
		if (!m_scenes.empty())
		{
			m_scenes.pop();
			if (!m_scenes.empty())
				m_currentScene = m_scenes.top().get();
			else
				m_currentScene = nullptr;
		}
	}

	void RenderScene()
	{
		if (!m_scenes.empty())
			m_scenes.top()->Render();
			
	}

	void UpdateScene(float dt)
	{
		if (!m_scenes.empty())
			m_scenes.top()->Update(dt);
	}
	
	void ClearScenes()
	{
		while (!m_scenes.empty())
			m_scenes.pop();
	}

};