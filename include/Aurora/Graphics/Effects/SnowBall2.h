#ifndef SNOWBALL2_H_
#define SNOWBALL2_H_

#include <Aurora/Math/Vector3.h>
#include <Aurora/Graphics/Vertex.h>
#include <pspmath.h>
#include <LameCraft/CraftWorld2.h>
#include <math.h>
#include <psptypes.h>

namespace Aurora
{
	namespace Graphics
	{
		class SnowBall2
		{
		public:
			SnowBall2(float pos2x, float pos2y, float pos2z);
			~SnowBall2();

			void SetTexture(int texture);
			void SetVeloc(float verAngle, float horAngle);
			void Update(CraftWorld* crtf);
			bool CheckCollision(CraftWorld* crtf);

			void Render();
			float pos_x;
			float pos_y;
			float pos_z;
			ScePspFVector3 veloc;

		private:

			CraftPSPVertex *ballVertices;
			int textureNumber;
			float snowHScale;
			float snowVScale;
			float startImpulse;
			float speed;
		};
	}
}

#endif

