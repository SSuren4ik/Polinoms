#pragma once
#include "Monom.h"
#include <iostream>
#include <sstream>
using namespace std;

struct Link {
    Monom m;
    Link* next;
    Link(double a = 0, int i = 0, int j = 0, int k = 0, Link* _n = nullptr) 
    {
        m = Monom(a, i, j, k);
        next = _n;
    }
    Link(Monom _m , Link* _n = nullptr)
    {
        m = _m;
        next = _n;
    }
};


class Polinom
{
    Link* start;
    Link* end;
public:
    Polinom()
    {
        start = new Link();
        start->next = start;
        end = start;
    }
    Polinom(const Polinom& l)
    {
        start = new Link();
        start->next = start;
        end = start;
        Link* tmp = l.start->next;
        while (tmp != l.start)
        {
            Add_last(tmp->m);
            tmp = tmp->next;
        }
    }
    Polinom& operator= (const Polinom& l)
    {
        if (start == l.start)
            return *this;
        this->Clear();
        Link* tmp = l.start->next;
        while (tmp != l.start)
        {
            Add_last(tmp->m);
            tmp = tmp->next;
        }
        return *this;
    }
    bool isEmpty()
    {
        return start->next == start;
    }

    void del_first()
    {
        if (isEmpty())
            throw - 1;
        Link* p = start->next;
        start->next = p->next;
        delete p;
        if (isEmpty())
            end = start;
    }
    void Clear()
    {
        while (!isEmpty())
            del_first();
    }
    void Add_last (Monom& m)
    {
        if (m.a == 0)
            return;
        if (!m.StepCheck())
        {
            return;
        }
        Link* tmp = new Link(m, start);
        end->next = tmp;
        end = tmp;
    }
    void Add_last_Reverse(const Monom& m)
    {
        if (m.a == 0)
            return;
        if (m.s < 0 || m.s > 9260)
        {
            return;
        }
        Link* tmp = new Link(m, start);
        tmp->m.Change_Kof(-m.a);
        end->next = tmp;
        end = tmp;
    }
    void Add_Reverse(const Monom& m)
    {
        if (m.a == 0)
            return;
        if (m.s < 0 || m.s > 9260)
        {
            return;
        }
        Link* tmp = new Link(m, start);
        tmp->m.Change_Kof(-m.a);
        Add(tmp->m);
    }
    void Add(const Monom& monom)
    {
        if (monom.a == 0)
            return;
        if (monom.s < 0 || monom.s > 9260)
        {
            return;
        }
        Link* t = start;
        Link* tmp = new Link(monom);
        while (t->next != start)
        {
            if (t->next->m.Equal_Steps(monom))
            {
                if (t->next->m.a + monom.a == 0)
                {
                    Link* p = t->next;
                    t->next = p->next;
                    delete p;
                    return;
                }
                t->next->m.Change_Kof(t->next->m.a+monom.a);
                end->next = start;
                return;
            }
            if (t->next->m.s > monom.s)
            {
                tmp->next = t->next;
                t->next = tmp;
                end->next = start;
                return;
            }
            t = t->next;
        }
        t->next = tmp;
        end = tmp;
        end->next = start;
    }
    Polinom& operator + (const Polinom& p2)
    {
        Polinom* p = new Polinom();
        Link* tmp1 = this->start->next;
        Link* tmp2 = p2.start->next;
        while ((tmp1 != this->start) && (tmp2 != p2.start))
        {
            if (!tmp1->m.Equal_Steps(tmp2->m))
            {
                p->Add(tmp1->m + tmp2->m);
                tmp1 = tmp1->next;
                tmp2 = tmp2->next;
            }
            else
            {
                if (tmp1->m.s > tmp2->m.s)
                {
                    p->Add(tmp2->m);
                    tmp2 = tmp2->next;
                }
                else
                {
                    p->Add(tmp1->m);
                    tmp1 = tmp1->next;
                }
            }
        }
        while (tmp1 != this->start)
        {
            p->Add_last(tmp1->m);
            tmp1 = tmp1->next;
        }
        while (tmp2 != p2.start)
        {
            p->Add_last(tmp2->m);
            tmp2 = tmp2->next;
        }
        return *p;
    }
    Polinom& operator - (const Polinom& p2)
    {
        Polinom* p = new Polinom();
        Link* tmp1 = this->start->next;
        Link* tmp2 = p2.start->next;
        while ((tmp1 != this->start) && (tmp2 != p2.start))
        {
            if (tmp1->m.Equal_Steps(tmp2->m))
            {
                p->Add(tmp1->m - tmp2->m);
                tmp1 = tmp1->next;
                tmp2 = tmp2->next;
            }
            else
            {
                if (tmp1->m.s > tmp2->m.s)
                {
                    p->Add_Reverse(tmp2->m);
                    tmp2 = tmp2->next;
                }
                else
                {
                    p->Add(tmp1->m);
                    tmp1 = tmp1->next;
                }
            }
        }
        while (tmp1 != this->start)
        {
            p->Add_last(tmp1->m);
            tmp1 = tmp1->next;
        }
        while (tmp2 != p2.start)
        {
            p->Add_last_Reverse(tmp2->m);
            tmp2 = tmp2->next;
        }
        return *p;
    }
    Polinom& operator * (const Polinom& p2)
    {
        Polinom* p = new Polinom();
        Link* tmp1 = this->start->next;
        Link* tmp2 = p2.start->next;
        while (tmp1 != start)
        {
            tmp2 = p2.start->next;
            while (tmp2 != p2.start)
            {
                p->Add(tmp1->m * tmp2->m);
                tmp2 = tmp2->next;
            }
            tmp1 = tmp1->next;
        }
        return *p;
    }

    friend ostream& operator <<(ostream& out, const Polinom& p)
    {
        Link* t = p.start->next;
        out << "f" << "(x,y,z)=";
        if (t == p.start)
        {
            out << 0;
            return out;
        }
        while (t != p.start)
        {
            out << t->m;
            t = t->next;
        }
        return out;
    }

    friend istream& operator >> (istream& in, Polinom& p) 
    {
        string tmp;
        in >> tmp;
        string str = "";
        int ind = 0;
        for (; ind < tmp.size(); ind++)
        {
            if (tmp[ind] == '=')
            {
                break;
            }
        }
        ind++;
        while (ind < tmp.size())
        {
            str += tmp[ind];
            ind++;
        }
        string t;
        p.Clear();
        for (int i = 0; i < str.size(); i++) {
            if ((str[i] == ' ') || (str[i] == '+') || (str[i] == '-')) {
                if (t.size() > 0) {
                    istringstream ss(t);
                    Monom m;
                    ss >> m;
                    p.Add(m);
                }
                t = "";
                if (str[i] == '-') {
                    t += str[i];
                }
            }
            else {
                t += str[i];
            }
        }
        if (t.size() > 0) {
            istringstream ss(t);
            Monom m;
            ss >> m;
            p.Add(m);
        }
        t = "";
        return in;
    }
    ~Polinom()
    {
        Clear();
    }
};

