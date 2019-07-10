#include "SceneText.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "LoadHmap.h"
#include <sstream>

using namespace std;

#define TERRAINCOLOR Color(1,0.5,0.5)
#define SKYCOLOR Color(0.5,0.5,1)

SceneText::SceneText()
{
}

SceneText::~SceneText()
{
}

void SceneText::Init()
{
	// Black background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 
	
	glEnable(GL_CULL_FACE);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	 
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	m_programID = LoadShaders( "Shader//Fog.vertexshader", "Shader//Fog.fragmentshader" );
	
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");
	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled[0]");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture[0]");
	m_parameters[U_COLOR_TEXTURE_ENABLED + 1] = glGetUniformLocation(m_programID, "colorTextureEnabled[1]");
	m_parameters[U_COLOR_TEXTURE + 1] = glGetUniformLocation(m_programID, "colorTexture[1]");
	m_parameters[U_COLOR_TEXTURE_ENABLED + 2] = glGetUniformLocation(m_programID, "colorTextureEnabled[2]");
	m_parameters[U_COLOR_TEXTURE + 2] = glGetUniformLocation(m_programID, "colorTexture[2]");
	m_parameters[U_COLOR_TEXTURE_ENABLED + 3] = glGetUniformLocation(m_programID, "colorTextureEnabled[3]");
	m_parameters[U_COLOR_TEXTURE+ 3] = glGetUniformLocation(m_programID, "colorTexture[3]");
	m_parameters[U_COLOR_TEXTURE_ENABLED + 4] = glGetUniformLocation(m_programID, "colorTextureEnabled[4]");
	m_parameters[U_COLOR_TEXTURE + 4] = glGetUniformLocation(m_programID, "colorTexture[4]");
	m_parameters[U_COLOR_TEXTURE_ENABLED + 5] = glGetUniformLocation(m_programID, "colorTextureEnabled[5]");
	m_parameters[U_COLOR_TEXTURE + 5] = glGetUniformLocation(m_programID, "colorTexture[5]");
	m_parameters[U_COLOR_TEXTURE_ENABLED + 6] = glGetUniformLocation(m_programID, "colorTextureEnabled[6]");
	m_parameters[U_COLOR_TEXTURE + 6] = glGetUniformLocation(m_programID, "colorTexture[6]");
	m_parameters[U_COLOR_TEXTURE_ENABLED+7] = glGetUniformLocation(m_programID, "colorTextureEnabled[7]");
	m_parameters[U_COLOR_TEXTURE+7] = glGetUniformLocation(m_programID, "colorTexture[7]");
	
	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");


	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	m_parameters[U_FOG_COLOR] = glGetUniformLocation(m_programID, "fogParam.color");
	m_parameters[U_FOG_START] = glGetUniformLocation(m_programID, "fogParam.start");
	m_parameters[U_FOG_END] = glGetUniformLocation(m_programID, "fogParam.end");
	m_parameters[U_FOG_DENSITY] = glGetUniformLocation(m_programID, "fogParam.density");
	m_parameters[U_FOG_TYPE] = glGetUniformLocation(m_programID, "fogParam.type");
	m_parameters[U_FOG_ENABLED] = glGetUniformLocation(m_programID, "fogParam.enabled");

	// Use our shader
	glUseProgram(m_programID);

	lights[0].type = Light::LIGHT_POINT;
	lights[0].position.Set(0, 20, 0);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 1.f;
	lights[0].kC = 1.f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.001f;
	lights[0].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0].cosInner = cos(Math::DegreeToRadian(30));
	lights[0].exponent = 3.f;
	lights[0].spotDirection.Set(0.f, 1.f, 0.f);

	lights[1].type = Light::LIGHT_DIRECTIONAL;
	lights[1].position.Set(1, 1, 0);
	lights[1].color.Set(1, 1, 0.5f);
	lights[1].power = 0.0f;
	//lights[1].kC = 1.f;
	//lights[1].kL = 0.01f;
	//lights[1].kQ = 0.001f;
	//lights[1].cosCutoff = cos(Math::DegreeToRadian(45));
	//lights[1].cosInner = cos(Math::DegreeToRadian(30));
	//lights[1].spotDirection.Set(0.f, 1.f, 0.f);
	
	glUniform1i(m_parameters[U_NUMLIGHTS], 1);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &lights[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], lights[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], lights[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], lights[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], lights[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], lights[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], lights[0].exponent);
	
	glUniform1i(m_parameters[U_LIGHT1_TYPE], lights[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &lights[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], lights[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], lights[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], lights[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], lights[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], lights[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], lights[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], lights[1].exponent);

	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));

	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	
	rotateAngle = 0; 
	bLightEnabled = true;

	fogColor.Set(0.79f, 0.84f, 0.85f);
	glUniform3fv(m_parameters[U_FOG_COLOR], 1, &fogColor.r);
	fogStart = 10.f;
	glUniform1f(m_parameters[U_FOG_START], fogStart);
	fogEnd = 1000.f;
	glUniform1f(m_parameters[U_FOG_END], fogEnd);
	fogDensity = 0.0001f;
	glUniform1f(m_parameters[U_FOG_DENSITY], fogDensity);
	glUniform1i(m_parameters[U_FOG_TYPE], 1);
	glUniform1i(m_parameters[U_FOG_ENABLED], 1);

	watertranslate = 0.f;

	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference");
	meshList[GEO_CROSSHAIR] = MeshBuilder::GenerateCrossHair("crosshair");
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f);
	meshList[GEO_QUAD]->textureArray[0] = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureArray[0] = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);
	meshList[GEO_OBJECT] = MeshBuilder::GenerateOBJ("OBJ1", "OBJ//chair.obj");
	meshList[GEO_OBJECT]->textureArray[0] = LoadTGA("Image//chair.tga");
	meshList[GEO_RING] = MeshBuilder::GenerateRing("ring", Color(1, 0, 1), 36, 1, 0.5f);
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 18, 36, 1.f);
	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1, 0, 0), 18, 36, 10.f);
	meshList[GEO_CONE] = MeshBuilder::GenerateCone("cone", Color(0.5f, 1, 0.3f), 36, 10.f, 10.f);
	meshList[GEO_CONE]->material.kDiffuse.Set(0.99f, 0.99f, 0.99f);
	meshList[GEO_CONE]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_SKYPLANE] = MeshBuilder::GenerateSkyPlane("skyplane", Color(1, 0, 1), 4, 100.f, 150.f, 10.f, 10.f);

	// Load the ground mesh and texture
	meshList[GEO_GRASS_DARKGREEN] = MeshBuilder::GenerateQuad("GRASS_DARKGREEN", Color(1, 0, 1), 1.f);
	meshList[GEO_GRASS_DARKGREEN]->textureArray[0] = LoadTGA("Image//grass_darkgreen.tga");
	meshList[GEO_GRASS_LIGHTGREEN] = MeshBuilder::GenerateQuad("GEO_GRASS_LIGHTGREEN", Color(0, 1, 1), 1.f);
	meshList[GEO_GRASS_LIGHTGREEN]->textureArray[0] = LoadTGA("Image//grass_lightgreen.tga");

	meshList[GEO_SKYPLANE] = MeshBuilder::GenerateSkyPlane("skyplane", Color(1.0f, 0, 0), 128, 200.f, 2100.f, 1, 1);
	meshList[GEO_SKYPLANE]->textureArray[0] = LoadTGA("Image//sky.tga");
	//TERRAIN
	meshList[GEO_TERRAIN] = MeshBuilder::GenerateTerrain("terrain", "Image//heightmap2.raw", m_heightMap);
	meshList[GEO_TERRAIN]->textureArray[0] = LoadTGA("Image//grass_darkgreen.tga");
	meshList[GEO_TERRAIN]->textureArray[1] = LoadTGA("Image//ForestFloor.tga");

	//TREE
	meshList[GEO_TREE] = MeshBuilder::GenerateOBJ("treeObj", "OBJ//Tree.obj");
	meshList[GEO_TREE]->textureArray[0] = LoadTGA("Image//Tree.tga");
	meshList[GEO_TREE]->textureArray[1] = LoadTGA("Image//TreeMoss.tga");

	//WATER
	meshList[GEO_WATER] = MeshBuilder::GenerateQuad("WaterPlane", Color(0, 0, 0), 150.f);
	meshList[GEO_WATER]->textureArray[0] = LoadTGA("Image//sea.tga");


	meshList[GEO_FIRE] = MeshBuilder::GenerateSpriteAnimation("Fire", 1, 6);
	meshList[GEO_FIRE]->textureArray[0] = LoadTGA("Image//Fire.tga");
	fireanim = dynamic_cast<SpriteAnimation*>(meshList[GEO_FIRE]);
	if (fireanim)
	{
		fireanim->m_anim = new Animation();
		fireanim->m_anim->Set(0, 5, 1, 1.f, true);
	}


	meshList[GEO_CAMPFIRE] = MeshBuilder::GenerateOBJ("Campfire", "OBJ//Campfire.obj");
	meshList[GEO_CAMPFIRE]->textureArray[0] = LoadTGA("Image//Campfire.tga");

	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	//perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	perspective.SetToPerspective(75.0f, 4.0f / 3.0f, 0.1f, 10000.0f);

	projectionStack.LoadMatrix(perspective);
	
	rotateAngle = 0; 

	bLightEnabled = true;
}

