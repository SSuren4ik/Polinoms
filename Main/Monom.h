#pragma once
#include <iostream>
#include <string>
using namespace std;

const int offset = 10;
const int numbsystem = 21;
const int Max_Pow = 10;
struct Monom
{
    double a;
    int s;
public:
    Monom(double _a = 0, int pow1 = 0, int pow2 = 0, int pow3 = 0)
    {
        s = (pow1 + offset) + (pow2 + offset) * numbsystem + (pow3 + offset) * numbsystem * numbsystem;
        if (!StepCheck())
        {
            throw exception();
        }
        a = _a;
    }
    Monom(int _s, double _a)
    {
        s = _s;
        if (!StepCheck())
        {
            throw exception();
        }
        a = _a;
    }
    Monom(const Monom& m)
    {
        a = m.a;
        s = m.s;
    }
    Monom(const string& str)
    {
        int sx = 0;
        bool xh = false;
        int sy = 0;
        bool yh = false;
        int sz = 0;
        bool zh = false;
        int last_step = 0;
        string sup = "+*^";
        string tmp = "";
        a = 0;
        for (int i = 0; i < str.size(); i++)
        {
            char c = str[i];
            int fres = sup.find(c);
            if (c == '-')
            {
                char check = tmp.find(c);
                if (check < 0)
                {
                    string tmp2 = "-";
                    tmp = tmp2 + tmp;
                }
                else
                {
                    throw - 1;
                }
            }
            else if (c >= '0' && c <= '9')
            {
                if (c == '0' && last_step == 0)
                {
                    a = 0;
                    s = 0;
                    return;
                }
                tmp += c;
            }
            else if (c == 'x' || c == 'y' || c == 'z')
            {
                switch (c)
                {
                case 'x':
                {
                    xh = true;
                    if (tmp != "")
                        a = stod(tmp);
                    else
                    {
                        a = 1.0;
                    }
                    last_step = 1;
                    break;
                }
                case 'y':
                {
                    yh = true;
                    if (xh == true)
                    {
                        if (tmp != "")
                            sx = stod(tmp);
                        else
                            sx = 1;
                        if (sx > numbsystem / 2 || sx < -numbsystem / 2)
                            throw - 1;
                    }
                    last_step = 2;
                    break;
                }
                case 'z':
                {
                    zh = true;
                    if (yh == true)
                    {
                        if (tmp != "")
                            sy = stod(tmp);
                        else
                            sy = 1;
                        if (sy > numbsystem / 2 || sy < -numbsystem / 2)
                            throw exception("Incorrect y");
                    }
                    else if (xh == true)
                    {
                        if (tmp != "")
                            sx = stod(tmp);
                        else
                            sx = 1;
                        if (sx > numbsystem / 2 || sx < -numbsystem / 2)
                            throw exception("Incorrect x");
                    }
                    else
                    {
                        if (tmp != "")
                            a = stod(tmp);
                        else
                            a = 1.0;
                    }
                    last_step = 3;
                    break;
                }
                }
                tmp = "";
            }
            else if (fres < 0)
            {
                throw - 1;
            }
        }
        switch (last_step)
        {
        case 1:
        {
            if (xh == true)
            {
                if (tmp != "")
                    sx = stod(tmp);
                else
                    sx = 1;
                if (sx > numbsystem / 2 || sx < -numbsystem / 2)
                    throw exception("Incorrect x");
            }
            break;
        }
        case 2:
        {
            if (yh == true)
            {
                if (tmp != "")
                    sy = stod(tmp);
                else
                    sy = 1;
                if (sy > numbsystem / 2 || sy < -numbsystem / 2)
                    throw exception("Incorrect y");
            }
            break;
        }
        case 3:
        {
            if (zh == true)
            {
                if (tmp != "")
                {
                    sz = stod(tmp);
                }
                else
                    sz = 1;
                if (sz > numbsystem / 2 || sz < -numbsystem / 2)
                    throw exception("Incorrect z");
            }
            break;
        }
        default:
        {
            s = 0;
            return;
        }
        }

        s = (sx + offset) + (sy + offset) * numbsystem + (sz + offset) * numbsystem * numbsystem;
    }

