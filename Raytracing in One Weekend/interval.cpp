#include "interval.h"


Interval::Interval() {
	(*this).m_min = +infinity;
	(*this).m_max = -infinity;
}

Interval::Interval(double min, double max) {
	(*this).m_min = min;
	(*this).m_max = max;
}

double Interval::getSize() const {
	return (*this).m_max - (*this).m_min;
}

bool Interval::containsInterval(double x) const {
	return (*this).m_min <= x && x <= (*this).m_max;
}

bool Interval::surroundsInterval(double x) const {
	return (*this).m_min < x && x < (*this).m_max;
}
