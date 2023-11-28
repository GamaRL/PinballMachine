/* Semestre 2024-1
Animación por keyframes
La textura del skybox fue conseguida desde la página https://opengameart.org/content/elyvisions-skyboxes?page=1
y edité en Gimp rotando 90 grados en sentido antihorario la imagen  sp2_up.png para poder ver continuidad.
Fuentes :
	https ://www.khronos.org/opengl/wiki/Keyframe_Animation
	http ://what-when-how.com/wp-content/uploads/2012/07/tmpcd0074_thumb.png
	*/
	//para cargar imagen
#include <glm/fwd.hpp>
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>//para abrir archivos
#include <iostream>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "./include/CameraToggleController.h"
#include "Texture.h"
#include "Model.h"
#include "Skybox.h"

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
const float toRadians = 3.14159265f / 180.0f;

//variables para animación
float movCoche;
float movOffset;
float rotllanta;
float rotllantaOffset;
bool avanza;
float toffsetflechau = 0.0f;
float toffsetflechav = 0.0f;
float toffsetnumerou = 0.0f;
float toffsetnumerov = 0.0f;
float toffsetnumerocambiau = 0.0;
float angulovaria = 0.0f;

//variables para keyframes
float reproduciranimacion, habilitaranimacion, guardoFrame, reinicioFrame, ciclo, ciclo2, contador = 0;

glm::vec3 pos_ball = glm::vec3(0.0f, 0.0f, 0.0f);


///////////////////////////////KEYFRAMES/////////////////////


bool animacion = false;



//NEW// Keyframes
float posXavion = 53.5f, posYavion = 2.0f, posZavion = 84.0f;
float	movBall_x = 0.0f, movBall_z=0.0f;
float	tamXBall = 1.0f, tamYBall = 1.0f, tamZBall = 1.0f;
float giroAvion = 0.0f;

#define MAX_FRAMES 100
int i_max_steps = 90;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float movBall_x;		//Variable para PosicionX
	float movBall_z;		//Variable para PosicionZ
	float movBall_xInc;		//Variable para IncrementoX
	float movBall_zInc;		//Variable para IncrementoY
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void) //tecla L
{

	printf("frameindex %d\n", FrameIndex);


	KeyFrame[FrameIndex].movBall_x = movBall_x;
	KeyFrame[FrameIndex].movBall_z = movBall_z;
	FILE* archivo;

  /*if (fopen_s(&archivo, "Animacion.txt", "a") == 0) {
		// Verifica si el archivo se abrió correctamente
		if (archivo != nullptr) {
			// Escribe el texto en el archivo utilizando fprintf
			fprintf(archivo, "KeyFrame[%d].movBall_x = %f f;\n", FrameIndex, KeyFrame[FrameIndex].movBall_x);
			fprintf(archivo, "KeyFrame[%d].movBall_y = %f f;\n", FrameIndex, KeyFrame[FrameIndex].movBall_y);
			fprintf(archivo, "KeyFrame[%d].movBall_z = %f f;\n", FrameIndex, KeyFrame[FrameIndex].movBall_z);
			fprintf(archivo, "KeyFrame[%d].scaleBall_x = %f f;\n", FrameIndex, KeyFrame[FrameIndex].scaleBall_x);
			fprintf(archivo, "KeyFrame[%d].scaleBall_y = %f f;\n", FrameIndex, KeyFrame[FrameIndex].scaleBall_y);
			fprintf(archivo, "KeyFrame[%d].scaleBall_z = %f f;\n", FrameIndex, KeyFrame[FrameIndex].scaleBall_z);
			fprintf(archivo, "KeyFrame[%d].giroAvion = %f;\n", FrameIndex, KeyFrame[FrameIndex].giroAvion);

			// Cierra el archivo
			fclose(archivo);

			printf("Texto guardado exitosamente en %s\n", "Animacion.txt");
		}
		else {
			perror("Error al abrir el archivo");
		}
	}
	else {
		perror("Error al abrir el archivo");
	}*/


	FrameIndex++;

}

