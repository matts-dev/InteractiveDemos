#pragma once
#include "DrawVectorDemo.h"
#include "Framework/Cameras/QuaternionCamera.h"
#include "Tools/Text/BitmapFont/Montserrat_BMF.h"


namespace TutorialEngine
{
	/** This is the ported version of the class, which is more generally usable and does not need the base ray triangel demo set up. */
	class RayTriDemo_SlideBase : public DrawVectorDemo
	{
	protected:
		virtual void init() override;

	protected:
		up<Engine::QuaternionCamera> quatCam = nullptr;
		sp<Engine::Montserrat_BMF> font = nullptr; 
		sp<Engine::TextBlockSceneNode> TestText3D = nullptr;
	};
}