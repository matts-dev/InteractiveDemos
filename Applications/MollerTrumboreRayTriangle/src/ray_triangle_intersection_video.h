#pragma once
#include "Framework/DrawVectorDemo.h"
// #include "RenderablePrimitives/ImmediateTriangle.h"
#include <optional>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// THIS FILE WAS PORTED FROM A PREVIOUS PROJECT.
//
// Some modifications were made to get this compiling, which may yield the code lookign a bit strange in places!
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TutorialEngine
{
	class VisualPoint;
	class VectorProjectionAnimation;
	class VectorGridLines;
	class ClickableVisualRay;
	class SceneNode_TriangleList;
	class Matrix_3D;

	struct ImmediateTriangle;
	struct ClickableVisualPoint;
	struct ClickableVisualVector;
	struct TriangleList_SNO;
}
namespace Engine
{

	struct TextBlockSceneNode;
}


namespace ray_tri_ns
{
	//using TutorialEngine::VisualVector;
	//using TutorialEngine::ClickableVisualVector;
	//using TutorialEngine::SceneNode_VectorEnd;
	//using TutorialEngine::VectorCollisionTriangleList;
	//using TutorialEngine::VectorProjectionAnimation;
	//using TutorialEngine::VectorGridLines;

	//TODO move things over to header as this has grown large
	class SlideBase : public TutorialEngine::DrawVectorDemo //NOTE: see RayTriDemo_SlideBase for a more portable port of this file!
	{
	public:
		SlideBase()
		{
			// since engine auto runs UI -- we have to explicitly tell it not to do this, since this demo was built under different method of updating.
			bRegisterEditorUiOnPostConstruct = false;
			autoRegisterRenderGame = false;
			bAutoRegisterTick = false;
			bLeftMouseCanSelect = false;
		}
	};

/////////////////////////////////////////////////////////////////////////////////////
// slides
/////////////////////////////////////////////////////////////////////////////////////

	struct Slide_HighlevelOverview : public SlideBase
	{
		virtual void init() override;
		virtual void inputPoll(float dt_sec) override;
		virtual void tick(float dt_sec) override;
		virtual void render_game(float dt_sec) override;
		virtual void render_UI(/*float dt_sec*/) override;
		virtual void gatherInteractableCubeObjects(std::vector<const TutorialEngine::TriangleList_SNO*>& objectList) override;
		void updateRay();
	private:
		bool bRenderTriangleArea = true;
		bool bTriWireFrame = false;
		bool bRenderRay = true;
		bool bRenderEdgeA = false;
		bool bRenderEdgeB = false;
		bool bRenderTriangleNormals = false;
		bool bNormalizeTriXproduct = true;
		bool bRenderThreeNormals = false;
		bool bRenderPlanePnt = false;
		bool bRenderTriPlane = false;
		bool bTransparentPlane = false;

		bool bTestAPoint = false;
		bool bTestBPoint = false;
		bool bTestCPoint = false;
		bool binsideTest_RenderTriEdge = false;
		bool binsideTest_PntXproduct = false;
		bool bInsideTest_DotResult = false;

	private:
		sp<TutorialEngine::ImmediateTriangle> triRender = nullptr;
		sp<TutorialEngine::ClickableVisualPoint> pntA = nullptr;
		sp<TutorialEngine::ClickableVisualPoint> pntB = nullptr;
		sp<TutorialEngine::ClickableVisualPoint> pntC = nullptr;
		sp<TutorialEngine::VisualVector> vectorRenderer = nullptr;
		sp<TutorialEngine::VisualPoint> pointRenderer = nullptr;
		sp<TutorialEngine::PlaneRenderer> planeRenderer = nullptr;
		sp<Engine::TextBlockSceneNode> textRenderer = nullptr;
		sp<TutorialEngine::ClickableVisualRay> ray;
		float yawRad = 0.f, pitchRad = 0.f;
		float targetRayT = 6.f;
	};

	struct Slide_VectorAndPointReview : public SlideBase
	{
		//nothing, just let user draw vectors and points
	};