void resetElements(void) //Tecla 0
{

	movBall_x = KeyFrame[0].movBall_x;
	movBall_z = KeyFrame[0].movBall_z;
}

void interpolation(void)
{
	KeyFrame[playIndex].movBall_xInc = (KeyFrame[playIndex + 1].movBall_x - KeyFrame[playIndex].movBall_x) / i_max_steps;
	KeyFrame[playIndex].movBall_zInc = (KeyFrame[playIndex + 1].movBall_z - KeyFrame[playIndex].movBall_z) / i_max_steps;

}


void animate(void)
{
	//Movimiento del objeto con barra espaciadora
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //fin de animación entre frames?
		{
			playIndex++;
			printf("playindex : %d\n", playIndex);
			if (playIndex > FrameIndex - 2)	//Fin de toda la animación con último frame?
			{
				printf("Frame index= %d\n", FrameIndex);
				printf("termino la animacion\n");
				playIndex = 0;
				play = false;
			}
			else //Interpolación del próximo cuadro
			{

				i_curr_steps = 0; //Resetea contador
				//Interpolar
				interpolation();
			}
		}
		else
		{
			//Dibujar Animación
			movBall_x += KeyFrame[playIndex].movBall_xInc;
			movBall_z += KeyFrame[playIndex].movBall_zInc;
			i_curr_steps++;
		}

	}
}

///////////////* FIN KEYFRAMES*////////////////////////////



void inputKeyframes(bool* keys)
{
	if (keys[GLFW_KEY_SPACE])
	{
		if (reproduciranimacion < 1)
		{
			if (play == false && (FrameIndex > 1))
			{
				resetElements();
				//First Interpolation				
				interpolation();
				play = true;
				playIndex = 0;
				i_curr_steps = 0;
				reproduciranimacion++;
				printf("\n presiona 0 para habilitar reproducir de nuevo la animación'\n");
				habilitaranimacion = 0;

			}
			else
			{
				play = false;

			}
		}
	}
	if (keys[GLFW_KEY_0])
	{
		if (habilitaranimacion < 1 && reproduciranimacion>0)
		{
			printf("Ya puedes reproducir de nuevo la animación con la tecla de barra espaciadora'\n");
			reproduciranimacion = 0;

		}
	}

	if (keys[GLFW_KEY_L])
	{
		if (guardoFrame < 1)
		{
			saveFrame();
			printf("movBall_x es: %f\n", movBall_x);
			printf("presiona P para habilitar guardar otro frame'\n");
			guardoFrame++;
			reinicioFrame = 0;
		}
	}
	if (keys[GLFW_KEY_P])
	{
		if (reinicioFrame < 1 && guardoFrame>0)
		{
			guardoFrame = 0;
			printf("Ya puedes guardar otro frame presionando la tecla L'\n");
		}
	}


	if (keys[GLFW_KEY_Z])
	{
		if (ciclo < 1)
		{
			printf("movBall_x es: %f\n", movBall_x);
			movBall_x += 1.0f;
			printf("\n movBall_x es: %f\n", movBall_x);
			ciclo++;
			ciclo2 = 0;
			printf("\n Presiona la tecla 2 para poder habilitar la variable\n");
		}

	}




	if (keys[GLFW_KEY_X])
	{
		if (ciclo < 1)
		{
			printf("movBall_x es: %f\n", movBall_x);
			movBall_x -= 1.0f;
			printf("\n movBall_x es: %f\n", movBall_x);
			ciclo++;
			ciclo2 = 0;
			printf("\n Presiona la tecla 2 para poder habilitar la variable\n");
		}

	}


	if (keys[GLFW_KEY_C])
	{
		if (ciclo < 1)
		{
			printf("movBall_z es: %f\n", movBall_z);
			movBall_z += 1.0f;
			printf("\n movBall_x es: %f\n", movBall_z);
			ciclo++;
			ciclo2 = 0;
			printf("\n Presiona la tecla 2 para poder habilitar la variable\n");
		}

	}


	if (keys[GLFW_KEY_V])
	{
		if (ciclo < 1)
		{
			printf("movBall_z es: %f\n", movBall_z);
			movBall_z -= 1.0f;
			printf("\n movBall_z es: %f\n", movBall_z);
			ciclo++;
			ciclo2 = 0;
			printf("\n Presiona la tecla 2 para poder habilitar la variable\n");
		}

	}


	if (keys[GLFW_KEY_2])
	{
		if (ciclo2 < 1 && ciclo>0)
		{
			ciclo = 0;
			printf("\n Ya puedes modificar tu variable presionando la tecla correspondiente\n");
		}
	}

}


Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Texture plainTexture;

