//
// Created by Pratyush Tulsian on 11/10/20.
//

#include <core/particle.h>
#include <catch2/catch.hpp>
#include "cinder/gl/gl.h"
#include <visualizer/gascontainer.h>
#include "random"
#include "cinder/gl/gl.h"

using namespace idealgas;

TEST_CASE("Test histogram values") {
  Particle p1 = Particle(vec2(1, 1), vec2(130, 150), 1, kBlueMass,
                         ParticleColor::blue);
  Particle p2 = Particle(vec2(.2, .3), vec2(150, 130), 1, kRedMass,
                         ParticleColor::red);
  Particle p3 = Particle(vec2(.7, .7), vec2(150, 130), 1, kGreenMass,
                         ParticleColor::green);
  Particle p4 = Particle(vec2(1.2, 1.3), vec2(150, 130), 1, kRedMass,
                         ParticleColor::red);
  Particle p5 = Particle(vec2(3.2, 4.3), vec2(150, 130), 1, kRedMass,
                         ParticleColor::red);
  vector<Particle> vec({p1,p2,p3,p4,p5});
  GasContainer gas_container_(vec);
  Histograms histograms = Histograms();
  histograms.Update(gas_container_.GetParticles());
  map<ParticleColor, vector<Particle>> histogram = histograms.GetHistogram();

  SECTION("Test particles are in correct histogram"){
    REQUIRE(histogram[ParticleColor::red].size() == 3);
    REQUIRE(histogram[ParticleColor::blue].size() == 1);
    REQUIRE(histogram[ParticleColor::green].size() == 1);
  }

}

TEST_CASE("Test histogram with no particles"){
  vector<Particle> vec;
  GasContainer gas_container_(vec);
  Histograms histograms = Histograms();
  histograms.Update(gas_container_.GetParticles());
  map<ParticleColor, vector<Particle>> histogram = histograms.GetHistogram();

  SECTION("Check if bins are empty"){
    REQUIRE(histogram[ParticleColor::red].empty());
    REQUIRE(histogram[ParticleColor::blue].empty());
    REQUIRE(histogram[ParticleColor::green].empty());
  }
}