	struct Slide_RayReview : public SlideBase
	{
		virtual void init() override;
		virtual void inputPoll(float dt_sec) override;
		virtual void tick(float dt_sec) override;
		virtual void render_game(float dt_sec) override;
		virtual void render_UI(/*float dt_sec*/) override;
		virtual void gatherInteractableCubeObjects(std::vector<const TutorialEngine::TriangleList_SNO*>& objectList) override;
	private:
		sp<TutorialEngine::ClickableVisualRay> ray;
	};


	/////////////////////////////////////////////////////////////////////////////////////
	// dot product review
	/////////////////////////////////////////////////////////////////////////////////////
	struct Slide_DotProductReview : public SlideBase
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
	private://state
		bool bNormalizeVectors = false;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// cross product review
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	struct Slide_CrossProductReview : public SlideBase
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
		sp<TutorialEngine::ClickableVisualVector> crossVecVisual;
		sp<Engine::TextBlockSceneNode> crossProductText;
		sp<TutorialEngine::ImmediateTriangle> triRender;
	private://state
		bool bNormalizeVectors = false;
		bool bShowCrossProduct = false;
		bool bShowLength = false;
		bool bRenderArea = false;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Plane Review
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	struct Slide_PlaneEquation : public SlideBase
	{
	protected:
		virtual void gatherInteractableCubeObjects(std::vector<const TutorialEngine::TriangleList_SNO*>& objectList) override;
		virtual void init() override;
		virtual void render_game(float dt_sec) override;
		virtual void render_UI(/*float dt_sec*/) override;
		virtual void tick(float dt_sec) override;
		sp<TutorialEngine::ClickableVisualVector> planeNormal;
		sp<TutorialEngine::ClickableVisualPoint> testPoint;
		sp<TutorialEngine::ClickableVisualVector> vecToPoint;
		sp<TutorialEngine::PlaneRenderer> planeRenderer;
		sp<Engine::TextBlockSceneNode> text_dotProductValue;

		sp<TutorialEngine::VisualVector> genericVector;
		sp<TutorialEngine::VisualPoint> genericPoint;
	private:
		bool bRenderPlaneNormal = true;
		bool bRenderPlanePoint = false;
		bool bRenderTestPoint = false;
		bool bRenderVecToPoint = false;
		bool bRenderDotProduct = false;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Live Coding
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	struct Slide_LiveCoding : public SlideBase
	{
	protected:
		virtual void gatherInteractableCubeObjects(std::vector<const TutorialEngine::TriangleList_SNO*>& objectList) override;
		virtual void init() override;
		virtual void render_game(float dt_sec) override;
		virtual void render_UI(/*float dt_sec*/) override;
		virtual void tick(float dt_sec) override;

		void reviewCode_template();
		void reviewCode_recorded();

		bool codeGroundTruth();
		bool liveCodingIntersection();

		sp<TutorialEngine::ImmediateTriangle> triRender = nullptr;
		sp<TutorialEngine::VisualVector> genericVector = nullptr;
		sp<TutorialEngine::VisualPoint> genericPoint = nullptr;
	private:
		glm::vec3 rayStart{ -100.f };
		glm::vec3 rayEnd{ -100.1f };

	private: //live coding
		glm::vec3 triPoint_A = glm::vec3(-1, -1, -1); //left
		glm::vec3 triPoint_B = glm::vec3(1, -1, -1); //right
		glm::vec3 triPoint_C = glm::vec3(0, 1, -1); //top

	};

	////////////////////////////////////////////////////////
	// simple vector projection
	////////////////////////////////////////////////////////
	struct Slide_VectorProjectionExplanation : public SlideBase
	{
		using Parent = SlideBase;
	protected:
		virtual void init() override;
		virtual void render_game(float dt_sec) override;
		virtual void render_UI(/*float dt_sec*/) override;
		virtual void tick(float dt_sec) override;
		virtual void gatherInteractableCubeObjects(std::vector<const TutorialEngine::TriangleList_SNO*>& objectList) override;
		void handleVisualVectorUpdated(const TutorialEngine::ClickableVisualVector& updatedVec);

		//sp<TutorialEngine::ImmediateTriangle> triRender = nullptr;
		//sp<TutorialEngine::VisualVector> genericVector = nullptr;
		//sp<TutorialEngine::ClickableVisualPoint> genericPoint = nullptr;

		sp<TutorialEngine::ClickableVisualVector> aVec;
		sp<TutorialEngine::ClickableVisualVector> bVec;

		sp<TutorialEngine::VectorProjectionAnimation> projectionAnim;

		sp<Engine::TextBlockSceneNode> text;
	};


	////////////////////////////////////////////////////////
	// vector projection on unit axis
	////////////////////////////////////////////////////////
	struct Slide_ProjectionOnAxesGrid : public SlideBase
	{
		using Parent = SlideBase;
	protected:
		virtual void init() override;
		virtual void render_game(float dt_sec) override;
		virtual void render_UI(/*float dt_sec*/) override;
		virtual void tick(float dt_sec) override;
		virtual void gatherInteractableCubeObjects(std::vector<const TutorialEngine::TriangleList_SNO*>& objectList) override;
		void handleVisualVectorUpdated(const TutorialEngine::ClickableVisualVector& updatedVec);
		void clearProjections();
	public:
		bool bRenderZ = false;
		bool bProject = false;

	private:
		sp<TutorialEngine::ClickableVisualVector> vectorToProject;

		sp<TutorialEngine::ClickableVisualVector> x_basis;
		sp<TutorialEngine::ClickableVisualVector> y_basis;
		sp<TutorialEngine::ClickableVisualVector> z_basis;

		sp<TutorialEngine::VectorProjectionAnimation> projectionAnim_x;
		sp<TutorialEngine::VectorProjectionAnimation> projectionAnim_y;
		sp<TutorialEngine::VectorProjectionAnimation> projectionAnim_z;
		sp<TutorialEngine::VectorGridLines> gridX;
		sp<TutorialEngine::VectorGridLines> gridY;
		sp<TutorialEngine::VectorGridLines> gridZ;

		sp<Engine::TextBlockSceneNode> text;
	};

	////////////////////////////////////////////////////////
	// Scalar triple product review
	////////////////////////////////////////////////////////

	struct Slide_ScalarTripleProductReview : public SlideBase
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
		sp<TutorialEngine::ClickableVisualVector> cVec;
		sp<TutorialEngine::ClickableVisualVector> crossVecVisual;
		sp<Engine::TextBlockSceneNode> crossProductText;
		sp<TutorialEngine::ImmediateTriangle> triRender;
		sp<TutorialEngine::LineRenderer> lineRenderer;
		sp<TutorialEngine::VectorProjectionAnimation> projAnim;
	private://state
		bool bNormalizeSourceVecs = false;
		bool bShowCrossProduct = false;
		bool bShowLength = false;
		bool bRenderArea = false;
		bool bNormalizeCrossResult = false;
		bool bProjectC = false;
		bool bShowParallelpiped = false;
		bool bParallelepiped = false;
		bool bRenderCrossAreaSweeping = false;
	private://impl
		bool bResetAnimProjection = false;
	private:
		float timePassedSec = 0.f;
		float timestamp_showArea = 0.f; 
		float timestamp_projection = 0.f;
		float timestamp_showPiped = 0.f;
		float timestamp_areaSweep = 0.f;
	};

