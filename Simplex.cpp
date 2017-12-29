#include <iostream>
#include <vector>
#include <cstdio>
#include <climits>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#define size 100

int status;
vector< vector<double> > a;
vector<double> b, c, ct, sga, x;
vector<int> eql;
vector<size_t> ar_id, base_id;
size_t st_num, x_num, x_num_, min_max;
size_t add_num=0, ba_num=0, ar_num=0;
size_t step = 1, section = 1, count = 1;
size_t in, out, inputMathod;
string datapath = "../data.txt";
ifstream ifs;
double z=0;

void inPut() {

    while(1) {
        cout << "The objective function: 1->max, 2->min:(1/2)";
        cin >> min_max;
        if (min_max!=1 && min_max!=2)
            cout << "Unexpected input! Please input the right number." << endl;
        else break;
    }

    while(1) {
        cout << "The number of x:";
        cin >> x_num;
        cout << "Input c1~c" << x_num << ":" << endl;
        for (size_t i=0; i<x_num; ++i) {
            cout << "c" << i+1 << " = ";
            double c_;
            cin >> c_;
            c.push_back(c_);
        }

        if (min_max==1) cout << "max z = ";
        else cout << "min z = ";

        if (c[0]==1) cout << "x[1]";
        else if(c[0]==-1) cout << "-x[1]";
        else if(c[0]!=0) cout << " " << c[0] << "x[1]";
        for (size_t i=1; i<x_num; ++i) {
            if(c[i]==1) cout << " + x[" << i+1 << "]";
            else if (c[i]==-1) cout << " - x[" << i+1 << "]";
            else if (c[i]>0) cout << " + " << c[i] << "x[" << i+1 << "]";
            else if (c[i]<0) cout << " - " << -c[i] << "x[" << i+1 << "]";
        }
        cout << "\t";
a1: cout << "right?:(y/n)";
        char yn;
        cin >> yn;
        if (yn == 'y') break;
        else if (yn == 'n') continue;
        else {
            cout << "Unexpected input!" << endl;
            goto a1;
        }
    }

    cout << "Input number of constraint equations: ";
    cin  >> st_num;
    eql.resize(size);
    b.resize(size);
    base_id.resize(size);
    ar_id.resize(size);

    for (size_t i=0; i<st_num; ++i) {
        cout << "st." << i+1 << ":" << endl;
        while (1) {
            cout << "Select: 1、==; 2、>=, 3、<= ：(1/2/3)";
            cin >> eql[i];
            if(eql[i]!=1 && eql[i]!=2 && eql[i]!=3)
                cout << "Unexpected input! Please input the right number." << endl;
            else break;
        }

        cout << "Input a: " << endl;
        vector<double> a_(x_num);
        for (size_t j=0; j<x_num; ++j) {
            cout << "a" << j+1 << " = ";
            cin >> a_[j];
        }
        a.push_back(a_);

        cout << "Input b: " << endl;
        cout << "b" << i+1 << " = ";
        cin >> b[i];
        cout << "st." << i+1 << ": ";
        if (a[i][0]==1) cout << "x[1]";
        else if(a[i][0]==-1) cout << "-x[1]";
        else if(a[i][0]!=0) cout << " " << a[i][0] << "x[1]";
        for (size_t j=1; j<x_num; ++j) {
            if(a[i][j]==1) cout << " + x[" << j+1 << "]";
            else if (a[i][j]==-1) cout << " - x[" << j+1 << "]";
            else if (a[i][j]>0) cout << " + " << a[i][j] << "x[" << j+1 << "]";
            else if (a[i][j]<0) cout << " - " << -a[i][j] << "x[" << j+1 << "]";
        }
        switch (eql[i]) {
        case 1: cout << " == " << b[i]; break;
        case 2: cout << " >= " << b[i]; break;
        case 3: cout << " <= " << b[i]; break;
        }

        while (1) {
            cout << "\t" ;
            cout << "right?:(y/n)";
            char yn;
            cin >> yn;
            if (yn == 'y') break;
            else if(yn == 'n') {--i; a.pop_back();break;}
        }
        cout << endl;
    }

    c.resize(size);
    a.resize(size);


//    {
//        min_max = 1;
//        st_num = 3;
//        x_num = 2;
//        c.resize(size);
//        a.resize(size);
//        b.resize(size);
//        eql.resize(size);
//        base_id.resize(size);
//        ar_id.resize(size);
//        c[0] = 2;
//        c[1] = -1;
//        a[0].push_back(1); a[0].push_back(1);
//        a[1].push_back(1); a[1].push_back(-1);
//        a[2].push_back(1); a[2].push_back(0);
//        b[0] = 2;  b[1] = 1;   b[2] = 3;
//        eql[0] = 2; eql[1] = 2; eql[2] = 3;
//    }
//    {
//        min_max = 2;
//        st_num = 3;
//        x_num = 4;
//        c.resize(size);
//        a.resize(size);
//        b.resize(size);
//        eql.resize(size);
//        base_id.resize(size);
//        ar_id.resize(size);
//        c[0] = -0.75;   c[1] = 20;
//        c[2] = -0.5;    c[3] = 6;
//        a[0].push_back(0.25); a[0].push_back(-8);
//        a[0].push_back(-1); a[0].push_back(9);
//        a[1].push_back(0.5); a[1].push_back(-12);
//        a[1].push_back(-0.5); a[1].push_back(3);
//        a[2].push_back(0); a[2].push_back(0);
//        a[2].push_back(1); a[2].push_back(0);
//        b[0] = 0;  b[1] = 0;   b[2] = 1;
//        eql[0] = 3; eql[1] = 3; eql[2] = 3;
//    }

}

