// Created on: 2013-12-20
// Created by: Denis BOGOLEPOV
// Copyright (c) 2013-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _BVH_BinnedBuilder_Header
#define _BVH_BinnedBuilder_Header

#include <BVH_Builder.hxx>

//! Stores parameters of single node bin (slice of AABB).
template<class T, int N>
struct BVH_Bin
{
  //! Creates new node bin.
  BVH_Bin() : Count (0) {}

  Standard_Integer Count; //!< Number of primitives in the bin
  BVH_Box<T, N>    Box;   //!< AABB of primitives in the bin
};

//! Performs building of BVH tree using binned SAH algorithm.
//! Number of Bins controls tree's quality (greater - better) in cost of construction time.
template<class T, int N, int Bins = 32>
class BVH_BinnedBuilder : public BVH_Builder<T, N>
{
public:

  //! Type for the array of bins of BVH tree node.
  typedef BVH_Bin<T, N> BVH_BinVector[Bins];

public:

  //! Creates binned SAH BVH builder.
  BVH_BinnedBuilder (const Standard_Integer theLeafNodeSize = 5,
                     const Standard_Integer theMaxTreeDepth = 32);

  //! Releases resources of binned SAH BVH builder.
  virtual ~BVH_BinnedBuilder();

protected:

  //! Builds BVH node for specified task info.
  virtual void BuildNode (BVH_Set<T, N>*         theSet,
                          BVH_Tree<T, N>*        theBVH,
                          const Standard_Integer theNode);

  //! Arranges node primitives into bins.
  virtual void GetSubVolumes (BVH_Set<T, N>*         theSet,
                              BVH_Tree<T, N>*        theBVH,
                              const Standard_Integer theNode,
                              BVH_BinVector&         theBins,
                              const Standard_Integer theAxis);

};

#include <BVH_BinnedBuilder.lxx>

#endif // _BVH_BinnedBuilder_Header
