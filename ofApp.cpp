#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(3);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(36);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	auto len = 10;
	auto noise_seed_x = ofRandom(1000);
	auto noise_seed_y = ofRandom(1000);
	auto noise_seed_z = ofRandom(1000);
	for (auto radius = 10; radius < 150; radius += len + 2) {

		auto noise_value_x = ofNoise(noise_seed_x, radius * 0.005 + ofGetFrameNum() * 0.005);
		auto angle_x = 0.f;
		if (noise_value_x < 0.2) { angle_x = ofMap(noise_value_x, 0, 0.2, -PI, 0); }
		if (noise_value_x > 0.8) { angle_x = ofMap(noise_value_x, 0.8, 1, 0, PI); }

		auto noise_value_y = ofNoise(noise_seed_y, radius * 0.005 + ofGetFrameNum() * 0.005);
		auto angle_y = 0.f;
		if (noise_value_y < 0.2) { angle_y = ofMap(noise_value_y, 0, 0.2, -PI, 0); }
		if (noise_value_y > 0.8) { angle_y = ofMap(noise_value_y, 0.8, 1, 0, PI); }

		auto noise_value_z = ofNoise(noise_seed_z, radius * 0.005 + ofGetFrameNum() * 0.005);
		auto angle_z = 0.f;
		if (noise_value_z < 0.2) { angle_z = ofMap(noise_value_z, 0, 0.2, -PI, 0); }
		if (noise_value_z > 0.8) { angle_z = ofMap(noise_value_z, 0.8, 1, 0, PI); }

		vector<glm::vec3> out, in, line_out, line_in;
		for (auto deg = 0; deg <= 360; deg++) {
			
			auto location = glm::vec3((radius + len * 0.5) * cos(deg * DEG_TO_RAD), (radius + len * 0.5) * sin(deg * DEG_TO_RAD), 0);
			auto rotation_x = glm::rotate(glm::mat4(), angle_x, glm::vec3(1, 0, 0));
			auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));
			auto rotation_z = glm::rotate(glm::mat4(), angle_z, glm::vec3(0, 0, 1));
			location = glm::vec4(location, 0) * rotation_z * rotation_y * rotation_x;

			out.push_back(glm::normalize(location) * (radius + len * 0.5));
			in.push_back(glm::normalize(location) * (radius - len * 0.5));
			line_out.push_back(glm::normalize(location) * (radius + len * 0.5 + 1));
			line_in.push_back(glm::normalize(location) * (radius - len * 0.5 - 1));
		}

		std::reverse(in.begin(), in.end());

		ofFill();
		ofSetColor(239);

		ofBeginShape();
		ofVertices(out);
		ofVertices(in);
		ofEndShape(true);

		ofNoFill();
		ofSetColor(39);

		ofBeginShape();
		ofVertices(line_out);
		ofEndShape(true);

		ofBeginShape();
		ofVertices(line_in);
		ofEndShape(true);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}