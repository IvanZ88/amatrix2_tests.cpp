// amatrix2_test.cpp
// Тесты для функций, определённых в amatrix2.hpp.
#include "amatrix2.hpp"
#include <sstream>
#include <cassert>

using namespace std;


class Amatrix2_test
{
  using Num = double;
  using Row = Matrix_row<Num>;
  using Mtx = Matrix<Num>;


  static int test_readln()
  {
    // Прочитаем вектор.
    istringstream is("4 5 6.5 -1.125");
    Row row;
    readln(is, row);
    if (row != Row{ 4., 5., 6.5, -1.125 })
      return 1;

    // Прочитаем две матрицы подряд.
    is.clear();
    is.str
      (
      "0.5   1.5   2.5  3.5\n"
      "6.1  -0.1\n"
      "8.2\n\n"
      "12   42\n"
      "16  -12\n\n"
      );

    Mtx mtx, mtx2;
    readln(is, mtx);
    readln(is, mtx2);
    if (rows(mtx) != 3 || cols(mtx) != 4)
      return 2;

    if (mtx != Mtx
      {
        Row{ 0.5,  1.5, 2.5, 3.5 },
        Row{ 6.1, -0.1, 0.0, 0.0 },
        Row{ 8.2,  0.0, 0.0, 0.0 }
      })
      return 3;

    if (mtx2 != Mtx
      {
        Row{ 12.,  42. },
        Row{ 16., -12. }
      })
      return 4;
    
    return 0;
  }


  static int test_writeln()
  {
    // Запишем вектор.
    ostringstream os;
    writeln(os, Row{ -1.5, 0., 2.7 });
    if (os.str() != " -1.5 0 2.7\n")
      return 1;

    // Запишем матрицу.
    os.str("");
    writeln(os, Mtx
      {
        Row{ 10.1, 100, 0 },
        Row{ 0, -1, 42.5 }
      });

    if (os.str() !=
      " 10.1 100 0\n"
      " 0 -1 42.5\n\n")
      return 2;

    return 0;
  }


  static int test_reshape_and_fill()
  {
    Mtx mtx;
    reshape(mtx, 10, 100);
    if (rows(mtx) != 10 || rows(mtx) != mtx.size())
      return 1;
    if (cols(mtx) != 100 || cols(mtx) != mtx[0].size())
      return 2;
    
    fill(mtx, 42.);
    if (!consists_of(mtx, 42.))
      return 3;

    return 0;
  }


  static int test_matrix_creation()
  {
    // matrix (1)
    {
      auto mtx = matrix(9, 4, 111.);
      if (rows(mtx) != 9 || cols(mtx) != 4)
        return 1;
      if (!consists_of(mtx, 111.))
        return 2;
    }

    // matrix (2)
    {
      double arr[2][4] =
      {
        { 1., 2., 3., 4. },
        { 4., 1., 3., 2. }
      };

      auto mtx = matrix(arr);
      if (rows(mtx) != 2 || cols(mtx) != 4)
        return 3;
      if (mtx != Mtx
        {
          Row{ 1., 2., 3., 4. },
          Row{ 4., 1., 3., 2. }
        })
        return 3;
    }

    // diagonal
    {
      const Mtx dref
      {
        Row { 1., 0.,  0.,  0. },
        Row { 0., 2.,  0.,  0. },
        Row { 0., 0., 42.,  0. },
        Row { 0., 0.,  0., 23. }
      };

      double darr[4] = { 1., 2., 42., 23. };
      if (diagonal(darr) != dref)
        return 4;

      if (diagonal({ 1., 2., 42., 23. }) != dref)
        return 5;

      if (diagonal(Row{ 1., 2., 42., 23. }) != dref)
        return 6;

      if (diagonal({ 1., 1., 1. }) != diagonal(3, 1.))
        return 7;
    }

    return 0;
  }

public:
  static int test_all()
  {
    int result = 0;
    // Здесь именно =, а не ==.
    if (result = test_readln())
      return 100 + result;
    if (result = test_writeln())
      return 200 + result;
    if (result = test_reshape_and_fill())
      return 300 + result;
    if (result = test_matrix_creation())
      return 400 + result;

    return 0;
  }

  Amatrix2_test()
  {
    assert(test_all() == 0);
  }
};

const Amatrix2_test test_it;