//void SceneText::InitParameters()
//{
//	{
//		m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
//
//
//		m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
//		m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
//		m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
//		m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
//		m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
//		m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
//		m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
//
//		//init light parameters
//		for (int i = 0; i < LIGHTCOUNT; i++)
//		{
//
//			cout << "LIGHT " << i << " :" << endl;
//
//			string thestring = "lights[" + to_string(i) + "].position_cameraspace";
//			{
//				const char *c_str = thestring.c_str();
//				m_parameters[i * 12 + 7] = glGetUniformLocation(m_programID, c_str);
//				cout << "- [" << i * 12 + 7 << "] " << thestring << endl;
//			}
//			thestring = "lights[" + to_string(i) + "].color";
//			{
//				const char *c_str = thestring.c_str();
//				m_parameters[i * 12 + 8] = glGetUniformLocation(m_programID, c_str);
//				cout << "- [" << i * 12 + 8 << "] " << thestring << endl;
//			}
//			thestring = "lights[" + to_string(i) + "].power";
//			{
//				const char *c_str = thestring.c_str();
//
//				m_parameters[i * 12 + 9] = glGetUniformLocation(m_programID, c_str);
//				cout << "- [" << i * 12 + 9 << "] " << thestring << endl;
//			}
//			thestring = "lights[" + to_string(i) + "].kC";
//			{
//				const char *c_str = thestring.c_str();
//				m_parameters[i * 12 + 10] = glGetUniformLocation(m_programID, c_str);
//				cout << "- [" << i * 12 + 10 << "] " << thestring << endl;
//			}
//			thestring = "lights[" + to_string(i) + "].kL";
//			{
//				const char *c_str = thestring.c_str();
//				m_parameters[i * 12 + 11] = glGetUniformLocation(m_programID, c_str);
//				cout << "- [" << i * 12 + 11 << "] " << thestring << endl;
//			}
//			thestring = "lights[" + to_string(i) + "].kQ";
//			{
//				const char *c_str = thestring.c_str();
//				m_parameters[i * 12 + 12] = glGetUniformLocation(m_programID, c_str);
//				cout << "- [" << i * 12 + 12 << "] " << thestring << endl;
//			}
//			if (i > 0)
//				thestring = "light" + to_string(i) + "Enabled";
//			else
//				thestring = "lightEnabled";
//			{
//				const char *c_str = thestring.c_str();
//				m_parameters[i * 12 + 13] = glGetUniformLocation(m_programID, c_str);
//				cout << "- " << thestring << endl;
//			}
//			thestring = "lights[" + to_string(i) + "].type";
//			{
//				const char *c_str = thestring.c_str();
//				m_parameters[i * 12 + 14] = glGetUniformLocation(m_programID, c_str);
//				cout << "- [" << i * 12 + 14 << "] " << thestring << endl;
//			}
//			thestring = "lights[" + to_string(i) + "].spotDirection";
//			{
//				const char *c_str = thestring.c_str();
//				m_parameters[i * 12 + 15] = glGetUniformLocation(m_programID, c_str);
//				cout << "- [" << i * 12 + 15 << "] " << thestring << endl;
//			}
//			thestring = "lights[" + to_string(i) + "].cosCutoff";
//			{
//				const char *c_str = thestring.c_str();
//				m_parameters[i * 12 + 16] = glGetUniformLocation(m_programID, c_str);
//				cout << "- [" << i * 12 + 16 << "] " << thestring << endl;
//			}
//			thestring = "lights[" + to_string(i) + "].cosInner";
//			{
//				const char *c_str = thestring.c_str();
//				m_parameters[i * 12 + 17] = glGetUniformLocation(m_programID, c_str);
//				cout << "- [" << i * 12 + 17 << "] " << thestring << endl;
//			}
//			thestring = "lights[" + to_string(i) + "].exponent";
//			{
//				const char *c_str = thestring.c_str();
//				m_parameters[i * 12 + 18] = glGetUniformLocation(m_programID, c_str);
//				cout << "- [" << i * 12 + 18 << "] " << thestring << endl;
//			}
//
//			cout << "==============" << endl;
//		}
//		cout << "NUMLIGHTCUTOFF VALUE: " << NUMLIGHTCUTOFF << endl;
//
//		glUniform1i(m_parameters[U_NUMLIGHTS], LIGHTCOUNT);
//		glEnable(GL_DEPTH_TEST);
//
//		// passing uniform parameters after glUseProgram()
//		for (int i = 0; i < LIGHTCOUNT; i++)
//		{
//			glUniform1i(m_parameters[i * 12 + 14], lights[i].type);
//			glUniform3fv(m_parameters[i * 12 + 8], 1, &lights[i].color.r);
//			glUniform1f(m_parameters[i * 12 + 9], lights[i].power);
//			glUniform1f(m_parameters[i * 12 + 10], lights[i].kC);
//			glUniform1f(m_parameters[i * 12 + 11], lights[i].kL);
//			glUniform1f(m_parameters[i * 12 + 12], lights[i].kQ);
//			glUniform1f(m_parameters[i * 12 + 16], lights[i].cosCutoff);
//			glUniform1f(m_parameters[i * 12 + 17], lights[i].cosInner);
//			glUniform1f(m_parameters[i * 12 + 18], lights[i].exponent);
//		};
//
//		// init other non-light parameters here
//		m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
//		m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
//		m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
//		m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");
//
//	}
//}

