#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

double getSum(double* nums, int size)
{
	double sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += nums[i];
	}
	return sum;
}
double getMean(double* nums, int size)
{
	double sum = getSum(nums, size);
	return sum / size;
}

void merge(double arr[], int l, int m, int r)
{
	int n1 = m - l + 1;
	int n2 = r - m;

	// Create temp arrays
	double* L = new double[n1];
	double* R = new double[n2];


	// Copy data to temp arrays L[] and R[]
	for (int i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	// Merge the temp arrays back into arr[l..r]

	// Initial index of first subarray
	int i = 0;

	// Initial index of second subarray
	int j = 0;

	// Initial index of merged subarray
	int k = l;

	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements of L[], if there are any
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	// Copy the remaining elements of R[], if there are any
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}

	delete[] L;
	delete[] R;
}

// Source: https://www.geeksforgeeks.org/merge-sort/
// l is for left index and r is right index of the sub-arrayof arr to be sorted 
void mergeSort(double arr[], int l, int r)
{
	if (l >= r)
	{
		return; //returns recursively
	}
	int m = l + (r - l) / 2;
	mergeSort(arr, l, m);
	mergeSort(arr, m + 1, r);
	merge(arr, l, m, r);
}

// Assume that nums are already sorted
double getMedian(double* nums, int size)
{
	if (size % 2 != 0) return nums[size / 2];

	return (nums[(size - 1) / 2] + nums[size / 2]) / 2;
}

// Assume that nums are already sorted
string getModes(double* nums, int size)
{
	if (size == 0) return "{}";
	if (size == 1) return "{" + to_string(nums[0]) + "}";
	double* modes = new double[size];
	int freq = 1;
	int max_freq = 1;
	int mode_i = 0;
	for (int i = 0; i < size; i++)
	{
		if (nums[i] == nums[i + 1])
		{
			freq++;
		}
		else
		{
			if (freq > max_freq)
			{
				max_freq = freq;
				modes[0] = nums[i];
				mode_i = 1;
			}
			else if (freq == max_freq)
			{
				modes[mode_i] = nums[i];
				mode_i++;
			}
			freq = 1;
		}
	}

	string s = "{";
	for (int i = 0; i < mode_i - 1; i++)
	{
		s += to_string(modes[i]);
		s += ",";
	}
	s += to_string(modes[mode_i - 1]);
	s += "}";
	delete[] modes;
	return s;
}

double getVariance(double* nums, int size)
{
	double sum = getSum(nums, size);
	double mean = sum / size;
	double devSum = 0;
	for (int i = 0; i < size; i++)
	{
		devSum += pow(nums[i] - mean, 2);
	}
	double var = devSum / size;
	return var;
}

double getStandardDeviation(double* nums, int size)
{
	double stdev = sqrt(getVariance(nums, size));
	return stdev;
}

double getMeanAbsoluteDeviations(double* nums, int size)
{
	double mean = getMean(nums, size);
	double sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += abs(nums[i] - mean);
	}
	double mad = sum / size;
	return mad;
}

double getFirstQuartile(double* nums, int size)
{
	double Q1 = getMedian(nums, size / 2);
	return Q1;
}

double getSkewness(double* nums, int size)
{
	double sum = 0;
	double mean = getMean(nums, size);
	double stdev = getStandardDeviation(nums, size);
	double diff = 0;
	for (int i = 0; i < size; i++)
	{
		diff = (nums[i] - getMean(nums, size)) / stdev;
		sum += diff * diff * diff;
	}
	double skewness = sum / size;
	return skewness;
}

double getKurtosis(double* nums, int size)
{
	double sum = 0;
	double mean = getMean(nums, size);
	double stdev = getStandardDeviation(nums, size);
	double diff = 0;
	for (int i = 0; i < size; i++)
	{
		diff = (nums[i] - getMean(nums, size)) / stdev;
		sum += diff * diff * diff * diff;
	}
	double kurtosis = sum / size - 3;
	return kurtosis;
}

double getCovariance(double* x, double* y, int size)
{
	double mean_x = getMean(x, size);
	double mean_y = getMean(y, size);

	double sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += (x[i] - mean_x) * (y[i] - mean_y);
	}
	return sum / (size - 1);
}
double getPearsonCorrelationCoefficient(double* x, double* y, int size)
{
	double sum_x = 0, sum_y = 0, sum_xy = 0;
	double sqrsum_x = 0, sqrsum_y = 0;

	for (int i = 0; i < size; i++)
	{
		sum_x += x[i];
		sum_y += y[i];
		sum_xy += x[i] * y[i];
		sqrsum_x += x[i] * x[i];
		sqrsum_y += y[i] * y[i];
	}

	double pcc = (size * sum_xy - (sum_x * sum_y)) / sqrt((size * sqrsum_x - sum_x * sum_x) * (size * sqrsum_y - sum_y * sum_y));
	return pcc;
}

