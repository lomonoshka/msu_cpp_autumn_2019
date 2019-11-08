#include "Bigint.cpp"
#include <cstdlib>
using namespace std;

int main()
{

    for(int count=0; count<10000; count++)
    {
        long long digit1 = rand()%(int)(1e9);
        long long digit2 = rand()%(int)(1e9);
        Bigint Dig1(digit1);
        Bigint Dig2(digit2);
        Bigint sum(digit1 + digit2);
        Bigint dif(digit1 - digit2);

        if(Dig1 + Dig2 != sum)
        {
            cout<<"+"<<endl<<Dig1<<endl<<Dig2<<endl<<Dig1+Dig2<<endl<<sum<<endl<<'\n';
            return -1;
        }

        if((Dig1 - Dig2) != dif)
        {
            cout<<"-"<<endl<<Dig1<<endl<<Dig2<<endl<<Dig1-Dig2<<endl<<dif<<endl<<'\n';
            return -1;
        }

        if(Dig1 > Dig2 != digit1 > digit2)
        {
            cout<<">"<<endl<<Dig1<<endl<<Dig2<<endl;
            return -1;
        }

        if(Dig1 < Dig2 != digit1 < digit2)
        {
            cout<<"<"<<endl<<Dig1<<endl<<Dig2<<endl;
            return -1;
        }

        if(Dig1 >= Dig2 != digit1 >= digit2)
        {
            cout<<">="<<endl<<Dig1<<endl<<Dig2<<endl;
            return -1;
        }

        if(Dig1 <= Dig2 != digit1 <= digit2)
        {
            cout<<"<="<<endl<<Dig1<<endl<<Dig2<<endl;
            return -1;
        }

        if(Dig1 == Dig2 != digit1 == digit2)
        {
            cout<<"=="<<endl<<Dig1<<endl<<Dig2<<endl;
            return -1;
        }

        if((Dig1 != Dig2) != (digit1 != digit2))
        {
            cout<<"!="<<endl<<Dig1<<endl<<Dig2<<endl;
            return -1;
        }

    }
    cout<<"Done"<<endl;
    return 0;
}
