// \file   bridge-dynamic-static.cc
// \author Tristan Carel
// Mail	   <mail@tristan-carel.com>
//
// Started on  Tue May 16 15:54:32 2006 Tristan Carel
// Last update Sat Aug 26 15:33:28 2006 Tristan Carel
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

// This program tackles about:
// - bridge between buildtime and runtime.
// - type lists

#include <stdexcept>

namespace typelist
{
  /// Terminal element of the list.
  struct NullType {};

  /// Generic type list.
  template <typename T, typename U>
  struct List
  {
    /// The current element.
    typedef T	head;
    /// The end of the list.
    typedef U	tail;

  };

  // To ease instanciation...
#define TLIST_1(T1) typelist::List<T1, typelist::NullType>
#define TLIST_2(T1, T2) typelist::List<T1, TLIST_1(T2) >
#define TLIST_3(T1, T2, T3) typelist::List<T1, TLIST_2(T2, T3) >
  // ...


  /** Bridge from the wonderful templated world to the ugly dynamic one.
   **
   ** This class allow you to apply a functor to typelist's elements.
   **
   ** \param List those defined in the `typelist' namespace.
   ** \param Functor an simple template object, which implement the
   ** following method:
   ** \code
   ** void operator() ();
   ** \endcode
   */
  template <class List, template <typename> class Functor>
  class Map
  {

  public:
    /// Apply the functor only to the nth element of the list.
    static void exec  (int n) { map_ith_<0, List, Functor> :: call (n); }

    /// Apply the functor on all element of the list.
    static void exec ()
    {
      Functor<typename List::head> fun; fun (); // functor instanciation/call
      Map<typename List::tail, Functor> :: exec (); // recursive call
    }

  private:
    /** Look for a specific element, and apply the functor on this type
     ** when found.
     ** \exception std::out_of_range if thrown when the end of list if reached.
     */
    template <int N_, class List_, template <typename> class Functor_>
    struct map_ith_
    {
      static void call (int t)
      {
        if (N_ == t)
        {
          Functor_<typename List_::head> fun; // functor instanciation
          fun (); // functor call
        }
        else map_ith_<N_ + 1, typename List_::tail, Functor_> :: call(t);
      }
    };

    /// The terminal case
    template <int N_, template <typename> class Functor_>
    struct map_ith_<N_, typelist::NullType, Functor_>
    {
      static void call (int) { throw std::out_of_range ("End of list."); }
    };

  };

  template <template <typename> class Functor>
  struct Map<NullType, Functor>
  {
    static void exec () {};
  };

} // namespace typelist




// Specify list of functor you want to apply on you typelists!
namespace functor
{
  // call the static method render of its template parameter.
  template <class T>
  struct StaticRenderer
  {
    void operator ()() { T::render (); }
  };
} // namespace functor




// -- TESTS --------------------
#include <iostream>

namespace test
{

  // Because to borring without
#define DECLARE_CLASS(CLASS)                                \
struct CLASS                                                \
{                                                           \
  static void render () { std::cout << #CLASS "::render()"  \
                                    << std::endl;}          \
}
  DECLARE_CLASS(foo);
  DECLARE_CLASS(bar);
  DECLARE_CLASS(kikookikoolol);
#undef DECLARE_CLASS

  /** A wonderful list of 3 differents types
   ** Each of them has a static method named `render' */
  typedef TLIST_3(foo, bar, kikookikoolol)			MyTypeList;

  /** Here we define a typelist::Map which is designed to applied
   ** the static method `render' on the typelist.
   */
  typedef typelist::Map<MyTypeList, functor::StaticRenderer>	TListRenderer;

} // namespace test

using namespace test;


/// The most complete test suite I've ever written :)
int	main ()
{
  TListRenderer :: exec (1);
  TListRenderer :: exec (2);
  TListRenderer :: exec (0);
  try
    {
      TListRenderer :: exec (12);
    }
  catch (std::exception& e)
    {
      std::cout << e.what () << std::endl;
    }

  // apply the functor of each element.
  TListRenderer :: exec ();
}
