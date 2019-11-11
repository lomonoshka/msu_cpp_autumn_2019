#include "matrix.cpp"

main()
{
    const int rows = 5;
    const int columns = 7;

    Matrix a(rows, columns), b(rows, columns);

    for(int i=0; i<a.get_rows(); i++)
        for(int j=0; j<a.get_columns(); j++)
        {
            a[i][j] = i + j;
            b[i][j] = -i + j;
        }
    a*=5;

    for(int i=0; i<a.get_rows(); i++)
        for(int j=0; j<a.get_columns(); j++)
            if(a[i][j] != 5*(i+j))
            {
                cout<<"Incorrect multiplication."<<endl;
                return -1;
            }

    if(a.get_columns() != columns or a.get_rows() != rows)
    {
        cout<<"Inclorrect sizes of matrix."<<endl;
    }


    if((a==a) != 1 or (a != b) != 1)
    {
        cout<<"Incorrect bool operator.";
        return -1;
    }

    try
    {
        a[-1][0];
        a[10][0];
    }

    catch(exception& exc)
    {
        cout<< exc.what() <<endl;
    }
    cout<<"Done."<<endl;
    return 0;
}
