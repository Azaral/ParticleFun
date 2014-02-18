#pragma once
#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <cmath>

#include "Math.hpp"
#include "Constants.hpp"
#include "Particle.hpp"

namespace Functions
{
    inline Particle clusterToParticle(Cluster a)
    {
        Particle temp;

        temp.mass = a.mass;

        temp.elasticity = a.elasticity;

        temp.velocity.x = a.velocityAfterCollisions.x;
        temp.velocity.y = a.velocityAfterCollisions.y;

        temp.force.x = a.force.x;
        temp.force.y = a.force.y;

        temp.acceleration.x = a.acceleration.x;
        temp.acceleration.y = a.acceleration.y;

        temp.position.x = a.position.x;
        temp.position.y = a.position.y;
        //a.~Cluster();
        return(temp);
    }
    inline Particle addParticle(Particle a, Particle b)
    {
        Particle temp;

        temp.mass = a.mass + b.mass;
        temp.body.radius = sqrt((pow(a.mass,2)+pow(b.mass,2)));
        temp.elasticity = (a.elasticity+b.elasticity)/2;

        temp.velocity.x = a.velocityAfterCollisions.x;//-b.velocityAfterCollisions.x;
        temp.velocity.y = a.velocityAfterCollisions.y;//-b.velocityAfterCollisions.y;

        temp.force.x = temp.velocity.x*temp.mass;
        temp.force.y = temp.velocity.y*temp.mass;

        temp.acceleration.x = temp.force.x/temp.mass;
        temp.acceleration.y = temp.force.y/temp.mass;
        temp.position.x = (a.position.x*a.mass+b.position.x*b.mass)/temp.mass;
        temp.position.y = (a.position.y*a.mass+b.position.y*b.mass)/temp.mass;
        return(temp);

    }

    inline long double GetSquaredDistanceBetween( const Math::Vector& a, const Math::Vector& b )
    {

        return ( a.x - b.x ) * ( a.x - b.x ) +  (a.y - b.y ) * ( a.y - b.y );
    }

    inline long double CreateGravitationForce( double massA, double massB, long double squaredDistance )
    {
        long double force = Constants::GravConstant * ( ( massA * massB ) / (squaredDistance) );

        return force;
    }

    inline long double GetAngleOfTwoPoints( Math::Vector& a, Math::Vector& b )
    {
        return std::atan2( b.y - a.y , b.x - a.x ) * Constants::RadiansToDegrees;
    }

    inline Math::Vector CreateForceVectorFromGravity( Particle& a, Particle& b )
    {

        long double force = CreateGravitationForce( a.mass, b.mass, GetSquaredDistanceBetween( (a.position), (b.position)));

        long double angle = GetAngleOfTwoPoints( a.position, b.position );

        Math::Vector forceVector;

        forceVector.x = force * std::cos( angle * Constants::DegreesToRadians );
        forceVector.y = force * std::sin( angle * Constants::DegreesToRadians );

        return forceVector;
    }

    inline void ApplyForce( Particle& a )
    {
        a.acceleration.x = a.force.x / a.mass;
        a.acceleration.y = a.force.y / a.mass;

        a.force = Math::Vector(0,0);
    }

    inline void ApplyAcceleration( Particle& a )
    {
        a.velocity += a.acceleration;
    }

    inline void ApplyVelocity( Particle& a )
    {
       /* if( a.velocityAfterCollisions.x != 0 || a.velocityAfterCollisions.y != 0 )
        {
            a.velocity = a.velocityAfterCollisions;

            a.velocityAfterCollisions = Math::Vector( 0,0 );
        }*/

        if(a.position.x <= -40 )
        {
            a.position.x = 1940;
            //a.position.y = 1120-a.position.y;
        }
        if(a.position.x >=1980)
        {
            a.position.x = -40;
            //a.position.y = 1120-a.position.y;
        }
        if(a.position.y <= -40)
        {
            a.position.y = 1120;
            //a.position.x = 1980-a.position.x;
        }
        if(a.position.y >=1120)
        {
            a.position.y = -40;
            //a.position.x = 1980-a.position.x;
        }
        a.position += a.velocity;


    }

    inline long double GetSquaredSpeed( Particle& a )
    {
        return a.velocity * a.velocity;
    }

    inline void HandleCollision( Particle& a, Particle& b )
    {
        long double cor = ( a.elasticity * b.elasticity );

        Math::Vector momentumA = a.velocity * a.mass;
        Math::Vector momentumB = b.velocity * b.mass;

        Math::Vector totalMomentum = momentumA + momentumB;

        long double totalMass = a.mass + b.mass;

        //a.velocityAfterCollisions += ((( b.velocity - a.velocity )  * totalMomentum ) / totalMass );

       // b.velocityAfterCollisions +=  (((a.velocity - b.velocity )  * totalMomentum ) / totalMass );

        //a.velocityAfterCollisions += ((( a.velocity * (( a.mass - b.mass ) / totalMass )) + (b.velocity * ( ( 2*b.mass ) / totalMass ) ))* cor) ;
        //b.velocityAfterCollisions += ((( b.velocity * (( b.mass - a.mass ) / totalMass )) + (a.velocity * ( ( 2*a.mass ) / totalMass ) ))* cor) ;
        /*if(a.mass >= b.mass)
        {

            b.velocityAfterCollisions += (((momentumA+momentumB))*cor/totalMass)*-1;
        }
        if(b.mass >= a.mass)
        {

            a.velocityAfterCollisions += (((momentumA+momentumB))*cor/totalMass)*-1;
        }*/
        b.velocityAfterCollisions = (((totalMomentum))/totalMass)*(1-cor);
        a.velocityAfterCollisions = (((totalMomentum))/totalMass)*(1-cor);

    }

    inline bool CheckForCollision( Particle& a, Particle& b )
    {
        Math::Vector distanceApart = a.position - b.position;

        long double totalRadius = a.mass + b.mass;

        return (( (distanceApart.x * distanceApart.x) + (distanceApart.y * distanceApart.y)) <= totalRadius * totalRadius );
    }

    inline std::vector< Particle > CreateParticles( unsigned int particleCount )
    {
        std::vector< Particle > particles;

        auto seed = std::chrono::system_clock::now().time_since_epoch().count();

        std::default_random_engine generator (seed);

        std::uniform_int_distribution<int> x( 0, 1920 );
        std::uniform_int_distribution<int> y( 0, 1080 );
        std::uniform_int_distribution<int> mass( 1,2 );

        std::uniform_real_distribution<long double> elasticity( 0.00001, 0.99999 );

        for( unsigned int i = 0; i < particleCount; i++ )
        {
            long double setMass = mass( generator );

            Particle temp( setMass, Math::Vector( x( generator ), y( generator ) ), setMass, elasticity( generator )  );

            bool valid = true;

            /*
            for( unsigned int j = 0; j < particles.size(); j++ )
            {
                if( Functions::CheckForCollision( temp.body, particles[i].body ) )
                {
                    valid = false;
                    j = particles.size();
                    i--;
                }
            }
            */

            if( valid == true )
            {
                particles.push_back( temp );
            }
        }

        return particles;
    }
}
#endif // FUNCTIONS_HPP