void SceneText::InitMeshList()
{
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference");
	meshList[GEO_CROSSHAIR] = MeshBuilder::GenerateCrossHair("crosshair");
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f);
	meshList[GEO_QUAD]->textureArray[0] = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureArray[0] = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);
	meshList[GEO_OBJECT] = MeshBuilder::GenerateOBJ("OBJ1", "OBJ//chair.obj");
	meshList[GEO_OBJECT]->textureArray[0] = LoadTGA("Image//chair.tga");
	meshList[GEO_RING] = MeshBuilder::GenerateRing("ring", Color(1, 0, 1), 36, 1, 0.5f);
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 18, 36, 1.f);
	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1, 0, 0), 18, 36, 10.f);
	meshList[GEO_CONE] = MeshBuilder::GenerateCone("cone", Color(0.5f, 1, 0.3f), 36, 10.f, 10.f);
	meshList[GEO_CONE]->material.kDiffuse.Set(0.99f, 0.99f, 0.99f);
	meshList[GEO_CONE]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_SKYPLANE] = MeshBuilder::GenerateSkyPlane("skyplane", Color(1.0f, 0, 0), 128, 200.f, 2100.f, 1, 1);
	meshList[GEO_SKYPLANE]->textureArray[0] = LoadTGA("Image//sky.tga");
	//TERRAIN
	meshList[GEO_TERRAIN] = MeshBuilder::GenerateTerrain("terrain", "Image//heightmap2.raw", m_heightMap);
	meshList[GEO_TERRAIN]->textureArray[0] = LoadTGA("Image//grass_darkgreen.tga");
	meshList[GEO_TERRAIN]->textureArray[1] = LoadTGA("Image//ForestFloor.tga");

	//TREE
	meshList[GEO_TREE] = MeshBuilder::GenerateOBJ("treeObj", "OBJ//Tree.obj");
	meshList[GEO_TREE]->textureArray[0] = LoadTGA("Image//Tree.tga");
	meshList[GEO_TREE]->textureArray[1] = LoadTGA("Image//TreeMoss.tga");
	 
	//WATER
	meshList[GEO_WATER] = MeshBuilder::GenerateQuad("WaterPlane", Color(0, 0, 0), 150.f);
	meshList[GEO_WATER]->textureArray[0] = LoadTGA("Image//sea.tga");


	// Load the ground mesh and texture
	meshList[GEO_GRASS_DARKGREEN] = MeshBuilder::GenerateQuad("GRASS_DARKGREEN", Color(1, 0, 1), 1.f);
	meshList[GEO_GRASS_DARKGREEN]->textureArray[0] = LoadTGA("Image//grass_darkgreen.tga");
	meshList[GEO_GRASS_LIGHTGREEN] = MeshBuilder::GenerateQuad("GEO_GRASS_LIGHTGREEN", Color(0, 1, 1), 1.f);
	meshList[GEO_GRASS_LIGHTGREEN]->textureArray[0] = LoadTGA("Image//grass_lightgreen.tga");

	//meshList[GEO_FIRE] = MeshBuilder::GenerateSpriteAnimation("Fire", 8, 8);
	//meshList[GEO_FIRE]->textureArray[0] = LoadTGA("Image//Fire1.tga");
	//fireanim = dynamic_cast<SpriteAnimation*>(meshList[GEO_FIRE]);
	//if (fireanim)
	//{
	//	fireanim->m_anim = new Animation();
	//	fireanim->m_anim->Set(0, 59, 1, 1.f, true);
	//}
	meshList[GEO_FIRE] = MeshBuilder::GenerateSpriteAnimation("Fire", 6, 6);
	meshList[GEO_FIRE]->textureArray[0] = LoadTGA("Image//Fire2.tga");
	fireanim = dynamic_cast<SpriteAnimation*>(meshList[GEO_FIRE]);
	if (fireanim)
	{
		fireanim->m_anim = new Animation();
		fireanim->m_anim->Set(0, 35, 1, 0.5f, true);
	}
	
	/*meshList[GEO_COTTAGE] = MeshBuilder::GenerateOBJ("cottage", "OBJ//cottagev2.obj");
	meshList[GEO_COTTAGE]->textureArray[0] = LoadTGA("Image//cottagev2.tga");
	meshList[GEO_COTTAGE]->textureArray[1] = LoadTGA("Image//cottage1v2.tga");*/

}

