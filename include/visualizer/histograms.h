//
// Created by Pratyush Tulsian on 11/6/20.
//

#pragma once
#include <visualizer/gascontainer.h>
#include <core/particle.h>
#include "visualizer/histograms.h"

namespace idealgas {

using std::vector;
using std::map;
using std::string;

const size_t kHistogramLength = 200;
const size_t kBinLength = 10;
const size_t kBinWidth = 20;
const size_t kMaxSpeed = 20;

const string kYAxis = "frequencies";
const string kXAxis = "speed";

class Histograms {
 public:

  Histograms();

  /**
   * Draw Histogram the histograms
   */
  void Draw();

  /**
   * Update the particles used in the histograms
   */
  void Update(vector<Particle> &particles);

  map<ParticleColor, vector<Particle>> &GetHistogram();

 private:

  /**
   * DrawHistogram a histogram of particles showing speed distribution
   */
  void DrawHistogram(int x, int y, vector<Particle> &particles);

  /**
   * Draw the Rectangles for a histogram from Point(x,y) of a certain color
   */
  void DrawRectangles(int x, int y, map<int, vector<Particle>> histogram, ParticleColor color);



  /**
   * All of the histograms by color of particle
   */
  map<ParticleColor, vector<Particle>> histogram_;

  /**
   * Set the color of the brush
   */
  void SetColor(ParticleColor color);

};

} // namespace idealgas