#include <iostream>
using namespace std;

template <typename T>
class statisticalCalculation
{
private:
  T *data;
  int size;

public:
  statisticalCalculation(int size);
  ~statisticalCalculation();
  void sort();
  // statistical functions
  T findMedian();
  T findMin();
  T findMax();
  double findMean();
  T findSum();
  // utility functions
  void DisplayArray();
  void inputdata();
  void statisticsmenue();
};

template <typename T>
statisticalCalculation<T>::statisticalCalculation(int size)
{
  this->size = size;
  data = new T[size];
}

template <typename T>
statisticalCalculation<T>::~statisticalCalculation()
{
  delete[] data;
}

template <typename T>
void statisticalCalculation<T>::sort()
{
  bool flag = false;
  for (int i = 0; i < size - 1; i++)
  {
    for (int j = 0; j < size - i - 1; j++)
    {
      if (data[j] > data[j + 1])
      {
        swap(data[j], data[j + 1]);
        flag = true;
      }
    }

    if (flag == false)
    {
      break;
    }
  }
}

template <typename T>
T statisticalCalculation<T>::findMin()
{
  sort();
  return data[0];
}

template <typename T>
T statisticalCalculation<T>::findSum()
{
  T sum = 0;
  for (int i = 0; i < size; i++)
  {
    sum += data[i];
  }
  return sum;
}

template <typename T>
double statisticalCalculation<T>::findMean()
{
  return static_cast<double>(findSum()) / size;
}

template <typename T>
T statisticalCalculation<T>::findMax()
{
  sort();
  return data[size - 1];
}

template <typename T>
T statisticalCalculation<T>::findMedian()
{
  sort();
  if (size % 2 == 0)
  {
    int mid = size / 2;
    return (data[mid] + data[mid - 1]) / 2.0;
  }
  else
  {
    return data[size / 2];
  }
}

template <typename T>
void statisticalCalculation<T>::DisplayArray()
{
  for (int i = 0; i < size; i++)
  {
    cout << data[i] << " ";
  }
  cout << endl;
}

template <typename T>
void statisticalCalculation<T>::inputdata()
{
  cout << "Enter the size of the array: ";
  cin >> size;

  if (data != nullptr)
    delete[] data;

  data = new T[size];

  for (int i = 0; i < size; i++)
  {
    cout << "Enter element " << i + 1 << ": ";

    cin >> data[i];
    // cout << endl;
  }
}

template <typename T>
void statisticalCalculation<T>::statisticsmenue()
{
  int choice;
  do
  {
    cout << "Statistics Menu:\n\n";
    cout << "1 - Find Min\n\n";
    cout << "2 - Find Max\n\n";
    cout << "3 - Find Mean\n\n";
    cout << "4 - Find Median\n\n";
    cout << "5 - Find Sum\n\n";
    cout << "6 - Display Data\n\n";
    cout << "0 - Exit\n\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cout << endl;

    switch (choice)
    {
    case 1:
      cout << "Minimum Value: " << findMin() << endl;
      cout << endl;
      break;
    case 2:
      cout << "Maximum Value: " << findMax() << endl;
      cout << endl;
      break;
    case 3:
      cout << "Mean Value: " << findMean() << endl<<endl;
      cout << endl;
      break;
    case 4:
      cout << "Median Value: " << findMedian() << endl;
      cout << endl;
      break;
    case 5:
      cout << "Sum: " << findSum() << endl;
      cout << endl;
      break;
    case 6:
      DisplayArray();
      cout << endl;
      break;
    case 0:
      cout << "Exiting...\n";
      break;
    default:
      cout << "Invalid choice! Please try again.\n";
    }
  } while (choice != 0);
}

int main()
{
  statisticalCalculation<int> obj(0);
  obj.inputdata();
  obj.sort();
  cout << endl;
  cout << "Array Elements:\n";
  obj.DisplayArray();
  cout << endl;
  obj.statisticsmenue();
}
