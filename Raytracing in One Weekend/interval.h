#ifndef INTERVAL_H
#define INTERVAL_H


class Interval {
public:
	Interval() {
		(*this).m_min = +infinity;
		(*this).m_max = -infinity;
	}
	Interval(double min, double max) {
		(*this).m_min = min;
		(*this).m_max = max;
	}

	double getSize() const {
		return (*this).m_max - (*this).m_min;
	}
	double getMax() const {
		return (*this).m_max;
	}
	double getMin() const {
		return (*this).m_min;
	}

	bool containsInterval(double x) const {
		return (*this).m_min <= x && x <= (*this).m_max;
	}

	bool surroundsInterval(double x) const {
		return (*this).m_min < x && x < (*this).m_max;
	}

public:
	static const Interval empty, universe;

private:
	double m_min, m_max;
};


const Interval Interval::empty = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);

#endif