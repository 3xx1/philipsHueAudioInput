#pragma once

#include "ofMain.h"
#include "ofxPhilipsHue.h"
#include "fft.h"

#define BUFFER_SIZE 1024
#define NUM_WINDOWS 80


class ofApp : public ofBaseApp
{
	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        void audioReceived (float *input, int bufferSize, int nChannels);
        ofxPhilipsHue hue;
    
        bool shortTermEvent_amp;
        bool longTermEvent_amp;
        int recognition_index;
        int recognition_index_previous;
        int recognition_sustain;
        int temporary_index_buffer;
    
    private:
        float *left;
        float *right;
        int bufferCounter;
        fft myfft;
    
        float magnitude[BUFFER_SIZE];
        float phase[BUFFER_SIZE];
        float power[BUFFER_SIZE];
    
        float freq[NUM_WINDOWS][BUFFER_SIZE/2];
        float freq_phase[NUM_WINDOWS][BUFFER_SIZE/2];
};
