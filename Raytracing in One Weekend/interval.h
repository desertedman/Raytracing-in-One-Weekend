#ifndef INTERVAL_H
#define INTERVAL_H


class Interval {
public:
	Interval() {
		mMin = +infinity;
		mMax = -infinity;
	}

	Interval(double min, double max) {
		mMin = min;
		mMax = max;
	}


	double getSize() const {
		return mMax - mMin;
	}

	double getMax() const {
		return mMax;
	}

	double getMin() const {
		return mMin;
	}


	bool containsInterval(double x) const {
		return mMin <= x && x <= mMax;
	}

	bool surroundsInterval(double x) const {
		return mMin < x && x < mMax;
	}


	double clampToInterval(double x) const {
		if (x < mMin) {
			return mMin;
		}

		if (x > mMax) {
			return mMax;
		}

		return x;
	}

public:
	static const Interval empty, universe;

private:
	double mMin, mMax;
};


const Interval Interval::empty = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);

#endif