#include <NEMain.h>

#define ASTEROID_SPEED 0.1
#define CLOSE_IN_SPEED 0.005
#define SHIP_SPEED 0.03

typedef struct {
  float x;
  float y;
  float z;

  float rotation;
} Asteroid;

static NE_Model* afield[10];

void loadAsteroid();
void drawAsteroid();
void updateAsteroid(int keyState);
void initAA(NE_Model *a);