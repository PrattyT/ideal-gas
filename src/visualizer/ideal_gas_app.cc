//
// Created by Pratyush Tulsian on 11/1/20.
//

#include <visualizer/ideal_gas_app.h>
#include "cinder/gl/gl.h"

namespace idealgas {

using namespace ci;
using namespace app;
using namespace gl;

idealgas::IdealGasApp::IdealGasApp() : gas_container_() {
}

void idealgas::IdealGasApp::setup() {
  setWindowSize((int) kWindowSizeX, (int) kWindowSizeY);
  setFrameRate(60.0f);
}

void idealgas::IdealGasApp::update() {
  gas_container_.Update();
  histograms_.Update(gas_container_.GetParticles());
}

void idealgas::IdealGasApp::draw() {
  clear();
  gas_container_.Draw();
  histograms_.Draw();
}

void IdealGasApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_UP:gas_container_.SpeedUp();
      break;
    case KeyEvent::KEY_DOWN:gas_container_.SlowDown();
      break;
    case KeyEvent::KEY_r:gas_container_.SpawnParticles(ParticleColor::red, kRedMass, 1);
      break;
    case KeyEvent::KEY_g:gas_container_.SpawnParticles(ParticleColor::green, kGreenMass, 1);
      break;
    case KeyEvent::KEY_b:gas_container_.SpawnParticles(ParticleColor::blue, kBlueMass, 1);
      break;
  }

}

} //namespace idealgas