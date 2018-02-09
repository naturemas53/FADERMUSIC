#include "../ESGLib.h"
#include "JUDGELIST_ENUM.h"
#include "Bombs\AbstructBomb.h"
#include "Bombs\JudgeBomb.h"
#include "Bombs\LongBreakBomb.h"
#include "Bombs\LongBomb.h"
#include "Bombs\FlashBomb.h"
#include <vector>

//このクラス内でノートは検索にしか使わないので、
//前方参照のみ！
class ABSTRUCT_NOTE;

class EffectBomb{
public:

	EffectBomb();
	~EffectBomb();

	void Update(int elapsedtime);
	void BeforeDraw();
	void AfterDraw();
	void SetJudgeBomb(Vector3 fader_pos, Vector2 fader_inner, float height, JUDGELIST judge);
	void SetLongBreakBomb(Vector3 fader_pos, Vector2 inner_size, float height, Color_by_Name color, float longxscale);
	void SetLongBomb(Vector3 fader_pos, Vector2 inner_size, float height, Color_by_Name color);
	void SetFlashBomb(Vector3 fader_pos, Vector2 inner_size, float height);

private:

	std::vector<JudgeBomb*> judgebomb_;
	std::vector<LongBreakBomb*> longbreakbomb_;
	std::vector<LongBomb*> longbomb_;
	std::vector<FlashBomb*> flashbomb_;
	std::vector<AbstructBomb*> nowbeforebomb_;
	std::vector<AbstructBomb*> nowafterbomb_;

};