/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "FullVector.h"
#include "FullMatrix.ref.h"
#include "FullRow.ref.h"

namespace MbD {

	template<typename T>
	class FullRow : public FullVector<T>
	{
	public:
		FullRow() : FullVector<T>() {}
		FullRow(std::vector<T> vec) : FullVector<T>(vec) {}
		FullRow(int count) : FullVector<T>(count) {}
		FullRow(int count, const T& value) : FullVector<T>(count, value) {}
		FullRow(typename std::vector<T>::const_iterator begin, typename std::vector<T>::const_iterator end) : FullVector<T>(begin, end) {}
		FullRow(std::initializer_list<T> list) : FullVector<T>{ list } {}
		FRowsptr<T> times(T a);
		FRowsptr<T> negated();
		FRowsptr<T> plusFullRow(FRowsptr<T> fullRow);
		FRowsptr<T> minusFullRow(FRowsptr<T> fullRow);
		T timesFullColumn(FColsptr<T> fullCol);
		T timesFullColumn(FullColumn<T>* fullCol);
		void equalSelfPlusFullRowTimes(FRowsptr<T> fullRow, double factor);
		void equalFullRow(FRowsptr<T> fullRow);
		FColsptr<T> transpose();
		FRowsptr<T> copy();
		void atiplusFullRow(int j, FRowsptr<T> fullRow);
		FMatDsptr transposeTimesFullRow(FRowDsptr fullRow);
		std::shared_ptr<FullRow<T>> clonesptr();
		//double dot(std::shared_ptr<FullColumn<T>> vec);
		//double dot(std::shared_ptr<FullRow<T>> vec);
		double dot(std::shared_ptr<FullVector<T>> vec);
		std::shared_ptr<FullVector<T>> dot(std::shared_ptr<std::vector<std::shared_ptr<FullColumn<T>>>> vecvec);

		
		std::ostream& printOn(std::ostream& s) const override;

        FRowsptr<double> timesTransposeFullMatrix(std::shared_ptr<FullMatrixDouble> fullMat);
        // FRowsptr<std::shared_ptr<FullMatrixDouble>> timesTransposeFullMatrixForFMFMDsptr(std::shared_ptr<FullMatrixFullMatrixDouble> fullMat);
        FRowsptr<double> timesFullMatrix(std::shared_ptr<FullMatrixDouble> fullMat);
    };

	template<>
	inline FRowDsptr FullRow<double>::times(double a)
	{
		int n = (int)this->size();
		auto answer = std::make_shared<FullRow<double>>(n);
		for (int i = 0; i < n; i++) {
			answer->at(i) = this->at(i) * a;
		}
		return answer;
	}
	template<typename T>
	inline FRowsptr<T> FullRow<T>::times(T a)
	{
        assert(a == a); // for warning suppression; this function never called when T != double
		assert(false);
	}
	template<typename T>
	inline FRowsptr<T> FullRow<T>::negated()
	{
		return this->times(-1.0);
	}
	template<typename T>
	inline FRowsptr<T> FullRow<T>::plusFullRow(FRowsptr<T> fullRow)
	{
		int n = (int) this->size();
		auto answer = std::make_shared<FullRow<T>>(n);
		for (int i = 0; i < n; i++) {
			answer->at(i) = this->at(i) + fullRow->at(i);
		}
		return answer;
	}
	template<typename T>
	inline FRowsptr<T> FullRow<T>::minusFullRow(FRowsptr<T> fullRow)
	{
		int n = (int) this->size();
		auto answer = std::make_shared<FullRow<T>>(n);
		for (int i = 0; i < n; i++) {
			answer->at(i) = this->at(i) - fullRow->at(i);
		}
		return answer;
	}
	template<typename T>
	inline T FullRow<T>::timesFullColumn(FColsptr<T> fullCol)
	{
		return this->timesFullColumn(fullCol.get());
	}
	template<typename T>
	inline T FullRow<T>::timesFullColumn(FullColumn<T>* fullCol)
	{
		auto answer = this->at(0) * fullCol->at(0);
		for (size_t i = 1; i < this->size(); i++)
		{
			answer += this->at(i) * fullCol->at(i);
		}
		return answer;
	}
	template<typename T>
	inline void FullRow<T>::equalSelfPlusFullRowTimes(FRowsptr<T> fullRow, double factor)
	{
		this->equalSelfPlusFullVectortimes(fullRow, factor);
	}
	template<typename T>
	inline void FullRow<T>::equalFullRow(FRowsptr<T> fullRow)
	{
		this->equalArrayAt(fullRow, 0);
	}
	template<typename T>
	inline FColsptr<T> FullRow<T>::transpose()
	{
		return std::make_shared<FullColumn<T>>(*this);
	}
	template<>
	inline FRowDsptr FullRow<double>::copy()
	{
		auto n = (int)this->size();
		auto answer = std::make_shared<FullRow<double>>(n);
		for (int i = 0; i < n; i++)
		{
			answer->at(i) = this->at(i);
		}
		return answer;
	}
	template<typename T>
	inline void FullRow<T>::atiplusFullRow(int j1, FRowsptr<T> fullRow)
	{
		for (size_t jj = 0; jj < fullRow->size(); jj++)
		{
			auto j = j1 + jj;
			this->at(j) += fullRow->at(jj);
		}
	}
	template<typename T>
	inline std::shared_ptr<FullRow<T>> FullRow<T>::clonesptr()
	{
		return std::make_shared<FullRow<T>>(*this);
	}
	template<typename T>
	inline double FullRow<T>::dot(std::shared_ptr<FullVector<T>> vec)
	{
		int n = (int)this->size();
		double answer = 0.0;
		for (int i = 0; i < n; i++) {
			answer += this->at(i) * vec->at(i);
		}
		return answer;
	}
	template<typename T>
	inline std::shared_ptr<FullVector<T>> FullRow<T>::dot(std::shared_ptr<std::vector<std::shared_ptr<FullColumn<T>>>> vecvec)
	{
		auto ncol = (int)this->size();
		auto nelem = vecvec->at(0)->size();
		auto answer = std::make_shared<FullVector<T>>(nelem);
		for (int k = 0; k < nelem; k++) {
			auto sum = 0.0;
			for (int i = 0; i < ncol; i++)
			{
				sum += this->at(i) * vecvec->at(i)->at(k);
			}
			answer->at(k) = sum;
		}
		return answer;
	}
	template<typename T>
	inline std::ostream& FullRow<T>::printOn(std::ostream& s) const
	{
		s << "FullRow{";
		s << this->at(0);
		for (size_t i = 1; i < this->size(); i++)
		{
			s << ", " << this->at(i);
		}
		s << "}";
		return s;
	};

}

