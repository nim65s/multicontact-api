// Copyright (c) 2015-2018, CNRS
// Authors: Justin Carpentier <jcarpent@laas.fr>
//
#ifndef __multicontact_api_scenario_fwd_hpp__
#define __multicontact_api_scenario_fwd_hpp__

#include "multicontact-api/geometry/fwd.hpp"
#include <pinocchio/spatial/fwd.hpp>

namespace multicontact_api {
namespace scenario {

template <class T>
struct traits {};

template <typename _Scalar>
struct ContactPatchTpl;
typedef ContactPatchTpl<double> ContactPatch;

template <typename _Scalar>
struct ContactPhaseTpl;
typedef ContactPhaseTpl<double> ContactPhase;

template <typename _ContactPhase>
struct ContactSequenceTpl;
typedef ContactSequenceTpl<ContactPhase> ContactSequence;

template <typename Scalar>
struct ContactModelPlanarTpl;
typedef ContactModelPlanarTpl<double> ContactModelPlanar;

enum ConicType { CONIC_SOWC, CONIC_DOUBLE_DESCRIPTION, CONIC_UNDEFINED };

}  // namespace scenario
}  // namespace multicontact_api

#endif  // ifndef __multicontact_api_scenario_fwd_hpp__
