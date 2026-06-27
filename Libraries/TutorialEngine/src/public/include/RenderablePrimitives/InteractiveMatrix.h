#pragma once

// OLD HEADERS
// #include "../header_only/Event.h"
// #include "../header_only/share_ptr_typedefs.h"
// #include "../header_only/Transform.h"
// #include "../header_only/SceneNode.h"
// #include "../header_only/bitmap_font/bitmap_font_base.h"
// #include "../header_only/bitmap_font/Montserrat_BitmapFont.h"

#include "Event.h"
#include "GameObjectBase.h"
#include "SceneNode.h"
#include "Tools/Text/BitmapFont/BitmapFontBase.h"
#include "Tools/Text/BitmapFont/Montserrat_BMF.h"
#include <optional>

namespace TutorialEngine
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// an individual element of a 3d world space matrix.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class Scalar_3D: 
		public Engine::GameObjectBase,
		public std::enable_shared_from_this<Scalar_3D>,
		public Engine::IEventSubscriber
	{
	public:
		
	public://visual
		void setMaxSize(float inSize) { maxWidth = inSize; }
		void setValue(float inValue);
		void setValue(const std::string& val);
		//float operator=(float inValue) { setValue(inValue); return value; }
		bool hasManualPlacement() { return bInCustomLocation; }
		float getMaxSize() { return maxWidth; }
		Engine::SceneNode& getXform() { return *text3D; }
		void recalculateTextData();
	public:
		void render(float dt_sec, const glm::mat4& projection, const glm::mat4& view);
	protected:
		virtual void postConstruct() override;
	private://numeric
		std::optional<float> value;
		std::string symbolicValue; //for when this scalar represents a non-value; perhaps should make this a base class and have concrete and symbolic subclasses
	private://visual
		float maxWidth = 1.f; //the size that this should take up in 3d world spacec, think of this as defining a cube that the text lives within.
		bool bInCustomLocation = false;
		//sp<Engine::SceneNode> mySceneNode = new_sp<Engine::SceneNode>();
		static sp<Engine::Montserrat_BMF> font;
		sp<Engine::TextBlockSceneNode> text3D = nullptr;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// A matrix that exists in 3d world space that can be interated with
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class Matrix_3D:
		public Engine::GameObjectBase,
		public std::enable_shared_from_this<Matrix_3D>,
		public Engine::IEventSubscriber
	{
		template<typename T>
		using Matrix = std::vector<std::vector<T>>;
	public:
		Matrix_3D() = default;
		Matrix_3D(size_t col, size_t row) { setSize(col, row); }
		virtual ~Matrix_3D() = default;
	public:
		template<typename T> /**Set elements from POD values */
		void setElements(const std::vector<std::vector<T>>& rawElements);
	public: //matrix operations
		const sp<Scalar_3D>& get(size_t col, size_t row) const;
		void set(size_t col, size_t row, const sp<Scalar_3D>& value);
		void setSize(size_t column, size_t row);
		std::vector<sp<Scalar_3D>>& operator[](size_t col) { return matrix[col]; } //allow unsafe [][] access
	public://graphics settings
		void setElementBoxSize(float size); //determines how big each scalar in the matrix will be, ultimately determining visual size of matrix
		void render(float dt_sec, const glm::mat4& projection, const glm::mat4& view);
		void refreshElements();
		Engine::SceneNode& getXform() { return *mySceneNode; }
	protected:
		virtual void postConstruct() override;
	private: //matrix data
		Matrix<sp<Scalar_3D>> matrix;
		sp<Scalar_3D> nullScalar = nullptr;
	private://visual data
		float elementBoxSize = 0.1f;
		sp<Engine::SceneNode> mySceneNode = new_sp<Engine::SceneNode>(); //sceneNode by composition so that it can have the post construct callback
	};



	////////////////////////////////////////////////////////
	// template implementations
	////////////////////////////////////////////////////////

	template<typename T>
	void Matrix_3D::setElements(const std::vector<std::vector<T>>& rawElements)
	{
		matrix.clear(); //clear all scalars in the matrix

		for (auto& column : rawElements)
		{
			matrix.push_back({});
			auto& columnOfScalars = matrix.back();
			for (auto& rowEle : column)
			{
				sp<Scalar_3D> scalar = new_sp<Scalar_3D>();
				scalar->setValue(rowEle);
				columnOfScalars.push_back(scalar);

				//make the scalar a child of this 
				scalar->getXform().setParent(mySceneNode);
			}
		}
	}

}

