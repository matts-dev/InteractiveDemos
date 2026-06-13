#pragma once
#include <vector>

#include "RenderablePrimitives/ClickableVisualVector.h"
#include "RenderablePrimitives/ClickableVisualPoint.h"
#include "InteractableDemoBase.h"

// #include "../new_utils/header_only/share_ptr_typedefs.h"
#include "GameObjectBase.h" //for sp<>

namespace TutorialEngine
{
struct ClickableVisualVector;

class DrawVectorDemo : public InteractableDemoBase
{
public:
	virtual void init()override;
	virtual void render_game(float dt_sec) override;
	virtual void tick(float dt_sec) override;
	virtual void inputPoll(float dt_sec)override;
protected:
	virtual void gatherInteractableCubeObjects(std::vector<const TriangleList_SNO *>& objectList) override;
	const sp<TutorialEngine::ClickableVisualVector>& getSelection() { return selectionLater; }
private:
	void tick_drawVector(/*float dt_sec*/);
	void tick_selectVectors(/*float dt_sec*/); 
	void tick_dragPoint(/*float dt_sec*/);
protected:
	bool bEnablePointDrawing = true;
	bool bEnableVectorDrawing = true;
	bool bColorSelectedVectors = true;
	bool bAltWasPressed = false;
	std::vector<sp<TutorialEngine::ClickableVisualVector>> customVectors;
	std::vector<sp<TutorialEngine::ClickableVisualPoint>> customPoints;
	sp<TutorialEngine::ClickableVisualVector> newVector = nullptr;
	sp<TutorialEngine::ClickableVisualPoint> draggingPoint = nullptr;
private:
	bool bSelectNextVector = true;
	sp<TutorialEngine::ClickableVisualVector> selectionFormer = nullptr;
	sp<TutorialEngine::ClickableVisualVector> selectionLater = nullptr;
};

}