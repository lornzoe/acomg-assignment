#ifndef SCENE_SHADOW_H
#define SCENE_SHADOW_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "CameraAss.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "SpriteAnimation.h"
#include "ParticleObject.h"
#include "GeoType.h"
#include <vector>

#define LIGHTCOUNT 2
#define MAX_PARTICLE 1000
#define NUMLIGHTCUTOFF 7 + LIGHTCOUNT * 12

class SceneShadow : public Scene
{
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,

		U_LIGHT0_TYPE, // 7
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT, // 17 

		U_LIGHT1_TYPE,
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_ENABLED,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,

		U_NUMLIGHTS = NUMLIGHTCUTOFF,

		U_COLOR_TEXTURE_ENABLED,
		// colortextureenabled lasts for 56 to (56 + 7)
		U_COLOR_TEXTURE = U_COLOR_TEXTURE_ENABLED + MAX_TEXTURES,
		// colortexture takes up 64 to (64 + 7)

		U_COLOR = U_COLOR_TEXTURE + MAX_TEXTURES,

		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		U_FOG_COLOR,
		U_FOG_START,
		U_FOG_END,
		U_FOG_DENSITY,
		U_FOG_TYPE,
		U_FOG_ENABLED,

		U_TOTAL,
	};

public:
	SceneShadow();
	~SceneShadow();

	virtual void Init();
	void InitParameters();
	void InitMeshList();

	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void UpdateParticles(double dt);
	ParticleObject * GetParticle(void);

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshIn2D(Mesh *mesh, bool enableLight, float size = 1.0f, float x = 0.0f, float y = 0.0f);
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderGround();
	void RenderSkybox();
	void RenderParticle(ParticleObject*);
	//void RenderFire();

	void RenderSkyPlane();
	void RenderTerrain();

private:
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	CameraAssignment camera;

	float rotateAngle;

	MS modelStack;
	MS viewStack;
	MS projectionStack;

	Light lights[LIGHTCOUNT];

	bool bLightEnabled;
	float watertranslate;

	std::vector<unsigned char> m_heightMap;

	float fps;
	SpriteAnimation * fireanim;

	Color fogColor;
	float fogDensity;
	float fogStart, fogEnd;

	std::vector<GameObject *> m_goList;
	std::vector<ParticleObject *> m_poList;
	int i_particleCount;
};

#endif //scene_shadow