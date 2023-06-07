
typedef struct{
	float x;
	float y;
	float z;

  float rotX;
  float rotZ;
} Ship;

void loadShip();
void drawShip();
void updateShip(int kState, Ship *s);