void SceneText::Update(double dt)
{
	if(Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	if(Application::IsKeyPressed('5'))
	{
		lights[0].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}
	else if(Application::IsKeyPressed('6'))
	{
		lights[0].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}
	else if(Application::IsKeyPressed('7'))
	{
		lights[0].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}
	else if(Application::IsKeyPressed('8'))
	{
		bLightEnabled = true;
	}
	else if(Application::IsKeyPressed('9'))
	{
		bLightEnabled = false;
	}

	//if(Application::IsKeyPressed('I'))
	//	lights[0].position.z -= (float)(10.f * dt);
	//if(Application::IsKeyPressed('K'))
	//	lights[0].position.z += (float)(10.f * dt);
	//if(Application::IsKeyPressed('J'))
	//	lights[0].position.x -= (float)(10.f * dt);
	//if(Application::IsKeyPressed('L'))
	//	lights[0].position.x += (float)(10.f * dt);
	//if(Application::IsKeyPressed('O'))
	//	lights[0].position.y -= (float)(10.f * dt);
	//if(Application::IsKeyPressed('P'))
	//	lights[0].position.y += (float)(10.f * dt);
	if (Application::IsKeyPressed('M'))
	{
		lights[0].power += (float)(10.f * dt);
		glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);

	}
	if (Application::IsKeyPressed('N'))
	{
		lights[0].power -= (float)(10.f * dt);
		glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);
	}

	if (Application::IsKeyPressed('Z'))
	{
		glUniform1i(m_parameters[U_FOG_ENABLED], 0);
	}
	else if (Application::IsKeyPressed('X'))
	{
		glUniform1i(m_parameters[U_FOG_ENABLED], 1);
	}
	
	if (Application::IsKeyPressed(VK_RETURN))
	{
		cout << camera.position.x << ',' << camera.position.z << '\n';
	}
	if (Application::IsKeyPressed('O'))
	{
		/*fogDensity += dt;
		cout << "adding to fog density, it's now : " << fogDensity << '\n';
		glUniform1f(m_parameters[U_FOG_DENSITY], fogDensity);*/

		fogDensity = 10.f;
		cout << "forced fogdensity to value of " << fogDensity << '\n';
		glUniform1f(m_parameters[U_FOG_DENSITY], fogDensity);

	}
	if (Application::IsKeyPressed('P'))
	{
		/*fogDensity -= dt;
		if (fogDensity < 0.f)
			fogDensity = 0.f;
		cout << "reducing to fog density, it's now : " << fogDensity << '\n';*/
		fogDensity = 1.f;
		cout << "forced fogdensity to value of " << fogDensity << '\n';

		glUniform1f(m_parameters[U_FOG_DENSITY], fogDensity);
	}
	if (Application::IsKeyPressed('K'))
	{

		fogStart += 10.f * dt;
		fogEnd += 10.f * dt;
		glUniform1f(m_parameters[U_FOG_START], fogStart);
		glUniform1f(m_parameters[U_FOG_END], fogEnd);

	}
	if (Application::IsKeyPressed('L'))
	{

		fogStart -= 10.f * dt;
		fogEnd -= 10.f * dt;
		glUniform1f(m_parameters[U_FOG_START], fogStart);
		glUniform1f(m_parameters[U_FOG_END], fogEnd);

	}

	if (camera.position.y < 80.f)
	{
		fogColor.Set(0, 0, 1.f);
		glUniform3fv(m_parameters[U_FOG_COLOR], 1, &fogColor.r);
	}
	else
	{
		fogColor.Set(0.79f, 0.84f, 0.85f);
		glUniform3fv(m_parameters[U_FOG_COLOR], 1, &fogColor.r);
	}

	if (Application::IsKeyPressed('C'))
	{
		// reset fog color
		fogColor.Set(0.79f, 0.84f, 0.85f);
		glUniform3fv(m_parameters[U_FOG_COLOR], 1, &fogColor.r);

	}
	if (Application::IsKeyPressed('V'))
	{
		fogColor.Set(0, 0, 1.f);
		glUniform3fv(m_parameters[U_FOG_COLOR], 1, &fogColor.r);
	}


	rotateAngle += (float)(10 * dt);
	watertranslate += (float)(dt) * 50;

	lights[0].position.Set(camera.position.x, camera.position.y, camera.position.z);

	camera.Update(dt);
	camera.SetCameraY(30 + 350.f * ReadHeightMap(m_heightMap, camera.position.x / 4000, camera.position.z / 4000), dt);

	fps = (float)(1.f / dt);

	fireanim = dynamic_cast<SpriteAnimation*>(meshList[GEO_FIRE]);
	if (fireanim)
	{
		fireanim->Update(dt);
		fireanim->m_anim->animActive = true;
	}
}

