/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include <string>
#include <sstream> 

#include "FullVector.h"
#include "FullColumn.ref.h"
#include "FullRow.ref.h"
#include "FullMatrix.ref.h"
//#include "Symbolic.h"

namespace MbD {
	class Symbolic;

	template<typename T>
	class FullColumn : public FullVector<T>
	{
	public:
		FullColumn() : FullVector<T>() {}
		explicit FullColumn(std::vector<T> vec) : FullVector<T>(vec) {}
		explicit FullColumn(int count) : FullVector<T>(count) {}
		FullColumn(int count, const T& value) : FullVector<T>(count, value) {}
		FullColumn(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end) : FullVector<T>(begin, end) {}
		FullColumn(std::initializer_list<T> list) : FullVector<T>{ list } {}
		FColsptr<T> plusFullColumn(FColsptr<T> fullCol);
		// FColsptr<T> plusFullColumntimes(FColsptr<T> fullCol, double factor);
		FColsptr<T> minusFullColumn(FColsptr<T> fullCol);
		FColsptr<T> times(T a);
		FColsptr<T> negated();
		void atiputFullColumn(int i, FColsptr<T> fullCol);
		void atiplusFullColumn(int i, FColsptr<T> fullCol);
		void equalSelfPlusFullColumnAt(FColsptr<T> fullCol, int i);
		void atiminusFullColumn(int i, FColsptr<T> fullCol);
		void equalFullColumnAt(FColsptr<T> fullCol, int i);
		FColsptr<T> copy();
		FRowsptr<T> transpose();
		void atiplusFullColumntimes(int i, FColsptr<T> fullCol, T factor);
		T transposeTimesFullColumn(const FColsptr<T> fullCol);
		void equalSelfPlusFullColumntimes(FColsptr<T> fullCol, T factor);
		FColsptr<T> cross(FColsptr<T> fullCol);
		FColsptr<T> simplified();
		std::shared_ptr<FullColumn<T>> cloneFcSptr();
		double dotVec(std::shared_ptr<FullVector<T>> vec);
		std::shared_ptr<FullVector<T>> dot(std::shared_ptr<std::vector<std::shared_ptr<FullColumn<T>>>> vecvec);
		std::ostream& printOn(std::ostream& s) const override;
	};
    // the following "printOn" needs to be in the header for unknown reasons linker
    template<typename T>
    std::ostream& FullColumn<T>::printOn(std::ostream& s) const
    {
        s << "FullCol{";
        s << this->at(0);
        for (size_t i = 1; i < this->size(); i++)
        {
            s << ", " << this->at(i);
        }
        s << "}";
        return s;
    }
    template<typename T>
    std::shared_ptr<FullColumn<T>> FullColumn<T>::cloneFcSptr()
    {
        return std::make_shared<FullColumn<T>>(*this);
    }
    template<typename T>
    double FullColumn<T>::dotVec(std::shared_ptr<FullVector<T>> vec)
    {
        int n = (int)this->size();
        double answer = 0.0;
        for (int i = 0; i < n; i++) {
            answer += this->at(i) * vec->at(i);
        }
        return answer;
    }

}
