#include <NEMain.h>
#include <nds.h>
#include <stdio.h>

#include "helper.h"
#include "asteroid.h"
#include "asteroid_bin.h"
#include "asteroid_tex_bin.h"

NE_Material *a_mat;

void initAA(NE_Model *a){
    NE_ModelSetCoord(a, -(rand() % 5)-10, -(rand() % 5)+2.5, (rand() % 10)-5);
    NE_ModelSetRot(a, rand() % 511, rand() % 511, rand() % 511);
}

void loadAsteroid()
{
    a_mat = NE_MaterialCreate();
    NE_MaterialTexLoad(a_mat, GL_RGB256, 128, 128, TEXGEN_TEXCOORD, (void *)asteroid_tex_bin);
    for (int i = 0; i < 10; i++)
    {
        afield[i] = NE_ModelCreate(NE_Static);

        NE_ModelLoadStaticMesh(afield[i], (void *)asteroid_bin);
        NE_ModelSetMaterial(afield[i], a_mat);
        initAA(afield[i]);
    }
}

void drawAsteroid() {
    for (int i = 0; i < 10; i++) {
        NE_PolyFormat(31, 0, NE_LIGHT_ALL, NE_CULL_NONE, 0);
        NE_ModelDraw(afield[i]);
    }
}

void updateAsteroid(int keyState)
{
    for (int i = 0; i < 10; i++) {
        if ((float)afield[i]->x/4096 > -7) {
            if (keyState & KEY_UP)
                NE_ModelTranslate(afield[i], 0, SHIP_SPEED, 0); 
            if (keyState & KEY_DOWN)
                NE_ModelTranslate(afield[i], 0, -SHIP_SPEED, 0); 

            if (keyState & KEY_LEFT)
                NE_ModelTranslate(afield[i], 0, 0, SHIP_SPEED); 
            if (keyState & KEY_RIGHT)
                NE_ModelTranslate(afield[i], 0, 0, -SHIP_SPEED); 
    
        }
        NE_ModelTranslate(afield[i], ASTEROID_SPEED, 0, 0);

        float ty = afield[i]->y > 0 ? -CLOSE_IN_SPEED : CLOSE_IN_SPEED;
        float tz = afield[i]->z > 0 ? -CLOSE_IN_SPEED : CLOSE_IN_SPEED;
        NE_ModelTranslate(afield[i], 0, ty, tz);
        NE_ModelRotate(afield[i], 0, rand() % 5, 0);

        if ((float)afield[i]->x/4096 > 1){
            initAA(afield[i]);
        }
    }
}