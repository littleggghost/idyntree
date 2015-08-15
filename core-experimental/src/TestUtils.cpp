/*
 * Copyright (C) 2015 Fondazione Istituto Italiano di Tecnologia
 * Authors: Silvio Traversaro
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <iDynTree/Core/TestUtils.h>
#include <iDynTree/Core/Transform.h>

#include <iostream>

#include <cstdlib>
#include <cmath>

namespace iDynTree
{

void assertVectorAreEqual(const IVector& vec1, const IVector& vec2, double tol)
{
    if( vec1.size() != vec2.size() )
    {
        std::cerr << "assertVectorAreEqual failure: vec1 has size " << vec1.size()
                  << " while vec2 has size " << vec2.size() << std::endl;
        exit(EXIT_FAILURE);
    }

    for( unsigned int i = 0; i < vec1.size(); i++ )
    {
        if( fabs(vec1(i)-vec2(i)) >= tol )
        {
            std::cerr << "assertVectorAreEqual failure: element " << i << " of vec1 is " << vec1(i)
                  << " while of vec2 is " << vec2(i) << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

void assertMatrixAreEqual(const IMatrix& mat1, const IMatrix& mat2, double tol)
{
    if( mat1.rows() != mat2.rows() ||
        mat2.cols() != mat1.cols() )
    {
        std::cerr << "assertMatrixAreEqual failure: mat1 has size " << mat1.rows() << " " << mat1.cols()
                  << " while mat2 has size " << mat2.rows() << " " << mat2.cols() << std::endl;
        exit(EXIT_FAILURE);
    }

    for( unsigned int row = 0; row < mat2.rows(); row++ )
    {
        for( unsigned int col = 0; col < mat2.cols(); col++ )
        {
            if( fabs(mat1(row,col)-mat1(row,col)) >= tol )
            {
                std::cerr << "assertMatrixAreEqual failure: element " << row << " " << col << " of mat1 is " << mat1(row,col)
                  << " while of mat2 is " << mat2(row,col) << std::endl;
                exit(EXIT_FAILURE);
            }
        }
    }
}

void assertTransformsAreEqual(const Transform& trans1, const Transform& trans2, double tol)
{
    assertVectorAreEqual(trans1.getPosition(),trans2.getPosition(),tol);
    assertMatrixAreEqual(trans1.getRotation(),trans2.getRotation(),tol);
}


}