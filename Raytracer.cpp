#include "stdafx.h"
#include "Raytracer.h"
#include <SDL.h>
#include "Texture.h"


Raytracer::Raytracer(int width, int height) :
	m_Width(width),
	m_Height(height),
	m_HalfWidth(width / 2.0f),
	m_HalfHeight(height / 2.0f),
	m_Fov((float)(M_PI / 4.0f)),
	m_Near(0.5f),
	m_Far(100.0f),
	m_Angle(0.0f),
	m_Ambient(7,30,35)
{
	SetLookAt(Float3(10, 10, 5.0f), Float3(0, 0, 0));



	SetPerspective(m_Near, m_Far, m_Fov);

	m_NearInv = 1.0f / m_Near;
	m_HalfWidthInv = 1.0f / m_HalfWidth;
	m_HalfHeightInv = 1.0f / m_HalfHeight;
}


Raytracer::~Raytracer()
{
	SDL_DestroyTexture(m_pColorBuffer);
}

void Raytracer::Init(SDL_Renderer* renderer) {
	m_pColorBuffer = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_BGR888,
		SDL_TEXTUREACCESS_STREAMING,
		m_Width, m_Height);
}

void Raytracer::SetLookAt(Float3 origin, Float3 target) {
	m_View.SetAsViewTransform(origin, target);
}

void Raytracer::SetPerspective(float nearPlane, float farPlane, float fov)
{
	m_Near = nearPlane;
	m_Far = farPlane;
	m_Fov = fov;
	m_AR = m_Width * 1.0f / m_Height;
	m_HNear = (float)(m_Near * tan(m_Fov));
	m_WNear = m_HNear * m_AR;

	m_XR = m_WNear / m_Width;
	m_YR = m_HNear / m_Height;
}

void Raytracer::Tick(double deltaTime) {
	Ray ray;
	ray.Start = Float3(0, 0, 0);
	Float3 ls;

	Matrix44 vI;
	m_View.ViewInverse(vI);


	Uint32* pPixels;
	int pitch;
	SDL_LockTexture(m_pColorBuffer, NULL, (void**)&pPixels, &pitch);
	// set pixel at 200,200 to green
	for (int x = 0; x < m_Width; ++x)
	{
		for (int y = 0; y < m_Height; ++y) {
			ray.Dir.Set(x*m_XR - m_WNear / 2, y*m_YR - m_HNear / 2, m_Near);
			Float3 rs, rd; // rs: ray start, rd: ray direction
			vI.TransformPoint(ray.Start, rs);
			vI.TransformVector(ray.Dir, rd);
			float minT = FLT_MAX;
			Mesh* currentMesh = nullptr;
			for (auto it = m_Meshes.begin(); it != m_Meshes.end(); ++it)
			{
				Mesh* mesh = *it;
				for (int i = 0; i < mesh->GetNrOfTriangles(); ++i) {
					Triangle tri = mesh->GetTriangle(i);
					Int3 indices = mesh->GetTriangleIndices(i);
					Float3 meshLambdas;
					float currentT=0;
					Float3 I;
					if (tri.DotWithNorm(rd) > 0 &&
						tri.Intersect2(rs, rd, meshLambdas, currentT, I) )
					{
						if (currentT < minT) {
							minT = currentT;
							currentMesh = mesh;
						}
						break;
					}
				}
			}
			if (currentMesh != nullptr) {
				pPixels[x + y*m_Width] = 0xff0000;
			}
			else {
				pPixels[x + y*m_Width] = 0x00000ff;
			}
		}
	}
	
	SDL_UnlockTexture(m_pColorBuffer);
}