void SceneText::RenderText(Mesh* mesh, std::string text, Color color)
{
	if(!mesh || mesh->textureArray[0] <= 0)
		return;
	
	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureArray[0]);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SceneText::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if(!mesh || mesh->textureArray[0] <= 0)
		return;
	
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10);
	projectionStack.PushMatrix();
		projectionStack.LoadMatrix(ortho);
		viewStack.PushMatrix();
			viewStack.LoadIdentity();
			modelStack.PushMatrix();
				modelStack.LoadIdentity();
				modelStack.Translate(x, y, 0);
				modelStack.Scale(size, size, size);
				glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
				glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
				glUniform1i(m_parameters[U_LIGHTENABLED], 0);
				glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, mesh->textureArray[0]);
				glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
				for(unsigned i = 0; i < text.length(); ++i)
				{
					Mtx44 characterSpacing;
					characterSpacing.SetToTranslation(i * 1.0f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
					Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
					glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	
					mesh->Render((unsigned)text[i] * 6, 6);
				}
				glBindTexture(GL_TEXTURE_2D, 0);
				glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
			modelStack.PopMatrix();
		viewStack.PopMatrix();
	projectionStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void SceneText::RenderMeshIn2D(Mesh *mesh, bool enableLight, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(-80, 80, -60, 60, -10, 10);
	projectionStack.PushMatrix();
		projectionStack.LoadMatrix(ortho);
		viewStack.PushMatrix();
			viewStack.LoadIdentity();
			modelStack.PushMatrix();
				modelStack.LoadIdentity();
				modelStack.Scale(size, size, size);
				modelStack.Translate(x, y, 0);
       
				Mtx44 MVP, modelView, modelView_inverse_transpose;
	
				MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
				glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
				if(mesh->textureArray[0] > 0)
				{
					glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, mesh->textureArray[0]);
					glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
				}
				else
				{
					glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
				}
				mesh->Render();
				if(mesh->textureArray[0] > 0)
				{
					glBindTexture(GL_TEXTURE_2D, 0);
				}
       
			modelStack.PopMatrix();
		viewStack.PopMatrix();
	projectionStack.PopMatrix();

}

