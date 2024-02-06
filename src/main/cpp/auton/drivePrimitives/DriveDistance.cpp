
//====================================================================================================================================================
// Copyright 2022 Lake Orion Robotics FIRST Team 302
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================

// C++ Includes
#include <cmath>
#include <memory>

// FRC includes

// Team 302 includes
#include <auton/PrimitiveParams.h>
#include <auton/drivePrimitives/DriveDistance.h>
#include <chassis/IChassis.h>

// Third Party Includes


using namespace std;
using namespace frc;



DriveDistance::DriveDistance() :
	SuperDrive(),
	m_targetDistance(0.0)
{
}

void DriveDistance::Init(PrimitiveParams* params) 
{
	SuperDrive::Init(params);
	m_targetDistance = params->GetDistance();

	delete m_initialPose;
	auto chassis = GetChassis();
	if (chassis != nullptr)
	{
		m_initialPose = new Pose2d(chassis->GetPose());
	}
	else
	{
		m_initialPose = new Pose2d();
	}
}

bool DriveDistance::IsDone() 
{
	auto chassis = GetChassis();
	if (chassis != nullptr)
	{
		auto pose = chassis->GetPose();
	    auto currX = pose.X().to<double>();
    	auto currY = pose.Y().to<double>();

		auto initialX = m_initialPose->X().to<double>();
		auto initialY = m_initialPose->Y().to<double>();

    	auto deltaX = abs(currX - initialX);
    	auto deltaY = abs(currY - initialY);
		return deltaX < 0.01 && deltaY < 0.01;
	}
	return false;
}


