#include "../ESGLib.h"
#include "JUDGELIST_ENUM.h"
#include <vector>
#include <map>

//このクラス内でノートは検索にしか使わないので、
//前方参照のみ！
class ABSTRUCT_NOTE;

class EffectBomb{

public:

	EffectBomb();
	~EffectBomb();

	void Update();
	void Draw(Vector3 faderpos,Vector2 fadersize);
	void SetBomb(ABSTRUCT_NOTE* noteptr, JUDGELIST judge, float height);

private:

	struct BOMBNOTICE{

		void* noteptr;
		SPRITE sp;
		float height;
		int nowcount;

		BOMBNOTICE(ABSTRUCT_NOTE* noteptr, SPRITE sp, float height){

			this->noteptr = noteptr;
			this->sp = sp;
			this->height = height;
			this->nowcount = 0;

		}

		BOMBNOTICE(){

			this->noteptr = noteptr;
			this->sp = nullptr;
			this->height = 0.0f;
			this->nowcount = 0;

		}

	};

	void BombReset(BOMBNOTICE& resetdata,JUDGELIST judge,float height);

	const Vector2 CELLSIZE_;
	const int ANIMECOUNT_;
	const int ONECELLCOUNT_;

	static std::map<JUDGELIST, SPRITE>* bombsprites_;
	static SPRITE addalphabomb_;

	std::vector<BOMBNOTICE> bombdatas_;

};