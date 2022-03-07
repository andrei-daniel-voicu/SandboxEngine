#include "Trajectory.h"

Trajectory::Trajectory ()
{
	distanceToNextPoint = 0;
	distanceTraveled = 0;
	currentPoint = -1;
	way = 1;
}

Vector3 Trajectory::GetNextPosition ()
{
	if (iteration)
	{
		currentPoint += way;
	}
	if (way == -1)
	{
		if (currentPoint == 0)
		{
			way = 1;
			if (iteration != -1)
			{
				iteration--;
			}
		}
	}
	else
	{
		if (currentPoint == trajPoints.size ())
		{
			if (trajDir == TrajDir::alternate)
			{
				way = -1;
				currentPoint--;

			}
			else if (trajDir == TrajDir::normal)
			{
				currentPoint = 0;
			}
			if (iteration != -1)
			{
				iteration--;
			}
		}
	}
	return trajPoints[currentPoint];
}
