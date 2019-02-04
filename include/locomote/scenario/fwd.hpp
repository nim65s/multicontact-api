// Copyright (c) 2015-2018, CNRS
// Authors: Justin Carpentier <jcarpent@laas.fr>
// Simplified BSD license :
//Redistribution and use in source and binary forms, with or without modification,
//are permitted provided that the following conditions are met:

//1. Redistributions of source code must retain the above copyright notice,
//this list of conditions and the following disclaimer.

//2. Redistributions in binary form must reproduce the above copyright notice,
//this list of conditions and the following disclaimer in the documentation
//and/or other materials provided with the distribution.

//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
//OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
//OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
//WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
//OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
//ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#ifndef __locomote_scenario_fwd_hpp__
#define __locomote_scenario_fwd_hpp__

#include "locomote/geometry/fwd.hpp"
#include <pinocchio/spatial/fwd.hpp>

namespace locomote
{
  namespace scenario
  {
    
    template<class T> struct traits {};
    
    template<typename _Scalar> struct ContactPatchTpl;
    typedef ContactPatchTpl<double> ContactPatch;
    
    template<typename _Scalar, int _dim> struct ContactPhaseTpl;
    typedef ContactPhaseTpl<double,4> ContactPhase4;
    
    template<typename _Scalar> struct ContactPhaseHumanoidTpl;
    typedef ContactPhaseHumanoidTpl<double> ContactPhaseHumanoid;
    
    template<class _ContactPhase> struct ContactSequenceTpl;
    typedef ContactSequenceTpl<ContactPhase4> ContactSequence4;
    typedef ContactSequenceTpl<ContactPhaseHumanoid> ContactSequenceHumanoid;
    
    
    template<class SOC> struct ContactConstraintSOC;
    typedef ContactConstraintSOC<geometry::SOC6d> ContactConstraintSOC6;
    
    template<typename Scalar> struct ContactModelPlanarTpl;
    typedef ContactModelPlanarTpl<double> ContactModelPlanar;
    
    template<typename Scalar> struct ContactConstraintPlanarTpl;
    typedef ContactConstraintPlanarTpl<double> ContactConstraintPlanar;
    
    enum HumanoidPhaseType
    {
      SINGLE_SUPPORT,
      DOUBLE_SUPPORT,
      TRIPLE_SUPPORT,
      QUADRUPLE_SUPPORT,
      HUMANOID_PHASE_UNDEFINED
    };
    
    enum ConicType
    {
      CONIC_SOWC,
      CONIC_DOUBLE_DESCRIPTION,
      CONIC_UNDEFINED
    };
  }
}

#endif // ifndef __locomote_scenario_fwd_hpp__