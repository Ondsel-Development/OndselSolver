/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "FullMatrix.h"

using namespace MbD;

template<typename T>
inline FMatsptr<T> FullMatrix<T>::tildeMatrix(FColDsptr col)
{
    //"tildeMatrix is skew symmetric matrix related to angular velocity and cross product."
    if (col->size() != 3) throw std::runtime_error("Column is not of dimension 3");
    auto tilde = std::make_shared<FullMatrix<double>>(3, 3);
    auto c0 = col->at(0);
    auto c1 = col->at(1);
    auto c2 = col->at(2);
    tilde->atijput(0, 0, 0.0);
    tilde->atijput(1, 1, 0.0);
    tilde->atijput(2, 2, 0.0);
    tilde->atijput(1, 2, -c0);
    tilde->atijput(0, 2, c1);
    tilde->atijput(0, 1, -c2);
    tilde->atijput(1, 0, c2);
    tilde->atijput(2, 0, -c1);
    tilde->atijput(2, 1, c0);
    return tilde;
}
template<>
inline void FullMatrix<double>::zeroSelf()
{
    for (int i = 0; i < this->size(); i++) {
        this->at(i)->zeroSelf();
    }
}
template<typename T>
inline FColsptr<T> FullMatrix<T>::column(int j) {
    int n = (int)this->size();
    auto answer = std::make_shared<FullColumn<T>>(n);
    for (int i = 0; i < n; i++) {
        answer->at(i) = this->at(i)->at(j);
    }
    return answer;
}
template<>
inline FMatDsptr FullMatrix<double>::times(double a)
{
    int m = this->nrow();
    auto answer = std::make_shared<FullMatrix<double>>(m);
    for (int i = 0; i < m; i++) {
        answer->at(i) = this->at(i)->times(a);
    }
    return answer;
}
template<typename T>
inline FMatsptr<T> FullMatrix<T>::times(T a)
{
    assert(false);
}
template<typename T>
inline FMatsptr<T> FullMatrix<T>::transposeTimesFullMatrix(FMatsptr<T> fullMat)
{
    return this->transpose()->timesFullMatrix(fullMat);
}
template<typename T>
inline FMatsptr<T> FullMatrix<T>::plusFullMatrix(FMatsptr<T> fullMat)
{
    int n = (int)this->size();
    auto answer = std::make_shared<FullMatrix<T>>(n);
    for (int i = 0; i < n; i++) {
        answer->at(i) = this->at(i)->plusFullRow(fullMat->at(i));
    }
    return answer;
}
template<typename T>
inline FMatsptr<T> FullMatrix<T>::minusFullMatrix(FMatsptr<T> fullMat)
{
    int n = (int)this->size();
    auto answer = std::make_shared<FullMatrix<T>>(n);
    for (int i = 0; i < n; i++) {
        answer->at(i) = this->at(i)->minusFullRow(fullMat->at(i));
    }
    return answer;
}
template<typename T>
inline FMatsptr<T> FullMatrix<T>::transpose()
{
    int nrow = this->nrow();
    auto ncol = this->ncol();
    auto answer = std::make_shared<FullMatrix<T>>(ncol, nrow);
    for (int i = 0; i < nrow; i++) {
        auto& row = this->at(i);
        for (int j = 0; j < ncol; j++) {
            answer->at(j)->at(i) = row->at(j);
        }
    }
    return answer;
}
template<typename T>
inline FMatsptr<T> FullMatrix<T>::negated()
{
    return this->times(-1.0);
}
template<typename T>
inline void FullMatrix<T>::symLowerWithUpper()
{
    int n = (int)this->size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            this->at(j)->at(i) = this->at(i)->at(j);
        }
    }
}
template<typename T>
inline void FullMatrix<T>::atijput(int i, int j, T value)
{
    this->at(i)->atiput(j, value);
}
template<typename T>
inline void FullMatrix<T>::atijputFullColumn(int i1, int j1, FColsptr<T> fullCol)
{
    for (int ii = 0; ii < fullCol->size(); ii++)
    {
        this->at(i1 + ii)->at(j1) = fullCol->at(ii);
    }
}
template<typename T>
inline void FullMatrix<T>::atijplusFullRow(int i, int j, FRowsptr<T> fullRow)
{
    this->at(i)->atiplusFullRow(j, fullRow);
}
template<typename T>
inline void FullMatrix<T>::atijplusNumber(int i, int j, T value)
{
    auto rowi = this->at(i);
    rowi->at(j) += value;
}
template<typename T>
inline void FullMatrix<T>::atijminusNumber(int i, int j, T value)
{
    auto rowi = this->at(i);
    rowi->at(j) -= value;
}
template<typename T>
inline FMatsptr<T> FullMatrix<T>::copy()
{
    auto m = (int)this->size();
    auto answer = std::make_shared<FullMatrix<T>>(m);
    for (int i = 0; i < m; i++)
    {
        answer->at(i) = this->at(i)->copy();
    }
    return answer;
}
template<typename T>
inline FullMatrix<T> FullMatrix<T>::operator+(const FullMatrix<T> fullMat)
{
    int n = (int)this->size();
    auto answer = FullMatrix<T>(n);
    for (int i = 0; i < n; i++) {
        answer.at(i) = this->at(i)->plusFullRow(fullMat.at(i));
    }
    return answer;
}
template<typename T>
inline FColsptr<T> FullMatrix<T>::transposeTimesFullColumn(FColsptr<T> fullCol)
{
    auto sptr = std::make_shared<FullMatrix<T>>(*this);
    return fullCol->transpose()->timesFullMatrix(sptr)->transpose();
}
template<typename T>
inline void FullMatrix<T>::magnifySelf(T factor)
{
    for (int i = 0; i < this->size(); i++) {
        this->at(i)->magnifySelf(factor);
    }
}
template<typename T>
inline T FullMatrix<T>::trace()
{
    T trace = 0.0;
    for (int i = 0; i < this->size(); i++)
    {
        trace += this->at(i)->at(i);
    }
    return trace;
}
template<typename T>
inline bool FullMatrix<T>::isDiagonal()
{
    auto m = this->nrow();
    auto n = this->ncol();
    if (m != n) return false;
    for (int i = 0; i < m; i++)
    {
        auto rowi = this->at(i);
        for (int j = 0; j < n; j++)
        {
            if (i != j && rowi->at(j) != 0) return false;
        }
    }
    return true;
}
template<typename T>
inline bool FullMatrix<T>::isDiagonalToWithin(double ratio)
{
    double maxMag = this->maxMagnitude();
    auto tol = ratio * maxMag;
    auto nrow = this->nrow();
    if (nrow == this->ncol()) {
        for (int i = 0; i < 3; i++)
        {
            for (int j = i + 1; j < 3; j++)
            {
                if (std::abs(this->at(i)->at(j)) > tol) return false;
                if (std::abs(this->at(j)->at(i)) > tol) return false;
            }
        }
        return true;
    }
    else {
        return false;
    }
}
template<typename T>
inline std::shared_ptr<DiagonalMatrix<T>> FullMatrix<T>::asDiagonalMatrix()
{
    int nrow = this->nrow();
    auto diagMat = std::make_shared<DiagonalMatrix<T>>(nrow);
    for (int i = 0; i < nrow; i++)
    {
        diagMat->atiput(i, this->at(i)->at(i));
    }
    return diagMat;
}
template<typename T>
inline void FullMatrix<T>::conditionSelfWithTol(double tol)
{
    for (auto row : *this) {
        row->conditionSelfWithTol(tol);
    }
}
template<typename T>
inline FColsptr<T> FullMatrix<T>::timesFullColumn(FColsptr<T> fullCol)
{
    return this->timesFullColumn(fullCol.get());
}
template<typename T>
inline FColsptr<T> FullMatrix<T>::timesFullColumn(FullColumn<T>* fullCol)
{
    //"a*b = a(i,j)b(j) sum j."
    auto nrow = this->nrow();
    auto answer = std::make_shared<FullColumn<T>>(nrow);
    for (int i = 0; i < nrow; i++)
    {
        answer->at(i) = this->at(i)->timesFullColumn(fullCol);
    }
    return answer;
}
