#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(6);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->span = 30;
	for (auto x = this->span * 1.5; x <= ofGetWidth() - this->span * 1.5; x += this->span) {

		for (int y = this->span * 1.5; y <= ofGetHeight() - this->span * 1.5; y += this->span) {

			this->location_list.push_back(glm::vec2(x, y));
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofColor color;
	for (int i = 0; i < this->location_list.size(); i++) {

		ofPushMatrix();
		ofTranslate(this->location_list[i]);

		auto noise_value = ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0035);
		auto start_param = noise_value < 0.5 ? (noise_value < 0.45 ? 0 : ofMap(noise_value, 0.45, 0.5, 0, 25)) : 25;

		auto start = this->make_point(this->span, start_param);
		auto end = this->make_point(this->span, start_param + 50);

		color.setHsb(ofRandom(255), 180, 255);
		ofSetColor(color);

		ofDrawLine(start, end);
		ofDrawCircle(start, 7);
		ofDrawCircle(end, 7);

		ofPopMatrix();
	}
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}