	////////////////////////////////////////////////////////
	// Determinant Review
	////////////////////////////////////////////////////////

	struct Slide_DeterminantReview : public SlideBase
	{
	protected:
		virtual void gatherInteractableCubeObjects(std::vector<const TutorialEngine::TriangleList_SNO*>& objectList) override;
		virtual void init() override;
		virtual void render_game(float dt_sec) override;
		virtual void render_UI(/*float dt_sec*/) override;
		virtual void tick(float dt_sec) override;
	private:
		sp<TutorialEngine::Matrix_3D> matrix;
		sp<TutorialEngine::ImmediateTriangle> triRender = nullptr;
		sp<TutorialEngine::VisualVector> genericVector = nullptr;
		sp<TutorialEngine::VisualPoint> genericPoint = nullptr;
	};


	////////////////////////////////////////////////////////
	// Barycentric reivew
	////////////////////////////////////////////////////////

	namespace EBarycentricMode
	{
		enum Type {
			MY_METHOD = 0,
			OPTIMIZED_PROJECTION,
			AREA_METHOD,
			LINEAR_SYSTEMS_METHOD
		};
	}

	struct TickData
	{
		float tickedTime = 0.f;
		float timestamp_start = 0.f;
		float dt_sec = 0.0001f;
		//float animDurationSecs = 1.f; //make this separate from tick data so we can one-line function calls
	};

