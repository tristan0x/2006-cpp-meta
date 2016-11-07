// File    ackermann-naive.hh
// Made by Tristan Carel
// Mail    <tristan.carel@gmail.com>
//
// Started on  Thu Nov 24 05:27:25 2005 Tristan Carel
// Last update Thu Nov 24 05:45:10 2005 ken
//
// Copyright (C) 2005 Tristan Carel
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

#ifndef   __ACKERMANN_NAIVE_HH__
# define   __ACKERMANN_NAIVE_HH__

typedef unsigned long long ull;

struct ackermann_naive
{
  ull operator() (ull m, ull n);
};

#endif // ndef __ACKERMANN_NAIVE_HH__
