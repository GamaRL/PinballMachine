/**
 * Semestre 2024-1
 * Proyecto Máquina de Pinball
 **/

//para cargar imagen
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float3x3.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>
#include <ctime>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "./include/Window.h"
#include "./include/Mesh.h"
#include "./include/Shader.h"
#include "./include/Camera.h"
#include "./include/CameraToggleController.h"
#include "./include/Texture.h"
#include "./include/Model.h"
#include "./include/Skybox.h"

//para iluminación
#include "./include/CommonValues.h"
#include "./include/DirectionalLight.h"
#include "./include/PointLight.h"
#include "./include/SpotLight.h"
#include "./include/Material.h"
#include "./include/Inador.h"
#include "./include/Flipper.h"
#include "./include/FlipperKeyController.h"
#include "./include/InadorAnimation.h"
#include "./include/PerryAnimation.h"
#include "./include/Spring.h"
#include "./include/SpringMouseController.h"
#include "./include/Earth.h"
#include "./include/Perry.h"
#include "./include/LightManager.h"
#include "./include/Bouncer.h"
#include "./include/Bumper.h"
#include "./include/Ball.h"
#include "./include/BallAnimation.h"
#include "./include/BallKeyframeAnimation.h"

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Texture plainTexture;
Texture floorTexture;

Model Pinball_Cover_M;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat dt = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// Vertex Shader
static const char* vShader = "resources/shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "resources/shaders/shader_light.frag";



//cálculo del promedio de las normales para sombreado de Phong
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-50.0f, 0.0f, -95.0f,	0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		50.0f, 0.0f, -95.0f,	1.0f, 1.0f,	0.0f, -1.0f, 0.0f,
		-50.0f, 0.0f, 95.0f,	0.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		50.0f, 0.0f, 95.0f,		1.0f, 0.0f,	0.0f, -1.0f, 0.0f
	};

	unsigned int powerIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat powerVertices[] = {
		-0.5f, 0.0f, -0.5f,	0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,	1.0f, 1.0f,	0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, 0.5f,	0.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		1.0f, 0.0f,	0.0f, -1.0f, 0.0f

	};


	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(powerVertices, powerIndices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj2);
}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}