	struct AnimationHelperFunctions
	{
		static void renderVector(
			bool bShouldRender,
			const TickData& td,
			glm::vec3 start,
			glm::vec3 dir,
			glm::vec3 color,
			TutorialEngine::VisualVector& genericVector,
			const Engine::FrameRenderData& rd
		);
		static void renderVector(
			bool bShouldRender,
			const TickData& td,
			glm::vec3 start,
			glm::vec3 dir,
			glm::vec3 color,
			float timestampSecs,
			float animDurSecs,
			TutorialEngine::VisualVector& genericVector,
			const Engine::FrameRenderData& rd,
			bool bDriftToOrigin = false
		);
		static void renderProjection(
			bool bShouldRender,
			const TickData& td,
			TutorialEngine::VectorProjectionAnimation& projAnim, 
			glm::vec3 aVec,
			glm::vec3 bVec,
			glm::vec3 aStart,
			glm::vec3 bStart, 
			float animDurationSecs,
			bool bResetAnim,
			bool bForceUpdate,
			const Engine::FrameRenderData& rd, 
			std::optional<glm::vec3> color = std::nullopt
		);
		static void renderCrossArea(
			bool bShouldRender,
			const TickData& td,
			glm::vec3 first,
			glm::vec3 second,
			glm::vec3 start,
			glm::vec3 color,
			float timestamp_start,
			float animDurSecs,
			TutorialEngine::ImmediateTriangle& triRender,
			const Engine::FrameRenderData& rd,
			bool bRenderHalfAreas = false
		);
	};

	struct Slide_BaryCentricsExplanation : public SlideBase
	{
	public:
		static glm::vec3 calcBarycentrics_myMethod(glm::vec3 testPoint, glm::vec3 pntA, glm::vec3 pntB, glm::vec3 pntC);
		static glm::vec3 calcBarycentrics_optimizedProjection(glm::vec3 testPoint, glm::vec3 pntA, glm::vec3 pntB, glm::vec3 pntC);
		static glm::vec3 calcBarycentrics_AreaMethod(glm::vec3 testPoint, glm::vec3 pntA, glm::vec3 pntB, glm::vec3 pntC);
		static glm::vec3 calcBarycentrics_LinearSystemMethod(glm::vec3 testPoint, glm::vec3 pntA, glm::vec3 pntB, glm::vec3 pntC);
	protected:
		virtual void init() override;
		virtual void render_game(float dt_sec) override;
		void renderGame_Barycentric_myMethod(float dt_sec);
		void renderGame_Barycentric_OptimizedProjectionMethod(float dt_sec);
		void renderGame_Barycentric_AreaMethod(float dt_sec);
		void renderGame_Barycentric_SolvingLinearSystem(float dt_sec);
		virtual void render_UI(/*float dt_sec*/) override;
		virtual void tick(float dt_sec) override;
		virtual void gatherInteractableCubeObjects(std::vector<const TutorialEngine::TriangleList_SNO*>& objectList) override;
		// virtual void gatherInteractableCubeObjects(std::vector<const TriangleList_SNO*>& objectList) = 0;
		void handleTestPointUpdated(const TutorialEngine::VisualPoint& pnt);
	private:
		//avoiding using anim helpers for these atm because helpers cannot be done in single line, after refactoring them will use those instead of having explicit methods below
		//also avoiding because reworked some logic with projection updates to be non-negative language (reset anim instead of talkinga bout test opint updated)
		void helper_renderVector(bool bShouldRender, glm::vec3 start, glm::vec3 dir, glm::vec3 color);
		void helper_renderVector(bool bShouldRender, glm::vec3 start, glm::vec3 dir, glm::vec3 color, float timestampSecs, bool bDriftToOrigin = false);
		void helper_renderProjection(bool bShouldRender, TutorialEngine::VectorProjectionAnimation& projAnim, glm::vec3 aVec, glm::vec3 bVec, glm::vec3 aStart, glm::vec3 bStart, float dt_sec, std::optional<glm::vec3> color = std::nullopt);
		void helper_renderCrossArea(bool bShouldRender, glm::vec3 first, glm::vec3 second, glm::vec3 start, glm::vec3 color, float timestamp_start);
	private:
		sp<TutorialEngine::ImmediateTriangle> triRender = nullptr;
		sp<TutorialEngine::VisualVector> genericVector = nullptr;
		sp<TutorialEngine::VisualPoint> genericPoint = nullptr;
		sp<Engine::TextBlockSceneNode> text;
	private:
		bool bTestPointUpdated = false;
	private:
		EBarycentricMode::Type barymode = EBarycentricMode::MY_METHOD;


