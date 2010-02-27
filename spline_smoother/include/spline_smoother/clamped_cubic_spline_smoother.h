/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2009, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the Willow Garage nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

/** \author Mrinal Kalakrishnan */

#ifndef CLAMPED_CUBIC_SPLINE_SMOOTHER_H_
#define CLAMPED_CUBIC_SPLINE_SMOOTHER_H_

#include "spline_smoother.h"
#include "numerical_differentiation_spline_smoother.h"

namespace spline_smoother
{

/**
 * \brief Generates a clamped cubic spline trajectory from the input waypoints.
 *
 * This spline smoother forms cubic spline segments between way-points. The velocities
 * at the way-points are generated by constraining accelerations of adjoining sections to
 * be equal, constraining start and end velocities to be equal to zero, then solving the resulting
 * linear system of equations.
 *
 * Processing time is O(N), but this method appears to be numerically unstable for long trajectories
 * (N>20)
 */
class ClampedCubicSplineSmoother: public SplineSmoother
{
public:
  ClampedCubicSplineSmoother();
  virtual ~ClampedCubicSplineSmoother();

  static const int MAX_TRIDIAGONAL_SOLVER_ELEMENTS = 20;

  /**
   * \brief Smooths the input position trajectory by generating velocities and accelerations at the waypoints.
   *
   * \return true if successful, false if not
   */
  virtual bool smooth(const motion_planning_msgs::JointTrajectoryWithLimits& trajectory_in, motion_planning_msgs::JointTrajectoryWithLimits& trajectory_out) const;

private:
  NumericalDifferentiationSplineSmoother num_diff_spline_smoother_;
  bool smoothSegment(std::vector<trajectory_msgs::JointTrajectoryPoint>& waypoints) const;

};

}

#endif /* CLAMPED_CUBIC_SPLINE_SMOOTHER_H_ */
