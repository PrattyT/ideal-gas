#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "gascontainer.h"
#include "histograms.h"
#include <core/particle.h>

namespace idealgas {

using namespace ci;
using namespace app;
using namespace gl;
using std::map;
/**
 * Represents the Ideal Gas App
 */
class IdealGasApp : public ci::app::App {
 public:

  /**
   * Create a new Ideal Gas app
   */
  IdealGasApp();

  /**
   * Setup the app
   */
  void setup() override;

  /**
   * DrawHistogram the state of the app
   */
  void draw() override;

  /**
   * Update the state of the app
   */
  void update() override;

  /**
   * Check if a key is pressed for speeding up or slowing down simulation or adding particles
   */
  void keyDown(ci::app::KeyEvent event) override;

  /**
   * Side lengths of the app
   */
  const double kWindowSizeX = 1200 ;
  const double kWindowSizeY = 1200 ;

 private:

  /**
   * The gas container holding all the particles in this app
   */
  GasContainer gas_container_;

  Histograms histograms_ = Histograms();


};

}  // namespace naivebayes
