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
            if(r.size()==0) throw std::exception("invalid denominator");
            while(coef.size()>1)
                if(coef.back().isZero()) coef.pop_back();
                else break;
        }
        Element(): type(nullptr), coef(){}
    public:
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
        Element& operator/=(Element const& r){
            return operator=(div(r).first);
        }
        Element& operator%=(Element const& r){
            return operator=(div(r).second);
        }

        Element operator/(Element const& r)const{
            return div(r).first;
        }
        Element operator%(Element const&)const{
            return div(r).second;
        }
        pair<Element,Element> div(Element d)const{
            /// this(x) = q(x) * d(x) + r(x)
            d.reduce();
            Element r = *this, q;
            q.type = type;
            q.coef.resize(coef.size()-d.coef.size()+1,type->coefType->zero);

            auto lead = d.coef.back();
            for(int i=0;i<d.coef.size();++i) d.coef[i] /= lead;
            for(int i=coef.size()-d.coef.size()-1;i>=0;--i){
                q[i] = coef[i+d.coef.size()];
                for(int j=0;j<d.coef.size();++j)
                    r[i+j] -= c*q[i];
            }
            r.reduce();
            return {q, r};
        }
    };

    FieldPoly::Element one()const{
        Element out;
        out.type = this;
        out.coef.resize(1,coefType->one());
        return out;
    }
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
