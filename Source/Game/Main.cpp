#include "Game/Actor.h"
#include "game/GamePlayer.h"
#include "game/GameGame.h"

#define RENDERER viper::GetEngine().GetRenderer()
#define AUDIO viper::GetEngine().GetAudioSystem()
#define INPUT viper::GetEngine().GetInputSystem()
#define TIME viper::GetEngine().GetTime()
#define PARTICLES viper::GetEngine().GetParticleSystem()

int main(int argc, char* argv[]) {

    //set the file path
    viper::file::SetCurrentDirectory("Assets");


	std::ifstream file("test.txt");
    if (!file) {
        std::cerr << "Failed to open file: test.txt" << std::endl;
		return 1;
    }
	std::cout << "File opened successfully." << std::endl;
	std::cout << file.rdbuf(); // Read and print the file content

	viper::vec2 v{ 124.5f, 100.0f };
	std::cout << v << std::endl;

	std::string vstr("{124.5, 100.0}");
	std::stringstream ss(vstr);

	viper::vec2 v2;
    ss >> v2;
	std::cout << v2 << std::endl;

	return 0;


    //init engine
	viper::GetEngine().Initialize();

	std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
	game->Initialize();


    //create stars
    std::vector<viper::vec2> stars;
    for (int i = 0; i < 100; i++)
    {
        stars.push_back(viper::vec2{viper::random::getReal() * 1280, viper::random::getReal() * 1024});
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
        viper::GetEngine().Update();
        float dt = TIME.GetDeltatime();
        game->Update(dt);
		PARTICLES.Update(dt);



        if (INPUT.GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;


		viper::vec3 color{ 1, 1, 1 };

        RENDERER.SetColor(0.0f, 0.0f, 0.0f);
        RENDERER.Clear();


        for(auto& star : stars)
        {
            RENDERER.SetColor(color.x, color.y, color.z);
            RENDERER.DrawPoint(star.x, star.y);
            star.x -= 50.0f * dt;
            star.y += 50.0f * dt;

            star.x = viper::Wrap(star.x, 0.0f, 1280.0f);
            star.y = viper::Wrap(star.y, 0.0f, 1024.0f);
		}

		game->Draw(RENDERER);


        RENDERER.Present();

    }
    
	game->Shutdown();
	game.release();
	viper::GetEngine().Shutdown();

    return 0;
}