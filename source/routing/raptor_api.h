/* Copyright © 2001-2014, Canal TP and/or its affiliates. All rights reserved.
  
This file is part of Navitia,
    the software to build cool stuff with public transport.
 
Hope you'll enjoy and contribute to this project,
    powered by Canal TP (www.canaltp.fr).
Help us simplify mobility and open public transport:
    a non ending quest to the responsive locomotion way of traveling!
  
LICENCE: This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
   
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Affero General Public License for more details.
   
You should have received a copy of the GNU Affero General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
  
Stay tuned using
twitter @navitia 
IRC #navitia on freenode
https://groups.google.com/d/forum/navitia
www.navitia.io
*/

#pragma once
#include "type/type.pb.h"
#include "type/response.pb.h"
#include "type/request.pb.h"
#include <limits>

namespace navitia{
    namespace type{
        struct EntryPoint;
        struct AccessibiliteParams;
    }
    namespace georef{
        struct StreetNetwork;
    }
}

namespace navitia { namespace routing {

struct RAPTOR;

pbnavitia::Response make_response(RAPTOR &raptor,
                                  const type::EntryPoint &origin,
                                  const type::EntryPoint &destination,
                                  const std::vector<uint64_t> &datetimes,
                                  bool clockwise,
                                  const type::AccessibiliteParams & accessibilite_params,
                                  std::vector<std::string> forbidden,
                                  georef::StreetNetwork & worker,
                                  bool disruption_active,
                                  uint32_t max_duration=std::numeric_limits<uint32_t>::max(),
                                  uint32_t max_transfers=std::numeric_limits<uint32_t>::max(),
                                  bool show_codes = false);

pbnavitia::Response make_nm_response(RAPTOR &raptor, const std::vector<type::EntryPoint> &origins,
                                     const std::vector<type::EntryPoint> &destinations,
                                     const uint64_t& datetimes, bool clockwise,
                                     const type::AccessibiliteParams & accessibilite_params,
                                     std::vector<std::string> forbidden,
                                     georef::StreetNetwork & worker,
                                     bool disruption_active,
                                     uint32_t max_duration, uint32_t max_transfers,
                                     bool show_codes);

pbnavitia::Response make_isochrone(RAPTOR &raptor,
                                   type::EntryPoint origin,
                                   const uint64_t datetime, bool clockwise,
                                   const type::AccessibiliteParams & accessibilite_params,
                                   std::vector<std::string> forbidden,
                                   georef::StreetNetwork & worker,
                                   bool disruption_active,
                                   int max_duration = 3600,
                                   uint32_t max_transfers=std::numeric_limits<uint32_t>::max(),
                                   bool show_codes = false);


}}
