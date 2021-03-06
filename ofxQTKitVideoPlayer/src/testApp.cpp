/*
 *  ofxQTKitMoviePlayer example
 *
 * Created by James George, http://www.jamesgeorge.org
 * over a long period of time for a few different projects in collaboration with
 * FlightPhase http://www.flightphase.com 
 * and the rockwell group lab http://lab.rockwellgroup.com
 *
 **********************************************************
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * ----------------------
 * 
 * ofxQTKitVideoPlayer provides QTKit/CoreVideo accelerated movie playback
 * for openFrameworks on OS X
 * 
 * This class replaces almost all of the functionality of ofVideoPlayer on OS X
 * and uses the modern QTKit and CoreVideo libraries for playback
 *
 * Special Thanks to Marek Bereza for his initial QTKitVideoTexture
 * http://www.mrkbrz.com/
 *
 * Thanks to Anton Marini for help wrangling buffer contexts
 * http://vade.info/ 
 */

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetVerticalSync(true);
	ofEnableAlphaBlending();
	
	//try out different modes!
	mode = OFXQTVIDEOPLAYER_MODE_TEXTURE_ONLY;
	//mode = OFXQTVIDEOPLAYER_MODE_PIXELS_ONLY;
	//mode = OFXQTVIDEOPLAYER_MODE_PIXELS_AND_TEXTURE;
	
	testMovie.loadMovie("synchronizedswim.mp4", mode);	
	testMovie.play();
	if(mode != OFXQTVIDEOPLAYER_MODE_TEXTURE_ONLY){
		ourOwnTexture.allocate(testMovie.getWidth(), testMovie.getHeight(), GL_RGBA);
	}
}

//--------------------------------------------------------------
void testApp::update(){

	if(testMovie.update()){
		//if we have created our video player with pixels, we can use make an oftexture
		//with any custom pixel processing we want
		//these modes are how to integrate ofxQTKitVideoPlayer with openCV
		if(mode != OFXQTVIDEOPLAYER_MODE_TEXTURE_ONLY){
			unsigned char* moviePixels = testMovie.getPixels();
			//process pixels here if you want
			//...
			//load them into our own ofTexture to draw
			ourOwnTexture.loadData(moviePixels, testMovie.getWidth(), testMovie.getHeight(), GL_RGBA);
		}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(0,0,0);
	if(mode != OFXQTVIDEOPLAYER_MODE_TEXTURE_ONLY){
		ourOwnTexture.draw(0,0);	
	}
	else {
		testMovie.draw(0,0);
	}
	
	ofSetColor(255, 255, 255);	
	char format[1024];
	sprintf(format, "playback framerate: %f\nmovie is size %d x %d\nat time: %f/%f\non frame %d / %d\npercent done: %f \nLoops? %s\nDone Yet? %s",  
			ofGetFrameRate(), 
			testMovie.getWidth(), testMovie.getHeight(),
			testMovie.getPositionInSeconds(), testMovie.getDuration(),
			testMovie.getCurrentFrame(), testMovie.getTotalNumFrames(),
			testMovie.getPosition()*100,
			(testMovie.getMovieLoopState() ? "yes" : "no"), (testMovie.getIsMovieDone() ? "yes" : "no") );
	
	ofDrawBitmapString(format, 20, testMovie.getHeight()+15);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	//random testing functions
	if(key == 'p'){
		if(testMovie.isPaused()){
			testMovie.play();
		}
		else {
			testMovie.pause();
		}
	}

	if(key == 'm'){
		//move play head to the middle
		testMovie.setPosition(.5);
	}
	
	if(key == 'f'){
		//test movie set frame frame
		testMovie.setFrame(100);
	}
	
	if(key == 'l'){
		//toggle loop
		testMovie.setLoopState(!testMovie.getMovieLoopState());
	}	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

