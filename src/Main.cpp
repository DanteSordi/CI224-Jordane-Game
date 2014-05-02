#define GLEW_STATIC // Easier debugging
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory> 

#include "GameAsset.h"
#include "Md2Asset.h"
#include "TriangularPyramidAsset.h"
#include "CubeAsset.h"

#include "BallisticInterpolator.h"
#include "Camera.h"


using namespace std;

#define RUN_GRAPHICS_DISPLAY 0x00;

string filename = "data/ogre.md2";
vector<shared_ptr<GameAsset> > assets;

bool isWKeyPressed = false;
bool isSKeyPressed = false;
bool isAKeyPressed = false;
bool isDKeyPressed = false;

bool horrible_global_go = false;

/*
 * SDL timers run in separate threads.  In the timer thread
 * push an event onto the event queue.  This event signifies
 * to call display() from the thread in which the OpenGL 
 * context was created.
 */
Uint32 display(Uint32 interval, void *param) {
	SDL_Event event;
	event.type = SDL_USEREVENT;
	event.user.code = RUN_GRAPHICS_DISPLAY;
	event.user.data1 = 0;
	event.user.data2 = 0;
	SDL_PushEvent(&event);
	return interval;
}

void display() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);




  // This O(n + n^2 + n) sequence of loops is written for clarity,
  // not efficiency
  for(auto it : assets) {
    it->update();
  }
////////////////////////////////////////////////////////////////////////////////////////////////
  //for(auto i : assets) {
    //for(auto j : assets) {
     // if((i != j) && i->collidesWith(*j)) {
	//cout << "We have a collision"  << endl;      //the collission
     // }
   // }
 // }
/////////////////////////////////////////////////////////////////////////////////////////////////
  for(auto it : assets) {
    it->draw();
  }
  
  // Don't forget to swap the buffers
  SDL_GL_SwapBuffers();
}



int main(int argc, char ** argv) {
	SDL_Surface * surf;
	Uint32 width = 640;
	Uint32 height = 480;
	Uint32 colour_depth = 16; // in bits
	Uint32 delay = 1000/60; // in milliseconds
      
	// Initialise SDL - when using C/C++ it's common to have to
	// initialise libraries by calling a function within them.
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER)<0) {
			cout << "Failed to initialise SDL: " << SDL_GetError() << endl;
			SDL_Quit();
	}

	// When we close a window quit the SDL application
	atexit(SDL_Quit);

	// Create a new window with an OpenGL surface
	if (!(surf = SDL_SetVideoMode(width, height, colour_depth, SDL_OPENGL))) {
			cout << "Failed to initialise video mode: " << SDL_GetError() << endl;
			SDL_Quit();
	}

	// Initialise GLEW - an easy way to ensure OpenGl 2.0+
	// The *must* be done after we have set the video mode - otherwise we have no OpenGL context.
	glewInit();
	if (!glewIsSupported("GL_VERSION_2_0")) {
	  cerr<< "OpenGL 2.0 not available" << endl;
	  return 1;
	}


	shared_ptr<CubeAsset> p = shared_ptr<CubeAsset> (new CubeAsset(0, 1, 7));  //right  up  left
	shared_ptr<IInterpolator> i = shared_ptr<IInterpolator>(new BallisticInterpolator(Vector3(0.0, 0.0, 0.0), 60));
	p->setInterpolator(i);
	assets.push_back(p);

       
	assets.push_back(shared_ptr<TriangularPyramidAsset> (new TriangularPyramidAsset(-1, -3, 0)));
        assets.push_back(shared_ptr<TriangularPyramidAsset> (new TriangularPyramidAsset(6, -3, 0)));

      assets.push_back(shared_ptr<TriangularPyramidAsset> (new TriangularPyramidAsset(-1, -3, 12)));
        assets.push_back(shared_ptr<TriangularPyramidAsset> (new TriangularPyramidAsset(6, -3, 12)));
//FLOOR

for (int i=0; i<=12;i++){
assets.push_back(shared_ptr<CubeAsset> (new CubeAsset(-1, -4, i)));} 

for (int i=0; i<=12;i++){
assets.push_back(shared_ptr<CubeAsset> (new CubeAsset(0, -4, i)));} 

for (int i=0; i<=12;i++)
{assets.push_back(shared_ptr<CubeAsset> (new CubeAsset(1, -4, i)));}

for (int i=0; i<=12;i++)
{assets.push_back(shared_ptr<CubeAsset> (new CubeAsset(2, -4, i)));}       

for (int i=0; i<=12;i++)
{assets.push_back(shared_ptr<CubeAsset> (new CubeAsset(3, -4, i)));}        

for (int i=0; i<=12;i++)
{assets.push_back(shared_ptr<CubeAsset> (new CubeAsset(4, -4, i)));}

for (int i=0; i<=12;i++)
{assets.push_back(shared_ptr<CubeAsset> (new CubeAsset(5, -4, i)));}

for (int i=0; i<=12;i++)
{assets.push_back(shared_ptr<CubeAsset> (new CubeAsset(6, -4, i)));}

