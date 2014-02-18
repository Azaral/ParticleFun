///*
#include <vector>
#include <random>
#include <chrono>
#include <fstream>

#include <SFML/Graphics.hpp>

#include "Functions.hpp"
#include "Particle.hpp"
#include "Math.hpp"
#include "Constants.hpp"

void OutputParticleData( std::vector< Particle >& particles );

int main()
{
    sf::RenderWindow window( sf::VideoMode::getDesktopMode(), "Accretion Fun", sf::Style::Fullscreen );

    //window.setFramerateLimit(1);

    bool running = true;

    std::vector< Particle > particles = Functions::CreateParticles(50);
    Particle NULL_PARTICLE;
    Cluster cluster(NULL_PARTICLE);

    OutputParticleData( particles );

    while( running )
    {
        sf::Event input;

        while( window.pollEvent( input ) )
        {
            if( input.type == sf::Event::KeyReleased )
            {
                if( input.key.code == sf::Keyboard::Escape )
                {
                    running = false;
                }
            }
        }
        for( unsigned int i = 0; i < particles.size(); i++ )
        {
            for( unsigned int j = 0; j < particles.size(); j++ )
            {
                if( i != j )
                {
                    particles[i].force += Functions::CreateForceVectorFromGravity( particles[i], particles[j] );
                }
            }
        }
        for( unsigned int i = 0; i < particles.size(); i++ )
        {
            for( unsigned int j = 0; j < particles.size(); j++ )
            {
                if( j != i)
                {
                    if ( Functions::CheckForCollision( particles[i], particles[j]) )
                    {
                        Functions::HandleCollision( particles[i], particles[j] );
                        cluster = Functions::addParticle(particles[i],particles[j]) ;
                        //particles.push_back(Functions::clusterToParticle(cluster));
                        particles.erase(particles.begin()+i);
                        particles.insert(particles.begin()+i,Functions::clusterToParticle(cluster));
                        particles.erase(particles.begin()+j);
                        cluster.~Cluster();
                        //particles.shrink_to_fit();
                    }
                }
            }
        }

        for( unsigned int i = 0; i < particles.size(); i++ )
        {
            Functions::ApplyForce( particles[i] );
        }

        for( unsigned int i = 0; i < particles.size(); i++ )
        {
            Functions::ApplyAcceleration( particles[i] );
        }
        for( unsigned int i = 0; i < particles.size(); i++ )
        {
            Functions::ApplyVelocity( particles[i] );
        }
      /*  for( unsigned int i = 0; i < clusters.size(); i++ )
        {
            Functions::ApplyVelocity( clusters[i] );
        }
        for( unsigned int i = 0; i < clusters.size(); i++ )
        {
            Functions::ApplyForce( clusters[i] );
        }

        for( unsigned int i = 0; i < clusters.size(); i++ )
        {
            Functions::ApplyAcceleration( clusters[i] );
        }*/

        window.clear();

        for( unsigned int i = 0; i < particles.size(); i++ )
        {
            particles[i].particle.setRadius( particles[i].mass );

            particles[i].particle.setOrigin( particles[i].particle.getRadius() / 2, particles[i].particle.getRadius() / 2 );

            particles[i].particle.setPosition( particles[i].position.x, particles[i].position.y );

            if(particles[i].mass <= 5)
            {
                particles[i].particle.setFillColor(sf::Color::Blue);
            }
            if(particles[i].mass > 5)
            {
                particles[i].particle.setFillColor(sf::Color::Red);
            }
            if(particles[i].mass > 10)
            {
                particles[i].particle.setFillColor(sf::Color::Yellow);
            }
            if(particles[i].mass > 20)
            {
                particles[i].particle.setFillColor(sf::Color::White);
            }
            window.draw( particles[i].particle );

        }



        window.display();
    }

    return 0;
}



void OutputParticleData( std::vector< Particle >& particles )
{
    std::ofstream tofile("Particle Data.txt");

    for( unsigned int i = 0; i < particles.size(); i++ )
    {
        tofile << "Particle " << i << " x position is " << particles[i].body.position.x << std::endl;
        tofile << "Particle " << i << " y position is " << particles[i].body.position.y << std::endl;
        tofile << "Particle " << i << " radius is " << particles[i].body.radius << std::endl;
        tofile << "Particle " << i << " mass is " << particles[i].mass << std::endl;
        tofile << "Particle " << i << " elasticity is " << particles[i].elasticity << std::endl << std::endl;
    }
}
