#include "Game/Actor.h"
#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"
#include "Core/Random.h"
#include "Core/Time.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Input/Input System.h"
#include "Audio/Audio System.h"
#include "game/scene.h"
#include "Engine.h"
#include "Renderer/font.h"
#include "Renderer/text.h"

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <memory>

#define RENDERER viper::GetEngine().GetRenderer()
#define AUDIO viper::GetEngine().GetAudioSystem()
#define INPUT viper::GetEngine().GetInputSystem()
#define TIME viper::GetEngine().GetTime()

int main(int argc, char* argv[]) {

    //init engine
    viper::GetEngine().Initialize();

    viper::Font* font = new viper::Font();
    font->Load("bsde.ttf", 20);

    viper::Text* text = new viper::Text(font);
    text->Create(RENDERER, "Hello World", viper::vec3{ 1, 1, 1 });


    SDL_Event e;
    bool quit = false;

    //main loop
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        //update engine systems
        viper::GetEngine().Update();


        viper::vec3 color{ 1, 1, 1 };

        RENDERER.SetColor(0.0f, 0.0f, 0.0f);
        RENDERER.Clear();

        text->Draw(RENDERER, 40.0f, 40.0f);

        RENDERER.Present();

    }

    viper::GetEngine().Shutdown();

    return 0;
}