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
};

void HW04marinemrApp::setup()
{
	console() << "Test" << endl;

	
	ifstream in("Starbucks_2006.csv");
	vector<Entry> list2;
	string str;
	double x, y;
	char filler;

	// take in file input and save Entries
	while(in.good()){
		Entry* e = new Entry;
		getline(in, str, ',');
		in >> x;
		in >> filler;
		in >> y;

		e->identifier = str;
		e->x = x;
		e->y = y;

		list2.push_back(*e);
	}

	// make array for Entries
	Entry* entrie = new Entry[(int)list2.size()];

	for(int i = 0; i < (int)list2.size(); i++){
		entrie[i] = list2[i];
	}


	console() << list2.size() << endl;

	

	//vpTree = new marinemrStarbucks();
	//console() << "Build() complete" << endl;
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
