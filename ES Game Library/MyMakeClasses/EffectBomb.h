#include "../ESGLib.h"
#include "JUDGELIST_ENUM.h"
#include "Bombs\JudgeBomb.h"
#include <vector>

//このクラス内でノートは検索にしか使わないので、
//前方参照のみ！
class ABSTRUCT_NOTE;

class EffectBomb{
public:

	EffectBomb();
	~EffectBomb();

	void Update(int elapsedtime);
	void Draw();
	void SetJudgeBomb(Vector3 fader_pos,Vector2 fader_inner, float height,JUDGELIST judge);

private:

	std::vector<JudgeBomb*> judgebombs_;
	std::vector<JudgeBomb*> nowbomb_;

};