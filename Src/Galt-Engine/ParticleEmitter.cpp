#include "ParticleEmitter.h"

using namespace GaltE;


ParticleEmitter::ParticleEmitter(float xPos, float yPos, int intensity, sf::Color particleColor, float particleLifeTime)
{
	mData.xPos = xPos;
	mData.yPos = yPos;
	mIntensity = intensity;
	mData.particleColor = particleColor;
	mData.lifeTime = particleLifeTime;
	mExtraTime = 0;
	mTotalTime = 0;
	mParticles.reserve(0);

	//set seed
	srand(std::time(NULL));
}

ParticleEmitter::~ParticleEmitter()
{
}

void ParticleEmitter::update(float timeDelta)
{
	mTotalTime += timeDelta;
	mExtraTime += timeDelta;

	//update old particles and eliminate those that exceeded their lifeTime
	updateParticles(timeDelta);

	//now add particles based on intensity * deltaT
	int particlesToAdd = (int)(mIntensity * mExtraTime);

	if (particlesToAdd >= 1)
	{
		//TODO We have an inconsitent extraTime, eventually, someTime will be left out, thus less particles will get add
		//then should be
		mExtraTime = 0;
		addParticles(particlesToAdd);
	}
}

void ParticleEmitter::addParticles(int particlesToAdd)
{
	/**
	* If the vector has been filled up with particles, 
	* stop adding particales and reset the old particles
	*/
	if (mParticles.size() != mParticles.capacity())
	{
		for (int i = 0; i < particlesToAdd; i++)
		{
			//get random speed and angle in radians, then convert that to velocity
			//TODO Allow user to set a max particle speed
			float speed = (float) (50 + (rand() % 10));
			float angle = (float) (rand() % 360) * (float) (PI / 180);

			mData.xVel = speed * cos(angle);
			mData.yVel = speed * sin(angle);

			Particle tempParticle(mData);
			mParticles.push_back(tempParticle);
		}
	}
	else
	{
		bool found = false;
		int iterator = 0;

		for (int i = 0; i < particlesToAdd; i++)
		{
			found = false;
			while (found != true)
			{
				if (mParticles[iterator].isAlive() == false)
				{
					found = true;
					mParticles[iterator].reset();

					//set new speed
					float speed = (float) (50 + (rand() % 10));
					float angle = (float) (rand() % 360) * (float) (PI / 180);

					mParticles[iterator].setVelX(speed * cos(angle));
					mParticles[iterator].setVelY(speed * sin(angle));
				}
				iterator += 1;
			}
		}
	}
	
}

void ParticleEmitter::draw(Window& window, float timeDelta)
{
	update(timeDelta);
	for (int i = 0; i < mParticles.size(); i++)
	{
		mParticles[i].drawParticle(window);
	}
}

void ParticleEmitter::begin(int amount)
{
	/*
	* To calculate the maximum number of particles needed for the vector to hold 
	* we use the following formula:
	* (Intensity * particle lifetime) + inital burst value + 0.5
	*/
	int maxSize = (int)((mIntensity * mData.lifeTime) + amount + 0.5);
	mParticles.reserve(maxSize);
	addParticles(amount);
}

void ParticleEmitter::updateParticles(float timeDelta)
{
	for (int i = 0; i < mParticles.size(); i++)
	{
		if (mParticles[i].isAlive())
		{
			mParticles[i].update(timeDelta);
		}
	}
}