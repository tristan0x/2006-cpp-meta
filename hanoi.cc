// File    hanoi.cc
// Made by Tristan Carel
// Mail    <mail@tristan-carel.com>
//
// Started on  Sat Aug 26 17:47:00 2006 Tristan Carel
// Last update Sun Aug 27 11:16:48 2006 Tristan Carel
//
// Copyright (C) 2006 Tristan Carel
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//

#include <iostream>

namespace typelist
{
  /// Terminal element of the list.
  struct NullType {};

  /// Movemement List
  template <int From, int To, class T>
  struct Move
  {
    static const int from = From;
    static const int to = To;
    typedef T next;
  };

#define CREATE_MOVE(from, to)		\
  typelist :: Move <from, to, typelist :: NullType>

  // --- List Concatenation --------------------------------------------------
  template <class List, class E> struct Concat;

  template <>
  struct Concat <NullType, NullType>
  {
    typedef NullType result;
  };

  template <class T>
  struct Concat <NullType, T>
  {
    typedef T result;
  };

  template <int From, int To, class T, class Next>
  struct Concat <Move <From, To, T>, Next>
  {
    typedef Move<From, To, typename Concat <T, Next>::result > result;
  };
  // --------------------------------------------------------------------------


  // --- Pretty Print ---------------------------------------------------------
  template <class T>
  struct Print
  {
    inline static void doit (std::ostream&) {}
  };


  template <>
  template <int From, int To, class Next>
  struct Print <Move<From, To, Next> >
  {
    inline static
    void	doit (std::ostream& ostr)
    {
      ostr <<  From << "-" << To << std::endl;
      Print<Next> :: doit (ostr);
    }
  };
  // --------------------------------------------------------------------------
} // namespace typelist

namespace hanoi
{
  /** Compute the Hanoi sequence at compile time. The result is the typedef
   ** \a result.
   ** The aim of the class is to move \a from elements from \a nfrom to \a nto
   ** We need to keep \a nmid as the intermediate tower id.
   */
  template <int nfrom, int nmid, int nto, int from>
  struct Compute
  {
    typedef typename typelist::Concat <
      typename Compute <nfrom, nto, nmid, from - 1> :: result,
      typelist::Move <nfrom, nto, typename Compute <nmid, nfrom,
						    nto, from -1> :: result> >
    ::result result;
  };

  template <>
  struct Compute <1, 2, 3, 1>
  {
    typedef CREATE_MOVE (1, 3) result;
  };

  template <>
  struct Compute <1, 3, 2, 1>
  {
    typedef CREATE_MOVE (1, 2) result;
  };

  template <>
  struct Compute <2, 1, 3, 1>
  {
    typedef CREATE_MOVE (2, 3) result;
  };

  template <>
  struct
  Compute <2, 3, 1, 1>
  {
    typedef CREATE_MOVE (2, 1) result;
  };

  template <>
  struct
  Compute <3, 2, 1, 1>
  {
    typedef CREATE_MOVE (3, 1) result;
  };

  template <>
  struct
  Compute <3, 1, 2, 1>
  {
    typedef CREATE_MOVE (3, 2) result;
  };
} // namespace hanoi



int	main ()
{
  typedef hanoi::Compute<1, 2, 3, N> :: result  HanoiSequence;
  typelist :: Print < HanoiSequence > :: doit (std::cout);
}