int dataInput() {
    string line;
    if(!getline(ifs, line))return -1;
    //cout << line << endl;
    getline(ifs, line);
    stringstream sst(line);

    sst >> min_max >> st_num >> x_num;

    c.resize(size);
    a.resize(size);
    b.resize(size);
    eql.resize(size);
    base_id.resize(size);
    ar_id.resize(size);

    sst.clear();
    getline(ifs, line);
    sst.str(line);
    for (size_t i=0; i<x_num; ++i) sst >> c[i];

    for (size_t i=0; i<st_num; ++i) {
        vector<double> a_(size);
        sst.clear();
        getline(ifs, line);
        //cout << line << endl;
        sst.str(line);
        for (size_t j=0; j<x_num; ++j) {
            sst >> a_[j];
        }
        a[i] = a_;
    }

    sst.clear();
    getline(ifs, line);
    sst.str(line);
    for (size_t i=0; i<st_num; ++i) sst >> eql[i];
    //for (size_t i=0; i<st_num; ++i) cout << eql[i];

    sst.clear();
    getline(ifs, line);
    //cout << line << endl;
    sst.str(line);
    for (size_t i=0; i<st_num; ++i) sst >> b[i];
    //for (size_t i=0; i<st_num; ++i) cout << b[i];
    return 0;
}

void showOr() {
    cout << endl << "The original question: " << endl;
    if (min_max == 1) cout << "max z = ";
    else cout << "min z = ";
    if (c[0]==1) cout << "x[1]";
    else if(c[0]==-1) cout << "-x[1]";
    else if(c[0]!=0) cout << " " << c[0] << "x[1]";
    for (size_t i=1; i<x_num; ++i) {
        if(c[i]==1) cout << " + x[" << i+1 << "]";
        else if (c[i]==-1) cout << " - x[" << i+1 << "]";
        else if (c[i]>0) cout << " + " << c[i] << "x[" << i+1 << "]";
        else if (c[i]<0) cout << " - " << -c[i] << "x[" << i+1 << "]";
    }

    //cout << a[0][1] << endl;

    cout << endl << "st: " << endl;
    for (size_t i=0; i<st_num; ++i) {
        for (size_t j=0; j<x_num; ++j) {
            if (a[i][j] != 0) {
                if (a[i][j]==1 && j==0) cout << " x[" << j+1 << "]";
                else if (a[i][j]==1 && j!=0) cout << " + x[" << j+1 << "]";
                else if (a[i][j]==-1 && j==0) cout << " -x[" << j+1 << "]";
                else if (a[i][j]==-1 && j!=0) cout << " - x[" << j+1 << "]";
                else if (a[i][j]>0 && j==0) cout << " " << a[i][j] << "x[" << j+1 << "]";
                else if (a[i][j]>0 && j!=0) cout << " + " << a[i][j] << "x[" << j+1 << "]";
                else if (a[i][j]<0 && j==0) cout << " " << a[i][j] << "x[" << j+1 << "]";
                else if (a[i][j]<0 && j!=0) cout << " - " << -a[i][j] << "x[" << j+1 << "]";
            }
        }
        switch (eql[i]) {
        case 1:
            cout << " == " << b[i];
            break;
        case 2:
            cout << " >= " << b[i];
            break;
        case 3:
            cout << " <= " << b[i];
            break;
        }
        cout << endl;
    }
    cout << " x[1]~x[" << x_num << "] >= 0" << endl << endl;



}

