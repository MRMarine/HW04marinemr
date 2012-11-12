#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "marinemrStarbucks.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04marinemrApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
  private:
	marinemrStarbucks* vpTree;
	bool done;
	void drawMap();
	Census* census2;
	int censusSize;
	int height_, width_;
};



void HW04marinemrApp::setup()
{
	done = false;
	height_ = 800;
	width_ = 2.48 * height_;

	console() << "Begin constructor" << endl;

	vpTree = new marinemrStarbucks();
	console() << "Build() complete" << endl;
	console() << "Tree size = " << vpTree->size << endl;

	console() << (vpTree->getNearest(0.039313081, 0.91628776))->identifier << endl; // Yelm Washington 98597 Safeway-Yelm #1619,0.039313081,0.91628776
	console() << "GetNearest() complete!" << endl;

	////////////
	// Census //
	////////////
	ifstream in("Census_2010.csv");
	vector<Census> census;
	int state, county, track, block, population;
	double x, y;
	char filler;

	// take in file input and save Entries
	while(in.good()){
		Census* c = new Census;
		//getline(in, str, ',');
		in >> state;
		in >> filler;
		in >> county;
		in >> filler;
		in >> track;
		in >> filler;
		in >> block;
		in >> filler;
		in >> population;
		in >> filler;
		in >> x;
		in >> filler;
		in >> y;

		c->state = state;
		c->county = county;
		c->track = track;
		c->block = block;
		c->population = population;

		census.push_back(*c);
	}

	// make array for Census
	censusSize = (int)census.size();
	census2 = new Census[censusSize];

	for(int i = 0; i < censusSize; i++){
		census2[i] = census[i];
	}

	console() << "Census size = " << census.size() << endl;
}

void HW04marinemrApp::mouseDown( MouseEvent event )
{
}

void HW04marinemrApp::update()
{
}

void HW04marinemrApp::draw()
{
	if(!done){
		// clear out the window with black
		gl::clear( Color( 0, 0, 0 ) );

		drawMap();
		//gl::color(255,255,255);
		//gl::drawSolidCircle(Vec2f(50,50),10);

		done = true;
		console() << "Draw" << endl;
		/*try{
			drawEntry(vpTree->head);
		}
		catch(Exception e){
			console() << "Draw Error" << endl;
		}
		*/
		done = true;
	}
}



void HW04marinemrApp::drawMap(){

	for(int i = 0; i < censusSize; i++){

		if(census2[i].state % 3 == 0){
			gl::color(255,0,0);
		}
		else if(census2[i].state % 3 == 1){
			gl::color(0,255,0);
		}
		else{
			gl::color(0,0,255);
		}

		
		gl::drawSolidCircle(Vec2f((float)census2[i].x * width_,(float)census2[i].y * height_),10);
	}
}

CINDER_APP_BASIC( HW04marinemrApp, RendererGl )
