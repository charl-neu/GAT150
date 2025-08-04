//Old project, code no longer works with new Engine setup


/*
#include "Math/Math.h"
#include "Math\Vector2.h"
#include "Renderer/Renderer.h"
#include <Input/Input System.h>


#include <SDL3/SDL.h>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    std::vector<viper::vec2> points;

    viper::InputSystem inputSystem;
    inputSystem.Initialize();

    viper::Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("Viper Engine", 1280, 1024);

    SDL_Event e;
    bool quit = false;

    while (!quit) {


        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

		inputSystem.Update();
        renderer.SetColor(0, 0, 0);
		renderer.Clear();



        
         Step 1: Point addition to draw lines
        
        
        if (inputSystem.GetMouseButtonPressed(viper::InputSystem::MouseButton::Left)) {
            points.push_back(inputSystem.GetMousePosition());
        }
        for (int i = 0; i < (int)points.size() - 1; i++) {
            renderer.SetColor(255, 255, 255);
            renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }
        


        
        // Step 2: Click and drag drawing


        if (inputSystem.GetMouseButtonDown(viper::InputSystem::MouseButton::Left)) {
            viper::vec2 position = inputSystem.GetMousePosition();
            if (points.empty()) points.push_back(position);
            else if ((position - points.back()).Length() > 10) points.push_back(position);
        }
        for (int i = 0; i < (int)points.size() - 1; i++) {
            renderer.SetColor(255, 255, 255);
            renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }
        
        
        renderer.Present();
    }

	renderer.Shutdown();
}
*/

int main(int argc, char* argv[]) {
    return 0;
}