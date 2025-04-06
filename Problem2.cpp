#include <bits/stdc++.h>
using namespace std;

int main  (){
    int first, second;

    // Taking the first polynomial
    cout  << "Order of first polynomial: \n";
    cin >> first;
    auto* arr1 = new int[first+2];
    cout << "Enter polynomial: \n";
    for (int i = 0; i < first +2; i++) cin >> arr1[first+1 -i];

    // Taking the second polynomial
    cout  << "\nOrder of second polynomial: \n";
    cin >> second;
    auto* arr2 = new int[second+2];
    cout << "Enter polynomial: ";
    for (int i = 0; i < second+2; i++) cin >> arr2[second+1 -i];

    // Taking the size of the biggest polynomial
    int maxorder = max(first,second);
    int* sum =  new int[maxorder+2] ();
    int* diff = new int[maxorder+2]();

    // Getting the sum for the 2 polynomials
    if (maxorder==second)
    {
        for (int i = 0; i < second+2; i++)
        {
            sum[i] = arr2[i];
        }
        for (int i = 0; i < first+2; i++)
        {
            sum[i+(second-first)] += arr1[i];
        }

    }
    else
    {
        for (int i = 0; i < first+2; i++)
        {
            sum[i] = arr1[i];
        }
        for (int i = 0; i < second+2; i++)
        {
            sum[i+(first-second)] += arr2[i];
        }
    }

    // Getting the difference for the 2 polynomials
    for (int i = 0; i < second+2; i++)
    {
        diff[i+(maxorder-second)] = arr2[i] ;
    }
    for (int i = 0; i < first+2; i++)
    {
        diff[i+(maxorder-first)] -= arr1[i] ;
    }
        //  Printing the first polynomial
    int temp1 = first;

    cout << "\nFirst polynomial: ";
    if (arr1[0]==1) cout << "x^" << temp1--;
    else if (arr1[0]==-1) cout << "-x^" << temp1--;
    else cout << arr1[0] << "x^" << temp1--;

    for (int i=1 ; i < first ; i++)
    {
        if (arr1[i] == 0 )
        {
            temp1 --;
            continue;
        }
        if (arr1[i] < 0)
        {
            if (temp1 == 1)
            {
                if (arr1[i] == -1) cout << " - x" ;
                else cout << " - " << -arr1[i] << "x";
            }
            else if (arr1[i] == -1) cout << " - x^" << temp1--;
            else cout << " - " << -arr1[i] << "x^" << temp1--;
        }
        else
        {
            if (temp1 == 1)
            {
                if (arr1[i] == 1) cout << " + x" ;
                else cout << " + " << arr1[i] << "x";
            }
            else if (arr1[i] == 1) cout << " + x^" << temp1--;
            else cout << " + " << arr1[i] << "x^" << temp1--;
        }
    }
    if (arr1[first] == 0) cout << " = " <<arr1[first+1] <<"\n";
    else if (arr1[first] < 0) cout << " - " << -arr1[first] << " = " << arr1[first+1] << "\n";
    else cout << " + " << arr1[first] << " = " << arr1[first+1] << "\n";

    //  Printing the second polynomial
    int temp2 = second;
    cout << "second polynomial: ";
    if (arr2[0]==1) cout << "x^" << temp2--;
    else if (arr2[0]==-1) cout << "-x^" << temp2--;
    else cout << arr2[0] << "x^" << temp2--;

    for (int i=1 ; i < second ; i++)
    {
        if (arr2[i] == 0 )
        {
            temp2 --;
            continue;
        }
        if (arr2[i] < 0)
        {
            if (temp2 == 1)
            {
                if (arr2[i] == -1) cout << " - x" ;
                else cout << " - " << -arr2[i] << "x";
            }
            else if (arr2[i] == -1) cout << " - x^" << temp2--;
            else cout << " - " << -arr2[i] << "x^" << temp2--;
        }
        else
        {
            if (temp2 == 1)
            {
                if (arr2[i] == 1) cout << " + x" ;
                else cout << " + " << arr2[i] << "x";
            }
            else if (arr2[i] == 1) cout << " + x^" << temp2--;
            else cout << " + " << arr2[i] << "x^" << temp2--;
        }
    }
    if (arr2[second] == 0) cout << " = " <<arr2[second+1] <<"\n";
    else if (arr2[second] < 0) cout << " - " << -arr2[second] << " = " << arr2[second+1] << "\n";
    else cout << " + " << arr2[second] << " = " << arr2[second+1] << "\n";

    //  Printing the sum polynomial

    int temp3 = maxorder ;

    cout << "\nSum of polynomials: ";
    if (sum[0]==1) cout << "x^" << temp3--;
    else if (sum[0]==-1) cout << "-x^" << temp3--;
    else if (sum[0] != 0)cout << sum[0] << "x^" << temp3--;
    else temp3--;
    for (int i=1 ; i < maxorder ; i++)
    {
        if (sum[i] == 0 )
        {
            temp3 --;
            continue;
        }
        if (sum[i] < 0)
        {
            if (temp3 == 1)
            {
                if (sum[i] == -1) cout << " - x" ;
                else cout << " - " << -sum[i] << "x";
            }
            else if (sum[i] == -1) cout << " - x^" << temp3--;
            else cout << " - " << -sum[i] << "x^" << temp3--;
        }
        else
        {
            if (temp3 == 1)
            {
                if (sum[i] == 1) cout << " + x" ;
                else cout << " + " << sum[i] << "x";
            }
            else if (sum[i] == 1) cout << " + x^" << temp3--;
            else cout << " + " << sum[i] << "x^" << temp3--;
        }
    }
    if (sum[maxorder] == 0) cout << " = " <<sum[maxorder+1] <<"\n";
    else if (sum[maxorder] < 0) cout << " - " << -sum[maxorder] << " = " << sum[maxorder+1] << "\n";
    else cout << " + " << sum[maxorder] << " = " << sum[maxorder+1] << "\n";

    //  Printing the Difference polynomial

    int temp4 = maxorder;

    cout << "\nDifference of polynomials: ";
    if (diff[0]==1) cout << "x^" << temp4--;
    else if (diff[0]==-1) cout << "-x^" << temp4--;
    else if (diff[0] != 0)cout << diff[0] << "x^" << temp4--;
    else temp4--;
    for (int i=1 ; i < maxorder ; i++)
    {
        if (diff[i] == 0 )
        {
            temp4 --;
            continue;
        }
        if (diff[i] < 0)
        {
            if (temp4 == 1)
            {
                if (diff[i] == -1) cout << " - x" ;
                else cout << " - " << -diff[i] << "x";
            }
            else if (diff[i] == -1) cout << " - x^" << temp4--;
            else cout << " - " << -diff[i] << "x^" << temp4--;
        }
        else
        {
            if (temp4 == 1)
            {
                if (diff[i] == 1) cout << " + x" ;
                else cout << " + " << diff[i] << "x";
            }
            else if (diff[i] == 1) cout << " + x^" << temp4--;
            else cout << " + " << diff[i] << "x^" << temp4--;
        }
    }
    if (diff[maxorder] == 0) cout << " = " <<diff[maxorder+1] <<"\n";
    else if (diff[maxorder] < 0) cout << " - " << -diff[maxorder] << " = " << diff[maxorder+1] << "\n";
    else cout << " + " << diff[maxorder] << " = " << diff[maxorder+1] << "\n";


    // deleting the dynamically allocated arrays to avoid memory leaks
    delete[] arr1;
    delete[] arr2;
    delete[] sum;
    delete[] diff;
}