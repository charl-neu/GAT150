#include "Game/Actor.h"
#include "game/GamePlayer.h"
#include "game/GameGame.h"
#include "PlatformerGame.h"

#define RENDERER nebula::GetEngine().GetRenderer()
#define AUDIO nebula::GetEngine().GetAudioSystem()
#define INPUT nebula::GetEngine().GetInputSystem()
#define TIME nebula::GetEngine().GetTime()
#define PARTICLES nebula::GetEngine().GetParticleSystem()
#define JSON_READ(value, data) nebula::json::Read(value, #data, data)



int main(int argc, char* argv[]) {



    //set the file path
    nebula::file::SetCurrentDirectory("Assets/Platformer");
    
	auto spriteRenderer = nebula::Factory::Instance().Create<nebula::SpriteRenderer>("SpriteRenderer");
	auto meshRenderer = nebula::Factory::Instance().Create<nebula::MeshRenderer>("MeshRenderer");


    //init engine
	nebula::GetEngine().Initialize();

	std::unique_ptr<nebula::Game> game = std::make_unique<PlatformerGame>();
	game->Initialize();


    //create stars
    std::vector<nebula::vec2> stars;
    for (int i = 0; i < 100; i++)
    {
        stars.push_back(nebula::vec2{nebula::random::getReal() * 1280, nebula::random::getReal() * 1024});
    }

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
        nebula::GetEngine().Update();
        float dt = TIME.GetDeltatime();
        game->Update(dt);
		PARTICLES.Update(dt);



        if (INPUT.GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;


		nebula::vec3 color{ 1, 1, 1 };

        RENDERER.SetColor(0.0f, 0.0f, 0.0f);
        RENDERER.Clear();


        for(auto& star : stars)
        {
            RENDERER.SetColor(color.x, color.y, color.z);
            RENDERER.DrawPoint(star.x, star.y);
            star.x -= 50.0f * dt;
            star.y += 50.0f * dt;

            star.x = nebula::Wrap(star.x, 0.0f, 1280.0f);
            star.y = nebula::Wrap(star.y, 0.0f, 1024.0f);
		}

		game->Draw(RENDERER);


        RENDERER.Present();

    }
    
	game->Shutdown();
	game.release();
	nebula::GetEngine().Shutdown();

    return 0;
}