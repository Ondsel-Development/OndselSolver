#pragma once
#include <memory>
#include <vector>

#include "CartesianFrame.h"
#include "Part.h"
#include "MarkerFrame.h"
#include "EulerConstraint.h"
#include "AbsConstraint.h"
#include "FullColumn.h"

namespace MbD {
	class Part;
	class MarkerFrame;

	class PartFrame : public CartesianFrame
	{
		//ToDo: part iqX iqE qX qE qXdot qEdot qXddot qEddot aGeu aGabs markerFrames 
	public:
		PartFrame();

		void setqX(FullColumn<double>* x);
		FullColumn<double>* getqX();
		void setqE(FullColumn<double>* x);
		FullColumn<double>* getqE();
		void setPart(std::shared_ptr<Part> x);
		std::shared_ptr<Part> getPart();
		void addMarkerFrame(std::shared_ptr<MarkerFrame> x);

		std::weak_ptr<Part> part;
		int iqX, iqE;	//Position index of frame variables qX and qE in system list of variables
		FullColumn<double>* qX = new FullColumn<double>(3);
		FullColumn<double>* qE = new FullColumn<double>(4);
		std::shared_ptr<EulerConstraint> aGeu;
		std::vector<std::shared_ptr<AbsConstraint>> aGabs;
		std::vector<std::shared_ptr<MarkerFrame>> markerFrames;
	};
}