		//ground truths
		bool bRenderRealTimeCollisionBook = false;
		bool bRenderShirleyVersion = false;
	private:
		////////////////////////////////////////////////////////
		// shared between all methods
		////////////////////////////////////////////////////////
		bool bWireframe = false;
		bool bRenderBarycentricA = true;
		bool bRenderBarycentricB = false;
		bool bRenderBarycentricC = false;
		////////////////////////////////////////////////////////
		// slow intuitive method flags
		////////////////////////////////////////////////////////
		bool bRenderBToA = false;
		bool bRenderBToC = false;
		bool bRenderBCProj = false;
		bool bRender_EdgeProjectPointToTestPoint = false;
		bool bRender_PerpendicularToEdge = false;
		bool bRenderTestPointProjectionOntoPerpendicular = false;

		float timestamp_RenderBToA = 0.f;
		float timestamp_RenderBToC = 0.f;
		float timestamp_RenderBCProj = 0.f;
		float timestamp_Render_EdgeProjectPointToTestPoint = 0.f;
		float timestamp_Render_PerpendicularToEdge = 0.f;
		float timestamp_RenderTestPointProjectionOntoPerpendicular = 0.f;
		float timestamp_RenderBarycentricA = 0.f;
		float timestamp_RenderBarycentricB = 0.f;
		float timestamp_RenderBarycentricC = 0.f;

		////////////////////////////////////////////////////////
		// optimized projection method flags
		////////////////////////////////////////////////////////
		bool bRenderAB = false;
		bool bRenderCB = false;
		bool bRender_AtoTestPnt = false;
		bool bRender_ProjToCB = false;
		bool bRender_VectorFromFirstProjection = false;
		bool bRender_projTestPointOntoPerpendicular = false;
		bool bRender_projABontoPerpendicular = false;

		float timestamp_renderbRenderAB									= 0.f;
		float timestamp_renderbRenderCB									= 0.f;
		float timestamp_renderbRender_AtoTestPnt						= 0.f;
		float timestamp_renderbRender_Perpendicular						= 0.f;
		float timestamp_renderbRender_VectorFromFirstProjection	  		= 0.f;
		float timestamp_renderbRender_projTestPointOntoPerpendicular	= 0.f;
		float timestamp_renderbRender_projABontoPerpendicular			= 0.f;

		////////////////////////////////////////////////////////
		// area method
		////////////////////////////////////////////////////////
		bool bRenderHalfAreas = false; 
		bool bRenderCrossVec_first = false;
		bool bRenderCrossVec_second = false;

		bool bAreaMethod_RenderTriNormals = false;
		bool bRenderCrossProductVectors = false;
		bool bAreaMethod_normalizeNormals = false;
		bool bAreaMethod_renderFullArea = false;
		bool bAreaMethod_renderPBC_Area = false;
		bool bAreaMethod_renderPCA_Area = false;
		bool bAreaMethod_renderPAB_Area = false;

		
		float timestamp_area_normals = 0.f;
		float timestamp_area_fullarea = 0.f;
		float timestamp_area_PBC_area = 0.f;
		float timestamp_area_PCA_area = 0.f;
		float timestamp_area_PAB_area = 0.f;
		float timestamp_crossvecfirst = 0.f;
		float timestamp_crossvecsecond = 0.f;
		float timestamp_crossproductVecs = 0.f;

