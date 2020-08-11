#include "pch.h"
#include "Spea.hpp"

#include <ctime>
#include <limits>
#include <random>

#undef max
#undef min

template<typename Numeric, typename Generator = std::mt19937>
Numeric random(Numeric from, Numeric to)
{
	thread_local static Generator gen(std::random_device{}());

	using dist_type = typename std::conditional
		<
		std::is_integral<Numeric>::value,
		std::uniform_int_distribution<Numeric>,
		std::uniform_real_distribution<Numeric>
		>::type;

	thread_local static dist_type dist;

	return dist(gen, typename dist_type::param_type{ from, to });
}

Spea::Spea(const FitnessFunction& fitnessFunction)
:	fitnessFunction_(fitnessFunction),
	fitnessFunctionDimension_(2)
{}

void Spea::run()
{
	initFirstPopulation();
	fillAchive(takeNonDominatedGenoms());
	clearPopulationAndMoveAchiveInto();
}

void Spea::initFirstPopulation()
{
	for (int i = 0; i < populationSize_; i++)
	{
		population_[i] = createRandomGenom();
	}
}

void Spea::fillAchive(std::vector<Spea::Genom>& nonDominatedGenoms)
{
	if (nonDominatedGenoms.size() < achiveSize_)
	{
		auto range = achiveSize_ - nonDominatedGenoms.size();
		for (int i = 1; i <= range; i++)
		{
			nonDominatedGenoms.push_back(population_[i]);
		}
	}
	for (int i = 0; i < achive_.size(); i++)
	{
		achive_[i] = nonDominatedGenoms[i];
	}
}

void Spea::clearPopulationAndMoveAchiveInto()
{
	for (int i = 0; i < achiveSize_; i++)
	{
		population_[i] = achive_[i];
	}
}

void Spea::crossoverAllInPopulation()
{
}

std::vector<Spea::Genom> Spea::takeNonDominatedGenoms()
{
	std::vector<Genom> nonDominated;
	std::sort(std::begin(population_), std::end(population_),
		[this](const Genom& lhs, const Genom& rhs) -> bool
		{
			return this->getFitnessFunction()[0](lhs) < this->getFitnessFunction()[0](rhs);
		});
	auto bestFirstCriterium = fitnessFunction_[0](population_[0]);
	std::sort(std::begin(population_), std::end(population_),
		[this](const Genom& lhs, const Genom& rhs) -> bool
		{
			return this->getFitnessFunction()[1](lhs) < this->getFitnessFunction()[1](rhs);
		});
	auto bestSecondCriterium = fitnessFunction_[1](population_[0]);
	for (const auto& genom : population_)
	{
		if (fitnessFunction_[0](genom) == bestFirstCriterium
			|| fitnessFunction_[1](genom) == bestSecondCriterium)
		{
			nonDominated.push_back(genom);
		}
	}
	return nonDominated;
}

Spea::Genom Spea::crossover(const std::pair<Genom, Genom>& parents)
{
	Genom child;
	const auto gensPusher = [&parents, &child](const auto& iteratorCounter)
	{
		for (int i = 0; i < iteratorCounter; i++)
		{
			child.push_back(parents.first[i]);
		}
		for (int i = iteratorCounter; i < parents.second.size(); i++)
		{
			child.push_back(parents.second[i]);
		}
	};
	if (parents.first.size() % 2 == 0)
	{
		const auto& iteratorCounter = parents.first.size() / 2;
		gensPusher(iteratorCounter);
	}
	else
	{
		const auto& moreFromFirstOrFromSecond = static_cast<bool>(
			random<int>(0, 1));
		int iteratorCounter;
		if (moreFromFirstOrFromSecond) // zaokraglaniew gore albo w dol
		{

		}

	}
	return child;
}

Spea::Genom Spea::createRandomGenom()
{
	Genom randomGenom(fitnessFunctionDimension_);
	for (int i = 0; i < fitnessFunctionDimension_; i++)
	{
		randomGenom[i] = createRandomGen();
	}
	return randomGenom;
}


double Spea::createRandomGen()
{
	return random<double>(-100, 100);
}