void SceneText::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);

	if (enableLight && bLightEnabled)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);

		//load materidal
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}

	for (int i = 0; i < MAX_TEXTURES; ++i)
	{
		if (mesh->textureArray[i] > 0)
		{
			//cout << "asdf\n";
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 1);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, mesh->textureArray[i]);
			glUniform1i(m_parameters[U_COLOR_TEXTURE + i], 0);
		}
		else
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 0);
		}
	}
	mesh->Render();

	for (int i = 0; i < MAX_TEXTURES; ++i)
	{
		if (mesh->textureArray[i] > 0)
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

}

void SceneText::RenderGround()
{
	modelStack.PushMatrix();
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Translate(0, 0, -10);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Scale(400.0f, 400.0f, 400.0f);

	for (int x=0; x<10; x++)
	{
		for (int z=0; z<10; z++)
		{
			modelStack.PushMatrix();
			modelStack.Translate(x-5.0f, z-5.0f, 0.0f);
			if ( ((x*9+z) % 2) == 0)
				RenderMesh(meshList[GEO_GRASS_DARKGREEN], false);
			else
				RenderMesh(meshList[GEO_GRASS_LIGHTGREEN], false);
			modelStack.PopMatrix();
		}
	}
	modelStack.PopMatrix();
}

void SceneText::RenderTerrain()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Scale(4000.0f, 350.f, 4000.0f);
	RenderMesh(meshList[GEO_TERRAIN], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(90.f, 80.f, -186.f + watertranslate);
	modelStack.Rotate(-90.f, 1.f, 0.f, 0.);
	//modelStack.Scale(4000.f, 4000.f, 1.f);
	modelStack.Scale(50.f, 50.f, 1.f);
	RenderMesh(meshList[GEO_WATER], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(90.f, 80.f, -106.f + watertranslate);
	modelStack.Rotate(-90.f, 1.f, 0.f, 0.);
	//modelStack.Scale(4000.f, 4000.f, 1.f);
	modelStack.Scale(50.f, 50.f, 1.f);
	modelStack.PopMatrix();

}

void SceneText::RenderSkyPlane()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 2100, 0);
	modelStack.Rotate(rotateAngle, 0, 1, 0);
	RenderMesh(meshList[GEO_SKYPLANE], false);
	modelStack.PopMatrix();
}
void SceneText::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);
	
	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
						camera.position.x, camera.position.y, camera.position.z,
						camera.target.x, camera.target.y, camera.target.z,
						camera.up.x, camera.up.y, camera.up.z
					);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	/*if(lights[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[0].position.x, lights[0].position.y, lights[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if(lights[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}
	if(lights[1].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[1].position.x, lights[1].position.y, lights[1].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if(lights[1].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
	}*/
	
	for (int i = 0; i < LIGHTCOUNT; i++)
	{
		if (lights[i].type == Light::LIGHT_DIRECTIONAL)
		{
			Vector3 lightDir(lights[i].position.x, lights[i].position.y, lights[i].position.z);
			Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
			glUniform3fv(m_parameters[i * 12 + 8], 1, &lightDirection_cameraspace.x);
		}
		else if (lights[i].type == Light::LIGHT_SPOT)
		{
			Position lightPosition_cameraspace = viewStack.Top() * lights[i].position;
			glUniform3fv(m_parameters[i * 12 + 8], 1, &lightPosition_cameraspace.x);
			Vector3 spotDirection_cameraspace = viewStack.Top() * lights[i].spotDirection;
			glUniform3fv(m_parameters[i * 12 + 15], 1, &spotDirection_cameraspace.x);
		}
		else
		{
			Position lightPosition_cameraspace = viewStack.Top() * lights[i].position;
			glUniform3fv(m_parameters[i * 12 + 8], 1, &lightPosition_cameraspace.x);
		}
	}
	RenderMesh(meshList[GEO_AXES], false);


	RenderSkyPlane();
	RenderTerrain();

	//modelStack.PushMatrix();
	//modelStack.Translate(-116.f, 350.f * ReadHeightMap(m_heightMap, -116.f / 4000, -201.f / 4000) - 40.f, -201.f);
	//modelStack.Rotate(-20, 0, 0, 1);
	//modelStack.Scale(30.0f, 30.f, 30.f);
	//RenderMesh(meshList[GEO_TREE], true);
	//modelStack.PopMatrix();

	// Render LightBall
	modelStack.PushMatrix();
	modelStack.Translate(lights[0].position.x, lights[0].position.y, lights[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	RenderGround();
	//RenderSkybox();
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	RenderMesh(meshList[GEO_OBJECT], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1110.f, 350.f * ReadHeightMap(m_heightMap, -1110.f / 4000, -460.f / 4000) - 40.f, -460.f);
	modelStack.Rotate(-20, 0, 0, 1);
	modelStack.Scale(30.0f, 30.f, 30.f);
	RenderMesh(meshList[GEO_TREE], true);
	modelStack.PopMatrix(); 
	
	modelStack.PushMatrix();
	modelStack.Translate(-975.f, 350.f * ReadHeightMap(m_heightMap, -975.f / 4000, -735.f / 4000) - 40.f, -735.f);
	modelStack.Rotate(-20, 0, 0, 1);
	modelStack.Scale(30.0f, 30.f, 30.f);
	RenderMesh(meshList[GEO_TREE], true);
	modelStack.PopMatrix(); 
	
	modelStack.PushMatrix();
	modelStack.Translate(-1065.f, 350.f * ReadHeightMap(m_heightMap, -1065.f / 4000, -900.f / 4000) - 40.f, -900.f);
	modelStack.Rotate(-20, 0, 0, 1);
	modelStack.Scale(30.0f, 30.f, 30.f);
	RenderMesh(meshList[GEO_TREE], true);
	modelStack.PopMatrix(); 
	
	modelStack.PushMatrix();
	modelStack.Translate(-715.f, 350.f * ReadHeightMap(m_heightMap, -715.f / 4000, -1170.f / 4000) - 40.f, -1170.f);
	modelStack.Rotate(-20, 0, 0, 1);
	modelStack.Scale(30.0f, 30.f, 30.f);
	RenderMesh(meshList[GEO_TREE], true);
	modelStack.PopMatrix(); 
	
	modelStack.PushMatrix();
	modelStack.Translate(-675.f, 350.f * ReadHeightMap(m_heightMap, -675.f / 4000, -1350.f / 4000) - 40.f, -1350.f);
	modelStack.Rotate(-20, 0, 0, 1);
	modelStack.Scale(30.0f, 30.f, 30.f);
	RenderMesh(meshList[GEO_TREE], true);
	modelStack.PopMatrix(); 
	
	modelStack.PushMatrix();
	modelStack.Translate(-340.f, 350.f * ReadHeightMap(m_heightMap, -340.f / 4000, -1570.f / 4000) - 40.f, -1570.f);
	modelStack.Rotate(-20, 0, 0, 1);
	modelStack.Scale(30.0f, 30.f, 30.f);
	RenderMesh(meshList[GEO_TREE], true);
	modelStack.PopMatrix(); 
	
	modelStack.PushMatrix();
	modelStack.Translate(-80.f, 350.f * ReadHeightMap(m_heightMap, -80.f / 4000, -1810.f / 4000) - 40.f, -1810.f);
	modelStack.Rotate(-20, 0, 0, 1);
	modelStack.Scale(30.0f, 30.f, 30.f);
	RenderMesh(meshList[GEO_TREE], true);
	modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//modelStack.Translate(-20, 0, -20);
	//RenderMesh(meshList[GEO_OBJECT], false);
	//modelStack.PopMatrix();
	//
	//modelStack.PushMatrix();
	//modelStack.Translate(-20, 0, -20);
	//RenderMesh(meshList[GEO_OBJECT], false);
	//modelStack.PopMatrix();
	//
	//modelStack.PushMatrix();
	//modelStack.Translate(20, 0, -20);
	//RenderMesh(meshList[GEO_OBJECT], true);
	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//modelStack.Translate(-725.f, 350.f * ReadHeightMap(m_heightMap, -160.f / 4000, -120.f / 4000) + 100.f, 545.f);
	////modelStack.Scale(10, 10, 10);
	//RenderMesh(meshList[GEO_COTTAGE], false);
	//modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-160.f, 350.f * ReadHeightMap(m_heightMap, -160.f / 4000, -120.f / 4000), -120.f);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_CAMPFIRE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-160.f, 350.f * ReadHeightMap(m_heightMap, -160.f / 4000, -120.f / 4000) + 20.f, -120.f);
	modelStack.Scale(60, 60, 60);
	RenderMesh(meshList[GEO_FIRE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(10, 10, 10);
	//RenderText(meshList[GEO_TEXT], "Hello World", Color(0, 1, 0));
	RenderText(meshList[GEO_TEXT], "DM2210", Color(0, 1, 1));
	modelStack.PopMatrix();

	// Render the crosshair
	//RenderMeshIn2D(meshList[GEO_CROSSHAIR], false, 10.0f);

	//On screen text
	std::ostringstream ss;
	ss.precision(5);
	ss << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 6);
	
	std::ostringstream ss1;
	ss1.precision(4);
	ss1 << "Light0(" << lights[0].position.x << ", " << lights[0].position.y << ", " << lights[0].position.z << ")";
	RenderTextOnScreen(meshList[GEO_TEXT], ss1.str(), Color(0, 1, 0), 3, 0, 3);

	RenderTextOnScreen(meshList[GEO_TEXT], "Hello Screen", Color(0, 1, 0), 3, 0, 0);

}

void SceneText::Exit()
{
	// Cleanup VBO
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if(meshList[i])
			delete meshList[i];
	}
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}
