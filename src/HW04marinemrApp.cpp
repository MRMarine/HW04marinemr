#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04marinemrApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void HW04marinemrApp::setup()
{
}

void HW04marinemrApp::mouseDown( MouseEvent event )
{
}

void HW04marinemrApp::update()
{
}

void HW04marinemrApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( HW04marinemrApp, RendererGl )
