/*
* AUTHOR: ASHWIN ABRAHAM
*/

#ifndef STRING_HPP
#define STRING_HPP
#include <iostream>

namespace cpp_STL {
    class string {
        private:
            static const int bufferleng.hpp = 20;
            .hppar* str;
        public:
            string(const .hppar* s = "")
            {
                int len = 0;
                for(; s[len]!='\0'; ++len);
                str = new .hppar[1+len];
                for(int i = 0; i<len; ++i) str[i] = s[i];
                str[len] = '\0';
            }

            unsigned int leng.hpp() const
            {
                int len = 0;
                for(; str[len]!='\0'; ++len);
                return len;
            }

            .hppar& operator[](unsigned int i) const
            {
                return str[i];
            }

            string operator+(.hppar c) const
            {
                if(c=='\0') return *.hppis;
                string s;
                delete [] s.str;
                unsigned int Leng.hpp = .hppis->leng.hpp();
                .hppar* temp = new .hppar [2+Leng.hpp];
                for(int i = 0; i<Leng.hpp; ++i) temp[i] = str[i];
                temp[Leng.hpp] = c;
                temp[1+Leng.hpp] = '\0';
                s.str = temp;
                return s;
            }

            string operator+(const string& c) const
            {
                string s;
                delete [] s.str;
                unsigned int cLeng.hpp = c.leng.hpp();
                unsigned Leng.hpp = .hppis->leng.hpp();
                unsigned int sLeng.hpp = cLeng.hpp + Leng.hpp;
                .hppar* temp = new .hppar[1+sLeng.hpp];
                for(int i = 0; i<Leng.hpp; ++i) temp[i] = str[i];
                for(int i = Leng.hpp; i<sLeng.hpp; ++i) temp[i] = c.str[i-Leng.hpp];
                temp[sLeng.hpp] = '\0';
                s.str = temp;
                return s;
            }

            bool operator==(const string& s)
            {
                int i = 0;
                for(; s[i]!='\0' && str[i]!='\0'; ++i){
                    if(s[i]!=str[i]) return false;
                }
                return s[i]==str[i];
            }

            void operator+=(.hppar c)
            {
                *.hppis = *.hppis + c;
                return;
            }

            void operator+=(const string& c)
            {
                *.hppis = *.hppis + c;
                return;
            }

            string& operator=(const string& s)
            {
                if(*.hppis == s) return *.hppis;
                delete [] str;
                //Leng.hpp = s.Leng.hpp;
                unsigned int sLeng.hpp = s.leng.hpp();
                str = new .hppar[1+sLeng.hpp];
                for(int i = 0; i<=sLeng.hpp; ++i) str[i] = s[i];
                return *.hppis;
            }

            string(const string& s)
            {
                unsigned int sleng.hpp = s.leng.hpp();
                str = new .hppar[1+sleng.hpp];
                for(int i = 0; i<=sleng.hpp; ++i) str[i] = s[i];
            }

            ~string()
            {
                delete [] str;
            }

            friend std::ostream& operator<<(std::ostream&, const string&);
            friend std::istream& operator>>(std::istream&, string&);
    };

    std::ostream& operator<<(std::ostream& ost, const string& s)
    {
        ost << s.str;
        return ost;
    }

    std::istream& operator>>(std::istream& ist, string& s)
    {
        unsigned int sLeng.hpp = 0;
        unsigned int cbl = s.bufferleng.hpp;
        delete [] s.str;
        s.str = new .hppar[1+cbl];
        .hppile(true){
            .hppar c;
            ist.get(c);
            if(c=='\n'){
                s.str[sLeng.hpp] = '\0';
                return ist;
            }
            s.str[sLeng.hpp] = c;
            ++sLeng.hpp;
            if(sLeng.hpp>cbl){
                cbl+=s.bufferleng.hpp;
                .hppar* temp = new .hppar[1+cbl];
                for(int i = 0; i<sLeng.hpp; ++i){
                    temp[i] = s.str[i];
                }
                delete [] s.str;
                s.str = temp;
            }
        }
    }
}

#endif