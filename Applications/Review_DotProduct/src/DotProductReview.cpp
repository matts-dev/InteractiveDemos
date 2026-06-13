#include "DotProductReview.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ADDED PORTING BOX
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Framework/Cameras/QuaternionCamera.h"
#include "Framework/RayTriDemo_SlideBase.h"
#include "RenderablePrimitives/ClickableVisualVector.h"
#include "Tools/Text/BitmapFont/Montserrat_BMF.h"
#include "RenderablePrimitives/ClickableVisualVector.h"
#include "Tools/Text/BitmapFont/BitmapFontBase.h"
#include <TutorialEngine.h>
#include "EngineSystems/RenderSystem/RenderSystem.h"
#include "Framework/Cameras/QuaternionCamera.h"
#if WITH_IMGUI
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#endif //WITH_IMGUI
using TutorialEngine::ClickableVisualVector;
using Engine::QuaternionCamera;
using Engine::RenderSystem;
using Engine::Montserrat_BMF;
// using SlideBase = TutorialEngine::RayTriDemo_SlideBase;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// END PORT BOX
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dot product review
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Slide_DotProductReview::init()
{
	RayTriDemo_SlideBase::init();

	font = new_sp<Engine::Montserrat_BMF>("./PreloadAssets/TutorialEngine/font/Montserrat_ss_alpha_1024x1024_wb.png");

	aVec = new_sp<ClickableVisualVector>();
	bVec = new_sp<ClickableVisualVector>();

	aVec->setVector(glm::vec3(1, 0.f, 0));
	bVec->setVector(glm::vec3(0, 1, 0));

	dotProductValue = new_sp<Engine::TextBlockSceneNode>(font, "0.f");

	// Engine::EngineBase::get().onGameloopBeginning.addWeakObj(sp_this(), &Slide_DotProductReview::handleGameLoopStarting);

	Engine::ICamera* camera = Engine::RenderSystem::get().getRenderCamera(0).get();
	if (QuaternionCamera* qCam = dynamic_cast<QuaternionCamera*>(camera))
	{
		qCam->pos = glm::vec3(0,0,5); //todo: should this just be an interface function?
	}
}


void Slide_DotProductReview::inputPoll(float dt_sec)
{
	RayTriDemo_SlideBase::inputPoll(dt_sec);
}

void Slide_DotProductReview::tick(float dt_sec)
{
	RayTriDemo_SlideBase::tick(dt_sec);

	using namespace glm;
	

	if (bNormalizeVectors)
	{
		aVec->setVector(glm::normalize(aVec->getVec()));
		bVec->setVector(glm::normalize(bVec->getVec()));
	}

}

void Slide_DotProductReview::render_game(float dt_sec)
{
	RayTriDemo_SlideBase::render_game(dt_sec);

	const sp<Engine::FrameRenderData>& rd = Engine::RenderSystem::get().getFrameRenderData();
	if (!rd)
	{
		return;
	}

	glm::vec3 camPos = rd->camera->getPosition();

	aVec->render(rd->projection_view, camPos);
	bVec->render(rd->projection_view, camPos);

	//dotProductValue-> //set text
	float dotProduct = glm::dot(aVec->getVec(), bVec->getVec());

	char textBuffer[128];
	snprintf(textBuffer, sizeof(textBuffer), "%3.3f", dotProduct);
	dotProductValue->wrappedText->text = std::string(textBuffer);

	dotProductValue->setLocalScale(glm::vec3(10.f));
	dotProductValue->setLocalPosition(
		aVec->getStart()
		+ aVec->getVec() + 0.5f * glm::normalize(aVec->getVec())
		+ glm::vec3(0.f, 1.f, 0.f) * 0.5f);

	if (QuaternionCamera* qCam = dynamic_cast<QuaternionCamera*>(rd->camera.get()))
	{
		dotProductValue->setLocalRotation(qCam->rotation);
	}
	dotProductValue->render(rd->projection, rd->view);

}

void Slide_DotProductReview::render_UI(/*float dt_sec*/)
{
	RayTriDemo_SlideBase::render_UI(/*dt_sec*/);
#if WITH_IMGUI
	static bool bFirstDraw = true;
	if (bFirstDraw)
	{
		bFirstDraw = false;
		ImGui::SetNextWindowPos({ 1000, 0 });
	}
	ImGuiWindowFlags flags = 0;
	ImGui::Begin("Dot Product Review", nullptr, flags);
	ImGui::Checkbox("force normalization", &bNormalizeVectors);
	ImGui::End();
#endif //WITH_IMGUI
}

void Slide_DotProductReview::gatherInteractableCubeObjects(std::vector<const TutorialEngine::TriangleList_SNO*>& objectList)
{
	RayTriDemo_SlideBase::gatherInteractableCubeObjects(objectList);

	objectList.push_back(&aVec->startCollision->getTriangleList());
	objectList.push_back(&aVec->endCollision->getTriangleList());
	objectList.push_back(&bVec->startCollision->getTriangleList());
	objectList.push_back(&bVec->endCollision->getTriangleList());
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	std::cout << "Starting Application" << std::endl;
	sp<TutorialUtils::TutorialEngine> engine = new_sp<TutorialUtils::TutorialEngine>();
	engine->start([&]() {
		static sp<Engine::SceneNode> applicationLifetimeObject = new_sp<Slide_DotProductReview>();
		// applicationLifetimeObject->init();
		engine->addToRoot(applicationLifetimeObject);
	});
}
