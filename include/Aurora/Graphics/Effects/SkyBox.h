#ifndef SKYBOX_H_
#define SKYBOX_H_

#include <Aurora/Graphics/Vertex.h>
#include <Aurora/Graphics/RenderManager.h>
#include <pspmath.h>
#include <Aurora/Math/Frustum.h>

namespace Aurora
{
	namespace Graphics
	{
		class SkyBox
		{
		public:
			SkyBox();
			~SkyBox();

            void BuildVertexObject();
			void Update();
			void Render(Vector3 color);

		private:

			SimplePSPVertex2 *skyBoxVertices;

			float size;
		};
	}
}

#endif

