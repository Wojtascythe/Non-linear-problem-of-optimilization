#pragma once

#include <array>
#include <utility>
#include <vector>


class Spea
{
private:
	static constexpr const int numberOfCriteriums = 2;
	static constexpr const int populationSize_ = 100;
	static constexpr const int achiveSize_ = 20;
	static constexpr const int maximumGenerations_ = 100;

public:
	using Genom = std::vector<double>;
	using FitnessFunction = std::array<std::function<double(Genom)>, numberOfCriteriums>;

	explicit Spea(const FitnessFunction& fitnessFunction);

	void run();
	std::vector<Genom> takeNonDominatedGenoms();

	std::array<Genom, populationSize_> getPopulation() const { return population_; }
	std::array<Genom, achiveSize_> getAchive() const { return achive_; }
	FitnessFunction getFitnessFunction() const { return fitnessFunction_; }

private:
	void initFirstPopulation();
	void fillAchive(std::vector<Genom>& nonDominatedGenoms);
	void clearPopulationAndMoveAchiveInto();
	void crossoverAllInPopulation();

	Genom crossover(const std::pair<Genom, Genom>& parents);
	Genom createRandomGenom();
	double createRandomGen();

	int fitnessFunctionDimension_;

	std::array<Genom, populationSize_> population_;
	std::array<Genom, achiveSize_> achive_;

	FitnessFunction fitnessFunction_;
};