void normalize() {
    x_num_ = x_num;
    for (size_t i=0; i<st_num; ++i) {
        switch (eql[i]) {
        case 1:
        case 3:
            x_num++;
            break;
        case 2:
            x_num += 2;
            break;
        }
    }
    c.resize(x_num);
    for (size_t i=0; i<st_num; ++i) {
        a[i].resize(x_num);
    }

    if (min_max == 2)
        for (size_t i=0; i<x_num_; ++i) c[i] *= -1;

    for (size_t i=0; i<st_num; ++i) {
        switch (eql[i]) {
        case 1:
            break;
        case 2:
            add_num++;
            c[x_num_+add_num-1]=0;
            for(size_t j=x_num_; j<x_num; j++)
                if(j==x_num_+add_num-1) a[i][x_num_+add_num-1]=-1;
            break;
        case 3:
            add_num++;
            ba_num++;
            c[x_num_+add_num-1]=0;
            base_id[ba_num-1] = x_num_ + add_num;
            for(size_t j=x_num_; j<x_num; j++)
                if(j==x_num_+add_num-1) a[i][j]=1;
            break;
        }
    }

    for (size_t i=0; i<st_num; ++i) {
        switch (eql[i]) {
        case 1:
            add_num++;
            ba_num++;
            ar_num++;
            c[x_num_+add_num-1] = 0;
            base_id[ba_num-1] = ar_id[ar_num-1] = x_num_ + add_num;
            for(size_t j=x_num_; j<x_num; j++)
                if(j==x_num_+add_num-1) a[i][j] = 1;
            break;
        case 2:
            add_num++;
            ba_num++;
            ar_num++;
            c[x_num_+add_num-1]=0;
            base_id[ba_num-1] = ar_id[ar_num-1] = x_num_ + add_num;
            for(size_t j=x_num_;j<x_num;j++)
                if(j==x_num_+add_num-1) a[i][j] = 1;
            break;
        case 3:
            break;
        }

        vector<size_t> base_id_;
        for (size_t i=0; i<st_num; ++i) {
            for (size_t j=0; j<ba_num; ++j)
                if (a[i][base_id[j]-1] == 1)
                    base_id_.push_back(base_id[j]);
        }
        base_id = base_id_;
    }

    cout << "Normalized form: " << endl;
    if (min_max == 1) cout << "max z = ";
    else cout << "min z = ";
    if (c[0]==1) cout << "x[1]";
    else if(c[0]==-1) cout << "-x[1]";
    else if(c[0]!=0) cout << " " << c[0] << "x[1]";
    for (size_t i=1; i<x_num; ++i) {
        if(c[i]==1) cout << " + x[" << i+1 << "]";
        else if (c[i]==-1) cout << " - x[" << i+1 << "]";
        else if (c[i]>0) cout << " + " << c[i] << "x[" << i+1 << "]";
        else if (c[i]<0) cout << " - " << -c[i] << "x[" << i+1 << "]";
    }

    cout << endl << "st: " << endl;
    for (size_t i=0; i<st_num; ++i) {
        for (size_t j=0; j<x_num; ++j) {
            if (a[i][j] != 0) {
                if (a[i][j]==1 && j==0) cout << " x[" << j+1 << "]";
                else if (a[i][j]==1 && j!=0) cout << " + x[" << j+1 << "]";
                else if (a[i][j]==-1 && j==0) cout << " -x[" << j+1 << "]";
                else if (a[i][j]==-1 && j!=0) cout << " - x[" << j+1 << "]";
                else if (a[i][j]>0 && j==0) cout << " " << a[i][j] << "x[" << j+1 << "]";
                else if (a[i][j]>0 && j!=0) cout << " + " << a[i][j] << "x[" << j+1 << "]";
                else if (a[i][j]<0 && j==0) cout << " " << a[i][j] << "x[" << j+1 << "]";
                else if (a[i][j]<0 && j!=0) cout << " - " << -a[i][j] << "x[" << j+1 << "]";
            }
        }
        cout << " = " << b[i] << endl;
    }
    cout << " x[1]~x[" << x_num << "] >= 0" << endl << endl;
}

