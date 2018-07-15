#ifndef __GF_HPP__
#define __GF_HPP__

#include "Karatsuba.hpp"

namespace ECC{

template<typename type>
std::pair<type,type> extGCD(type left, type right){
    if(left.isZero() && right.isZero()) throw std::logic_error("Return value does not exist.\n");
    std::pair<type,type> lCor(1,0), rCor(0,1);
    while(!left.isZero()){
        std::swap(lCor,rCor);
        std::swap(left,right);
        lCor.first -= left/right*rCor.first;
        lCor.second -= left/right*rCor.second;
        left %= right;
    }
    return rCor;
}


template<typename> class RingPoly;
template<typename> class FieldPoly;
template<typename> class ExtnField;

template<typename Ring>
class RingPoly{
protected:
    Ring const* coefType;
public:
    class Element{
        friend RingPoly;
    protected:
        RingPoly const* type;
        vector<typename Ring::Element> coef;
        void reduce(){
            if(coef.size()==0) throw std::exception("invalid denominator");
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

        /// getter method
        inline RingPoly const* getType()const{
            return type;
        }
    };
    RingPoly(Ring const* coefType): coefType(coefType){}
    Element zero()const{
        Element out;
        out.type = this;
        out.coef.push_back(coefType->zero());
        return out;
    }
    /// getter method
    inline Ring const* getCoefType()const{
        return coefType;
    }
};

template<typename Field>
class FieldPoly: public RingPoly<Field>{
public:
    class Element: public RingPoly<Field>::Element{
        friend FieldPoly;
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
        Element operator%(Element const& r)const{
            return div(r).second;
        }
        pair<Element,Element> div(Element d)const{
            /// this(x) = q(x) * d(x) + r(x)
            d.reduce();
            Element r = *this, q;
            q.type = this->type;
            q.coef.resize(this->coef.size()-d.coef.size()+1,this->type->getCoefType()->zero());

            auto lead = d.coef.back();
            for(int i=0;i<d.coef.size();++i) d.coef[i] /= lead;
            for(int i=r.coef.size()-d.coef.size()-1;i>=0;--i){
                q[i] = r.coef[i+d.coef.size()];
                for(int j=0;j<d.coef.size();++j)
                    r[i+j] -= d[j]*q[i];
            }
            r.reduce();
            return {q, r};
        }
    };

    FieldPoly(Field const* coefType): RingPoly<Field>(coefType){}

    Element one()const{
        Element out;
        out.type = this;
        out.coef.resize(1,this->coefType->one());
        return out;
    }
};

template<typename Field>
class ExtnField{
protected:
    typename FieldPoly<Field>::Element irr;
public:
    class Element{
        friend ExtnField;
    protected:
        ExtnField const* type;
        typename FieldPoly<Field>::Element val;
    public:
        Element(Element const& r): type(r.type), val(r.val){}
        Element(ExtnField const* type, typename FieldPoly<Field>::Element const& val):
            type(type), val(val){}

        Element inv()const{
            return extGCD(val,type->getIrr()).first;
        }

        Element& operator+=(Element const& r){
            val += r.val;
            val %= type->getIrr();
            return *this;
        }
        Element& operator-=(Element const& r){
            val -= r.val;
            val %= type->getIrr();
            return *this;
        }
        Element& operator*=(Element const& r){
            val *= r.val;
            val %= type->getIrr();
            return *this;
        }
        Element& operator/=(Element const& r){
            val *= r.inv().val;
            val %= type->getIrr();
            return *this;
        }

        Element operator+(Element const& r)const{
            return val + r.val;
        }
        Element operator-(Element const& r)const{
            return val - r.val;
        }
        Element operator*(Element const& r)const{
            return (val * r.val) % type->irr;
        }
        Element operator/(Element const& r)const{
            return operator*(r.inv());
        }
        Element& operator=(Element const& r){
            type = r.type;
            val = r.val;
            return *this;
        }

        /// getter method
        inline ExtnField const* getType(){
            return type;
        }
    };
    Element zero()const{
        Element out(this, irr->getType()->zero());
        return out;
    }
    Element one()const{
        Element out(this, irr->getType->one());
        return out;
    }

    /// getter method
    inline typename FieldPoly<Field>::Element const& getIrr()const{
        return irr;
    }
};

template<typename Field> using GF = ExtnField<Field>;



}

#endif // __GF_HPP__
