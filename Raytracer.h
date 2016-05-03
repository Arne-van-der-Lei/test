#pragma once
#include "Mesh.h"
#include "Matrix44.h"
#include "Triangle.h"
#include <SDL.h>

class Raytracer
{
public:
	Raytracer(int width, int height);
	virtual ~Raytracer();

	void Init(SDL_Renderer* renderer);

	SDL_Texture* GetTexture() {
		return m_pColorBuffer;
	}

	void AddMesh(Mesh* mesh) {
		m_Meshes.push_back(mesh);
	}

	int GetWidth() {
		return m_Width;
	}

	int GetHeight() {
		return m_Height;
	}

	void SetLookAt(Float3 origin, Float3 target);
	void SetPerspective(float near, float far, float fov);
	void Tick(double deltaTime);
private:
	int m_Width, m_Height;
	float m_HalfWidth, m_HalfHeight;
	float m_HalfWidthInv, m_HalfHeightInv;

	Matrix44 m_View;

	float m_Angle;
	float m_Fov;
	float m_Near;
	float m_NearInv;
	float m_Far;

	float m_AR;
	float m_WNear;
	float m_HNear;

	float m_XR;
	float m_YR;

	std::vector<Mesh*> m_Meshes;
	SDL_Texture* m_pColorBuffer;
	Int3 m_Ambient;
};

