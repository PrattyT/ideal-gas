//
// Created by Pratyush Tulsian on 11/1/20.
//

#include <core/particle.h>
#include <catch2/catch.hpp>
#include "cinder/gl/gl.h"

using namespace idealgas;

TEST_CASE("Test Update position") {
  vec2 position(119.9, 120);
  vec2 velocity(0.1, 0);
  Particle particle(velocity, position, 1, 1, ParticleColor::red);
  particle.UpdatePosition();
  REQUIRE(particle.GetPosition() == vec2(120, 120));
}

TEST_CASE("Test Particle collision") {
  vec2 position(119.9, 120);
  vec2 velocity(0.1, 0);
  Particle particle(velocity, position, 1, 1, ParticleColor::red);
  vec2 position2(121.5, 121.4);
  vec2 velocity2(-0.1, 0);
  Particle particle2(velocity2, position2, 1, 1, ParticleColor::red);
  vec2 position3(130, 130);
  vec2 velocity3(-0.1, 0);
  Particle particle3(velocity3, position3, 1, 1, ParticleColor::red);


  SECTION("Check for collision constant mass") {
    REQUIRE_FALSE(particle.IsColliding(particle2));
    particle2.UpdatePosition();
    particle.UpdatePosition();
    REQUIRE(particle2.IsColliding(particle));
  }

  SECTION("Check if particles are moving towards each other") {
    REQUIRE(particle.MovingTowards(particle2));
  }

  particle2.UpdatePosition();
  particle.UpdatePosition();
  particle2.Collide(particle);
  SECTION("Check collided velocities") {
    REQUIRE (Approx((particle.GetVelocity().x)).margin(0.0001) == 0.0);
    REQUIRE(Approx(particle.GetVelocity().y) == -0.1);
  }

  particle2.UpdatePosition();
  particle.UpdatePosition();

  SECTION("Check if particles are no longer moving towards each other") {
    REQUIRE_FALSE(particle.MovingTowards(particle2));
  }

  SECTION("Check position after colliding") {
    REQUIRE(particle2.GetPosition() == vec2(121.4, 121.5));
    REQUIRE(particle.GetPosition() == vec2(120, 119.90));
  }

  SECTION("Check bystander particle is not affected") {
    REQUIRE_FALSE(particle3.IsColliding(particle2));
    REQUIRE(particle3.GetPosition() == vec2(130, 130));
  }

}

TEST_CASE("Test wall collision") {
  vec2 position(100, 150);
  vec2 velocity(-0.1, 0.2);
  Particle particle(velocity, position, 1, 1, ParticleColor::red);
  particle.HittingWall();
  vec2 position2(150, 100);
  vec2 velocity2(-0.1, -0.2);
  Particle particle2(velocity2, position2, 1, 1, ParticleColor::red);
  particle2.HittingWall();

  SECTION("vertical wall") {
    SECTION("Check x velocity is inverted") {
      REQUIRE(Approx(particle.GetVelocity().x).margin(0.001) == 0.1);
    }
    SECTION("Check y velocity is unchanged") {
      REQUIRE(Approx(particle.GetVelocity().y).margin(0.001) == 0.2);
    }
  }

  SECTION("horizontal wall") {
    SECTION("Check x velocity is unchanged") {
      REQUIRE(Approx(particle2.GetVelocity().x).margin(0.001) == -0.1);
    }
    SECTION("Check y velocity is inverted") {
      REQUIRE(Approx(particle2.GetVelocity().y).margin(0.001) == 0.2);
    }
  }
}

TEST_CASE("Test different mass") {

  vec2 position(119.9, 120);
  vec2 velocity(0.1, 0);
  Particle particle(velocity, position, 1, kRedMass, ParticleColor::red);
  vec2 position1(121.5, 121.4);
  vec2 velocity1(-0.1, 0);
  Particle particle1(velocity1, position1, 1, kBlueMass, ParticleColor::blue);

  particle.UpdatePosition();
  particle1.UpdatePosition();

  REQUIRE(particle1.IsColliding(particle));
  particle1.Collide(particle);
  particle1.UpdatePosition();

  SECTION("Test velocitiy") {
    REQUIRE(Approx(particle1.GetVelocity().x).margin(0.001) == -0.050);
    REQUIRE(Approx(particle1.GetVelocity().y).margin(0.001) == 0.050);
  }

  SECTION("Test Position") {
    REQUIRE(Approx(particle1.GetPosition().x).margin(0.001) == 121.35);
    REQUIRE(Approx(particle1.GetPosition().y).margin(0.001) == 121.45);
  }
}

