#include "../ESGLib.h"
#include "JUDGELIST_ENUM.h"
#include "Bombs\JudgeBomb.h"
#include <vector>

//���̃N���X���Ńm�[�g�͌����ɂ����g��Ȃ��̂ŁA
//�O���Q�Ƃ̂݁I
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