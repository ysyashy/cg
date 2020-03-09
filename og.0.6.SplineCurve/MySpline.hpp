#ifndef MY_SPLINES_HPP
#define MY_SPLINES_HPP

#include <vector>
#include <iostream>
#include "vec3.hpp"

class BSpline {
private:
	int _d;
	std::vector<Vec3> _ctrlPoints;
public:
	BSpline(int d = 2) { _d = d; }
	void setControlPoints(const std::vector<Vec3>& cps)
	{
		_ctrlPoints = cps;
		uA.resize(cps.size() + _d + 1);
		float step = 1.0f / (uA.size() - 1);
		for (int i = 0; i < uA.size(); i++) {
			uA[i] = i * step;
		}
	}
	bool isPrint = false;
	// unit test
	void unitTest()
	{
		glBegin(GL_LINES);
		Vec3 start = evaluation(0);
		glVertex3fv((float*)start);
		const int resolution = 1000;
		for (int i = 0; i < resolution; i++) {
			float u = float(i) / float(resolution - 1);
			Vec3 p = evaluation(u);
			glVertex3fv((float*)p);
			if (i < resolution - 1) {
				glVertex3fv((float*)p);
			}
			// if(!isPrint) std::cout << p << "\n";
		}
		isPrint = true;
		glEnd();
	}

	Vec3 deBoor(int k, float x)
	{
		//"""
		//	Evaluates S(x).

		//	Args
		//	----
		//	k : index of knot interval that contains x
		//	x : position
		//	t : array of knot positions, needs to be padded as described above
		//	c : array of control points
		//	p : degree of B - spline
		//	"""
		const std::vector<float>& t = uA;
		const std::vector<Vec3>& c = _ctrlPoints;
		int p = _d;

		Vec3 d[5];
		for (int i = 0; i < p + 1; i++) {
			d[i] = c[i + k - p];
		}
		// d = [c[j + k - p] for j in range(0, p + 1)];

		for (int r = 1; r < p + 1; r++) {
			for (int j = p; j > r - 1; j--) {
				float alpha = (x - t[j + k - p]) / (t[j + 1 + k - r] - t[j + k - p]);
				d[j] = (1.0 - alpha) * d[j - 1] + alpha * d[j];
			}
		}
		return d[p];
	}


	Vec3 evaluation(float u)
	{
		Vec3 ret;
		auto count = _ctrlPoints.size();
		for (auto k = 0; k < count; k++) {
			float coDeBoor = Co_deBoor(u, k, _d);
			ret += (_ctrlPoints[k] * coDeBoor);
		}
		return ret;
	}

private:
	std::vector<float> uA;

	float Co_deBoor(float u, int k, int d)
	{
		if (d == 1) {
			return (uA[k] <= u && u <= uA[k + 1]) ? 1 : 0;
		}
		// _d;
		float Den1 = uA[k + d - 1] - uA[k];
		float Den2 = uA[k + d] - uA[k + 1];
		float Eq1 = 0, Eq2 = 0;
		if (Den1 > 0) {
			Eq1 = (u - uA[k]) / Den1 * Co_deBoor(u, k, d - 1);
		}
		if (Den2 > 0) {
			Eq2 = (uA[k + d] - u) / Den2 * Co_deBoor(u, k + 1, d - 1);
		}
		return Eq1 + Eq2;
	}

};

#endif // SPLINES_HPP