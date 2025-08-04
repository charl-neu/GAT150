#pragma once
#include "../Core/StringHelperr.h"
#include <vector>
#include <memory>
#include <string>
#include <list>

namespace viper {
	class Game;

	class Scene
	{
	public:
		Scene(Game* game) : m_game(game) {}

		void Update(float deltaTime);
		void Draw(class Renderer& renderer);

		void AddActor(std::unique_ptr<class Actor> actor);
		void RemoveAllActors();

		template<typename T = Actor>
		T* GetActorByName(const std::string& name);

		template<typename T = Actor>
		std::vector<T*> GetActorsByTag(const std::string& tag);

		Game* GetGame() const { return m_game; }

	private:
		Game* m_game{ nullptr };
		std::list<std::unique_ptr<class Actor>> m_actors;
	};

	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name)
	{
		for (auto& actr : m_actors) {
			if (toLower(actr->name) == toLower(name)) {
				T* object = dynamic_cast<T*>(actr.get());
				if (object) {
					return object;
				}
			}
		}
		return nullptr;
	}
	template<typename T>
	inline std::vector<T*> Scene::GetActorsByTag(const std::string& tag)
	{
		std::vector<T*> results;
		for (auto& actr : m_actors) {
			if (toLower(actr->tag) == toLower(tag)) {
				T* object = dynamic_cast<T*>(actr.get());
				if (object) {
					results.push_back(object);
				}
			}
		}
		return results;
	}
	
}