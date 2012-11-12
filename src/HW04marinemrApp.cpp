#pragma once

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "marinemrStarbucks.h"
#include "cinder/gl/TextureFont.h"

using namespace ci;
using namespace ci::app;
using namespace std;

// fulfills:
//	A (20 pts) // Shows shape of the US and separates states using census data
//	B (10 pts) // Draws line to nearest Starbucks
//	C (20 pts) // drawLines()
//	F (30 pts) // by concentration of population
//	H (???) // Display the identifier of the nearest Starbucks in the bottom of the screen.


class HW04marinemrApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void keyDown(KeyEvent event);
	void update();
	void draw();
	void prepareSettings(Settings*);
  private:
	marinemrStarbucks* vpTree;
	bool done;
	void drawMap();
	void drawLines();
	Census* census2;
	int censusSize;
	static const int height_ = 640;
	static const int width_ = 1024;
	
	// controls whether or not lines are drawn to nearest starbucks
	bool drawLine;
};

void HW04marinemrApp::prepareSettings(Settings* settings){
	settings->setWindowSize(width_, height_);
	settings->setResizable(false);
}



void HW04marinemrApp::setup()
{
	done = false;
	drawLine = true;

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

		c->x = x;
		c->y = 1-y;

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
	// redraw to clear lines and text
	// clear out the window
	gl::clear( Color( 0, 0, 0 ) );

	drawMap();

	if(drawLine){
		drawLines();
	}
	
	drawEntry(vpTree->head);

	// find nearest Entry to points
	Entry* entry = vpTree->getNearest(event.getX() / (double)width_, event.getY() / (double)height_);

	// draw lines
	gl::color(1,1,1);
	gl::drawLine(Vec2f(event.getX(), event.getY()), Vec2f(entry->x * width_, entry->y * height_)); // used 1-entry->y earlier

	// draw text
	// I showed this to another student because she was curios about how this was done
	Font font = Font("Arial", 36);
	gl::TextureFontRef textureFont = gl::TextureFont::create(font);
	textureFont->drawStringWrapped(entry->identifier, Rectf(15,height_ - 75,width_,height_));
}

void HW04marinemrApp::keyDown(KeyEvent event){
	// swap drawLine's value
	drawLine = !drawLine;

	// redraw to clear lines
	// clear out the window
	gl::clear( Color( 0, 0, 0 ) );

	drawMap();

	if(drawLine){
		drawLines();
	}
	
	drawEntry(vpTree->head);
}

void HW04marinemrApp::update()
{
}

// draw the program
void HW04marinemrApp::draw()
{
	// Don't do this when you don't need to.  It takes forever as it is
	if(!done){
		// clear out the window with black
		gl::clear( Color( 0, 0, 0 ) );

		// draw Census_2010
		drawMap();

		done = true;
		console() << "Draw" << endl;

		// drawLines fulfills option C (20 points)
		// draw lines to nearest Starbucks
		if(drawLine){
			drawLines();
		}

		// Draw Starbucks locations
		drawEntry(vpTree->head);
	}
}


void HW04marinemrApp::drawLines(){
	for(int i = 0; i < censusSize; i++){

		double pop = (0.1 + ((double)census2[i].population) / 2452.0);
		double pop2 = 0;

		if(pop > 1.0){
			pop2 = pop-1;
			if(pop2 > 1.0){
				pop2 = 1.0;
			}
			pop = 1.0;
		}

		if(census2[i].state % 6 == 0){
			gl::color(pop,pop2,pop2);
		}
		else if(census2[i].state % 6 == 1){
			gl::color(pop2,pop,pop2);
		}
		else if(census2[i].state % 6 == 2){
			gl::color(pop2,pop2,pop);
		}
		else if(census2[i].state % 6 == 3){
			gl::color(pop,pop,pop2);
		}
		else if(census2[i].state % 6 == 4){
			gl::color(pop2,pop,pop);
		}
		else if(census2[i].state % 6 == 5){
			gl::color(pop2,pop*(150.0/255.0),pop*(250.0/255.0));
		}
		else{
			gl::color(pop,pop2,pop);
		}

		Entry* entry = vpTree->getNearest(census2[i].x, census2[i].y);

		gl::drawLine(Vec2f(census2[i].x * width_, census2[i].y * height_), Vec2f(entry->x * width_, entry->y * height_));
	}
}

void HW04marinemrApp::drawMap(){

	for(int i = 0; i < censusSize; i++){

		double pop = (0.1 + ((double)census2[i].population) / 2452.0);
		double pop2 = 0;

		if(pop > 1.0){
			pop2 = pop-1;
			if(pop2 > 1.0){
				pop2 = 1.0;
			}
			pop = 1.0;
		}

		if(census2[i].state % 6 == 0){
			gl::color(pop,pop2,pop2);
		}
		else if(census2[i].state % 6 == 1){
			gl::color(pop2,pop,pop2);
		}
		else if(census2[i].state % 6 == 2){
			gl::color(pop2,pop2,pop);
		}
		else if(census2[i].state % 6 == 3){
			gl::color(pop,pop,pop2);
		}
		else if(census2[i].state % 6 == 4){
			gl::color(pop2,pop,pop);
		}
		else if(census2[i].state % 6 == 5){
			gl::color(pop2,pop*(150.0/255.0),pop*(250.0/255.0));
		}
		else{
			gl::color(pop,pop2,pop);
		}
		
		gl::drawSolidCircle(Vec2f((float)census2[i].x * width_,(float)census2[i].y * height_),1);
	}
}

CINDER_APP_BASIC( HW04marinemrApp, RendererGl )
