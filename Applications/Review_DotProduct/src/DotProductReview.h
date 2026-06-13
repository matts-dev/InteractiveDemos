#include "Framework/InteractableDemoBase.h"
#include "Framework/RayTriDemo_SlideBase.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PORTED FROM OPENGL4 PROJECT - ray triangle intersection video
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TutorialEngine
{
	struct ClickableVisualVector;
	struct TriangleList_SNO;

}
namespace Engine
{
	class Montserrat_BMF;
	struct TextBlockSceneNode;
}

/////////////////////////////////////////////////////////////////////////////////////
// dot product review
/////////////////////////////////////////////////////////////////////////////////////

struct Slide_DotProductReview : public TutorialEngine::RayTriDemo_SlideBase
{
public:
	virtual void init() override;
	virtual void inputPoll(float dt_sec) override;
	virtual void tick(float dt_sec) override;
	virtual void render_game(float dt_sec) override;
	virtual void render_UI(/*float dt_sec*/) override;
	virtual void gatherInteractableCubeObjects(std::vector<const TutorialEngine::TriangleList_SNO*>& objectList) override;
private://visuals
	sp<TutorialEngine::ClickableVisualVector> aVec;
	sp<TutorialEngine::ClickableVisualVector> bVec;
	sp<Engine::TextBlockSceneNode> dotProductValue;

	//additions after port
	sp<Engine::Montserrat_BMF> font;
private://state
	bool bNormalizeVectors = false;
};
