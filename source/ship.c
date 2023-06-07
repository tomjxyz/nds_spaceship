#include <NEMain.h>
#include <nds.h>
#include <stdio.h>

#include "ship.h"
#include "helper.h"
#include "ship_bin.h"
#include "ship_tex_bin.h"
#include "palette_bin.h"

NE_Material *mat;
NE_Model *ship;

void loadShip()
{
    ship = NE_ModelCreate(NE_Static);
    mat = NE_MaterialCreate();
    pal = NE_PaletteCreate();

    NE_MaterialTexLoad(mat, GL_RGB256, 128, 128, TEXGEN_TEXCOORD, (void *)ship_tex_bin);
    NE_PaletteLoad(pal, (void *)palette_bin, 256, GL_RGB256);
    NE_ModelLoadStaticMesh(ship, (void *)ship_bin);
    NE_PaletteUse(pal);
    NE_ModelSetMaterial(ship, mat);
}

void drawShip(){
    NE_PolyFormat(31, 0, NE_LIGHT_ALL, NE_CULL_NONE, 0);
    NE_ModelDraw(ship);
}

void updateShip(int kState, Ship *s)
{
    if (kState & KEY_LEFT)
        s->rotX -= 5;
    if (kState & KEY_RIGHT)
        s->rotX += 5;
    
    if (kState & KEY_UP)
        s->rotZ += 3;
    if (kState & KEY_DOWN)
        s->rotZ -= 3;


    if (kState == 0)
    {
        s->rotX = 0;
        s->rotZ = 0;
    }

    s->rotX = clamp(s->rotX, -30, 30);
    s->rotZ = clamp(s->rotZ, -20, 30);

   NE_ModelSetCoord(ship, 0, -0.5, 0);
   NE_ModelSetRot(ship, s->rotX, s->rotX, s->rotZ);
}