	private:
		float tickedTime = 0.f;
		float vectorAnimSecs = 1.0f;
	private:
		sp<TutorialEngine::ClickableVisualPoint> pntA = nullptr;
		sp<TutorialEngine::ClickableVisualPoint> pntB = nullptr;
		sp<TutorialEngine::ClickableVisualPoint> pntC = nullptr;

		sp<TutorialEngine::ClickableVisualPoint> testPoint = nullptr;

		/////////////////////////////////////////////////////////////////////////////////////
		// intuitive method
		/////////////////////////////////////////////////////////////////////////////////////
		sp<TutorialEngine::VectorProjectionAnimation> projAnim_BC;
		sp<TutorialEngine::VectorProjectionAnimation> projAnim_PointOnPerpendicular;

		////////////////////////////////////////////////////////
		// optimized projection method
		////////////////////////////////////////////////////////
		sp<TutorialEngine::VectorProjectionAnimation> projAnim_ab_onto_cb;
		sp<TutorialEngine::VectorProjectionAnimation> projAnim_testPointOnPerpendicular;
		sp<TutorialEngine::VectorProjectionAnimation> projAnim_aBOnPerpendicular;
	};


	struct Slide_MollerAndTrumbore : public SlideBase
	{
	protected:
		virtual void init() override;
		virtual void render_game(float dt_sec) override;
		virtual void render_UI(/*float dt_sec*/) override;
		virtual void tick(float dt_sec) override;
		virtual void gatherInteractableCubeObjects(std::vector<const TutorialEngine::TriangleList_SNO*>& objectList) override { SlideBase::gatherInteractableCubeObjects(objectList); }

		virtual void doTrace();

		void liveCodingTemplate()
		{
			using namespace glm;

			////////////////////////////////////////////////////////
			// point, vector, and ray review
			////////////////////////////////////////////////////////
			vec3 startPoint(1.f, 2.f, 3.f);
			startPoint.x = 7.f;
			startPoint.y = 8.f;
			startPoint.z = 9.f;

			vec3 endPoint(-3.f, -4.f, 5.f);

			vec3 vectorBetweenPoints = endPoint - startPoint;

			struct Ray
			{
				vec3 startPoint;
				vec3 direction;
				float t;
			};

			Ray myRay;
			myRay.startPoint = startPoint;
			myRay.direction = vectorBetweenPoints;
			myRay.t = 3.99f;

			vec3 rayTracedPoint = myRay.startPoint + myRay.direction * myRay.t;

			////////////////////////////////////////////////////////
			// barycentrics review
			////////////////////////////////////////////////////////
			vec3 triPointA(-1, 0, 0);
			vec3 triPointB(1, 0, 0);
			vec3 triPointC(0, 1, 0);

			//note barycentrics are not exactly like weights,
			//but behave like weights when point is within tri
			vec3 barycentrics(0.33f, 0.33f, 0.33f);

			vec3 baryTestPoitn = barycentrics.r * triPoint_A 
				+ barycentrics.g * triPoint_B 
				+ barycentrics.b* triPoint_C;
			
		}

		void liveCodingRecorded();

		sp<TutorialEngine::ImmediateTriangle> triRender = nullptr;
		sp<TutorialEngine::VisualVector> genericVector = nullptr;
		sp<TutorialEngine::VisualPoint> genericPoint = nullptr;
	private:
		glm::vec3 rayStart{ -100.f };
		glm::vec3 rayEnd{ -100.1f };
	private:
		glm::vec3 triPoint_A = glm::vec3(-1, -1, -1); //left
		glm::vec3 triPoint_B = glm::vec3(1, -1, -1); //right
		glm::vec3 triPoint_C = glm::vec3(0, 1, -1); //top
	};

}
