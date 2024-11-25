#pragma once
#include "GL/glut.h"
#include "GL/GL.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include <soil-master/include/SOIL/SOIL.h>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Data::SqlClient;
using namespace MaterialSkin;
using namespace MaterialSkin::Controls;
using namespace System::Drawing::Printing;

namespace Airport
{
	public ref class AirplaneForm : public Form
	{
	public:
		AirplaneForm(String^ airplaneId, String^ model, String^ capacity, String^ baggageWeight, String^ year);
		~AirplaneForm();
	private:
		void InitializeComponent(String^ airplaneId, String^ model, String^ capacity, String^ baggageWeight, String^ year);

		void SetupOpenGL();
		void RenderScene();
		void Load3DModel();
		void CleanupOpenGL();

		void AirplaneForm_Load(Object^ sender, EventArgs^ e);
		void OnApplicationIdle(Object^ sender, EventArgs^ e);
		void OnMouseDown(Object^ sender, MouseEventArgs^ e);
		void OnMouseMove(Object^ sender, MouseEventArgs^ e);
		void OnMouseUp(Object^ sender, MouseEventArgs^ e);
		void AirplaneForm_FormClosed(Object^ sender, FormClosedEventArgs^ e);

		GLuint LoadTexture(const std::string& filePath);

		DataGridView^ airplaneDataGridView;
		MaterialLabel^ lblAirplaneId;
		MaterialLabel^ lblModel;
		MaterialLabel^ lblCapacity;
		MaterialLabel^ lblBaggageWeight;
		MaterialLabel^ lblYear;
		MaterialSingleLineTextField^ repairTextBox;
		ComboBox^ statusComboBox;
		MaterialRaisedButton^ saveButton;
		MaterialRaisedButton^ cancelButton;

		GLuint textureID;
		HDC hdc = NULL;
		HGLRC hrc = NULL;
		Panel^ openGLPanel;
		aiScene* loadedScene = nullptr;
		aiNode* rootNode;
		aiMesh* mesh;
		std::vector<aiVector3D>* vertices; 
		std::vector<aiFace>* faces;
		std::vector<aiVector3D>* normals;
		std::vector<aiVector3D>* texCoords;

		float rotationX = 0.0f;
		float rotationY = 0.0f;
		bool isDragging = false;
		int lastX = 0;
		int lastY = 0;

		float offsetX;
		float offsetY;
		float offsetZ;
	};
}