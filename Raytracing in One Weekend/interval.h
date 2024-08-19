#ifndef INTERVAL_H
#define INTERVAL_H


class Interval {
public:
	Interval();
	Interval(double min, double max);

	double getSize() const;
	double getMax() const;
	double getMin() const;

	bool containsInterval(double x) const;

	bool surroundsInterval(double x) const;

public:
	static const Interval empty, universe;

private:
	double m_min, m_max;
};


const Interval Interval::empty = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);

#endif