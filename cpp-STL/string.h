/*
* AUTHOR: ASHWIN ABRAHAM
*/
#include <iostream>

class string{
    private:
        static const int bufferlength = 20;
        char* str;
    public:
        string(const char* s = ""){
            int len = 0;
            for(; s[len]!='\0'; ++len);
            str = new char[1+len];
            for(int i = 0; i<len; ++i) str[i] = s[i];
            str[len] = '\0';
        }

        unsigned int length() const{
            int len = 0;
            for(; str[len]!='\0'; ++len);
            return len;
        }

        char& operator[](unsigned int i) const{
            return str[i];
        }

        string operator+(char c) const{
            if(c=='\0') return *this;
            string s;
            delete [] s.str;
            unsigned int Length = this->length();
            char* temp = new char [2+Length];
            for(int i = 0; i<Length; ++i) temp[i] = str[i];
            temp[Length] = c;
            temp[1+Length] = '\0';
            s.str = temp;
            return s;
        }

        string operator+(const string& c) const{
            string s;
            delete [] s.str;
            unsigned int cLength = c.length();
            unsigned Length = this->length();
            unsigned int sLength = cLength + Length;
            char* temp = new char[1+sLength];
            for(int i = 0; i<Length; ++i) temp[i] = str[i];
            for(int i = Length; i<sLength; ++i) temp[i] = c.str[i-Length];
            temp[sLength] = '\0';
            s.str = temp;
            return s;
        }

        bool operator==(const string& s){
            int i = 0;
            for(; s[i]!='\0' && str[i]!='\0'; ++i){
                if(s[i]!=str[i]) return false;
            }
            return s[i]==str[i];
        }

        void operator+=(char c){
            *this = *this + c;
            return;
        }

        void operator+=(const string& c){
            *this = *this + c;
            return;
        }

        string& operator=(const string& s){
            if(*this == s) return *this;
            delete [] str;
            //Length = s.Length;
            unsigned int sLength = s.length();
            str = new char[1+sLength];
            for(int i = 0; i<=sLength; ++i) str[i] = s[i];
            return *this;
        }

        string(const string& s){
            unsigned int slength = s.length();
            str = new char[1+slength];
            for(int i = 0; i<=slength; ++i) str[i] = s[i];
        }

        ~string(){
            delete [] str;
        }

        friend std::ostream& operator<<(std::ostream&, const string&);
        friend std::istream& operator>>(std::istream&, string&);
};

std::ostream& operator<<(std::ostream& ost, const string& s){
    ost << s.str;
    return ost;
}

std::istream& operator>>(std::istream& ist, string& s){
    unsigned int sLength = 0;
    unsigned int cbl = s.bufferlength;
    delete [] s.str;
    s.str = new char[1+cbl];
    while(true){
        char c;
        ist.get(c);
        if(c=='\n'){
            s.str[sLength] = '\0';
            return ist;
        }
        s.str[sLength] = c;
        ++sLength;
        if(sLength>cbl){
            cbl+=s.bufferlength;
            char* temp = new char[1+cbl];
            for(int i = 0; i<sLength; ++i){
                temp[i] = s.str[i];
            }
            delete [] s.str;
            s.str = temp;
        }
    }
}
