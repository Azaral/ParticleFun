#pragma once
#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "Math.hpp"

struct Circle
{
    double radius;

    Math::Vector position;

    Circle()
    {
        radius = 0;
        position.x = 0;
        position.y = 0;
    }

    Circle( double setRadius, Math::Vector setPosition )
    {
        radius = setRadius;
        position = setPosition;
    }
};

struct Particle
{
    long double mass;

    long double elasticity;

    Circle body;

    Math::Vector velocity;
    Math::Vector velocityAfterCollisions;
    Math::Vector acceleration;
    Math::Vector force;
    Math::Vector position;
    sf::CircleShape particle;

    ~Particle()
    {

    }
    Particle()
    {
        mass = 0;
        elasticity = 1.0;
    }

    Particle( long double setMass, Math::Vector startPosition, long double setRadius , long double setElasticity) : body( setRadius, startPosition )
    {
        mass = setMass;

        particle.setFillColor( sf::Color::Blue );
        elasticity = setElasticity;

        velocity.x = 0;
        velocity.y = 0;

        acceleration.x = 0;
        acceleration.y = 0;

        force.x = 0;
        force.y = 0;

        position.x = body.position.x;
        position.y = body.position.y;
    }

};

struct Cluster : Particle, Circle
{
    Circle body;

        Math::Vector velocity;
        Math::Vector velocityAfterCollisions;
        Math::Vector acceleration;
        Math::Vector force;
        Math::Vector position;

    Cluster()
    {
        mass = 0;
        elasticity = 1.0;
    }


    Cluster(Particle a)
    {


        mass = a.mass;
        //body.radius += a.mass;
        elasticity = a.elasticity;

        velocity.x = a.velocity.x;
        velocity.y = a.velocity.y;

        acceleration.x = a.acceleration.x;
        acceleration.y = a.acceleration.y;

        force.x = a.force.x;
        force.y = a.force.y;

        position.x = a.position.x;
        position.y = a.position.y;
    }
    ~Cluster()
    {

    }

};

#endif // PARTICLE_HPP
