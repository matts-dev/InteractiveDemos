#include "Framework/RayTriDemo_SlideBase.h"
#include "Framework/DrawVectorDemo.h"

//rendering
#include <Utils/Platform/OpenGLES2/PlatformOpenGLESInclude.h>
#include "Utils/Platform/OpenGLES2/OpenGLES2Utils.h"
//~rendering

namespace TutorialEngine
{

	void RayTriDemo_SlideBase::init() 
	{
		DrawVectorDemo::init();

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// FROM RAY TRI DEMO INIT, THAT WAS OUTSIDE THE SLIDE
		// lineRenderer = new_up<TutorialEngine::LineRenderer>();

		quatCam = new_up<Engine::QuaternionCamera>();
		quatCam->pos = glm::vec3(0, 0, 5.f);
		// frameRenderData.window = window;
		// font = new_sp<Engine::Montserrat_BMF>("./assets/textures/font/Montserrat_ss_alpha_1024x1024_wb.png");
		font = new_sp<Engine::Montserrat_BMF>("./PreloadAssets/TutorialEngine/font/Montserrat_ss_alpha_1024x1024_wb.png");
		TestText3D = new_sp<Engine::TextBlockSceneNode>(font, "Testing 3 2 1."); 

		/** 
		//unsure if this is needed... but probably so!
		*/
		ec(glEnable(GL_DEPTH_TEST));
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	};
}


