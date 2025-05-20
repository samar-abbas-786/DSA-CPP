
#include <iostream>
#include <cmath> // Include cmath for pow function
#include <conio.h>
using namespace std;

int main()
{   
    
    float carrier_frequency, frequency_deviation;
    float resultant_carrier_frequency, resultant_frequency_deviation;
    float oscillator_frequency;
    float frequency_consraint_initial, frequency_consraint_final;
    int Multiplier;
    int x1 = 0, x2 = 0;
    float Fl;
    
    cout << "Enter initial Carrier Frequency(MHz) : ";
    cin >> carrier_frequency;
    cout << "Enter initial Frequency of Deviation(MHz) : ";
    cin >> frequency_deviation;
    cout << "Enter the required Carrier Frequency(MHz) : ";
    cin >> resultant_carrier_frequency;
    cout << "Enter the required Frequency of Deviation(MHz) : ";
    cin >> resultant_frequency_deviation;
    cout << "Enter the range of oscillator frequency(MHz) {Enter two value with a space in between} : ";
    cin >> frequency_consraint_initial ;
	cin >> frequency_consraint_final;
    cout << "Enter the Multiplier Factor(i.e. 2,3...) : " ;
    cin >> Multiplier;
    
    for(int i = 1; ; i++)
    {	
        Fl = (resultant_carrier_frequency - (resultant_frequency_deviation/frequency_deviation)*carrier_frequency )/pow(Multiplier, i);
        if(Fl >= frequency_consraint_initial && Fl <= frequency_consraint_final)
        {   
            x1 = i;
            oscillator_frequency = Fl;
            break;
        }
		else if(-Fl >= frequency_consraint_initial && -Fl <= frequency_consraint_final)
        {   
            x1 = i;
            oscillator_frequency = Fl;
            break;
        }
		if(i>1000)
		{
			cout << "Sorry, invalid data! Please enter correct correct data.";
			return -1;
		}
    }
    
    for (int i = 0; ; i++)
    {
        int res = (resultant_frequency_deviation/frequency_deviation);
        if(pow(Multiplier, (x1+i)) == res)
        {
            x2 = i;
            break;
        }
		if(i>1000)
		{
			cout << "Sorry, invalid data! Please enter correct correct data.";
			return -1;
		}
    }
    
	cout << endl << endl;
	cout <<"----------------------------------------------------------------------------------"<<endl;
    cout << "The required Multipliers : " << Multiplier <<"^"<< x1 << " & " << Multiplier <<"^"<<x2 <<endl<<endl;
    cout << "The required Frequency of Oscillator : " << oscillator_frequency << "MHz or "<<oscillator_frequency*1000<< " KHz"<< endl;
    getch();
	
    return 0;
}
