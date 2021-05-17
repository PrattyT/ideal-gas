//
// Created by Pratyush Tulsian on 11/1/20.
//

#include <visualizer/ideal_gas_app.h>

using namespace idealgas;

void prepareSettings(IdealGasApp::Settings *settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(IdealGasApp, ci::app::RendererGl, prepareSettings);
