#include "ofApp.h"

bool state = false;

int numOfLights = 2;
float threshold = 50.0f;

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
    
    shortTermEvent_amp  = false;
    longTermEvent_amp   = false;
    recognition_sustain = 0;
    recognition_index   = 0;
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
 
    myfft.powerSpectrum(0, (int)BUFFER_SIZE/2, left, BUFFER_SIZE, &magnitude[0], &phase[0], &power[0], &avg_power);
   
    for (int i = 1; i < (int)(BUFFER_SIZE/2); i++) {
        ofLine(20+(i*2), 768, 20+(i*2), 768-magnitude[i]*2.0f);
        if (magnitude[i]>buffer_intensity) {
            buffer_intensity = magnitude[i];
            buffer_index = i;
        }
    }
    
    // printf("index: %d, amp: %f\n", buffer_index, buffer_intensity);
    
    // short term event flag
    if (buffer_intensity>threshold) {
        shortTermEvent_amp = true;
        if (temporary_index_buffer==0) temporary_index_buffer = buffer_index;
    } else {
        shortTermEvent_amp = false;
        recognition_sustain = 0;
    }
    
    // whether this short term event flag is valid or not
    if (shortTermEvent_amp) {
        // printf("temporarily recognized frequency index is %d\n", temporary_index_buffer);
        // printf("recognition duration is %d\n", recognition_sustain);
        if (abs(temporary_index_buffer-buffer_index)<3) {
            recognition_sustain++;
            temporary_index_buffer = buffer_index;
        } else {
            temporary_index_buffer = 0;
        }
    }
    
    // if the recognition_sustain is longer enough
    if (recognition_sustain > 30) {
        recognition_index = temporary_index_buffer;
        if (!longTermEvent_amp) {
            longTermEvent_amp = true;
            if (recognition_index_previous>recognition_index) {
                hue.setLightState(2, false);
            }else{
                hue.setLightState(2, true, 1.0, 1.0, 0.2, 10);
            }
            recognition_index_previous = recognition_index;
        }
    }else{
        longTermEvent_amp = false;
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