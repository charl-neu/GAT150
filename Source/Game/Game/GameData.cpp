#include "GameData.h"

namespace GameData {
	std::vector<nebula::vec2> pl_points{ // player
		{-4, -4},
		{4,0},
		{-4,4},
		{-2,0},
		{-4, -4}
	};
	std::vector<nebula::vec2> ba_points{ //basic enemy
		{-4,-3},
		{4,0},
		{-4,3},
		{-2,0},
		{-4, -3}

	};
	std::vector<nebula::vec2> ro_points{ //rocket
		{-4,-2},
		{4,0},
		{-4,2},
		{-2,0},
		{-4, -2}
	};
	std::vector<nebula::vec2> sp_points{ //speeder
		{-8,-3},
		{8,0},
		{-8,3},
		{-4,0},
		{-8, -3}

	};
	std::vector<nebula::vec2> bg_points{ //big guy
		{-2,-6},
		{2,0},
		{-2,6},
		{-1,0},
		{-2, -6}

	};
	std::vector<nebula::vec2> im_points{//snail
		{-4,-3},
		{4,0},
		{-4,3},
		{-2,0},
		{-4, -3}

	};
}