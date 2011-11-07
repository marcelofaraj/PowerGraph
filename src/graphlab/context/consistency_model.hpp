/**  
 * Copyright (c) 2009 Carnegie Mellon University. 
 *     All rights reserved.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing,
 *  software distributed under the License is distributed on an "AS
 *  IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 *  express or implied.  See the License for the specific language
 *  governing permissions and limitations under the License.
 *
 * For more about this software visit:
 *
 *      http://www.graphlab.ml.cmu.edu
 *
 */

/**
 * Also contains code that is Copyright 2011 Yahoo! Inc.  All rights
 * reserved.  
 *
 * Contributed under the iCLA for:
 *    Joseph Gonzalez (jegonzal@yahoo-inc.com) 
 *
 */


#ifndef GRAPHLAB_CONSISTENCY_MODEL_HPP
#define GRAPHLAB_CONSISTENCY_MODEL_HPP

namespace graphlab {

  /** \brief defines the types of scope consistency guarantees provided  
   
      There are several choices for consistency mechanisms in the
      graphlab framework.  Each choice determines to what extent
      adjacent vertices can be operated on in parallel.  

      <ul> 

        <li> Null Consistency: provides no guarantees allowing update
        functions to operate on the same vertex concurrently </li>

        <li> Vertex Read Consistency: On ensures that that you can
        read from the local vertex correctly</li>

        <li> Vertex Consistency: Ensures that a scope is aquired by
        only one processor at a time </li>

        <li> Edge Consistency: Ensures that adjacent vertices are not
        updated simultaneoulsy. If the update function only modifies
        the data on the scope vertex and its adjacent edges then this
        consistency model is sufficient to guarantee sequential
        consistency </li>

        <li> Fully Consistency: This consistency models guarantees
        sequential consistency but may limit the available
        parallelism.  Effectively, this consistency model ensures that
        overlapping scopes cannot be executed simultaneously.</li>

      </ul>

      The scope_range_enum is passed to the engine through the iengine
      interface or set using the engine factory.
 
   */
  struct consistency_model {
    /// \brief scope types
    enum model_enum {
      NULL_CONSISTENCY = 0,    ///< no locks
      VERTEX_READ_CONSISTENCY, ///< read only from self
      READ_CONSISTENCY,        ///< read from self and adjacent structures
      VERTEX_CONSISTENCY,      ///< write to self. no lock on adjacent
      SINGLE_EDGE_READ_CONSISTENCY, ///< only lock a single edge
      SINGLE_EDGE_WRITE_CONSISTENCY, ///< only lock a single edge for write access
      EDGE_CONSISTENCY,        ///< write to self, read from adjacent structures
      FULL_CONSISTENCY,        ///< write to self and adjacent structures
      USE_DEFAULT              ///< use externally described default
    };
    
    enum lock_type_enum {
      NO_LOCK = 0,
      READ_LOCK = 1,
      WRITE_LOCK = 2
    };

    static model_enum from_string(const std::string& str) {
      if(str == "edge") return EDGE_CONSISTENCY;
      else if(str == "full") return FULL_CONSISTENCY;
      else if(str == "vertex") return VERTEX_CONSISTENCY;
      else {
        logstream(LOG_FATAL) 
          << "Invalid consistency model \"" << str << "\"!  "
          << "Valid consistency models include {vertex, edge, full}."
          << std::endl;
      }
      return FULL_CONSISTENCY;
    }

  };





}; // end of graphlab namespace
#endif 