/*
 * (C) Copyright 2017-2018 UCAR
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 */

#ifndef UFO_CRTM_OBSRADIANCECRTM_H_
#define UFO_CRTM_OBSRADIANCECRTM_H_

#include <ostream>
#include <string>
#include <vector>

#include <boost/scoped_ptr.hpp>

#include "oops/base/Variables.h"
#include "oops/util/Logger.h"
#include "oops/util/ObjectCounter.h"
#include "ufo/crtm/ObsRadianceCRTM.interface.h"
#include "ufo/ObsOperatorBase.h"

namespace eckit {
  class Configuration;
}

namespace ioda {
  class ObsSpace;
  class ObsVector;
}

namespace ufo {
  class GeoVaLs;
  class ObsBias;

// -----------------------------------------------------------------------------
/// RadianceCRTM observation for UFO.
class ObsRadianceCRTM : public ObsOperatorBase,
                    private util::ObjectCounter<ObsRadianceCRTM> {
 public:
  static const std::string classname() {return "ufo::ObsRadianceCRTM";}

  ObsRadianceCRTM(const ioda::ObsSpace &, const eckit::Configuration &);
  virtual ~ObsRadianceCRTM();

// Obs Operator
  void simulateObs(const GeoVaLs &, ioda::ObsVector &, const ObsBias &) const;

// Other
  const oops::Variables & variables() const {return *varin_;}
  const oops::Variables & observed() const {return *varout_;}

  int & toFortran() {return keyOperRadianceCRTM_;}
  const int & toFortran() const {return keyOperRadianceCRTM_;}

 private:
  void print(std::ostream &) const;
  F90hop keyOperRadianceCRTM_;
  const ioda::ObsSpace& odb_;
  boost::scoped_ptr<const oops::Variables> varin_;
  boost::scoped_ptr<const oops::Variables> varout_;
};

// -----------------------------------------------------------------------------

}  // namespace ufo
#endif  // UFO_CRTM_OBSRADIANCECRTM_H_
