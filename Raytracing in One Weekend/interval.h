#ifndef INTERVAL_H
#define INTERVAL_H


class Interval {
public:
	Interval() {
		m_Min = +infinity;
		m_Max = -infinity;
	}

	Interval(double min, double max) {
		m_Min = min;
		m_Max = max;
	}


	double getSize() const {
		return m_Max - m_Min;
	}

	double getMax() const {
		return m_Max;
	}

	double getMin() const {
		return m_Min;
	}


	bool containsInterval(double x) const {
		return m_Min <= x && x <= m_Max;
	}

	bool surroundsInterval(double x) const {
		return m_Min < x && x < m_Max;
	}


	double clampToInterval(double x) const {
		if (x < m_Min) {
			return m_Min;
		}

		if (x > m_Max) {
			return m_Max;
		}

		return x;
	}

public:
	static const Interval empty, universe;

private:
	double m_Min, m_Max;
};


const Interval Interval::empty = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);

#endif