    int StepMin()
    {
        int minstep = -Max_Pow;
        int _s = (minstep + offset) + (minstep + offset) * numbsystem + (minstep + offset) * numbsystem * numbsystem;
        return _s;
    }
    int StepMax()
    {
        int maxstep = Max_Pow;
        int _s = (maxstep + offset) + (maxstep + offset) * numbsystem + (maxstep + offset) * numbsystem * numbsystem;
        return _s;
    }
    bool StepCheck()
    {
        if (GetStepX() > Max_Pow || GetStepX() < -Max_Pow)
        {
            return false;
        }
        if (GetStepY() > Max_Pow || GetStepY() < -Max_Pow)
        {
            return false;
        }
        if (GetStepZ() > Max_Pow || GetStepZ() < -Max_Pow)
        {
            return false;
        }
        return true;
    }
    int GetStepX()
    {
        return s % numbsystem - offset;
    }
    int GetStepY()
    {
        return (s / numbsystem) % numbsystem - offset;
    }
    int GetStepZ()
    {
        return (s / numbsystem / numbsystem) % numbsystem - offset;
    }

    double Aproce_monom(double x, double y, double z)
    {
        double res = a;
        int i = GetStepX();
        int j = GetStepY();
        int k = GetStepZ();
        res = multy(x, i) * multy(y, j) * multy(z, k);
        return res;
    }
    friend ostream& operator <<(ostream& out, Monom& m)
    {
        int i = m.GetStepX();
        int j = m.GetStepY();
        int k = m.GetStepZ();
        int ch = 0;
        if (m.a == 0)
        {
            out << 0;
            return out;
        }
        if (m.a > 0)
        {
            out << "+";
        }
        if (m.a != 1 )
        {   
            out << m.a;
        }
        if (i == 0 && j == 0 && k == 0)
        {
            return out;
        }
        else
        {
            if (m.a != 1.0)
                out << "*";
            if (i != 0)
            {
                out << "x";
                if (i != 1)
                    out << "^" << i;
                ch++;
            }
            if (j != 0)
            {
                if (ch != 0)
                    out << "*";
                out << "y";
                if (j != 1)
                    out << "^" << j;
                ch++;
            }
            if (k != 0)
            {
                if (ch != 0)
                    out << "*";
                out << "z";
                if (k != 1)
                    out << "^" << k;
            }
        }
        return out;
    }

    friend istream& operator >> (istream& in, Monom& m)
    {
        string str;
        in >> str;
        m = Monom(str);
        return in;
    }

    double multy(double x, int i)
    {
        double res = 1.0;
        if (i > 0)
        {
            for (int k = 0; k < i; k++)
            {
                res *= x;
            }
        }
        else if (i < 0)
        {
            for (int k = 0; k > i; k--)
            {
                res /= x;
            }
        }
        return res;
    }

    void Change_Kof(double _a)
    {
        a += _a;
    }
    bool Equal_Steps(const Monom& _m)
    {
        if (s == _m.s) 
        {
            return true;
        }
        return false;
    }
    Monom& operator + (Monom& m2)
    {
        double _a = this->a + m2.a;
        return *new Monom(_a, GetStepX(), GetStepY(), GetStepZ());
    }
    Monom& operator - (Monom& m2)
    {
        double _a = this->a - m2.a;
        return *new Monom(_a, GetStepX(), GetStepY(), GetStepZ());
    }
    Monom& operator * (Monom& m2)
    {
        double _a = this->a * m2.a;
        int x = GetStepX() + m2.GetStepX();
        int y = GetStepY() + m2.GetStepY();
        int z = GetStepZ() + m2.GetStepZ();
        int _s = (x + offset) + (y + 10) * numbsystem + (z + 10) * numbsystem * numbsystem;
        return *new Monom(_s, _a);
    }

};
