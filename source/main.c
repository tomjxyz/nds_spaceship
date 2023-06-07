
#include <nds.h>
#include <stdio.h>
//#include <time.h>
#include <NEMain.h>

#include "helper.h"
#include "ship.h"
#include "asteroid.h"

int held;
Ship player = {0,0,0,0, 0};
NE_Camera *camera;

void Draw3DScene(void)
{
	NE_CameraUse(camera);

	drawAsteroid();
	drawShip();
}

int main() {	
	irqEnable(IRQ_HBLANK);
	irqSet(IRQ_VBLANK, NE_VBLFunc);
	irqSet(IRQ_HBLANK, NE_HBLFunc);

	// Init Nitro Engine 3D rendering in one screen.
	NE_Init3D();
	// libnds uses VRAM_C for the text console, reserve A and B only
	NE_TextureSystemReset(0, 0, NE_VRAM_AB);
	// Init console in non-3D screen
	consoleDemoInit();

	camera = NE_CameraCreate();
	// NE_CameraMove(camera, -2, 2, 0);
	// NE_CameraRotateAxis(camera, 90, 0, 1, 0);
	// NE_CameraRotateAxis(camera, 16, 0, 0, 1);
	NE_CameraSet(camera,
	1.5, 0.45, 0,
	0, 0, 0,
	0, 1, 0);

	// Set up the white light
	NE_LightSet(0,NE_White,1,1,0);

	//Enable shading
	NE_ShadingEnable(true);

	loadShip();
	loadAsteroid();

	printf("3D Ship and Asteroid Game\n");

    srand(time(NULL));

	//main loop
	while (1) {
		held = keysHeld();
		//process input
		scanKeys();
		if(held & KEY_START) break;
		if (keysDown() & KEY_A)
			printf("\nROT: %f", player.rotX);

		updateShip(held, &player);

		updateAsteroid(held);

		// Draw scene
		NE_Process(Draw3DScene);
		NE_WaitForVBL(0);
	}

	return 0;
}