#include "ofApp.h"

bool state = false;
int numOfLights = 2;

//--------------------------------------------------------------
void ofApp::setup(){
    hue.setup("10.0.0.49", "399909d27bace7fb29fa01a8efa5f");
    
    srand((unsigned int)time((time_t *)NULL));
    ofSoundStreamSetup(0, 2, this, 44100, BUFFER_SIZE, 4);
    
    left = new float[BUFFER_SIZE];
    right = new float[BUFFER_SIZE];
    
    for (int i = 0; i < NUM_WINDOWS; i++)
    {
        for (int j = 0; j < BUFFER_SIZE/2; j++)
        {
            freq[i][j] = 0;
        }
    }
    
    ofBackground(0);
    ofSetColor(255);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    static int index=0;
    float avg_power = 0.0f;
    float buffer_intensity = .0f;
    int buffer_index = 0;
    
    if(index < 80)
        index += 1;
    else
        index = 0;
    
    /* do the FFT */
    myfft.powerSpectrum(0,(int)BUFFER_SIZE/2, left,BUFFER_SIZE, &magnitude[0], &phase[0], &power[0], &avg_power);
    
    /* start from 1 because mag[0] = DC component */
    /* and discard the upper half of the buffer */
    for(int j=1; j < BUFFER_SIZE/2; j++) {
        freq[index][j] = magnitude[j];
    }
    
    /* draw the FFT */
    for (int i = 1; i < (int)(BUFFER_SIZE/2); i++) {
        ofLine(20+(i*2),768,20+(i*2),768-magnitude[i]*2.0f);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    state = !state;
    if(state){
        hue.setLightState(2, true, 1.0, 1.0, 0.2, 10);
    }else{
        hue.setLightState(2, false);
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::audioReceived(float * input, int bufferSize, int nChannels){
    // samples are "interleaved"
    for (int i = 0; i < bufferSize; i++){
        left[i] = input[i*2];
        right[i] = input[i*2+1];
    }
    bufferCounter++;
}