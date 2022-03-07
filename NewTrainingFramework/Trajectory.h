#pragma once
#include <vector>
#include "../Utilities/utilities.h" 

enum class TrajType
{
	linear,
	circle,
};
enum class TrajDir
{
	normal,
	alternate,
};

class Trajectory
{
public:
	Trajectory ();
	TrajType trajType;
	TrajDir trajDir;
	int iteration;
	int currentPoint;
	int way;
	float distanceToNextPoint;
	float distanceTraveled;

	std::vector<Vector3> trajPoints;
	int nrPoints;
	Vector3 GetNextPosition ();
};