int main()
{
  srand(time(NULL));
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

  LightManager lm = LightManager();

	Camera* camera = nullptr;
  CameraToggleController cameraController(&mainWindow);

	plainTexture = Texture("resources/textures/plain.png");
	plainTexture.LoadTextureA();
	floorTexture = Texture("resources/textures/fondopiso_galaxia.png");
	floorTexture.LoadTextureA();

  Perry::Initialise();
	Perry perry(10.0f, 5.0f, 60.0f);


  Ball::Initialise();
	Ball ball1(10.0f, 5.0f, 0.0f);
	Ball ball2(10.0f, 5.0f, 0.0f);

  BallAnimation ballAnimation(&ball1, &mainWindow);
  BallKeyframeAnimation ballKeyAnimation(&ball2);

  PerryAnimation perryAnimation(&perry, &mainWindow);

  Inador::Initialise();

  Inador in1 = Inador(-20.0f, 0.0f, -45.0f, 0.0f, &lm.GetObstacleLights()[0]);
  Inador in2 = Inador(20.0f, 0.0f, -45.0f, glm::pi<float>(), &lm.GetObstacleLights()[1]);
  Inador in3 = Inador(30.0f, 0.0f, 30.0f, glm::pi<float>() / 2.0f, &lm.GetObstacleLights()[2]);

  Bouncer::Initialise();

  Bouncer bn1 = Bouncer(-25, 0.0f, -33.0f, true);
  Bouncer bn2 = Bouncer(25, 0.0f, -33.0f, false);
  Bouncer bn3 = Bouncer(-35, 0.0f, 50.0f, true);
  Bouncer bn4 = Bouncer(35, 0.0f, 50.0f, false);

  Bumper::Initialise();
  Bumper bp1 = Bumper(-35, 0.0f, 0.0f, 1.0f);
  Bumper bp2 = Bumper(-25, 0.0f, -15.0f, 0.8f);
  Bumper bp3 = Bumper(20, 0.0f, -15.0f, 1.2f);

  InadorAnimation in_an_1(&in1);
  InadorAnimation in_an_2(&in2);
  InadorAnimation in_an_3(&in3);

	Earth::Initialise();
	Earth earth(0.0f, 0.0f, 40.0f);

  Spring::Initialise();
  Spring spring = Spring(43.5f, 3.0f, 80.0f);

  SpringMouseController springMouseController(&mainWindow, &spring);

  Flipper::Initialise();
  Flipper fizq = Flipper(-25.0f, 0.0f, 65.0f, 0);
  Flipper fder = Flipper(25.0f, 0.0f, 65.0f, 1);
  Flipper fmin = Flipper(25.0f, 0.0f, 0.0f, 2);

  FlipperKeyController flipperController(&mainWindow);


  Pinball_Cover_M = Model();
  Pinball_Cover_M.LoadModel("resources/models/Pinball_Cover.obj");

  Skybox skybox;
	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("resources/textures/skybox/arc_rt.png");
	skyboxFaces.push_back("resources/textures/skybox/arc_lf.png");
	skyboxFaces.push_back("resources/textures/skybox/arc_dn.png");
	skyboxFaces.push_back("resources/textures/skybox/arc_up.png");
	skyboxFaces.push_back("resources/textures/skybox/arc_bk.png");
	skyboxFaces.push_back("resources/textures/skybox/arc_ft.png");

  skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);

  Texture facesTextures[10];

  for(int i = 0; i < 10; i++)
  {
    char plantilla[] = "resources/textures/personaje$.tga";
    plantilla[28] = '0' + i;
    facesTextures[i] = Texture(plantilla);
    facesTextures[i].LoadTextureA();
  }

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset=0;
	GLuint uniformColor = 0;
	glm::mat4* projection = nullptr;

	
  ////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		dt = now - lastTime;
		deltaTime = dt + (now - lastTime) / limitFPS;
		lastTime = now;

    //Recibir eventos del usuario
		glfwPollEvents();
    cameraController.HandleKeyBoard(dt);
    camera = cameraController.GetCamera();
    projection = cameraController.GetProjection();
    lm.HandleKeyBoard(mainWindow.getsKeys());

    perry.SetPosition(
      cameraController.GetUserCamera()->getCameraPosition().x,
      cameraController.GetUserCamera()->getCameraPosition().y,
      cameraController.GetUserCamera()->getCameraPosition().z + 4.0f
    );

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    skybox.DrawSkybox(camera->calculateViewMatrix(), *projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		uniformTextureOffset = shaderList[0].getOffsetLocation();

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(*projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera->calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera->getCameraPosition().x, camera->getCameraPosition().y, camera->getCameraPosition().z);

		shaderList[0].SetDirectionalLight(lm.GetAmbientLight());
		shaderList[0].SetPointLights(lm.GetPointLights(), lm.GetNumOfPointLights());
    shaderList[0].SetSpotLights(lm.GetSpotLights(), lm.GetNumOfSpottLights());

    glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec2 toffset = glm::vec2(0.0f, 0.0f);
		
    // Para el piso
		model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
    glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		floorTexture.UseTexture();

		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[1]->RenderMesh();

    // Cubierta de la máquina de pinball
    model = glm::mat4(1.0f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
    Pinball_Cover_M.RenderModel();

    // Obstáculo aleatorio
    Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
    bn1.Render(uniformModel);
    bn2.Render(uniformModel);
    bn3.Render(uniformModel);
    bn4.Render(uniformModel);

    bp1.Render(uniformModel);
    bp2.Render(uniformModel);
    bp3.Render(uniformModel);

    springMouseController.Handle();
    spring.Animate(dt);
    spring.Render(uniformModel);

    ballAnimation.HandleStart();
    ballAnimation.Update(dt);
		ball1.Render(uniformModel, uniformSpecularIntensity, uniformShininess);

    ballKeyAnimation.Update(dt);
		ball2.Render(uniformModel, uniformSpecularIntensity, uniformShininess);

    // Rotación de articulaciones
    in_an_1.Update(dt);
    in_an_2.Update(dt);
    in_an_3.Update(dt);

    // Se despliegan los dos inadores
    in1.Render(uniformModel);
    in2.Render(uniformModel);
    in3.Render(uniformModel);

    // Se despliegan los flippers
    fizq.Render(uniformModel, uniformSpecularIntensity, uniformShininess);
    fder.Render(uniformModel, uniformSpecularIntensity, uniformShininess);
    fmin.Render(uniformModel, uniformSpecularIntensity, uniformShininess);

    flipperController.Handle(&fizq, dt);
    flipperController.Handle(&fder, dt);
    flipperController.Handle(&fmin, dt);

    // Personaje
    perryAnimation.HandleKeyboard(dt);
    if(cameraController.GetCameraType() == 0)
      perry.Render(uniformModel);
    perry.Animate(dt);

		earth.Animate(dt);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		earth.Render(uniformModel);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Para las caras
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));
    model = glm::scale(model, glm::vec3(5.0f, 1.0f, 5.0f));
    glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		facesTextures[0].UseTexture();
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(-10.0f, 0.5f, 0.0f));
    model = glm::scale(model, glm::vec3(5.0f, 1.0f, 5.0f));
    glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		facesTextures[1].UseTexture();
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(10.0f, 0.5f, 0.0f));
    model = glm::scale(model, glm::vec3(5.0f, 1.0f, 5.0f));
    glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		facesTextures[2].UseTexture();
		meshList[0]->RenderMesh();

    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(0.0f, 0.5f, 10.0f));
    model = glm::scale(model, glm::vec3(5.0f, 1.0f, 5.0f));
    glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		facesTextures[3].UseTexture();
		meshList[0]->RenderMesh();

    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(10.0f, 0.5f, 10.0f));
    model = glm::scale(model, glm::vec3(5.0f, 1.0f, 5.0f));
    glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		facesTextures[4].UseTexture();
		meshList[0]->RenderMesh();

    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(-10.0f, 0.5f, 10.0f));
    model = glm::scale(model, glm::vec3(5.0f, 1.0f, 5.0f));
    glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		facesTextures[5].UseTexture();
		meshList[0]->RenderMesh();

    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(-5.0f, 0.5f, 20.0f));
    model = glm::scale(model, glm::vec3(5.0f, 1.0f, 5.0f));
    glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		facesTextures[6].UseTexture();
		meshList[0]->RenderMesh();

    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(5.0f, 0.5f, 20.0f));
    model = glm::scale(model, glm::vec3(5.0f, 1.0f, 5.0f));
    glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		facesTextures[7].UseTexture();
		meshList[0]->RenderMesh();

    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(5.0f, 0.5f, -10.0f));
    model = glm::scale(model, glm::vec3(5.0f, 1.0f, 5.0f));
    glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		facesTextures[8].UseTexture();
		meshList[0]->RenderMesh();

    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(-5.0f, 0.5f, -10.0f));
    model = glm::scale(model, glm::vec3(5.0f, 1.0f, 5.0f));
    glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		facesTextures[9].UseTexture();
		meshList[0]->RenderMesh();

    glDisable(GL_BLEND);

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
