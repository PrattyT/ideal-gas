//
// Created by Pratyush Tulsian on 11/6/20.
//

#include <visualizer/histograms.h>
#include "cinder/gl/gl.h"
#include <core/particle.h>

namespace idealgas {
using namespace ci;
using namespace gl;
using ci::Color;

Histograms::Histograms() {
  histogram_[ParticleColor::red] = vector<Particle>();
  histogram_[ParticleColor::blue] = vector<Particle>();
  histogram_[ParticleColor::green] = vector<Particle>();
}

void Histograms::Update(vector<Particle> &particles) {
  histogram_.clear();

  for (Particle &p : particles) {
    histogram_[p.GetColor()].push_back(p);
  }
}

void Histograms::Draw() {
  DrawHistogram(800, 100, histogram_[ParticleColor::red]);
  DrawHistogram(800, 400, histogram_[ParticleColor::blue]);
  DrawHistogram(800, 700, histogram_[ParticleColor::green]);
}

void Histograms::DrawHistogram(int x, int y, vector<Particle> &particles) {

  // draw border
  color(Color::white());
  drawStrokedRect(ci::Rectf( y,x, x + kHistogramLength, y + kHistogramLength));

  // create bins
  map<int, vector<Particle>> bins;
//  for (size_t speed = 0; speed < kMaxSpeed; speed++) {
//    bins[speed] = vector<Particle>();
//  }
  for (Particle &particle : particles) {
    bins[std::floor(glm::length(particle.GetVelocity()))].push_back(particle);
  }

  DrawRectangles(x, y, bins, particles[0].GetColor());

  // write labels
  drawStringCentered(kXAxis, vec2(x+kHistogramLength/2,y+kHistogramLength+kBinWidth));
  drawStringCentered(kYAxis, vec2(x-kBinLength*kYAxis.length()/2,y+kHistogramLength/2));
}

void Histograms::DrawRectangles(int x, int y, map<int, vector<Particle>> histogram, ParticleColor color) {
  // set color of rectangles
  SetColor(color);

  // set y coord to bottom left of histogram box
  y += kHistogramLength;

  for (size_t speed = 0; speed < kMaxSpeed; speed++) {
    drawSolidRect(ci::Rectf(x, y - (histogram[speed].size()) * kBinWidth, x + kBinLength, y));
    x += kBinLength;
  }
}

void Histograms::SetColor(ParticleColor c) {
  if (c == ParticleColor::red) {
    color(Color(255, 0, 0));
  }
  if (c == ParticleColor::blue) {
    color(Color(0, 0, 255));
  }
  if (c == ParticleColor::green) {
    color(Color(0, 255, 0));
  }
}

map<ParticleColor, vector<Particle>> &Histograms::GetHistogram() {
  return histogram_;
}

} // namespace idealgas