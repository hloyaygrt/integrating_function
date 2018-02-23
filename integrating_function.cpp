#include <iostream>
#include <functional>
#include <vector>
#include <math.h>
#include <iomanip>

template<typename T>
T input(const std::string& dialog = "") {
	std::cout << dialog << "\n";
	T tmp;
	std::cin >> tmp;
	return tmp;
}

int main() {
	std::vector<std::function<double(double)> > allFunctions = {
		[](double x) -> double {return sqrt(1.5 * x * x + 2.3) / (3. + sqrt(0.3 * x + 1.));},
		[](double x) -> double {return cos(0.3 * x + 0.5) / (1.8 + sin(x * x + 0.8));},
		[](double x) -> double {return 1. / sqrt(3. * x * x + 1.);},
		[](double x) -> double {return log10(x * x + 2.) / (x + 1.);}
	};

	std::vector<std::pair<double, double> > integralBounds = {
		{0.8, 2.4},
		{0.3, 1.1},
		{1.4, 2.2},
		{1.4, 2.2}
	};

	std::vector<std::function<double(int,double,double,std::function<double(double)>)> > integrationMethods = {
		// left
		[](int n, double a, double b, std::function<double(double)> f) -> double {
			double h = (b - a) / n, sum = 0;

			for (int i = 0; i <= n - 1; i++)
				sum += f(a + h * i);

			return h * sum;
		},
		// right
		[](int n, double a, double b, std::function<double(double)> f) -> double {
			double h = (b - a) / n, sum = 0;

			for (int i = 1; i <= n; i++)
				sum += f(a + h * i);

			return h * sum;
		},
		// central
		[](int n, double a, double b, std::function<double(double)> f) -> double {
			double h = (b - a) / n, sum = 0;

			for (int i = 0; i <= n - 1; i++)
				sum += f(a + h * i + h / 2.);

			return h * sum;
		},
		// trapeze method
		[](int n, double a, double b, std::function<double(double)> f) -> double {
			double h = (b - a) / n, sum = (f(a + 0 * h) + f(a + n * h)) / 2.;

			for (int i = 1; i <= n - 1; i++)
				sum += f(a + h * i);

			return sum * h;
		}
	};

	
	int type = input<int>("Choose function [1..4]");
	type--;
	
	int methType = input<int>("Choose method [1 - left, 2 - right, 3 - central, 4 - trapeze]");
	methType--;

	double eps = input<double>("Choose epsilon");

	double previousIntegral, currentIntegral;
	for (int n = 1;; n += 10) {

		currentIntegral = integrationMethods[methType](
			n, integralBounds[type].first, integralBounds[type].second, allFunctions[type]
		);

		if (n != 1 && fabs(currentIntegral - previousIntegral) <= eps) {
			std::cout << std::fixed << std::setprecision(10) << currentIntegral << "\n";
			return 0;
		}

		previousIntegral = currentIntegral;
	}
	return 0;
}