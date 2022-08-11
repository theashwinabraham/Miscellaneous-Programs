/*
* AUTHOR: ASHWIN ABRAHAM
*/

#ifndef STRING_HPP
#define STRING_HPP
#include <iostream>

namespace cpp_STL {
    class string {
        private:
            unsigned int len;
            char* str;
            
        public:
            string(const char* s = "")
            {
                len = 0;
                for(; s[len]!='\0'; ++len);
                str = new char[1+len];
                for(int i = 0; i<len; ++i) str[i] = s[i];
                str[len] = '\0';
            }

            unsigned int length() const
            {
                return len;
            }

            char& operator[](unsigned int i)
            {
                return str[i];
            }

            const char& operator[](unsigned int i) const
            {
                return str[i];
            }

            string operator+(char c) const
            {
                if(c=='\0') return *this;
                string s;
                delete [] s.str;
                unsigned int Length = this->len;
                char* temp = new char [2+Length];
                for(int i = 0; i<Length; ++i) temp[i] = str[i];
                temp[Length] = c;
                temp[1+Length] = '\0';
                s.str = temp;
                return s;
            }

            string operator+(const string& c) const
            {
                string s;
                delete [] s.str;
                unsigned int cLength = c.len;
                unsigned Length = this->len;
                unsigned int sLength = cLength + Length;
                char* temp = new char [1+sLength];
                for(int i = 0; i<Length; ++i) temp[i] = str[i];
                for(int i = Length; i<sLength; ++i) temp[i] = c.str[i-Length];
                temp[sLength] = '\0';
                s.str = temp;
                return s;
            }

            bool operator==(const string& s)
            {
                if(len != s.len) return false;
                for(int i = 0; i < len; ++i)
                {
                    if(s[i] != str[i]) return false;
                }
                return true;
            }

            void operator+=(char c)
            {
                *this = *this + c;
                return;
            }

            void operator+=(const string& c)
            {
                *this = *this + c;
                return;
            }

            string& operator=(const string& s)
            {
                if(this == &s) return *this;
                delete [] str;
                str = new char[1+s.len];
                for(int i = 0; i<=s.len; ++i) str[i] = s[i];
                return *this;
            }

            string(const string& s)
            {
                str = new char[1+s.len];
                for(int i = 0; i<=s.len; ++i) str[i] = s[i];
            }

            ~string()
            {
                delete [] str;
            }

            friend std::ostream& operator<<(std::ostream& ost, const string& s)
            {
                ost << s.str;
                return ost;
            }

            friend std::istream& operator>>(std::istream& ist, string& s)
            {
                s.len = 0;
                unsigned int cbl = 20;
                delete [] s.str;
                s.str = new char[1+cbl];
                while(true){
                    char c;
                    ist.get(c);
                    if(c=='\n'){
                        s.str[s.len] = '\0';
                        return ist;
                    }
                    s.str[s.len++] = c;
                    if(s.len>cbl){
                        cbl*=2;
                        char* temp = new char[1+cbl];
                        for(int i = 0; i<s.len; ++i){
                            temp[i] = s.str[i];
                        }
                        delete [] s.str;
                        s.str = temp;
                    }
                }
            }
    };
}

#endif