/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "EulerAngles.h"

namespace MbD {


    template<typename T>
    void EulerAngles<T>::setRotOrder(int i, int j, int k)
    {
        rotOrder = std::make_shared<FullColumn<int>>(3);
        rotOrder->at(0) = i;
        rotOrder->at(1) = j;
        rotOrder->at(2) = k;
    }
    template<typename T>
    void EulerAngles<T>::initialize()
    {
        assert(false);
    }
    // type-specific 'initialize' versions specifically created for Windows compiler builds
    // it is not appropriate to actually call either of them.
    template<>
    void EulerAngles<double>::initialize()
    {
        assert(false);
    }
    template<>
    void EulerAngles<std::shared_ptr<MbD::Symbolic>>::initialize()
    {
        assert(false);
    }

    template<>
    void EulerAngles<Symsptr>::calc()
    {
        cA = std::make_shared<FullColumn<FMatDsptr>>(3);
        for (int i = 0; i < 3; i++)
        {
            auto axis = rotOrder->at(i);
            auto angle = this->at(i)->getValue();
            if (axis == 1) {
                cA->atiput(i, FullMatrixDouble::rotatex(angle));
            }
            else if (axis == 2) {
                cA->atiput(i, FullMatrixDouble::rotatey(angle));
            }
            else if (axis == 3) {
                cA->atiput(i, FullMatrixDouble::rotatez(angle));
            }
            else {
                throw std::runtime_error("Euler angle rotation order must be any permutation of 1,2,3 without consecutive repeats.");
            }
        }
        aA = cA->at(0)->timesFullMatrix(cA->at(1)->timesFullMatrix(cA->at(2)));
    }
    template<>
    void EulerAngles<double>::calc()
    {
        cA = std::make_shared<FullColumn<FMatDsptr>>(3);
        for (int i = 0; i < 3; i++)
        {
            auto axis = rotOrder->at(i);
            auto angle = this->at(i);
            if (axis == 1) {
                cA->atiput(i, FullMatrixDouble::rotatex(angle));
            }
            else if (axis == 2) {
                cA->atiput(i, FullMatrixDouble::rotatey(angle));
            }
            else if (axis == 3) {
                cA->atiput(i, FullMatrixDouble::rotatez(angle));
            }
            else {
                throw std::runtime_error("Euler angle rotation order must be any permutation of 1,2,3 without consecutive repeats.");
            }
        }
        aA = cA->at(0)->timesFullMatrix(cA->at(1)->timesFullMatrix(cA->at(2)));
    }
    // the generic version should never be called; only the specific types above
    template<typename T>
    void EulerAngles<T>::calc()
    {
        assert(false);
    }
    // type-specific helper functions
    std::shared_ptr<EulerAnglesDot<std::shared_ptr<MbD::Symbolic>>> differentiateWRT(EulerAngles<std::shared_ptr<MbD::Symbolic>>& ref, std::shared_ptr<MbD::Symbolic> var)
    {
        auto derivatives = std::make_shared<EulerAnglesDot<std::shared_ptr<MbD::Symbolic>>>();
        std::transform(ref.begin(), ref.end(), derivatives->begin(),
                       [var](std::shared_ptr<MbD::Symbolic> term) { return term->differentiateWRT(var); }
        );
        derivatives->aEulerAngles = &ref;
        return derivatives;
    }

    // instantiations for two specific types:
    template class EulerAngles<std::shared_ptr<MbD::Symbolic>>;
    template class EulerAngles<double>;
}

