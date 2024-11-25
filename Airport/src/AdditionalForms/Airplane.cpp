#include "Airplane.h"
#include <iostream>

namespace Airport
{
    bool isGlutInitialized = false;

    AirplaneForm::AirplaneForm(String^ airplaneId, String^ model, String^ capacity, String^ baggageWeight, String^ year)
    {
        InitializeComponent(airplaneId, model, capacity, baggageWeight, year);

        vertices = new std::vector<aiVector3D>();
        faces = new std::vector<aiFace>();
        normals = new std::vector<aiVector3D>();
        texCoords = new std::vector<aiVector3D>();
    }

    AirplaneForm::~AirplaneForm()
    {
        delete vertices;
        delete faces;
        delete normals;
        delete texCoords;
    }

    void AirplaneForm::InitializeComponent(String^ airplaneId, String^ model, String^ capacity, String^ baggageWeight, String^ year)
    {
        System::Drawing::Icon^ icon = gcnew System::Drawing::Icon("main_logo.ico");
        this->Icon = icon;
        this->Text = "Параметры самолета";
        this->StartPosition = FormStartPosition::CenterScreen;
        this->BackColor = System::Drawing::Color::White;
        this->Size = System::Drawing::Size(1500, 800);

        this->openGLPanel = gcnew System::Windows::Forms::Panel();
        this->openGLPanel->Location = System::Drawing::Point(20, 20);
        this->openGLPanel->Size = System::Drawing::Size(800, 700);
        this->openGLPanel->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right | AnchorStyles::Bottom);
        this->Controls->Add(this->openGLPanel);
        this->Load += gcnew System::EventHandler(this, &AirplaneForm::AirplaneForm_Load);
        this->openGLPanel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &AirplaneForm::OnMouseDown);
        this->openGLPanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &AirplaneForm::OnMouseMove);
        this->openGLPanel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &AirplaneForm::OnMouseUp);
        this->FormClosed += gcnew FormClosedEventHandler(this, &AirplaneForm::AirplaneForm_FormClosed);

        this->statusComboBox = gcnew System::Windows::Forms::ComboBox();
        this->statusComboBox->Items->AddRange(gcnew cli::array<String^>{"На ремонте", "Готов к полёту", "Требуется осмотр"});
        this->statusComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
        this->statusComboBox->Location = System::Drawing::Point(850, 450);
        this->statusComboBox->Size = System::Drawing::Size(300, 50);
        //this->Controls->Add(this->statusComboBox); 

        this->airplaneDataGridView = gcnew System::Windows::Forms::DataGridView();
        this->airplaneDataGridView->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::None;
        this->airplaneDataGridView->AlternatingRowsDefaultCellStyle->BackColor = System::Drawing::Color::LightGray;
        this->airplaneDataGridView->DefaultCellStyle->BackColor = System::Drawing::Color::White;
        this->airplaneDataGridView->DefaultCellStyle->ForeColor = System::Drawing::Color::Black;
        this->airplaneDataGridView->ColumnHeadersDefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
        this->airplaneDataGridView->ColumnHeadersDefaultCellStyle->BackColor = System::Drawing::Color::White;
        this->airplaneDataGridView->ColumnHeadersDefaultCellStyle->ForeColor = System::Drawing::Color::Black;
        this->airplaneDataGridView->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font("Arial", 12, System::Drawing::FontStyle::Bold);
        this->airplaneDataGridView->EnableHeadersVisualStyles = false;
        this->airplaneDataGridView->GridColor = System::Drawing::Color::LightGray;
        this->airplaneDataGridView->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
        this->airplaneDataGridView->RowHeadersDefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
        this->airplaneDataGridView->DefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
        this->airplaneDataGridView->DefaultCellStyle->SelectionForeColor = System::Drawing::Color::Black;
        this->airplaneDataGridView->Margin = System::Windows::Forms::Padding(10);
        this->airplaneDataGridView->Font = gcnew System::Drawing::Font("Arial", 14, System::Drawing::FontStyle::Regular);
        this->airplaneDataGridView->BackgroundColor = System::Drawing::Color::White;
        this->airplaneDataGridView->ForeColor = System::Drawing::Color::Black;
        this->airplaneDataGridView->RowTemplate->Height = 40;
        this->airplaneDataGridView->Location = System::Drawing::Point(850, 20);
        this->airplaneDataGridView->Size = System::Drawing::Size(600, 400);
        this->airplaneDataGridView->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
        this->airplaneDataGridView->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right | AnchorStyles::Bottom);
        this->airplaneDataGridView->Columns->Add("Property", "Свойство");
        this->airplaneDataGridView->Columns->Add("Value", "Значение");

        this->airplaneDataGridView->Rows->Add("ID", airplaneId);
        this->airplaneDataGridView->Rows->Add("Модель", model);
        this->airplaneDataGridView->Rows->Add("Вместимость", capacity);
        this->airplaneDataGridView->Rows->Add("Вес багажа", baggageWeight);
        this->airplaneDataGridView->Rows->Add("Год выпуска", year);
        this->Controls->Add(this->airplaneDataGridView);
    }

    void AirplaneForm::SetupOpenGL()
    {
        if (hrc) return;

        if (!isGlutInitialized) {
            int argc = 0;
            char* argv[] = { nullptr };
            glutInit(&argc, argv);
            isGlutInitialized = true;
        }

        Load3DModel();

        hdc = GetDC((HWND)openGLPanel->Handle.ToPointer());

        if (hdc == nullptr) {
            MessageBox::Show("Failed to get the device context.");
            return;
        }

        PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR), 1,
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
            PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 8, 0,
            PFD_MAIN_PLANE, 0, 0, 0, 0 };

        int pixelFormat = ChoosePixelFormat(hdc, &pfd);
        if (pixelFormat == 0) {
            MessageBox::Show("Failed to choose pixel format.");
            return;
        }

        if (!SetPixelFormat(hdc, pixelFormat, &pfd)) {
            MessageBox::Show("Failed to set pixel format.");
            return;
        }

        hrc = wglCreateContext(hdc);
        if (!hrc) {
            MessageBox::Show("Failed to create OpenGL context.");
            return;
        }

        if (!wglMakeCurrent(hdc, hrc)) {
            MessageBox::Show("Failed to make OpenGL context current.");
            return;
        }

        glEnable(GL_DEPTH_TEST);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        GLfloat lightPos[] = { 1.0f, 1.0f, 1.0f, 0.0f };
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    }

    void AirplaneForm::RenderScene()
    {
        if (!wglGetCurrentContext()) return;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        glTranslatef(offsetX, offsetY, offsetZ);

        glTranslatef(0.0f, 5.0f, -50.0f);

        glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
        glRotatef(rotationY, 0.0f, 1.0f, 0.0f);

        if (textureID != 0) {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textureID);
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glBegin(GL_TRIANGLES);
        for (size_t i = 0; i < faces->size(); ++i) {
            const aiFace& face = (*faces)[i];
            for (unsigned int j = 0; j < face.mNumIndices; ++j) {
                unsigned int index = face.mIndices[j];
                aiVector3D vertex = (*vertices)[index];
                aiVector3D texCoord = (*texCoords)[index];
                aiVector3D normal = (*normals)[index];

                glNormal3f(normal.x, normal.y, normal.z);
                glTexCoord2f(texCoord.x, texCoord.y);
                glVertex3f(vertex.x, vertex.y, vertex.z);
            }
        }
        glEnd();

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            MessageBox::Show("OpenGL Error during rendering: " + error);
        }

        SwapBuffers(hdc);
    }

    void AirplaneForm::Load3DModel()
    {
        vertices->clear();
        faces->clear();
        normals->clear();
        texCoords->clear();

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile("C:/dev/Airport/Airport/vendor/models/source/DC8_AFRC_AIR_0824.glb", aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            MessageBox::Show("Ошибка загрузки модели!");
            return;
        }


        aiMesh* mesh = scene->mMeshes[0];
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            vertices->push_back(mesh->mVertices[i]);

            if (mesh->HasNormals()) {
                normals->push_back(mesh->mNormals[i]);
            }
            if (mesh->HasTextureCoords(0)) {
                texCoords->push_back(mesh->mTextureCoords[0][i]);
                aiVector3D texCoord = mesh->mTextureCoords[0][i];
            }
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
            faces->push_back(mesh->mFaces[i]);
        }

        if (mesh->mMaterialIndex >= 0) {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

            aiString path;
            path.Set("C:/dev/Airport/Airport/vendor/models/source/CRJ-900_Cityjet_texture-4k.tga.png");
            if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
                std::string texturePath = path.C_Str();
                textureID = LoadTexture(texturePath);
            }
        }

        GLfloat diffuseColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);

        aiVector3D min(1e10f, 1e10f, 1e10f);
        aiVector3D max(-1e10f, -1e10f, -1e10f);
        for (const auto& vertex : *vertices)
        {
            min.x = std::min(min.x, vertex.x);
            min.y = std::min(min.y, vertex.y);
            min.z = std::min(min.z, vertex.z);

            max.x = std::max(max.x, vertex.x);
            max.y = std::max(max.y, vertex.y);
            max.z = std::max(max.z, vertex.z);
        }

        aiVector3D center = (min + max) / 2.0f;
        offsetX = -center.x;
        offsetY = -center.y;
        offsetZ = -center.z;
    }

    void AirplaneForm::AirplaneForm_Load(Object^ sender, EventArgs^ e)
    {
        SetupOpenGL();

        Application::Idle += gcnew EventHandler(this, &AirplaneForm::OnApplicationIdle);
    }

    void AirplaneForm::OnApplicationIdle(Object^ sender, EventArgs^ e)
    {
        RenderScene();
    }

    void AirplaneForm::OnMouseDown(Object^ sender, MouseEventArgs^ e)
    {
        if (e->Button == System::Windows::Forms::MouseButtons::Left)
        {
            isDragging = true;
            lastX = e->X;
            lastY = e->Y;
        }
    }

    void AirplaneForm::OnMouseMove(Object^ sender, MouseEventArgs^ e)
    {
        if (isDragging)
        {
            int deltaX = e->X - lastX;
            int deltaY = e->Y - lastY;

            rotationX += deltaY * 0.5f;
            rotationY += deltaX * 0.5f;

            if (rotationX > 90.0f) rotationX = 90.0f;
            if (rotationX < -90.0f) rotationX = -90.0f;

            lastX = e->X;
            lastY = e->Y;
        }
    }

    void AirplaneForm::OnMouseUp(Object^ sender, MouseEventArgs^ e)
    {
        if (e->Button == System::Windows::Forms::MouseButtons::Left)
        {
            isDragging = false;
        }
    }

    void AirplaneForm::CleanupOpenGL()
    {
        if (hrc) {
            wglMakeCurrent(NULL, NULL);
            wglDeleteContext(hrc);
            hrc = nullptr;
        }

        if (textureID != 0) {
            //glDeleteTextures(1, );
            textureID = 0;
        }

        if (vertices) vertices->clear();
        if (faces) faces->clear();
        if (normals) normals->clear();
        if (texCoords) texCoords->clear();
    }

    void AirplaneForm::AirplaneForm_FormClosed(Object^ sender, FormClosedEventArgs^ e)
    {
        Application::Idle -= gcnew EventHandler(this, &AirplaneForm::OnApplicationIdle);
        CleanupOpenGL();
    }

    GLuint AirplaneForm::LoadTexture(const std::string& filePath)
    {
        GLuint texture = SOIL_load_OGL_texture(filePath.c_str(),
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y);

        return texture;
    }
}