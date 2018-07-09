#ifndef __GF_HPP__
#define __GF_HPP__

#include "Karatsuba.hpp"

namespace ECC{

template<typename> class RingPoly;
template<typename> class FieldPoly;
template<typename> class ExtnField;

template<typename Ring>
class RingPoly{
protected:
    Ring const* coefType;
public:
    class Element{
    protected:
        RingPoly const* type;
        vector<typename Ring::Element> coef;
        void reduce(){
            while(coef.size()>1)
                if(coef.back().isZero()) coef.pop_back();
                else break;
        }
    public:
        Element(): type(nullptr), coef(){}
        Element(Element const& r): type(r.type), coef(r.coef){
            if(coef.size()>1 && coef.back().isZero())
                throw std::exception("ring poly not reduced");
        }

        Element& operator+=(Element const& r){
            if(type != r.type) throw std::exception("ring poly += error");
            if(coef.size()<r.coef.size())
                coef.resize(r.coef.size(), type->zero());
            for(int i=0;i<r.coef.size();++i)
                coef[i] += r.coef[i];
            reduce();
            return *this;
        }
        Element& operator-=(Element const& r){
            if(type != r.type) throw std::exception("ring poly -= error");
            if(coef.size()<r.coef.size())
                coef.resize(r.coef.size(), type->zero());
            for(int i=0;i<r.coef.size();++i)
                coef[i] -= r.coef[i];
            reduce();
            return *this;
        }
        Element& operator*=(Element const& r){
            (*this) = (*this) * r;
            reduce();
            return *this;
        }

        Element operator+(Element const& r)const{
            Element out = *this;
            out += r;
            out.reduce();
            return out;
        }
        Element operator-(Element const& r)const{
            Element out = *this;
            out -= r;
            out.reduce();
            return out;
        }
        Element operator*(Element const& r)const{
            if(type != r.type) throw std::exception("ring poly *= error");
            Element out;
            conv(type, coef, r.coef, out.coef);
            out.reduce();
            return out;
        }
        Element& operator=(Element const& r){
            if(type != r.type) throw std::exception("ring poly = error");
            coef = r.coef;
            reduce();
            return *this;
        }
        void swap(Element& r){
            swap(type,r.type);
            coef.swap(r.coef);
        }
        bool isZero()const{
            for(int i=0;i<coef.size();++i)
                if(!coef[i].isZero()) return false;
            return true;
        }
        bool operator==(Element const& r)const{
            if(coef.size()!=r.coef.size()) return false;
            for(int i=0;i<coef.size();++i)
                if(coef[i]!=r.coef[i]) return false;
            return true;
        }
        inline bool operator!=(Element const& r)const{
            return !operator==(r);
        }
    };
    RingPoly(Ring const* coefType): coefType(coefType){}
    RingPoly::Element zero()const{
        RingPoly::Element out;
        out.type = this;
        out.coef.push_back(coefType->zero());
        return out;
    }

};

template<typename Field>
class FieldPoly: public RingPoly<Field>{
public:
    class Element: public RingPoly<Field>::Element{
    public:
        Element operator/=(Element const&);
        Element operator%=(Element const&);

        Element operator/(Element const&)const;
        Element operator%(Element const&)const;
        pair<Element,Element> div(Element const&)const;
    };

    FieldPoly::Element one()const;
};

template<typename Field>
class ExtnField{
protected:
    FieldPoly<Field> irr;
public:
    class Element{
    protected:
        ExtnField const* type;
        FieldPoly<Field> val;
    public:
        Element inv()const;

        Element operator+=(Element const&);
        Element operator-=(Element const&);
        Element operator*=(Element const&);
        Element operator/=(Element const&);

        Element operator+(Element const&)const;
        Element operator-(Element const&)const;
        Element operator*(Element const&)const;
        Element operator/(Element const&)const;
        Element& operator=(Element const&);
    };
    ExtnField::Element zero()const;
    ExtnField::Element one()const;

};

#define ExtnField GF

}

#endif // __GF_HPP__