void showPr() {
    if (section == 1) {
        cout << "min z = x[" << ar_id[0] << "]";
        for (size_t i=1; i<ar_num; ++i) {
            cout << " + x[" << ar_id[i] << "]";
        }
    } else if (section == 2) {
        cout << "min z = ";
        if (c[0]==1) cout << "x[1]";
        else if(c[0]==-1) cout << "-x[1]";
        else if(c[0]!=0) cout << " " << c[0] << "x[1]";
        for (size_t i=1; i<x_num; ++i) {
            if(c[i]==1) cout << " + x[" << i+1 << "]";
            else if (c[i]==-1) cout << " - x[" << i+1 << "]";
            else if (c[i]>0) cout << " + " << c[i] << "x[" << i+1 << "]";
            else if (c[i]<0) cout << " - " << -c[i] << "x[" << i+1 << "]";
        }
    } else cout << "Section wrong" << endl;


    cout << endl << "st: " << endl;
    for (size_t i=0; i<st_num; ++i) {
        int k = 0;
        for (size_t j=0; j<x_num; ++j) {
            if (a[i][j] != 0) {
                if (a[i][j]==1 && k==0) cout << " x[" << j+1 << "]";
                else if (a[i][j]==1 && k!=0) cout << " + x[" << j+1 << "]";
                else if (a[i][j]==-1 && k==0) cout << " -x[" << j+1 << "]";
                else if (a[i][j]==-1 && k!=0) cout << " - x[" << j+1 << "]";
                else if (a[i][j]>0 && k==0) cout << " " << a[i][j] << "x[" << j+1 << "]";
                else if (a[i][j]>0 && k!=0) cout << " + " << a[i][j] << "x[" << j+1 << "]";
                else if (a[i][j]<0 && k==0) cout << " " << a[i][j] << "x[" << j+1 << "]";
                else if (a[i][j]<0 && k!=0) cout << " - " << -a[i][j] << "x[" << j+1 << "]";
                k = 1;
            }
        }
        cout << " = " << b[i] << endl;
    }
    cout << " x[1]~x[" << x_num << "] >= 0" << endl << endl;;
}

void outPut() {
    cout << count << " interation : " << endl;
    cout << "c" << "\t";
    for ( size_t i=0; i<x_num; ++i )
        cout << c[i] << "\t";
    cout << z << endl;

    cout << " " << "\t";
    for ( size_t i=0; i<x_num; ++i ) {
        cout << "x" << i+1 << "\t";
    }
    cout << "b" << "\t" << endl;

    for ( size_t i=0; i<st_num; ++i ) {
        cout << "x[" << base_id[i] << "]\t";
        for( size_t j = 0 ; j < x_num ; ++j )
            cout << a[i][j] << "\t";
        cout << b[i] << "\t" << endl;
    }

    cout << "sigma" << "\t";
    for (size_t i=0; i<x_num; ++i) {
        cout << sga[i] << "\t" ;
    }
    cout << endl;
}

void _result() {
    x.resize(x_num);
    cout << " *x = (";
    for (size_t i=0; i<x_num; ++i) {
        for (size_t j=0; j<st_num; ++j) {
            if (i==base_id[j]-1) {
                x[i] = b[j];
                break;
            } else x[i] = 0;
        }
        cout << "  " << x[i] ;
    }
    cout << ")\t";
    cout << " *f = " << z << endl << endl;
}

void _iterator() {
    size_t k_f, k_a;
    size_t mainElerow;
    double mainElevalue;


    //sigma
    sga.resize(x_num);
    for (size_t i=0; i<x_num; ++i) {
        sga[i] = c[i];
        for (size_t j=0; j<st_num; ++j)
            sga[i] -= c[base_id[j]-1] * a[j][i];
        for (size_t j=0; j<st_num; ++j)
            if (i==base_id[j]-1) sga[i] = 0;
    }

    z = 0;
    for (size_t j=0; j<st_num; ++j)
        z -= c[base_id[j]-1] * b[j];

    outPut();

    size_t k_ = 0;
    for (; k_<x_num; ++k_)
        if (sga[k_] > 0) break;
    if (k_ == x_num) {
        for (size_t i=0; i<x_num; ++i) {
            k_f = k_a = 0;
            for(size_t j=0; j<ar_num; ++j)
                if(i==ar_id[j]) k_a=1;
            if(sga[i]==0 && k_a!=1) {
                for(size_t j=0; j<st_num; ++j) if(i==base_id[j]-1) k_f=1;
                if(k_f==0) {status=-1; return;}
            }
        }
        status = 1;
        return;
    }

    for(size_t i=0; i<x_num; ++i) {
        k_f = 0;
        if(sga[i] > 0) {
            for(size_t j=0; j<st_num; ++j) if(a[j][i]>0) k_f=1;
            if(k_f!=1) {status=0; return;}
        }
    }


    //base in
    double sgaMax = -INT_MAX;
    for (size_t i=0; i<x_num; ++i) {
        if (sga[i]>0 && sgaMax<sga[i] ) {
            in = i;
            sgaMax = sga[i];
        }
    }

    //base out
    double staMin = INT_MAX;
    //size_t staMinrow = 0;
    for (size_t i=0; i<st_num; ++i) {
        if (b[i]/a[i][in]<=staMin && a[i][in]>0) {
            bool exc = false;
            if(b[i]/a[i][in] == staMin) {
//                for (size_t j=0; j<ar_num; ++j)
//                    if (base_id[i] == ar_id[j])
//                        exc = true;
                for (size_t j=0; j<x_num; ++j) {
                    if (j == in) continue;
                    if (a[i][j]/a[i][in]<a[mainElerow][j]/a[mainElerow][in]) {
                        exc = true;
                        break;
                    }
                }

            } else exc = true;
            if (exc) {
                out = base_id[i];
                mainElerow = i;
                staMin = b[i]/a[i][in];
            }
        }
    }





    cout << "Base: (";
    for (size_t i=0; i<st_num; ++i)
        cout << " x[" << base_id[i] << "]";
    cout << ")\t\t";
    cout << "Base out: x[" << out << "]\t\t";
    cout << "Base in: x[" << in+1 << "]" << endl << endl;

    for (size_t i=0; i<st_num; ++i)
        if (base_id[i]==out) base_id[i]=in+1;

    mainElevalue = a[mainElerow][in];
    b[mainElerow] /= mainElevalue;
    for (size_t i=0; i<x_num; ++i) a[mainElerow][i]/=mainElevalue;
    for (size_t i=0; i<st_num; ++i) {
        if (i!=mainElerow) {
            b[i] -= b[mainElerow]*a[i][in];
            mainElevalue = a[i][in];
            for (size_t j=0; j<x_num; ++j)
                a[i][j] -= a[mainElerow][j]*mainElevalue;
        }
    }

    ++count;
    if (count > 200) {
        status = -2;
        return;
    }

    _iterator();




}