Model Pinball_Cover_M;
Model Animated_Ball;

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
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};
	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


	};
	

	unsigned int flechaIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat flechaVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

	};

	unsigned int scoreIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat scoreVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

	};

	unsigned int numeroIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat numeroVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.67f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		0.25f, 0.67f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		0.25f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

	};

	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);


	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	Mesh* obj5 = new Mesh();
	obj5->CreateMesh(flechaVertices, flechaIndices, 32, 6);
	meshList.push_back(obj5);

	Mesh* obj6 = new Mesh();
	obj6->CreateMesh(scoreVertices, scoreIndices, 32, 6);
	meshList.push_back(obj6);

	Mesh* obj7 = new Mesh();
	obj7->CreateMesh(numeroVertices, numeroIndices, 32, 6);
	meshList.push_back(obj7);

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

  Perry::Initialise();
	Perry perry(10.0f, 5.0f, 60.0f);


  Ball::Initialise();
	Ball ball(10.0f, 5.0f, 0.0f);

  BallAnimation ballAnimation(&ball, &mainWindow);

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
  Animated_Ball = Model();
  Animated_Ball.LoadModel("resources/models/Ball.obj");

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

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset=0;
	GLuint uniformColor = 0;
	glm::mat4* projection = nullptr;

	printf("\nTeclas para uso de Keyframes:\n1.-Presionar barra espaciadora para reproducir animacion.\n2.-Presionar 0 para volver a habilitar reproduccion de la animacion\n");
	printf("3.-Presiona L para guardar frame\n4.-Presiona P para habilitar guardar nuevo frame\n5.-Presiona z para mover en X positivo \n6.-Presiona M para mover x negativo \n7.-Presiona X para mover en Y positivo\n8.-Presiona N para mover en Y negativo\n9.-Presiona C para mover en Z positivo\n10.-Presiona B para mover en Z negativo\n11.-Presiona E para escalar en X positivo\n12.-Presiona O para escalar en X negativo\n13.-Presiona R para escalar en Y positivo\n14.-Presiona I para escalar en Y negativo\n15.-Presiona T para escalar en Z positivo\n16.-Presiona U para escalar en Z negativo\n17.Presiona U para reestablecer la escala original\n18.-Presiona 2 para habilitar las transformaciones");
	
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
		
    /*glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		plainTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();*/

    // Cubierta de la máquina de pinball
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
    Pinball_Cover_M.RenderModel();

    // Obstáculo aleatorio
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
		ball.Render(uniformModel, uniformSpecularIntensity, uniformShininess);

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

		earth.Animate(dt);
		earth.Render(uniformModel);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(movBall_x, 1.0f, movBall_z));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, giroAvion/9 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Animated_Ball.RenderModel();

    inputKeyframes(mainWindow.getsKeys());
    animate();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

  for (int i = 0; i < FrameIndex; i++)
  {
			printf("KeyFrame[%d].movBall_x = %ff;\n", i, KeyFrame[i].movBall_x);
			printf("KeyFrame[%d].movBall_z = %ff;\n", i, KeyFrame[i].movBall_z);
  }

	return 0;
}
