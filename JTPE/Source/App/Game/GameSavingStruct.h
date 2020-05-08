#ifndef GAMESAVINGSTRUCT
#define GAMESAVINGSTRUCT

namespace J
{
	namespace APP
	{
		const std::string AlreadyRunnedKey = "AlreadyRunned";
		const std::string GameSavingKey = "GameSaving";

		//GAME DATA STRUCTS
		//SAVE STRUCTS
		struct GameSaving
		{
			bool				mIsPlaying;
		};

		//JSON SERIALIZATIONS

		inline void to_json(json& j, const GameSaving& p)
		{
			j = json
			{
						{"mIsPlaying",p.mIsPlaying}
			};
		};
		inline void from_json(const json& j, GameSaving& p)
		{
			j.at("mIsPlaying").get_to(p.mIsPlaying);
		};
	}
}

#endif // !GAMESAVINGSTRUCT