string getLinearRegressionEquation(double* x, double* y, int size)
{
	double mean_x = getMean(x, size);
	double mean_y = getMean(y, size);
	double stdev_x = getStandardDeviation(x, size);
	double stdev_y = getStandardDeviation(y, size);
	double r = getPearsonCorrelationCoefficient(x, y, size);
	double a = r * stdev_y / stdev_x;
	double b = mean_y - a * mean_x;
	string s = "y = " + to_string(a) + "x + " + to_string(b);
	return s;
}

int main(int argc, char* argv[])
{
	// Check for invalid number of arguments
	if (argc != 2)
	{
		cout << "Please provide exactly 1 file name for this program!";
		return 0;
	}
	char* file_name = argv[1];
	ifstream infile(file_name);
	// Check file cannot be opened
	if (!infile)
	{
		cout << "Cannot open file " << file_name << endl;
		return 0;
	}

	// Initialize arrays with initial max size
	int array_max_size = 5000;
	double* arr_x = new double[array_max_size] {};
	double* arr_y = new double[array_max_size] {};

	int size = 0;
	string line;
	double x, y;
	int matches;
	while (getline(infile, line))
	{
		matches = sscanf_s(line.c_str(), "%lf,%lf", &x, &y);
		// Skip the line if it's not valid
		if (matches != 2)
			continue;
		// Check if array size has reached its capacity
		if (size >= array_max_size)
		{
			// Double the array size
			array_max_size *= 2;
			// Create new temporary arrays
			double* new_arr_x = new double[array_max_size];
			double* new_arr_y = new double[array_max_size];
			// Copy values from original arrays to new arrays
			for (int i = 0; i < size; i++)
			{
				new_arr_x[i] = arr_x[i];
				new_arr_y[i] = arr_y[i];
			}
			// Deallocate memory of original arrays
			delete[] arr_x;
			delete[] arr_y;
			// Make the original array pointers point to new arrays
			arr_x = new_arr_x;
			arr_y = new_arr_y;
		}
		arr_x[size] = x;
		arr_y[size] = y;
		size++;
	}
	infile.close();

	// Do things without sort here
	double cov_xy = getCovariance(arr_x, arr_y, size);
	double r_xy = getPearsonCorrelationCoefficient(arr_x, arr_y, size);
	string lr_xy = getLinearRegressionEquation(arr_x, arr_y, size);

	// Sort arrays
	mergeSort(arr_x, 0, size - 1);
	mergeSort(arr_y, 0, size - 1);

	//Do things after sort here
	double median_x = getMedian(arr_x, size);
	double median_y = getMedian(arr_y, size);
	string mode_x = getModes(arr_x, size);
	string mode_y = getModes(arr_y, size);
	double var_x = getVariance(arr_x, size);
	double var_y = getVariance(arr_y, size);
	double stdev_x = getStandardDeviation(arr_x, size);
	double stdev_y = getStandardDeviation(arr_y, size);
	double mad_x = getMeanAbsoluteDeviations(arr_x, size);
	double mad_y = getMeanAbsoluteDeviations(arr_y, size);
	double q1_x = getFirstQuartile(arr_x, size);
	double q1_y = getFirstQuartile(arr_y, size);
	double skew_x = getSkewness(arr_x, size);
	double skew_y = getSkewness(arr_y, size);
	double kurt_x = getKurtosis(arr_x, size);
	double kurt_y = getKurtosis(arr_y, size);

	cout << "median_x= " << median_x << " - median_y= " << median_y << endl;

	cout << "mode_x=" << mode_x << " - mode_y=" << mode_y << endl;

	cout << "var_x= " << var_x << " - var_y= " << var_y << endl;

	cout << "stdev_x= " << stdev_x << " - stdev_y= " << stdev_y << endl;

	cout << "mad_x= " << mad_x << " - mad_y= " << mad_y << endl;

	cout << "q1_x= " << q1_x << " - q1_y= " << q1_y << endl;

	cout << "skew_x= " << skew_x << " - skew_y= " << skew_y << endl;

	cout << "kurt_x= " << kurt_x << " - kurt_y= " << kurt_y << endl;

	cout << "cov(x_y)= " << cov_xy << endl;

	cout << "r(x_y)= " << r_xy << endl;

	cout << lr_xy << endl;

	cout << "ASSIGNMENT 1 GROUP 26" << endl;
	cout << "s3818074, s3818074@rmit.edu.vn, Khai, Truong" << endl;
	cout << "s3878636, s3878636@rmit.edu.vn, Quy, Nguyen" << endl;
	cout << "s3877746, s3877746@rmit.edu.vn, Thuy, Mai" << endl;
	cout << "s3905273, s3905273@rmit.edu.vn, Nam, Pham" << endl;

	// Deallocate memory before program exits
	delete[] arr_x;
	delete[] arr_y;
	return 0;
}