void dataClear() {
    a.clear();  b.clear();  c.clear();
    ct.clear(); sga.clear();    x.clear();
    eql.clear();
    ar_id.clear();  base_id.clear();
    add_num = 0;    ba_num = 0;     ar_num = 0;
    step = 1;       section = 1;    count = 1;
    z = 0;
}

int main()
{
    while (1) {
        cout << "Select : 1.Use the parpared data.\t 2.Input by yourself  (1/2)";
        cin >> inputMathod;
        if (inputMathod==1 || inputMathod==2) break;
        else cout << "Unexpected input! Please input the right number." << endl;
    }

    size_t dataCount = 1;
    if (inputMathod == 1) {
        ifs.open(datapath);
        if (!ifs.is_open()) {
            cout << "Can't open data file." << endl;
            exit(0);
        }
    }

    while (inputMathod) {

        if (inputMathod == 2) inPut();
        else {

            if (dataInput() == -1) {
                cout << "No more data!" << endl;

                size_t st = 0;
                while (1) {
                    cout << "Select : 1.Input by yourself\t 2.Stop (1/2)";
                    cin >> st ;
                    if (st!=1 && st!=2) {
                        cout << "Unexpected input! Please input the right number." << endl;
                        continue;
                    } else  break;
                }
                if (st == 1) {
                    inputMathod = 2;
                    continue;
                } else return 0;
            }
            cout << endl << "Data" << dataCount++ << " : ";
        }

        showOr();

        normalize();

        ct.resize(x_num);

        for (size_t i=0; i<x_num; ++i) {
            size_t j = 0;
            for (; j<ar_num; ++j)
                if (ar_id[j]-1 == i) break;
            if (j == ar_num) ct[i] = 0;
            else ct[i] = -1;
        }
        swap(c, ct);
        cout << "First section : " << endl;
        cout << "Result : " ;
        showPr();
        _iterator();
        if (status == -2) {
            cout << "Time out" << endl;
            exit(0);
        }
        _result();

        if (z != 0) {
            cout << "No feasible solution for equation set." << endl;
            exit(0);
        }

        swap(c, ct);
        x_num -= ar_num;
        ar_num = 0;
        cout << "Second section : " << endl;
        showPr();
        ++step;
        _iterator();
        cout << endl;

        switch (status) {
        case 1:
            cout << "One optimal solution : " << endl;
            _result();
            break;
        case 0:
            cout << "Unbounded solution." << endl;
            break;
        case -1:
            cout << "Alternative optimal solution." << endl;
            _result();
            break;
        case -2:
            cout << "Iteration time out" << endl;
            break;
        }
        size_t st = 0;
        while (1) {
            cout << "Select : 1.Next data\t 2.Stop (1/2)";
            cin >> st ;
            if (st!=1 && st!=2) {
                cout << "Unexpected input! Please input the right number." << endl;
                continue;
            } else  break;
        }
        if (st == 1) {
            dataClear();
            continue;
        }
        else return 0;

    }

    return 0;
}


