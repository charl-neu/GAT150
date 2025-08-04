//Old project, code no longer works with new Engine setup


/*
#include <iostream>
#include <vector>
#include <fmod.hpp>
#include "Input/Input System.h"
#include <SDL3/SDL.h>
#include "Renderer/Renderer.h"

int main(int argc, char* argv[]) {

	FMOD::System* audio;
	FMOD::System_Create(&audio);

	viper::InputSystem input;
	input.Initialize();

	viper::Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Viper Engine", 1280, 1024);

	void* extradriverdata = nullptr;
	audio->init(32, FMOD_INIT_NORMAL, extradriverdata);
	
	FMOD::Sound* sound = nullptr;
	std::vector<FMOD::Sound*> sounds;

	audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("open-hat.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	SDL_Event e;
	bool quit = false;

	while (!quit) {

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT) {
				quit = true;
			}
		}

		audio->update();
		input.Update();
		
		renderer.SetColoru(0, 0, 0);
		renderer.Clear();


		if (input.GetKeyDown(SDL_SCANCODE_Q) && !input.GetPreviousKeyDown(SDL_SCANCODE_Q))
		{
			// play bass 
			audio->playSound(sounds[0], nullptr, false, nullptr);
		}

		if (input.GetKeyDown(SDL_SCANCODE_W) && !input.GetPreviousKeyDown(SDL_SCANCODE_W))
		{
			// play snare
			audio->playSound(sounds[1], nullptr, false, nullptr);
		}

		if (input.GetKeyDown(SDL_SCANCODE_E) && !input.GetPreviousKeyDown(SDL_SCANCODE_E))
		{
			// play hihat 
			audio->playSound(sounds[2], nullptr, false, nullptr);
		}

		renderer.Present();
	}

	renderer.Shutdown();
	audio->release();
	input.Shutdown();
}
*/

int main(int argc, char* argv[]) {
	return 0;
}