///////////////////Arc/////////////////////////////////////////////

for (int i=0; i<=3;i++){   //left
assets.push_back(shared_ptr<CubeAsset> (new CubeAsset(0, i, 1)));} 
//first number left or right    // second number up or dawn    /third  number  diper

for (int i=0; i<=4;i++){
assets.push_back(shared_ptr<CubeAsset> (new CubeAsset(i, 3, 1)));} //top

for (int i=0; i<=3;i++){ //right
assets.push_back(shared_ptr<CubeAsset> (new CubeAsset(5, i, 1)));} 

for (int i=0; i<=5;i++){
assets.push_back(shared_ptr<CubeAsset> (new CubeAsset(i, -1, 1)));} //dawn

///////////////////////////ARC number 2

for (int i=0; i<=3;i++){   //left
assets.push_back(shared_ptr<CubeAsset> (new CubeAsset(0, i, 10)));} 

for (int i=0; i<=4;i++){
assets.push_back(shared_ptr<CubeAsset> (new CubeAsset(i, 3, 10)));} //top

for (int i=0; i<=3;i++){ //right
assets.push_back(shared_ptr<CubeAsset> (new CubeAsset(5, i, 10)));} 

for (int i=0; i<=5;i++){
assets.push_back(shared_ptr<CubeAsset> (new CubeAsset(i, -1, 10)));} //dawn


 //assets.push_back(shared_ptr<CubeAsset> (new CubeAsset(0, 0, 5)));


	//assets.push_back(shared_ptr<Md2Asset> (new Md2Asset(filename)));

	 //Set the camera; control where the camera will be when the player will start the game
	Camera::getInstance().lookAt(Point3(0.0, 0.0, 10.0), Point3(0.0, 0.0, -1.0), Vector3(0.0, 7.0, 0.0));
	  Camera::getInstance().setCamera(Camera::getInstance().getCameraM() * Matrix4::translation(Vector3(-10.0, 0.0, 20.0)));
		display();
        Camera::getInstance().setCamera(Matrix4::identity());

	// Call the function "display" every delay milliseconds
	SDL_AddTimer(delay, display, NULL);

	// Add the main event loop
	SDL_Event event;

	while (SDL_WaitEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
			  SDL_Quit();
			  break;
			case SDL_USEREVENT:
			  display();
			  break;
			//case SDL_KEYUP:
			 // Camera::getInstance().setCamera(Matrix4::identity());
			 // break;
			case SDL_KEYDOWN:
			 Matrix4 camera = Camera::getInstance().getCameraM();
			 
                             switch(event.key.keysym.sym){
			  
                          
//////////////////////////////// Keyboard Movment //////////////////////////////////////////////////

//if (isWKeyPressed)
//{Camera::getInstance().setCamera(camera * Matrix4::translation(Vector3(0.0, 0.0, -1.0)) );}

//else if (SDLK_s ==true)
//{Camera::getInstance().setCamera(camera * Matrix4::translation(Vector3(0.0, 0.0, 1.0)) );}

//else if (SDLK_a ==true)
//{Camera::getInstance().setCamera(camera * Matrix4::translation(Vector3(1.0, 0.0, 0.0)) );}

//else if (SDLK_d ==true)
//{Camera::getInstance().setCamera(camera * Matrix4::translation(Vector3(-1.0, 0.0, 0.0)) );}      






                      case SDLK_a:  //going left
                             isAKeyPressed = true; 
                            Camera::getInstance().setCamera(camera * Matrix4::translation(Vector3(1.0, 0.0, 0.0)) );
		            break;
		       case SDLK_d: //going right
                            isDKeyPressed = true; 
                            Camera::getInstance().setCamera(camera * Matrix4::translation(Vector3(-1.0, 0.0, 0.0)) );
                           break;
                       case SDLK_w: 
			  isWKeyPressed = true; 
                          Camera::getInstance().setCamera(camera * Matrix4::translation(Vector3(0.0, 0.0, -1.0)) );
                         break;
                        case SDLK_s:  //going back
                          isSKeyPressed = true; 
			    Camera::getInstance().setCamera(camera * Matrix4::translation(Vector3(0.0, 0.0, 1.0)) );
                           break;




                          case SDLK_LEFT:
                           Camera::getInstance().setCamera(camera * Matrix4::rotationY(5.0/180.0) );
			   break;
                          case SDLK_RIGHT:
                           Camera::getInstance().setCamera(camera * Matrix4::rotationY(-5.0/180.0) );
                            
			   break;



			  case SDLK_SPACE:   //JUMP
			    Camera::getInstance().setCamera(camera * Matrix4::translation(Vector3(0.0, -1.0, 0.0)) );
			    break;
                         
                            case SDLK_b:   //down
			    Camera::getInstance().setCamera(camera * Matrix4::translation(Vector3(0.0, 1.0, 0.0)) );
			    break;

                         
                          case SDLK_g:
			    horrible_global_go = true;
			  default:
			    break;
			  }
			  break;
			}
	}
}
