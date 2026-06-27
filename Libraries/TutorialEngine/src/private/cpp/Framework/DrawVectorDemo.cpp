#include "Framework/DrawVectorDemo.h"
#include "EngineSystems/RenderSystem/RenderSystem.h"
#include "EngineSystems/WindowSystem/WindowSystem.h"
#include "Utils/Platform/PlatformUtils.h"
#include "EngineSystems/WindowSystem/WindowWrapper.h"


#include<GLFW/glfw3.h> //this must come before glad include, otherwise get macro redifintion issues; likely related to including windows.h; https://github.com/Dav1dde/glad/issues/283 glad2 apparently resolves this.
#ifdef HTML_BUILD //ONLY HTML
	#include <emscripten/emscripten.h>
	#include <GLES2/gl2.h>
#else //DESKTOP ONLY
	#include<glad/glad.h>
#endif


// using namespace nho;
namespace TutorialEngine
{
void DrawVectorDemo::gatherInteractableCubeObjects(std::vector<const TriangleList_SNO *>& objectList)
{
	InteractableDemoBase::gatherInteractableCubeObjects(objectList);

	if (bEnablePointDrawing && bAltWasPressed)
	{
		for (const sp<ClickableVisualPoint>& point : customPoints)
		{
			objectList.push_back(&point->pointCollision->getTriangleList());
		}
	}
	else
	{
		//click vectors
		for (const sp<ClickableVisualVector>& vec : customVectors)
		{
			objectList.push_back(&vec->startCollision->getTriangleList());
			objectList.push_back(&vec->endCollision->getTriangleList());
		}
	}

}

void DrawVectorDemo::tick_drawVector(/*float dt_sec*/)
{
	std::optional<glm::vec3> lineStart = getDrawLineStart();
	std::optional<glm::vec3> lineEnd = getDrawLineEnd();

	bool bDrawingLine = lineStart && lineEnd;
	bool bCreatedVectorForLine = bool(newVector);
	if (bDrawingLine && bEnableVectorDrawing)
	{
		if (!bCreatedVectorForLine)
		{
			newVector = new_sp<ClickableVisualVector>();
			newVector->setStart(*lineStart);
			newVector->setEnd(*lineEnd);
			customVectors.push_back(newVector);
		}
		else
		{
			newVector->setEnd(*lineEnd);
		}
	}
	else
	{
		if (newVector)
		{
			if (glm::length(newVector->getVec()) < 0.5f)
			{
				//remove the custom vector as it is small and probably an error
				customVectors.pop_back();
			}

			//clear out previous new vectors
			newVector = nullptr;
		}
	}
}

void DrawVectorDemo::tick_selectVectors(/*float dt_sec*/)
{
	if (activeClickTarget)
	{
		if (bSelectNextVector)
		{
			if (const VectorCollisionTriangleList* triList = dynamic_cast<const VectorCollisionTriangleList*>(activeClickTarget))
			{
				if (triList->owner && triList->owner)
				{
					if (const SceneNode_VectorEnd* sn = dynamic_cast<const SceneNode_VectorEnd*>(triList->owner))
					{
						if (sn && sn->owner)
						{
							if (selectionFormer && bColorSelectedVectors)
							{
								selectionFormer->color = glm::vec3(1, 1, 1);
							}

							selectionFormer = selectionLater;
							selectionLater = sn->owner->getShared();

							if (selectionFormer && bColorSelectedVectors)
							{
								selectionFormer->color = glm::vec3(0, 1, 0);
							}
							if (selectionLater && bColorSelectedVectors)
							{
								selectionLater->color = glm::vec3(1, 0, 0);
							}
							bSelectNextVector = false;
						}
					}
				}
			}
		}
	}
	else
	{
		bSelectNextVector = true;
	}
}

void DrawVectorDemo::tick_dragPoint(/*float dt_sec*/)
{
	std::optional<glm::vec3> pointLocation = InteractableDemoBase::getDrawPoint();

	bool bCreatedNewPoint = bool(draggingPoint);
	if (pointLocation)
	{
		if (!bCreatedNewPoint)
		{
			draggingPoint = new_sp<ClickableVisualPoint>();
			draggingPoint->setPosition(*pointLocation);
			draggingPoint->setUserScale(glm::vec3(2.f));
			customPoints.push_back(draggingPoint);
		}
		else
		{
			draggingPoint->setPosition(*pointLocation);
		}
	}
	else
	{
		//stop dragging point
		draggingPoint= nullptr;
	}
}

void DrawVectorDemo::tick(float dt_sec)
{
	InteractableDemoBase::tick(dt_sec);

	//DRAW LOGIC
	tick_drawVector(/*dt_sec*/);
	tick_selectVectors(/*dt_sec*/);

	tick_dragPoint(/*dt_sec*/);

}

void DrawVectorDemo::inputPoll(float dt_sec)
{
	InteractableDemoBase::inputPoll(dt_sec);
	
	// const sp<Engine::FrameRenderData>& rd = Engine::RenderSystem::get().getFrameRenderData();
	// if (rd && rd->window)
	// {
	// 	bAltWasPressed = 
	// 		glfwGetKey(rd->window->get(), GLFW_KEY_LEFT_ALT) == GLFW_PRESS 
	// 		|| glfwGetKey(rd->window->get(), GLFW_KEY_RIGHT_ALT) == GLFW_PRESS;
	// }
	// else 
	// {
	// 	//this will be null before initialziation... probably an issue...
	// 	// STOP_DEBUGGER_HERE(); 
	// }

	// NEW ADDITION FROM PORTING -- delete the selected vector!
	if (const sp<Engine::Window>& window_wrapper = Engine::WindowSystem::get().getPrimaryWindow())
	{
		if (GLFWwindow* window = window_wrapper->get())
		{
			bAltWasPressed = 
				glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS 
				|| glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS;

			if (glfwGetKey(window, GLFW_KEY_DELETE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_BACKSPACE))
			{
				if (bAltWasPressed)
				{
					//if holding alt, delete all the things.
					selectionFormer = nullptr;
					selectionLater = nullptr;
					customVectors.clear();
					customPoints.clear();
				}
				else 
				{
					if (selectionLater != nullptr 
						&& customVectors.size() > 0)	
					{
						std::size_t selection_index = customVectors.size();
						
						for(std::size_t remove_idx = 0; remove_idx < customVectors.size(); ++remove_idx)
						// for(const sp<TutorialEngine::ClickableVisualVector>& customVec : customVectors )
						{
							const sp<TutorialEngine::ClickableVisualVector>& customVec = customVectors[remove_idx];
							if (customVec == selectionLater)
							{
								selection_index = remove_idx;
							}
						}
	
						const bool found_remove = selection_index < customVectors.size();
						if (found_remove)
						{
							std::size_t last_idx = customVectors.size() - 1;
							std::swap(customVectors[selection_index], customVectors[last_idx]); //swap before pop
							customVectors.pop_back(); //remove the swaped to back
						}
					}
				}
			}
		}
	}

}

void DrawVectorDemo::init()
{
	InteractableDemoBase::init();
	bRenderLineGeneration = false;
}

void DrawVectorDemo::render_game(float dt_sec)
{
	InteractableDemoBase::render_game(dt_sec);

	const sp<Engine::FrameRenderData>& rd = Engine::RenderSystem::get().getFrameRenderData();
	if( !rd) { STOP_DEBUGGER_HERE(); return;}

	glm::vec3 camPos = rd->camera->getPosition();
	for (const sp<ClickableVisualVector>& vec : customVectors)
	{
		vec->render(rd->projection_view, camPos);
	}
	for (const sp<ClickableVisualPoint>& point : customPoints)
	{
		point->render(rd->projection_view, camPos);
	}
}

}