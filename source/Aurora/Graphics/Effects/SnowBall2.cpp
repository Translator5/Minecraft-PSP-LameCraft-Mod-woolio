#include <Aurora/Graphics/Effects/SnowBall2.h>
#include <Aurora/Graphics/TextureManager.h>

#define PI 3.1415926535897f
#define DEG_TO_RAD (PI / 180.0f)

namespace Aurora
{
	namespace Graphics
	{
		SnowBall2::SnowBall2(float pos2x, float pos2y, float pos2z)
		{
			snowHScale = 0.2f;
			snowVScale = 0.2f;

			pos_x = pos2x;
			pos_y = pos2y;
			pos_z = pos2z;

			ballVertices = (CraftPSPVertex*)memalign(16,4 * sizeof(CraftPSPVertex));
			speed = 0.5;
			startImpulse = 1.0f;
		}

		SnowBall2::~SnowBall2()
		{
			free(ballVertices);
		}

		void SnowBall2::SetTexture(int texture)
		{
			textureNumber = texture;
		}

		void SnowBall2::SetVeloc(float verAngle, float horAngle)
		{
		    float del;
		    if (verAngle > 0)
            {
                del = (PI / (float)2 - verAngle);

            }
            else
            {
                del = (PI / (float)2 + verAngle);
            }
			veloc.z = (sinf(horAngle) * speed) * del;
			veloc.x = (cosf(horAngle) * speed) * del;
			veloc.y = (sinf(verAngle) * speed);
			startImpulse = 0;
		}

		void  SnowBall2::Update(CraftWorld* crtf)
		{
			ScePspFMatrix4 t;
			sceGumMatrixMode(GU_VIEW);
			sceGumStoreMatrix(&t);
			sceGumMatrixMode(GU_MODEL);

            ScePspFVector3 up, right;

			right.x = t.x.x * snowHScale * 1;
			right.y = t.y.x * snowHScale * 1;
			right.z = t.z.x * snowHScale * 1;
			up.x = t.x.y * snowVScale * 1;
			up.y = t.y.y * snowVScale * 1;
			up.z = t.z.y * snowVScale * 1;

			//float textureScale = 1.0f / stepScal
            if (startImpulse > -0.1)
            {
                startImpulse -= 0.0004;
            }

			if(veloc.y > -1)
            {
                veloc.y += startImpulse;
            }
			int i = 0;

			pos_x += veloc.x;
			pos_z += veloc.z;
			pos_y += veloc.y;

			ballVertices[i].x = pos_x - right.x + up.x;// * stepScale;
			ballVertices[i].y = pos_y - right.y + up.y;// * stepScale;
			ballVertices[i].z = pos_z - right.z + up.z;// * stepScale;
            ballVertices[i].u = 0.f;// * textureScale;
			ballVertices[i].v = 0.f;// * textureScale;
			ballVertices[i].color = GU_COLOR(crtf->lightColor.x,crtf->lightColor.y,crtf->lightColor.z,1);
			i++;

			// (x, y - 1, z)
			ballVertices[i].x = pos_x - right.x - up.x;// * stepScale;
			ballVertices[i].y = pos_y - right.y - up.y;// * stepScale;
			ballVertices[i].z = pos_z - right.z - up.z;// * stepScale;
			ballVertices[i].u = 0.f;// * textureScale;
			ballVertices[i].v = 1.f;// * textureScale;
			ballVertices[i].color = GU_COLOR(crtf->lightColor.x,crtf->lightColor.y,crtf->lightColor.z,1);
			i++;
//GU_COLOR(crtf->lightColor.x,crtf->lightColor.y,crtf->lightColor.z,1);
			// (x + 1, y, z)
			ballVertices[i].x = pos_x + right.x + up.x;// * stepScale;
			ballVertices[i].y = pos_y + right.y + up.y;// * stepScale;
			ballVertices[i].z = pos_z + right.z + up.z;// * stepScale;
			ballVertices[i].u = 1.f;// * textureScale;
			ballVertices[i].v = 0.f;// * textureScale;
			ballVertices[i].color = GU_COLOR(crtf->lightColor.x,crtf->lightColor.y,crtf->lightColor.z,1);
			i++;

			// (x + 1, y - 1, z)
			ballVertices[i].x = pos_x + right.x - up.x;// * stepScale;
			ballVertices[i].y = pos_y + right.y - up.y;//* stepScale;
			ballVertices[i].z = pos_z + right.z - up.z;// * stepScale;
			ballVertices[i].u = 1.f;// * textureScale;
			ballVertices[i].v = 1.f;// * textureScale;
			ballVertices[i].color = GU_COLOR(crtf->lightColor.x,crtf->lightColor.y,crtf->lightColor.z,1);


			sceKernelDcacheWritebackInvalidateRange(ballVertices,4 * sizeof(CraftPSPVertex));
		}

		bool SnowBall2::CheckCollision(CraftWorld* crtf)
		{
            if (crtf->GetBlock(pos_x,pos_y,pos_z) != 0)
            {
                return 1;
            }
            else
            {
                return 0;
            }
		}

		void SnowBall2::Render()
		{

			//sceGuColor(0xFFFFFFFF);
			sceGuEnable(GU_TEXTURE_2D);
			sceGuEnable(GU_BLEND);

			/*Image* image = TextureManager::Instance()->Images[textureNumber];

			sceGuTexMode(image->ColorMode,0,0,image->Swizzle);
			sceGuTexFunc( GU_TFX_MODULATE, GU_TCC_RGBA);
			sceGuTexFilter(GU_LINEAR, GU_LINEAR);
			sceGuTexScale(1.0f, 1.0f);                // No scaling
			sceGuTexOffset(0.0f, 0.0f);
			sceGuTexImage(0,image->power2Width,image->power2Height,image->power2Width,image->ImageData);*/

			sceGumDrawArray(GU_TRIANGLE_STRIP, GU_TEXTURE_32BITF |GU_COLOR_8888| GU_VERTEX_32BITF | GU_TRANSFORM_3D, 4, 0, ballVertices);

            sceGuDisable(GU_BLEND);
			sceGuDisable(GU_TEXTURE_2D);
		}
	}
}

